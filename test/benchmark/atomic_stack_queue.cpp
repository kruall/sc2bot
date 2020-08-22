#include <core/actors/atomic_forward_list.h>

#include <benchmark/benchmark.h>

#include <queue>
#include <stack>
#include <vector>
#include <memory>


using namespace core::actors;

struct A{};
using AQueue = AtomicQueue<A>;
using AStack = AtomicStack<A>;

AQueue aq;
AStack as;


std::queue<std::unique_ptr<AQueue::node_type>> q;
std::atomic_flag fq;
std::stack<std::unique_ptr<AQueue::node_type>> s;
std::atomic_flag fs;
std::vector<std::unique_ptr<AQueue::node_type>> v;
std::atomic_flag fv;

void lock(std::atomic_flag &a) {
    while (a.test_and_set())
    {}
}

void unlock(std::atomic_flag &a) {
    a.clear();
}

static void QueueBrench(benchmark::State& state) {
    // Code inside this loop is measured repeatedly
    auto n = std::make_unique<AQueue::node_type>();
    for (auto _ : state) {
        aq.push(std::move(n));
        benchmark::DoNotOptimize(n);
        n = aq.pop();
        benchmark::DoNotOptimize(n);
    }
}
// Register the function as a benchmark
BENCHMARK(QueueBrench)->Threads(2)->Threads(8);

static void StdQueueBrench(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
    auto n = std::make_unique<AQueue::node_type>();
    for (auto _ : state) {
        lock(fq);
        q.push(std::move(n));
        benchmark::DoNotOptimize(n);
        n = std::move(q.front());
        benchmark::DoNotOptimize(n);
        q.pop();
        unlock(fq);
    }
}
// Register the function as a benchmark
BENCHMARK(StdQueueBrench)->Threads(2)->Threads(8);

static void StackBrench(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  auto n = std::make_unique<AStack::node_type>();
  for (auto _ : state) {
        as.push(std::move(n));
        benchmark::DoNotOptimize(n);
        n = as.pop();
        benchmark::DoNotOptimize(n);
  }
}
// Register the function as a benchmark
BENCHMARK(StackBrench)->Threads(2)->Threads(8);

static void StdStackBrench(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
    auto n = std::make_unique<AQueue::node_type>();
    for (auto _ : state) {
        lock(fs);
        s.push(std::move(n));
        benchmark::DoNotOptimize(n);
        n = std::move(s.top());
        benchmark::DoNotOptimize(n);
        s.pop();
        unlock(fs);
    }
}
// Register the function as a benchmark
BENCHMARK(StdStackBrench)->Threads(2)->Threads(8);

static void StdVectorBrench(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  auto n = std::make_unique<AQueue::node_type>();
  for (auto _ : state) {
    lock(fv);
    v.push_back(std::move(n));
    benchmark::DoNotOptimize(n);
    n = std::move(v.back());
    benchmark::DoNotOptimize(n);
    v.pop_back();
    unlock(fv);
  }
}
// Register the function as a benchmark
BENCHMARK(StdVectorBrench)->Threads(2)->Threads(8);


BENCHMARK_MAIN();
