#include <iostream>
#include "example_models.hpp"

#define SIM_COUNT 100
#define START_SEED 42

struct HospitalizationAveragePeakObserver : stochastic::StateObserver
{
    std::map<int, size_t> seed_peaks;
    HospitalizationAveragePeakObserver() : seed_peaks()
    {
        for (auto s = START_SEED; s < START_SEED + SIM_COUNT; s++)
        {
            seed_peaks[s] = 0;
        }
    }

    void observe(const int seed, const double t, const stochastic::VesselState &s) override
    {
        auto &peak = seed_peaks[seed];
        const auto h = s.at("H");
        peak = std::max(h, peak);
    }
};

int main()
{
    auto o = std::make_shared<HospitalizationAveragePeakObserver>();
    auto v = seihr(10000);
    v.registerObserver(o);
    stochastic::SimPool p{};
    v.simulate_multi(100.0, START_SEED, SIM_COUNT);

    auto acc = 0;
    for (auto &seed_peak_pair : (*o).seed_peaks)
    {
        std::cout << seed_peak_pair.first << ": " << seed_peak_pair.second << std::endl;
        acc += seed_peak_pair.second;
    }

    std::cout << "average" << ": " << double(acc) / double(SIM_COUNT) << std::endl;
}
