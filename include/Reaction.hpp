#include <cstddef>
#include <memory>

namespace stochastic
{
    struct ReactionSide
    {
        size_t species_id;
        std::weak_ptr<size_t> catalyst;
    };

    struct Reaction
    {
        size_t consume_id;
        double rate;
        size_t produce_id;
    };

    struct ReactionProducer
    {
        size_t consume_id;
        double rate;
    };

    inline ReactionProducer operator>>(ReactionSide lhs, double rate)
    {
        return {lhs.species_id, rate};
    }

    inline Reaction operator>>=(ReactionProducer p, ReactionSide rhs)
    {
        return {p.consume_id, p.rate, rhs.species_id};
    }
} // namespace stochastic
