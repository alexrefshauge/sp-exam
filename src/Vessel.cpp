#include "Vessel.hpp"
namespace sim
{
    Vessel::Vessel(std::string name) : vessel_name(name) {}

    SpeciesState newSpecies(size_t count, std::string label)
    {
        return SpeciesState{count, label};
    }

    size_t Vessel::add(std::string label, int count0) {
        auto s = newSpecies(count0, label);
        state[0] = s;
        return 0;
    }
} // namespace sim
