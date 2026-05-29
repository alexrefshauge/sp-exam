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

    std::vector<std::shared_ptr<StateObserver>> observers;

  public:
    Vessel(std::string);
    ~Vessel() = default;

    std::string getName() const;

    Species add(std::string, int); // Add species with initial count
    void add(Reaction);            // Add reaction
    Species environment();         // Add and return the environment species "_ENV"

    double getReactionDelay(const Reaction &r, VesselState &s, std::mt19937 &generator) const;
    const std::vector<Reaction> getReactions() const
    {
      return reactions;
    };

    VesselState newState() const;

    void simulate(double sim_time) const;
    void simulate(double sim_time, int seed) const;

    void simulate_multi(double sim_time, int start_seed, int sim_count) const;

    void registerObserver(std::shared_ptr<StateObserver> observer);
    void accept(VesselVisitor &v) const;
  };

  struct VesselVisitor
  {
    virtual void visit(const Reaction &r) = 0;
    virtual void visit(const Species &s) = 0;
    virtual void visit(const Vessel &v) = 0;
  };

  inline void Reaction::accept(VesselVisitor &v) { v.visit(*this); }
  inline void Species::accept(VesselVisitor &v) { v.visit(*this); }
}; // namespace sim

#endif
