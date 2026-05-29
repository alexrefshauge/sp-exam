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

    double Vessel::getReactionDelay(const Reaction &r, VesselState &s, std::mt19937 &generator) const
    {
        auto inputProduct = 1.0;
        for (auto i : r.inputs)
            inputProduct *= s[i];
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
