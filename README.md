# ME766
ME766 - High Performance Scientific Computing 

1. Compile Trapezoidal_serial.C by "g++ -o trapezoidal_serial.o trapezoidal_serial.C -lm". Run the code "time ./trapezoidal_serial.o".

2. Compile Trapezoidal_OpenMP.C by "g++ -fopenmp -o trapezoidal_OpenMP.o trapezoidal_OpenMP.C -lm". Run this command to parallelize on 4 cores and execute the code "export OMP_NUM_THREADS=4 && time ./trapezoidal_OpenMP.o".

3. Compile MonteCarlo_serial.C by "g++ -o monteCarlo_serial.o monteCarlo_serial.C -lm". Run the code "time ./monteCarlo_serial.o".

4. Compile MonteCarlo_OpenMP.C by "g++ -fopenmp -o monteCarlo_OpenMP.o monteCarlo_OpenMP.C -lm". Run this command to parallelize on 4 cores and execute the code "export OMP_NUM_THREADS=4 && time ./monteCarlo_OpenMP.o"