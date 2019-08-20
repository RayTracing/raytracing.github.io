#ifndef RANDOMH
#define RANDOMH

#include <random>
#include <functional>
#include <cstdlib>

inline double random_double_1 () {
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double_2() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  static std::function<double()> rand_generator = 
    std::bind(distribution, generator);
  return rand_generator();
}

inline double random_double() {
  return random_double_1();
}

#endif
