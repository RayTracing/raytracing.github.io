#include <iostream>
#include <math.h>


int main() {
    for (int i = 0; i < 2000; i++) {
        float r1 = drand48();
        float r2 = drand48();
        float x = cos(2*M_PI*r1)*2*sqrt(r2*(1-r2));
        float y = sin(2*M_PI*r1)*2*sqrt(r2*(1-r2));
        float z = 1 - 2*r2;
        std::cout << x << " " << y << " " << z << "\n";
    }
}

