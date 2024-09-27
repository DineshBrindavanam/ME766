#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random floating-point number
double random_double() {
    return (double)rand() / RAND_MAX;
}

// Function to perform matrix multiplication for a subset of rows
void matrix_multiply(double* A, double* B, double* C, int local_rows, int N) {
    for (int i = 0; i < local_rows; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int N;
    int rank, size;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (N = 100; N <= 10000; N *= 10) {
        int local_rows = N / size; // Number of rows each process will handle

        // Allocate memory for local matrices and buffers
        double* A_local = (double*)malloc(local_rows * N * sizeof(double));
        double* B = (double*)malloc(N * N * sizeof(double)); // Matrix B is fully replicated across all processes
        double* C_local = (double*)malloc(local_rows * N * sizeof(double));

        // Initialize matrix A and B in rank 0
        double* A = NULL;
        if (rank == 0) {
            A = (double*)malloc(N * N * sizeof(double));
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    A[i * N + j] = random_double();
                    B[i * N + j] = random_double();
                }
            }
        }

        // Broadcast matrix B to all processes
        MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Scatter rows of matrix A to all processes
        MPI_Scatter(A, local_rows * N, MPI_DOUBLE, A_local, local_rows * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Record the start time for computation
        double start_time = MPI_Wtime();

        // Perform matrix multiplication for the local rows of A
        matrix_multiply(A_local, B, C_local, local_rows, N);

        // Gather the computed rows of matrix C from all processes
        double* C = NULL;
        if (rank == 0) {
            C = (double*)malloc(N * N * sizeof(double));
        }
        MPI_Gather(C_local, local_rows * N, MPI_DOUBLE, C, local_rows * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Record the end time for computation
        double end_time = MPI_Wtime();

        // Rank 0 prints the time taken for this computation
        if (rank == 0) {
            printf("N = %d, Time taken with %d processes: %f seconds\n", N, size, end_time - start_time);
            free(A);
            free(C);
        }

        // Free allocated memory
        free(A_local);
        free(B);
        free(C_local);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
