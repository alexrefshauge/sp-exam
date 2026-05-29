#ifndef STOCHASTIC_EXAMPLE_MODELS_HPP
#define STOCHASTIC_EXAMPLE_MODELS_HPP

#include <cstdint>
#include "Vessel.hpp"

stochastic::Vessel abc(int A0, int B0, int C0);
stochastic::Vessel seihr(uint32_t N);
stochastic::Vessel circadian();

#endif
