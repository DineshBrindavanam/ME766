# ME766 - High Performance Scientific Computing 

##  Instruction to compile and execute the Matrix Multiplication

1. Compile **matrix_multiplication.C** by `g++ -fopenmp -o matrix_multiplication.o matrix_multiplication.C -lm`. Run the code `time ./matrix_multiplication.o`.

---
## Convergence Study for Trapezoidal Rule and Monte-Carlo Method

- To do the convergence study for Trapezoidal Rule and Monte-Carlo Method, compile **convergence_study.C** code by `g++ -O3 -fopenmp -o convergence_study.o convergence_study.C -lm`. Execute the code `time ./convergence_study.o`.

<p style="text-align:center;">(OR)</p>

- To do the convergence study for Trapezoidal Rule and Monte-Carlo Method, compile and execute `g++ -O3 -fopenmp -o convergence_study.o convergence_study.C -lm && ./convergence_study.o > convergence_data.csv && python3 convergence_plot.py` to view the convergence plot from python.
---

## OpenMP timing study for Trapezoidal Rule and Monte-Carlo Method using 2, 4, 6 and 8 threads

- To compute the OpenMP timing study between Trapezoidal rule and Monte-Carlo method using 2, 4, 6 and 8 threads for average 5 times execution by running `g++ -O3 -fopenmp -o OpenMP_timing_study.o OpenMP_timing_study.C -lm && ./OpenMP_timing_study.o`.

---