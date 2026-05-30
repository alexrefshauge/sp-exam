#include "example_models.hpp"
#include <fstream>
#include <Vessel.hpp>
#include "gnuplot-iostream.h"

struct SeihrPlotter : stochastic::StateObserver
{
    std::vector<std::pair<double, double>> s_series;
    std::vector<std::pair<double, double>> e_series;
    std::vector<std::pair<double, double>> i_series;
    std::vector<std::pair<double, double>> h_series;
    std::vector<std::pair<double, double>> r_series;

    SeihrPlotter() : s_series(), e_series(), i_series(), h_series(), r_series() {}

    void observe(const double t, const stochastic::VesselState &s) override
    {
        s_series.emplace_back(t, s.at("S"));
        e_series.emplace_back(t, s.at("E"));
        i_series.emplace_back(t, s.at("I"));
        h_series.emplace_back(t, s.at("H") * 1000);
        r_series.emplace_back(t, s.at("R"));
    }
};

int main()
{
    Gnuplot gp; //

    auto o = std::make_shared<SeihrPlotter>();
    auto model = seihr(10000);
    model.registerObserver(o);
    model.simulate(100);

    gp << "set terminal pngcairo size 1400,900\n";
    gp << "set output 'seihr_NJ.png'\n";
    gp << "set xlabel 'time'\n";
    gp << "set ylabel 'Species'\n";
    gp << "set grid\n";

    gp << "plot '-' using 1:2 with lines lw 2 title 'S',"
       << "'-' using 1:2 with lines lw 2 title 'E',"
       << "'-' using 1:2 with lines lw 2 title 'I',"
       << "'-' using 1:2 with lines lw 2 title 'H',"
       << "'-' using 1:2 with lines lw 2 title 'R'\n";

    gp.send1d(o->s_series);
    gp.send1d(o->e_series);
    gp.send1d(o->i_series);
    gp.send1d(o->h_series);
    gp.send1d(o->r_series);
    gp << "unset output\n";
}
