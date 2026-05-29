#include <doctest/doctest.h>
#include "Sim.hpp"
#include "Vessel.hpp"
#include <iostream>

TEST_SUITE("Sim pool tests")
{
    TEST_CASE("Sim pool joins and terminates")
    {
        std::mutex lock{};
        int count = 0;

        stochastic::SimPool pool{};
        pool.repeat_job(10, [&](int i)
                        { lock.lock(); std::this_thread::sleep_for(std::chrono::milliseconds(10*i)); count++; lock.unlock(); });
    }

    TEST_CASE("Sim pool with ABC model")
    {
        auto rate = 0.001;
        auto v = stochastic::Vessel("A + C -> B + C");

        auto A = v.add("A", 100);
        auto B = v.add("B", 0);
        auto C = v.add("C", 1);

        v.add(A + C >> rate >>= B + C);

        v.simulate_multi(10000, 42, 100);
    }
}