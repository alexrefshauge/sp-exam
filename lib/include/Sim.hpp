#ifndef STOCHASTIC_SIM_HPP
#define STOCHASTIC_SIM_HPP

#include <cstddef>
#include <map>
#include <string>

namespace stochastic
{
    using VesselState = std::map<std::string, std::size_t>;

    struct StateObserver
    {
        virtual ~StateObserver() = default;
        virtual void observe(const VesselState &s) = 0;
    };
}

#endif