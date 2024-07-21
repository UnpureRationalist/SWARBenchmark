#include "restrict.h"

#include <benchmark/benchmark.h>
#include <cstdlib>
#include <vector>

constexpr int n = 1 << 20;

std::vector<int> a, b, c;

void initVector() {
  a.resize(n);
  b.resize(n);
  c.resize(n);
  for (int i = 0; i < n; ++i) {
    a[i] = std::rand();
    b[i] = std::rand();
  }
}

static void BM_Add1(benchmark::State &state) {
  for (auto _ : state) {
    add1(n, a.data(), b.data(), c.data());
  }
}
BENCHMARK(BM_Add1);

static void BM_Add2(benchmark::State &state) {
  for (auto _ : state) {
    add2(n, a.data(), b.data(), c.data());
  }
}
BENCHMARK(BM_Add2);

static void BM_Add3(benchmark::State &state) {
  for (auto _ : state) {
    add3(n, a.data(), b.data(), c.data());
  }
}
BENCHMARK(BM_Add3);

int main(int argc, char **argv) {
  initVector();

  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
  ::benchmark::Shutdown();

  return 0;
}
