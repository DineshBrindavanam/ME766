#include <stdio.h>
#include <math.h>
#include <omp.h>

#define PI 3.14159

double f(double x) {
    return cos(x);
}

double trapezoidal_rule_omp(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    
    #pragma omp parallel
    {
        double local_sum = 0.0;
        #pragma omp for
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            local_sum += f(x);
        }
        #pragma omp atomic
        sum += local_sum;
    }
    
    sum += 0.5 * (f(a) + f(b));
    return h * sum;
}

int main() {
    double a = -PI / 2;
    double b = PI / 2;
    int n = 1000000; // Number of intervals
    
    double result = trapezoidal_rule_omp(a, b, n);
    printf("OpenMP Trapezoidal Rule Result: %.10f\n", result);
    
    return 0;
}