#include <doctest/doctest.h>
#include "Sim.hpp"
#include <iostream>

TEST_SUITE("Sim pool tests")
{
    TEST_CASE("Sim pool joins and terminates")
    {
        stochastic::SimPool pool{};
        pool.repeatJob(100, [&](int i)
                       { std::cout << "done " << i << std::endl; });
    }
}