#include <iostream>
#include <math.h>



int main() {
    int N = 1000000;
    float sum = 0.0;
    for (int i = 0; i < N; i++) {
        float r1 = drand48();
        float r2 = drand48();
        float x = cos(2*M_PI*r1)*2*sqrt(r2*(1-r2));
        float y = sin(2*M_PI*r1)*2*sqrt(r2*(1-r2));
        float z = 1 - r2;
        sum += z*z*z / (1.0/(2.0*M_PI));
    }
    std::cout << "PI/2 = " << M_PI/2 << "\n";
    std::cout << "Estimate = " << sum/N << "\n";
}

