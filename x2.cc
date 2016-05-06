#include <math.h>
#include <stdlib.h>
#include <iostream>

int main() {
    int inside_circle = 0;
    int inside_circle_stratified = 0;
    int N = 1000000;
    float sum;
    for (int i = 0; i < N; i++) {
            float x = 2*drand48();
            sum += x*x;
    }
    std::cout << "I =" << 2*sum/N << "\n";
}



