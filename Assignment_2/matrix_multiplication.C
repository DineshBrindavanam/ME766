#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Function to generate a random floating-point number
double random_double() {
    return (double)rand() / RAND_MAX;
}

// Function to multiply matrices A and B and store the result in C
void matrix_multiply(double** A, double** B, double** C, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N;
    for (N = 100; N <= 10000; N *= 10) {
        // Seed for random number generation
        srand(time(NULL));

        // Allocate memory for matrices A, B, and C
        double** A = (double**)malloc(N * sizeof(double*));
        double** B = (double**)malloc(N * sizeof(double*));
        double** C = (double**)malloc(N * sizeof(double*));
        for (int i = 0; i < N; i++) {
            A[i] = (double*)malloc(N * sizeof(double));
            B[i] = (double*)malloc(N * sizeof(double));
            C[i] = (double*)malloc(N * sizeof(double));
        }

        // Initialize matrices A and B with random values
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = random_double();
                B[i][j] = random_double();
            }
        }

        // Record the start time
        double start_time = omp_get_wtime();

        // Perform matrix multiplication C = A * B
        matrix_multiply(A, B, C, N);

        // Record the end time
        double end_time = omp_get_wtime();

        // Report time taken
        printf("N = %d, Time taken: %f seconds\n", N, end_time - start_time);

        // Free allocated memory
        for (int i = 0; i < N; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}
