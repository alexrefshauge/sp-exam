#include <iostream>
#include "example_models.hpp"

int main()
{
    auto v = seihr(10000);
    stochastic::SimPool p{};
    v.simulate_multi(100, 42, 100);
}
