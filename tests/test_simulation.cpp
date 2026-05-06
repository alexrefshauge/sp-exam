//
// Created by sande on 03/05/2026.
//
#include <doctest/doctest.h>
#include "Vessel.hpp"

TEST_CASE("simple vessel")
{
    auto v = stochastic::Vessel("Simple");
    auto A = v.add("A", 100);
    auto B = v.add("B", 100);
    v.add(A >> 0.5 >>= B);
}
