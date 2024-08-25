#pragma once

#include "rng.hpp"

struct NormalDist
{
    float mean;
    float stddev;
};

float NormalSample(NormalDist *dist, RNG *rng);
float NormalLogProb(NormalDist *dist, float sample);
float NormalScoreMean(NormalDist *dist, float sample);
float NormalScoreStddev(NormalDist *dist, float sample);
