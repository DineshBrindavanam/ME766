# ME766 - High Performance Scientific Computing 

##  Instruction to compile and execute the Matrix Multiplication

1. Compile **matrix_multiplication.C** by `g++ -fopenmp -o matrix_multiplication.o matrix_multiplication.C -lm`. Run the code `time ./matrix_multiplication.o`.

---
## Instruction to compile and execute the MPI code for computing C = AB

- To do the computation of C = AB in the MPI, compile **mpi_matrix_multiplication.C** code by `mpicxx -o mpi_matrix_multiplication.o mpi_matrix_multiplication.C`. Execute the code `time ./mpi_matrix_multiplication.o`.

---