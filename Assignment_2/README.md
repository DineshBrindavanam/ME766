# ME766 - High Performance Scientific Computing 

##  Instruction to compile and execute the Matrix Multiplication on OpenMP

Compile **matrix_multiplication.C** by `g++ -fopenmp -o matrix_multiplication.o matrix_multiplication.C -lm`. 
- Set the number of threads and execute the code on 2 processors: `export OMP_NUM_THREADS=2 && ./matrix_multiplication.o`.
- Set the number of threads and execute the code on 4 processors: `export OMP_NUM_THREADS=4 && ./matrix_multiplication.o`.
- Set the number of threads and execute the code on 8 processors: `export OMP_NUM_THREADS=8 && ./matrix_multiplication.o`.

---
## Instruction to compile and execute the MPI code for computing C = AB

To do the computation of C = AB in the MPI, compile **mpi_matrix_multiplication.C** code by `mpicxx -o mpi_matrix_multiplication.o mpi_matrix_multiplication.C`. 
- Execute the code on 2 processors: `mpirun -np 2 ./mpi_matrix_multiplication.o`.
- Execute the code on 4 processors: `mpirun -np 4 ./mpi_matrix_multiplication.o`.
- Execute the code on 8 processors: `mpirun -np 8 ./mpi_matrix_multiplication.o`.
---