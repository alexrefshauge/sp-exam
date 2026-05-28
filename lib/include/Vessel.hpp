#ifndef STOCHASTIC_VESSEL_HPP
#define STOCHASTIC_VESSEL_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <random>
#include <map>

#include "Reaction.hpp"
#include "SymbolTable.hpp"
#include "Sim.hpp"

namespace stochastic
{


  class Vessel
  {
  private:
    std::string vessel_name;
    // map species name to state (count)
    SymbolTable<std::string, Species> species_table{};
    std::vector<Reaction> reactions{};

    std::mt19937 generator;

    std::vector<StateObserver *> observers;

  public:
    Vessel(std::string);
    ~Vessel() = default;

    void accept(VesselVisitor &v) const;

    Species add(std::string, int); // Add species with initial count
    void add(Reaction);            // Add reaction
    void environment();

    double getReactionDelay(const Reaction &r);
    const std::vector<Reaction> getReactions()
    {
      return reactions;
    };

    VesselState newState() const;

    void simulate(double sim_time);

    void registerObserver(StateObserver &observer);
  };
}; // namespace sim

#endif
