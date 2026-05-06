#ifndef STOCHASTIC_VESSEL_HPP
#define STOCHASTIC_VESSEL_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <random>
#include "Reaction.hpp"

namespace stochastic
{

  struct Species
  {
    size_t id;
    std::string label;

    operator ReactionSide() const
    {
      std::vector<size_t> species{id};
      return {species};
    }
  };

  class Vessel
  {
  private:
    size_t id_counter = 0;
    std::string vessel_name;
    std::unordered_map<std::string, size_t> species_table{};
    std::vector<size_t> state{};
    std::vector<Reaction> reactions{};

    std::mt19937 generator;

  public:
    Vessel(std::string);
    ~Vessel() = default;

    Species add(std::string, int); // Add species with initial count
    void add(Reaction);            // Add reaction
    void environment();

    double getReactionDelay(const Reaction &r);
    const std::vector<Reaction> getReactions()
    {
      return reactions;
    };
  };
}; // namespace sim

#endif