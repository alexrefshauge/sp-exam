#ifndef STOCHASTIC_REACTION_HPP
#define STOCHASTIC_REACTION_HPP

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include <utility>

namespace stochastic
{
    struct ReactionSide : std::vector<std::string>
    {
        using std::vector<std::string>::vector;
    };

    struct VesselVisitor; // Forward declaration for Reaction::accept
    struct Reaction
    {
        ReactionSide inputs;
        double rate;
        ReactionSide product;

        void accept(VesselVisitor &v);
    };

    struct ReactionProducer
    {
        ReactionSide inputs;
        double rate;
    };

    inline ReactionProducer operator>>(ReactionSide lhs, double rate)
    {
        return {lhs, rate};
    }

    inline Reaction operator>>=(ReactionProducer p, ReactionSide rhs)
    {
        return {p.inputs, p.rate, rhs};
    }

    struct Species
    {
        std::string label;
        size_t count0;

        Species(std::string _label, size_t _count0) : label(std::move(_label)), count0(_count0) {}

        operator ReactionSide() const
        {
            return {label};
        }

        ReactionSide operator+(const Species &rhs) const
        {
            ReactionSide lhs{label};
            lhs.push_back(rhs.label);
            return lhs;
        }

        void accept(VesselVisitor &v);
    };

    struct VesselVisitor
    {
        virtual void visit(const Reaction *r) = 0;
        virtual void visit(const Species *s) = 0;
    };

    inline void Reaction::accept(VesselVisitor &v) { v.visit(this); }
    inline void Species::accept(VesselVisitor &v) { v.visit(this); }
} // namespace stochastic

#endif
