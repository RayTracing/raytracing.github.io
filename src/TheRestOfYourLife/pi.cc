#include "rtweekend.h"

#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(12);

    int inside_circle = 0;
    int N = 100000;
    for (int i = 0; i < N; i++) {
        auto x = random_double(-1,1);
        auto y = random_double(-1,1);
        if (x*x + y*y < 1)
            inside_circle++;
    }

    std::cout << "Estimate of Pi = " << (4.0 * inside_circle) / N << '\n';
}
