#include "rng.hpp"

RNG CreateNewRNG(uint32_t seed)
{
    RNG new_rng = {0};
    new_rng.position = 0;
    new_rng.seed = seed;
    return new_rng;
}

#define BITNOISE1 0xB5297A4D;
#define BITNOISE2 0x68E31DA4;
#define BITNOISE3 0x1B56C4E9;
uint32_t RNGGenerate(RNG *rng)
{
    uint32_t mangled = rng->position;
    rng->position++;
    mangled *= BITNOISE1;
    mangled += rng->seed;
    mangled ^= (mangled >> 8);
    mangled += BITNOISE2;
    mangled ^= (mangled << 8);
    mangled *= BITNOISE3;
    mangled ^= (mangled >> 8);
    return mangled;
}
