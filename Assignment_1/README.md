# ME766 - High Performance Scientific Computing 

##  Instruction to compile and execute the Trapezoidal and Monte-Carlo Numerical integration technique:

1. Compile **Trapezoidal_serial.C** by `g++ -o trapezoidal_serial.o trapezoidal_serial.C -lm`. Run the code `time ./trapezoidal_serial.o`.

1. Compile **Trapezoidal_OpenMP.C** by `g++ -fopenmp -o trapezoidal_OpenMP.o trapezoidal_OpenMP.C -lm`. Run this command to parallelize on 4 cores and execute the code `export OMP_NUM_THREADS=4 && time ./trapezoidal_OpenMP.o`.

1. Compile **MonteCarlo_serial.C** by `g++ -o monteCarlo_serial.o monteCarlo_serial.C -lm`. Run the code `time ./monteCarlo_serial.o`.

1. Compile **MonteCarlo_OpenMP.C** by `g++ -fopenmp -o monteCarlo_OpenMP.o monteCarlo_OpenMP.C -lm`. Run this command to parallelize on 4 cores and execute the code `export OMP_NUM_THREADS=4 && time ./monteCarlo_OpenMP.o`.

---
## Convergence Study for Trapezoidal Rule and Monte-Carlo Method

- To do the convergence study for Trapezoidal Rule and Monte-Carlo Method, compile **convergence_study.C** code by `g++ -O3 -fopenmp -o convergence_study.o convergence_study.C -lm`. Execute the code `time ./convergence_study.o`.

<p style="text-align:center;">(OR)</p>

- To do the convergence study for Trapezoidal Rule and Monte-Carlo Method, compile and execute `g++ -O3 -fopenmp -o convergence_study.o convergence_study.C -lm && ./convergence_study.o > convergence_data.csv && python3 convergence_plot.py` to view the convergence plot from python.
---

## OpenMP timing study for Trapezoidal Rule and Monte-Carlo Method using 2, 4, 6 and 8 threads

- To compute the OpenMP timing study between Trapezoidal rule and Monte-Carlo method using 2, 4, 6 and 8 threads for average 5 times execution by running `g++ -O3 -fopenmp -o OpenMP_timing_study.o OpenMP_timing_study.C -lm && ./OpenMP_timing_study.o`.

---