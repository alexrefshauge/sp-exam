#include "Vessel.hpp"
#include <iostream>

namespace stochastic
{
    void Vessel::simulate_multi(double sim_time, int start_seed, int sim_count) const
    {
        if (observers.size() > 0)
            throw std::runtime_error("Concurrent simulations with observers are not supported yet");

        SimPool pool{};
        pool.repeat_job(sim_count, [&](int job_index)
                        { simulate(sim_time, start_seed + job_index); });
    }
}