#include <math.h>
#include <stdlib.h>
#include <iostream>

inline float pdf(float x) {
    return  3*x*x/8;
}

int main() {
    int inside_circle = 0;
    int inside_circle_stratified = 0;
    int N = 1;
    float sum;
    for (int i = 0; i < N; i++) {
            float x = pow(8*drand48(), 1./3.);
            sum += x*x / pdf(x);
    }
    std::cout << "I =" << sum/N << "\n";
}



