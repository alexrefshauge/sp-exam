#include "Vessel.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace stochastic
{
    void Vessel::simulate(double sim_time) const
    {
        std::random_device rd;
        int seed = rd();
        simulate(sim_time, seed);
    }

    void Vessel::simulate(double sim_time, int seed) const
    {
        std::map<std::string, size_t> state = newState();
        const auto reactions = getReactions();
        const auto sim_observers = observers;
        const auto reaction_count = reactions.size();
        if (reaction_count == 0)
            throw(std::runtime_error("Vessel must have 1 or more reactions for simulation"));

        std::mt19937 generator(seed);

        double t = 0.0;
        while (t < sim_time)
        {
            // Find next reaction and delay
            size_t next_reaction = 0;
            auto min_delay = getReactionDelay(reactions[0], state, generator);
            for (size_t i = 1; i < reaction_count; i++)
            {
                auto delay = getReactionDelay(reactions[i], state, generator);
                if (delay < min_delay)
                {
                    next_reaction = i;
                    min_delay = delay;
                }
            }
            t += min_delay;

            auto r = reactions[next_reaction];

            if (min_delay == INFINITY)
                continue;

            for (auto i : r.inputs)
                state[i]--;

            for (auto i : r.product)
                state[i]++;

            for (auto o : sim_observers)
                o->observe(t, state);
        }
        return;
    }

    void Vessel::registerObserver(std::shared_ptr<StateObserver> observer)
    {
        observers.push_back(observer);
    }
} // namespace stochastic
