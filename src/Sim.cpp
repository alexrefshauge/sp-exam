#include "Sim.hpp"

namespace stochastic
{
    void simulate(Vessel v, double sim_time)
    {
        const auto reactions = v.getReactions();
        const auto reaction_count = reactions.size();
        if (reaction_count == 0)
            throw(std::runtime_error("Vessel must have 1 or more reactions for simulation"));

        double t = 0.0;
        while (t < sim_time)
        {
            // Find next reaction and delay
            size_t next_reaction = 0;
            auto min_delay = v.getReactionDelay(reactions[0]);
            for (size_t i = 1; i < reaction_count; i++)
            {
                auto delay = v.getReactionDelay(reactions[0]);
                if (delay < min_delay)
                {
                    next_reaction = i;
                    min_delay = delay;
                }
            }

            // Resolve reaction
            t += min_delay;
            // TODO: change producer to reaction.inputs (instead of producer_id)
        }
        return;
    }
} // namespace stochastic
