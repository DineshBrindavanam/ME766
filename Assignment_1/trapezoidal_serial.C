#include <stdio.h>
#include <math.h>

#define PI 3.14159

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

int main() {
    double a = -PI / 2;
    double b = PI / 2;
    int n = 1000000; // Number of intervals
    
    double result = trapezoidal_rule(a, b, n);
    printf("Trapezoidal Rule Result: %.10f\n", result);
    
    return 0;
}