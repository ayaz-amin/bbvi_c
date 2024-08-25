#define M_PI 3.14159265358979323846

#include <math.h>
#include "bbvi.hpp"

float NormalSample(NormalDist *dist, RNG *rng)
{
    float u1 = RNGGenerate(rng) / (float)UINT32_MAX;
    float u2 = RNGGenerate(rng) / (float)UINT32_MAX;
    float mag = dist->stddev * sqrtf(-2.0 * logf(u1));
    return mag * cosf(2.0 * M_PI * u2) + dist->mean;
}

float NormalLogProb(NormalDist *dist, float sample)
{
    float z = (sample - dist->mean) / dist->stddev;
    return -0.5 * (z * z + logf(2 * M_PI)) - logf(dist->stddev);
}

float NormalScoreMean(NormalDist *dist, float sample)
{
    return (sample - dist->mean) / (dist->stddev * dist->stddev);
}

float NormalScoreStddev(NormalDist *dist, float sample)
{
    float a = sample - dist->mean;
    float b = dist->stddev;
    return (a * a - b * b) / (b * b * b);
}
