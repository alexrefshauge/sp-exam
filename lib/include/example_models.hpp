#ifndef STOCHASTIC_EXAMPLE_MODELS_HPP
#define STOCHASTIC_EXAMPLE_MODELS_HPP

#include <cstdint>
#include "Vessel.hpp"

#define N_DK 5822763
#define N_NJ 589755

stochastic::Vessel abc(int A0, int B0, int C0);
stochastic::Vessel seihr(uint32_t N);
stochastic::Vessel circadian();

#endif
