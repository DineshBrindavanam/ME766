#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define PI 3.14159

double f(double x) {
    return cos(x);
}

double monte_carlo_omp(double a, double b, int n) {
    double sum = 0.0;
    
    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        double local_sum = 0.0;
        
        #pragma omp for
        for (int i = 0; i < n; i++) {
            double x = a + (b - a) * ((double)rand_r(&seed) / RAND_MAX);
            local_sum += f(x);
        }
        
        #pragma omp atomic
        sum += local_sum;
    }
    
    return (b - a) * sum / n;
}

int main() {
    double a = -PI / 2;
    double b = PI / 2;
    int n = 1000000; // Number of random points
    
    double result = monte_carlo_omp(a, b, n);
    printf("OpenMP Monte Carlo Method Result: %.10f\n", result);
    
    return 0;
}