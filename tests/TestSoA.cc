#include <benchmark/benchmark.h>
#include <vector>

// Benchmark function
static void BM_VectorPushBack(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<int> v;
    for (int i = 0; i < state.range(0); ++i)
      v.push_back(i);
  }
}
BENCHMARK(BM_VectorPushBack)->Range(8, 8<<10);

BENCHMARK_MAIN();