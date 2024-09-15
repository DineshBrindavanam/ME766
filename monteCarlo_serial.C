#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159

double f(double x) {
    return cos(x);
}

double monte_carlo(double a, double b, int n) {
    double sum = 0.0;
    
    srand(time(NULL));
    
    for (int i = 0; i < n; i++) {
        double x = a + (b - a) * ((double)rand() / RAND_MAX);
        sum += f(x);
    }
    
    return (b - a) * sum / n;
}

int main() {
    double a = -PI / 2;
    double b = PI / 2;
    int n = 1000000; // Number of random points
    
    double result = monte_carlo(a, b, n);
    printf("Monte Carlo Method Result: %.10f\n", result);
    
    return 0;
}