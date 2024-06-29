#include "genString.h"
#include "swar.h"

#include "gtest/gtest.h"

#include <benchmark/benchmark.h>
#include <string>
#include <vector>

std::vector<std::string> inputStrings;

void inputInit() {
  int numStr = 1000;
  int strLen = 10000;
  inputStrings.reserve(numStr);
  for (int i = 0; i < numStr; ++i) {
    inputStrings.emplace_back(generateRandomString(strLen));
  }
}

static void BM_RedisPopcount(benchmark::State &state) {
  for (auto _ : state) {
    for (const std::string &str : inputStrings) {
      redisPopcount((void *)str.c_str(), str.size());
    }
  }
}
BENCHMARK(BM_RedisPopcount);

static void BM_BasicPopCount(benchmark::State &state) {
  for (auto _ : state) {
    for (const std::string &str : inputStrings) {
      basicPopcount((const unsigned char *)str.c_str(), str.size());
    }
  }
}
BENCHMARK(BM_BasicPopCount);

static void BM_BitAndPopCount(benchmark::State &state) {
  for (auto _ : state) {
    for (const std::string &str : inputStrings) {
      bitAndPopcount((const unsigned char *)str.c_str(), str.size());
    }
  }
}
BENCHMARK(BM_BitAndPopCount);

static void BM_GccBuiltinPopCount(benchmark::State &state) {
  for (auto _ : state) {
    for (const std::string &str : inputStrings) {
      gccBuildinPopCount((const unsigned char *)str.c_str(), str.size());
    }
  }
}
BENCHMARK(BM_GccBuiltinPopCount);

static void BM_OpenmpBasicPopCount(benchmark::State &state) {
  for (auto _ : state) {
    for (const std::string &str : inputStrings) {
      openmpBasicPopCount((const unsigned char *)str.c_str(), str.size());
    }
  }
}
BENCHMARK(BM_OpenmpBasicPopCount);

int main(int argc, char **argv) {
  inputInit();

  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
  ::benchmark::Shutdown();
  return 0;
}
