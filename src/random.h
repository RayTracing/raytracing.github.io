#ifndef RANDOMH
#define RANDOMH

#include <cstdlib>

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

#endif
