#include "models.cpp"
#include <fstream>

struct PlotObserver : stochastic::StateObserver
{
    size_t h_peak = 0;
    std::ofstream file;
    explicit PlotObserver() : file("out.csv")
    {
        file << "t,DA,D_A,DR,D_R,MA,MR,A,R,C\n";
    }

    ~PlotObserver()
    {
        file.close();
    }

    void observe(const double t, const VesselState &s) override
    {
        file << t << ","
             << s.at("DA") << ","
             << s.at("D_A") << ","
             << s.at("DR") << ","
             << s.at("D_R") << ","
             << s.at("MA") << ","
             << s.at("MR") << ","
             << s.at("A") << ","
             << s.at("R") << ","
             << s.at("C")
             << std::endl;
    }
};

int main()
{
    auto o = std::make_shared<PlotObserver>();
    auto model = circadian();
    model.registerObserver(o);
    model.simulate(48);
}