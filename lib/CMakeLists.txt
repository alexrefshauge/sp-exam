cmake_minimum_required(VERSION 3.5...4.3.1)

project(stochastic_simlib LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(STOCHASTIC_SIMLIB_BUILD_TESTS "Build stochastic_simlib tests" ON)
else()
    option(STOCHASTIC_SIMLIB_BUILD_TESTS "Build stochastic_simlib tests" OFF)
endif()

# LIB
add_library(stochastic
    src/Vessel.cpp
    src/Sim.cpp
    src/SimMulti.cpp
    src/SimPool.cpp
)

target_include_directories(stochastic PUBLIC src include)


if(STOCHASTIC_SIMLIB_BUILD_TESTS)
    find_package(doctest REQUIRED)

    # TESTS
    add_executable(tests
        tests/test_main.cpp
        tests/test_vessel.cpp
        tests/test_reaction.cpp
        tests/test_symbolTable.cpp
        tests/test_simulation.cpp
        tests/test_pool.cpp
    )

    target_link_libraries(tests PRIVATE stochastic doctest::doctest)
endif()
