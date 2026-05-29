#include <benchmark/benchmark.h>
#include "Vessel.hpp"
#include "example_models.hpp"

void single_thread_simulation(benchmark::State &state)
{
    auto v = circadian();
    for (auto _ : state)
    {
        for (auto i = 0; i < 100; i++)
        {
            v.simulate(48, 42);
        }
    }
}
BENCHMARK(single_thread_simulation)->ThreadRange(12, 12);

void multi_thread_simulation(benchmark::State &state)
{
    auto v = circadian();
    for (auto _ : state)
    {
        v.simulate_multi(48, 42, 20);
    }
}
BENCHMARK(single_thread_simulation)->ThreadRange(12, 12);