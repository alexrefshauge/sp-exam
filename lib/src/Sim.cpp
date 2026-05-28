#include "Vessel.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace stochastic
{
    void Vessel::simulate(double sim_time)
    {
        std::map<std::string, size_t> state = newState();
        const auto reactions = getReactions();
        const auto reaction_count = reactions.size();
        if (reaction_count == 0)
            throw(std::runtime_error("Vessel must have 1 or more reactions for simulation"));

        double t = 0.0;
        while (t < sim_time)
        {
            // Find next reaction and delay
            size_t next_reaction = 0;
            auto min_delay = getReactionDelay(reactions[0]);
            for (size_t i = 1; i < reaction_count; i++)
            {
                auto delay = getReactionDelay(reactions[i]);
                if (delay < min_delay)
                {
                    next_reaction = i;
                    min_delay = delay;
                }
            }
            t += min_delay;

            auto r = reactions[next_reaction];

            if (std::any_of(r.inputs.begin(), r.inputs.end(),
                            [&](std::string s)
                            { return state[s] <= 0; }))
                continue;

            for (auto i : r.inputs)
            {
                state[i]--;
            }
            for (auto i : r.product)
            {
                state[i]++;
            }

            auto i = 0;
            for (const auto &s : state)
            {
                std::cout << s.first << ": " << s.second;
                if (++i < species_table.size())
                    std::cout << " | ";
            }
            std::cout << std::endl;
        }
        return;
    }
    void Vessel::registerObserver(StateObserver &observer)
    {
        observers.push_back(&observer);
    }
} // namespace stochastic
