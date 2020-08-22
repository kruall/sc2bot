#include <core/actors/atomic_forward_list.h>

#include <gtest/gtest.h>


using namespace core::actors;

using IntQueue = AtomicQueue<int>;

constexpr int number = 42;

TEST(QueuePushPop, Add) {
    IntQueue q;
    auto h = std::make_unique<IntQueue::node_type>(number);
    q.push(std::move(h));
    h = q.pop();
    EXPECT_EQ(h->Get(), number);
}

TEST(QueuePush2, Add) {
    IntQueue q;
    for (uint64_t i = 0; i < 2; ++i) {
        q.push(std::make_unique<IntQueue::node_type>(number + i));
    }
}

TEST(QueuePop2, Add) {
    IntQueue q;
    for (uint64_t i = 0; i < 2; ++i) {
        EXPECT_EQ(q.pop().get(), nullptr);
    }
}

