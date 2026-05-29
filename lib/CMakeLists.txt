cmake_minimum_required(VERSION 3.5...4.3.1)

project(stochastic_simlib LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LIB
add_library(stochastic
    src/Vessel.cpp
    src/Sim.cpp
    src/SimMulti.cpp
    src/SimPool.cpp
)

target_include_directories(stochastic PUBLIC src include)

add_library(stochastic_models
    example_models.cpp
)

target_link_libraries(stochastic_models PUBLIC stochastic)
target_include_directories(stochastic_models PUBLIC include)


find_package(doctest REQUIRED)
find_package(benchmark REQUIRED)

# TESTS
add_executable(tests
    tests/test_main.cpp
    tests/test_vessel.cpp
    tests/test_reaction.cpp
    tests/test_symbolTable.cpp
    tests/test_simulation.cpp
    tests/test_pool.cpp
)

add_executable(bench
    bench/bench_main.cpp
    bench/bench_sim.cpp
)

target_link_libraries(tests PRIVATE stochastic stochastic_models doctest::doctest)
target_link_libraries(bench PRIVATE stochastic stochastic_models benchmark::benchmark)
