#pragma once

#include <stdint.h>

struct RNG
{
    int position;
    uint32_t seed;
};

RNG CreateNewRNG(uint32_t seed);
uint32_t RNGGenerate(RNG *rng);
