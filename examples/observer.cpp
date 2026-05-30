#include <map>
#include <Vessel.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include "example_models.hpp"

struct HospitalizationObserver : stochastic::StateObserver
{
    size_t h_peak = 0;

    void observe(const int seed, const double t, const stochastic::VesselState &s) override
    {
        auto h = s.at("H");
        h_peak = std::max(h, h_peak);
    }
};

int main()
{
    auto observer = std::make_shared<HospitalizationObserver>();
    auto model_nj = seihr(N_NJ);
    auto model_dk = seihr(N_DK);
    model_nj.registerObserver(observer);
    model_dk.registerObserver(observer);

    // Simulate Nordjylland
    model_nj.simulate(100);
    std::cout << "peak hospitalization (N_NJ): " << observer->h_peak << std::endl;

    observer->h_peak = 0;

    // Simulate Denmark
    model_dk.simulate(100);
    std::cout << "peak hospitalization (N_DK): " << observer->h_peak << std::endl;

    return 0;
}
