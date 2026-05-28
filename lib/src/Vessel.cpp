#include <assert.h>
#include <random>
#include <iostream>
#include <map>

#include "Vessel.hpp"
namespace stochastic
{
    Vessel::Vessel(std::string name) : vessel_name(std::move(name))
    {
        std::random_device rd;
        generator = std::mt19937(rd());
    }

    Species Vessel::add(std::string label, int count0)
    {
        Species s(label, count0);
        species_table.store(label, s);
        return s;
    }

    void Vessel::add(stochastic::Reaction reaction)
    {
        reactions.push_back(reaction);
    }

    double Vessel::getReactionDelay(const Reaction &r)
    {
        std::exponential_distribution<double> distribution(r.rate);
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
        for (auto r : reactions)
        {
            r.accept(v);
        }

        for (auto species_kv : species_table)
        {
            species_kv.second.accept(v);
        }
    }

} // namespace sim
