#ifndef RANDOMH
#define RANDOMH

#include <random>

double random_double() {
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static thread_local std::mt19937 generator;
    return distribution(generator);
}

#endif
