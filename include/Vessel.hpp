#include <string>
#include <unordered_map>

namespace sim
{

  struct SpeciesState
  {
    size_t count;
    std::string label;
  };
  SpeciesState newSpecies(size_t, std::string);

  struct Rule
  {
    int consume;
    double rate;
    int produce;
  };

  class Vessel
  {
  private:
    std::string vessel_name;
    std::unordered_map<size_t, SpeciesState> state{};

  public:
    Vessel(std::string);
    ~Vessel();

    size_t add(std::string, int);
    void environment();
  };
}; // namespace sim
