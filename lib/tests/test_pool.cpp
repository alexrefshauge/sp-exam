#include <doctest/doctest.h>
#include "Sim.hpp"

TEST_SUITE("Sim pool tests")
{
    TEST_CASE("Sim pool joins and terminates")
    {
        stochastic::SimPool{};
    }
}