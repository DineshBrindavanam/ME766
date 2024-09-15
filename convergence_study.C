#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define PI 3.14159
#define ANALYTICAL_RESULT 2.0

double f(double x) {
    return cos(x);
}

double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return h * sum;
}

double monte_carlo(double a, double b, int n) {
    double sum = 0.0;
    unsigned int seed = time(NULL);
    
    for (int i = 0; i < n; i++) {
        double x = a + (b - a) * ((double)rand_r(&seed) / RAND_MAX);
        sum += f(x);
    }
    
    return (b - a) * sum / n;
}

void convergence_study(double a, double b, int max_iterations) {
    printf("Convergence Study:\n");
    printf("N\tTrapezoidal Error\tMonte Carlo Error\n");

    for (int i = 1; i <= max_iterations; i++) {
        int n = pow(2, i) * 1000;  // Increase number of points exponentially
        
        double trap_result = trapezoidal_rule(a, b, n);
        double mc_result = monte_carlo(a, b, n);
        
        double trap_error = fabs(trap_result - ANALYTICAL_RESULT);
        double mc_error = fabs(mc_result - ANALYTICAL_RESULT);
        
        printf("%d\t%.10e\t%.10e\n", n, trap_error, mc_error);
    }
}

int main() {
    double a = -PI / 2;
    double b = PI / 2;
    int max_iterations = 10;  // This will go up to 2^10 * 1000 = 1,024,000 points
    
    convergence_study(a, b, max_iterations);
    
    return 0;
}