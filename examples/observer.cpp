#include <map>
#include <Vessel.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include "models.cpp"

const auto N_DK = 5822763;
const auto N_NJ = 589755;

const std::string outHeader = "t,s,e,i,h,r\n";

struct HospitalizationObserver : stochastic::StateObserver
{
    size_t h_peak = 0;

    void observe(const double t, const VesselState &s) override
    {
        auto h = s.at("H");
        h_peak = std::max(h, h_peak);
    }
};

void took(std::chrono::_V2::steady_clock::time_point s)
{
    std::cout << "took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - s).count()
              << "ms" << std::endl;
}

int main()
{
    auto observer = std::make_shared<HospitalizationObserver>();
    auto model_nj = seihr(N_NJ);
    auto model_dk = seihr(N_DK);
    model_nj.registerObserver(observer);
    model_dk.registerObserver(observer);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // Simulate Nordjylland
    model_nj.simulate(100);
    std::cout << "peak hospitalization (N_NJ): " << observer->h_peak << std::endl;
    took(start);

    start = std::chrono::steady_clock::now();
    observer->h_peak = 0;

    // Simulate Denmark
    model_dk.simulate(100);
    std::cout << "peak hospitalization (N_DK): " << observer->h_peak << std::endl;
    took(start);

    return 0;
}
