#include <string>
#include <unordered_map>


namespace Sim {

    struct SpeciesState {
        size_t cound;
        std::string label;
    };

    class Vessel
    {
    private:
        std::unordered_map<size_t, SpeciesState> state {};

    public:
        Vessel();
        ~Vessel();
    };
    
    Vessel::Vessel(/* args */)
    {
    }
    
    Vessel::~Vessel()
    {
    }
    
};