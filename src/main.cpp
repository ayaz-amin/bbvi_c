#define GUESS 8.5
#define MEASUREMENT 9.5

#include <math.h>
#include <stdio.h>

#include "rng.hpp"
#include "bbvi.hpp"

struct Stats {
    float elbo;
    float grad_mean;
    float grad_stddev;
};

void step(NormalDist *q_z, RNG *rng, float rate, int num_samples)
{
    Stats stats = {};

    float weight;
    for(int i = 0; i < num_samples; i++)
    {
        weight = NormalSample(q_z, rng);
        NormalDist p_z = {GUESS, 1.0};
        NormalDist p_xz = {weight, 0.75};
        float joint = NormalLogProb(&p_xz, MEASUREMENT) + NormalLogProb(&p_z, weight);
        float variational = NormalLogProb(q_z, weight);
        float _elbo = variational - joint;
        stats.elbo += _elbo;
        stats.grad_mean += _elbo * NormalScoreMean(q_z, weight);
        stats.grad_stddev += _elbo * NormalScoreStddev(q_z, weight);
    }
    
    stats.elbo /= num_samples;
    stats.grad_mean /= num_samples;
    stats.grad_stddev /= num_samples;

    q_z->mean -= rate * stats.grad_mean;
    q_z->stddev *= expf(-0.5 * rate * stats.grad_stddev);

    printf("Negative ELBO: %f\n", stats.elbo);
}

int main(void)
{
    NormalDist q_z = {GUESS, 1.0};
    RNG rng = CreateNewRNG(0xDEADBEEF);

    for(int i = 0; i < 200; i++)
    {
        step(&q_z, &rng, 1e-2, 10);
    }

    printf("[q(Z) parameters] Mean: %f, Stddev: %f\n", q_z.mean, q_z.stddev);
    
    return 0;
}
