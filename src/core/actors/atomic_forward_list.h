#pragma once

#include <value_holder_node.h>

#include <atomic>
#include <memory>


namespace core::actors {

    template <typename Derived>
    struct ForwardListNode {
        using self_type = ForwardListNode;
        using derived_type = Derived;


        ForwardListNode() = default;
        ForwardListNode(const self_type&) = delete;
        ForwardListNode(self_type&) = delete;

        virtual ~ForwardListNode() = default;

        std::unique_ptr<derived_type> Detach() {
            return std::move(Next);
        }

        void Attach(std::unique_ptr<derived_type> &&node) {
            Next = std::move(node);
        }

    protected:
        std::unique_ptr<derived_type> Next = nullptr;
    };

    template <typename T>
    struct ValueHolder {
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;


        template <typename ...Args>
        ValueHolder(Args ...args)
            : Value(args...)
        {}

        reference operator->() {
            return Value;
        }

        const_reference operator->() const {
            return Value;
        }

        reference Get() {
            return Value;
        }

        const_reference Get() const {
            return Value;
        } 

    protected:
        value_type Value;
    };

    template <typename T>
    struct ValueHolderNode : ForwardListNode<ValueHolderNode<T>>, ValueHolder<T> {
        using value_type = T;
        using value_holder_type = ValueHolder<value_type>;
        using self_type = ValueHolderNode<value_type>;
        using base_node_type = ForwardListNode<self_type>;
        using typename value_holder_type::reference;
        using typename value_holder_type::const_reference;


        template <typename ...Args>
        ValueHolderNode(Args ...args)
            : value_holder_type(args...)
        {}
    };

    template <typename Node, typename Interface>
    struct AtomicForwardListBase {
        using interface_type = Interface;
        using node_type = Node; 
        using value_type = typename node_type::value_type;
        using reference = typename node_type::reference;
        using const_reference = typename node_type::const_reference;
        using self_type = AtomicForwardListBase<node_type, interface_type>;

        enum class EState {
            None,
            Push,
            Pop
        };


        AtomicForwardListBase()
            : Head(nullptr)
            , Tail(nullptr)
            , State(EState::None)
        {}

        void push(std::unique_ptr<node_type> &&node) {
            interface_type::push(State, Head, Tail, std::move(node));
        }

        std::unique_ptr<node_type> pop() {
            return interface_type::pop(State, Head, Tail);
        }

    protected:
        std::atomic<node_type*> Head;
        std::atomic<node_type*> Tail;
        std::atomic<EState> State = EState::None;
    };

    template <typename T>
    struct AtomicQueueInterface {
        using node_type = ValueHolderNode<T>;
        using self_type = AtomicQueueInterface<T>;
        using container_type = AtomicForwardListBase<node_type, self_type>;
        using state_type = typename container_type::EState;

        using atomic_state_type = std::atomic<state_type>;
        using atomic_node_pointer_type = std::atomic<node_type*>;


        static void push(
                atomic_state_type &state,
                atomic_node_pointer_type &head,
                atomic_node_pointer_type &tail,
                std::unique_ptr<node_type> &&node)
        {
            state_type expected_state;
            do {
                expected_state = state_type::None;
            } while (not state.compare_exchange_weak(expected_state, container_type::EState::Push));
            
            if (auto current_tail = tail.load()) {
                tail.store(node.get());
                current_tail->Attach(std::move(node));
            } else {
                tail.store(node.get());
                head.store(node.release());
            }

            state.store(container_type::EState::None);
        }

        static std::unique_ptr<node_type> pop(
                atomic_state_type &state,
                atomic_node_pointer_type &head,
                atomic_node_pointer_type &tail)
        {
            state_type expected_state;
            do {
                expected_state = state_type::None;
            } while (not state.compare_exchange_weak(expected_state, container_type::EState::Pop));
        
            node_type *current_head = head.load();
            if (current_head) {
                if (auto next = current_head->Detach()) {
                    head.store(next.release());
                } else {
                    head.store(nullptr);
                    tail.store(nullptr);
                }
            }

            return std::unique_ptr<node_type>(current_head);
        }
    };

    template <typename T>
    struct AtomicStackInterface {
        using node_type = ValueHolderNode<T>;
        using self_type = AtomicQueueInterface<T>;
        using container_type = AtomicForwardListBase<node_type, self_type>;
        using state_type = typename container_type::EState;

        using atomic_state_type = std::atomic<state_type>;
        using atomic_node_pointer_type = std::atomic<node_type*>;


        static void push(
                atomic_state_type &state,
                atomic_node_pointer_type &head,
                atomic_node_pointer_type &tail,
                std::unique_ptr<node_type> &&node)
        {
            state_type expected_state;
            do {
                expected_state = state_type::None;
            } while (not state.compare_exchange_weak(expected_state, container_type::EState::Push));
            
            if (auto current_head = head.load()) {
                head.store(node.get());
                current_head->Attach(std::move(node));
            } else {
                head.store(node.release());
            }

            state.store(container_type::EState::None);
        }

        static std::unique_ptr<node_type> pop(
                atomic_state_type &state,
                atomic_node_pointer_type &head,
                atomic_node_pointer_type &tail)
        {
            state_type expected_state;
            do {
                expected_state = state_type::None;
            } while (not state.compare_exchange_weak(expected_state, container_type::EState::Pop));
        
            node_type *current_head = head.load();
            if (current_head) {
                auto next = current_head->Detach();
                head.store(next.release());
            }

            return std::unique_ptr<node_type>(current_head);
        }
    };

    template <typename T>
    using AtomicQueue = typename AtomicQueueInterface<T>::container_type;

    template <typename T>
    using AtomicStack = typename AtomicStackInterface<T>::container_type;

}