#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

#endif
