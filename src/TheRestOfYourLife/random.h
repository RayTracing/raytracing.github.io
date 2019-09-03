#ifndef RANDOMH
#define RANDOMH

#include <cstdlib>


double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

#endif
