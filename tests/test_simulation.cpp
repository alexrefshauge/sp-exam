//
// Created by sande on 03/05/2026.
//
#include <doctest/doctest.h>
#include "Vessel.hpp"
#include "Sim.hpp"

TEST_SUITE("Simulation tests")
{
    TEST_CASE("Simple vessel builds and simulates")
    {
        auto v = stochastic::Vessel("Simple");
        auto A = v.add("A", 100);
        auto B = v.add("B", 100);
        v.add(A >> 0.5 >>= B);
        stochastic::simulate(v, 100);
    }

    TEST_CASE("Empty vessel fails")
    {
        auto v = stochastic::Vessel("Simple");
        CHECK_THROWS(stochastic::simulate(v, 42));
    }
}