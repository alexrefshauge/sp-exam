#include <assert.h>
#include <random>
#include <iostream>
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
        auto id = ++id_counter;
        species_table.emplace(label, id);
        state.push_back(count0);
        assert(state.size() == species_table.size());

        return {id, label};
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
} // namespace sim
