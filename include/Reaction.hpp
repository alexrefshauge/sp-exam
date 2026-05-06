#ifndef STOCHASTIC_REACTION_HPP
#define STOCHASTIC_REACTION_HPP

#include <cstddef>
#include <memory>
#include <vector>
#include <utility>

namespace stochastic
{
    struct ReactionSide
    {
        std::vector<size_t> species_ids;
    };

    struct Reaction
    {
        std::vector<size_t> inputs;
        double rate;
        std::vector<size_t> outputs;
    };

    struct ReactionProducer
    {
        std::vector<size_t> inputs;
        double rate;
    };

    inline ReactionProducer operator>>(ReactionSide lhs, double rate)
    {
        return {lhs.species_ids, rate};
    }

    inline Reaction operator>>=(ReactionProducer p, ReactionSide rhs)
    {
        return {p.inputs, p.rate, rhs.species_ids};
    }
} // namespace stochastic

#endif