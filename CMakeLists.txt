cmake_minimum_required(VERSION 3.5...4.3.1)

project(stochastic_simlib LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(doctest REQUIRED)

add_library(stochastic src/Vessel.cpp src/Reaction.cpp)

target_include_directories(stochastic PUBLIC src include)



add_executable(tests tests/test_main.cpp tests/test_simulation.cpp tests/test_reactions.cpp)
target_link_libraries(tests PRIVATE stochastic doctest::doctest)
