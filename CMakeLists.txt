cmake_minimum_required(VERSION 3.10)

project(learnBenchmark
        LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -march=native)

add_subdirectory(third_party)

find_package(OpenMP REQUIRED)

set(SOURCES
    src/genString.h
    src/genString.cpp
    src/swar.h
    src/swar.cpp
    src/restrict.h
    src/restrict.cpp
)

add_executable("swarBenchmark" ${SOURCES} src/benchmark.cpp)
target_link_libraries("swarBenchmark" benchmark::benchmark OpenMP::OpenMP_CXX)

add_executable("restrictBenchmark" ${SOURCES} src/restrict_perf.cpp)
target_link_libraries("restrictBenchmark" benchmark::benchmark)

enable_testing()

add_executable("swarTest" ${SOURCES} src/test.cpp)
target_link_libraries("swarTest" gtest gtest_main OpenMP::OpenMP_CXX)
