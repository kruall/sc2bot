#pragma once

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

}
