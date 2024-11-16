#include <iostream>
#include <cuda_runtime.h>
#include <chrono>

// CUDA kernel for matrix multiplication
__global__ void matrixMultiplication(float* A, float* B, float* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N) {
        float value = 0;
        for (int k = 0; k < N; ++k) {
            value += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = value;
    }
}

// Helper function to initialize matrix with random values
void matrixInitialize(float* matrix, int N) {
    for (int i = 0; i < N * N; ++i) {
        matrix[i] = static_cast<float>(rand()) / RAND_MAX;
    }
}

int main() {
    for (int N = 100; N <= 10000; N += 100) { // Adjust step size as needed
        int size = N * N * sizeof(float);

        // Allocate memory on host
        float *h_A, *h_B, *h_C;
        h_A = (float*)malloc(size);
        h_B = (float*)malloc(size);
        h_C = (float*)malloc(size);

        // Initialize matrices A and B
        matrixInitialize(h_A, N);
        matrixInitialize(h_B, N);

        // Allocate memory on device
        float *d_A, *d_B, *d_C;
        cudaMalloc((void**)&d_A, size);
        cudaMalloc((void**)&d_B, size);
        cudaMalloc((void**)&d_C, size);

        // Copy data from host to device
        cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
        cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

        // Define thread block and grid dimensions
        dim3 threadsPerBlock(16, 16);
        dim3 blocksPerGrid((N + threadsPerBlock.x - 1) / threadsPerBlock.x,
                           (N + threadsPerBlock.y - 1) / threadsPerBlock.y);

        // Measure time
        auto start = std::chrono::high_resolution_clock::now();

        // Launch kernel
        matrixMultiplication<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
        cudaDeviceSynchronize();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = end - start;
        std::cout << "Matrix size N=" << N << ", Time: " << duration.count() << " ms" << std::endl;

        // Copy result back to host
        cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

        // Free memory
        free(h_A); free(h_B); free(h_C);
        cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    }

    return 0;
}
