#include <assert.h>
#include <random>
#include <iostream>
#include <map>
#include <algorithm>

#include "Vessel.hpp"

namespace stochastic
{
    const std::string ENV_LABEL = "_ENV";
    Vessel::Vessel(std::string name) : vessel_name(std::move(name))
    {
    }

    Species Vessel::add(std::string label, int count0)
    {
        if (label == ENV_LABEL)
            throw std::runtime_error("This species symbol is reserved for environment");
        Species s(label, count0);
        species_table.store(label, s);
        return s;
    }

    void Vessel::add(stochastic::Reaction reaction)
    {
        reactions.push_back(reaction);
    }

    Species Vessel::environment()
    {
        Species env(ENV_LABEL, 0);
        species_table.store(ENV_LABEL, env);
        return env;
    }

    SimReaction Reaction::toSimReaction() const
    {
        SimReaction sim_reaction{};
        sim_reaction.inputs = inputs;
        sim_reaction.rate = rate;
        sim_reaction.product = product;

        for (const auto &reactant : inputs)
        {
            sim_reaction.input_reactant_count[reactant]++;
        }

        return sim_reaction;
    }

    const std::vector<SimReaction> Vessel::getReactions() const
    {
        std::vector<SimReaction> sim_reactions;
        for (auto &r : reactions)
            sim_reactions.push_back(r.toSimReaction());
        return sim_reactions;
    }

    double Vessel::getReactionDelay(const SimReaction &r, const VesselState &s, std::mt19937 &generator) const
    {
        auto inputProduct = 1.0;
        for (const auto &reactant_count : r.input_reactant_count)
        {
            const auto &reactant = reactant_count.first;
            const auto required_count = reactant_count.second;
            const auto state_it = s.find(reactant);
            if (state_it == s.end() || state_it->second < static_cast<std::size_t>(required_count))
                return INFINITY;

            // Preserve multiplicity semantics from r.inputs with repeated multiplication.
            for (int i = 0; i < required_count; i++)
                inputProduct *= static_cast<double>(state_it->second);
        }
        std::exponential_distribution<double> distribution(r.rate * inputProduct);
        return distribution(generator);
    }

    VesselState Vessel::newState() const
    {
        VesselState state{};
        for (auto kv : species_table)
        {
            auto species = kv.second;
            state[species.label] = species.count0;
        }

        return state;
    }

    void Vessel::accept(VesselVisitor &v) const
    {
        v.visit(*this);
        for (auto r : reactions)
        {
            r.accept(v);
        }

        for (auto species_kv : species_table)
        {
            species_kv.second.accept(v);
        }
    }

    std::string Vessel::getName() const
    {
        return vessel_name;
    }

} // namespace sim
