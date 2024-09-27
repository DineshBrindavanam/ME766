#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define PI 3.14159
#define NUM_RUNS 5

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

void timing_study(double a, double b, int n) {
    int thread_counts[] = {2, 4, 6, 8};
    int num_thread_configs = sizeof(thread_counts) / sizeof(thread_counts[0]);

    printf("Timing Study (average of %d runs):\n", NUM_RUNS);
    printf("Threads\tTrapezoidal Time (s)\tMonte Carlo Time (s)\n");

    for (int i = 0; i < num_thread_configs; i++) {
        int threads = thread_counts[i];
        double trap_total_time = 0.0;
        double mc_total_time = 0.0;

        for (int run = 0; run < NUM_RUNS; run++) {
            omp_set_num_threads(threads);

            double start_time = omp_get_wtime();
            trapezoidal_rule_omp(a, b, n);
            double end_time = omp_get_wtime();
            trap_total_time += end_time - start_time;

            start_time = omp_get_wtime();
            monte_carlo_omp(a, b, n);
            end_time = omp_get_wtime();
            mc_total_time += end_time - start_time;
        }

        double trap_avg_time = trap_total_time / NUM_RUNS;
        double mc_avg_time = mc_total_time / NUM_RUNS;

        printf("%d\t%.6f\t\t%.6f\n", threads, trap_avg_time, mc_avg_time);
    }
}

int main() {
    double a = -PI / 2;
    double b = PI / 2;
    int n = 100000000; // 100 million points for a more noticeable execution time
    
    timing_study(a, b, n);
    
    return 0;
}