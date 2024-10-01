import matplotlib.pyplot as plt
import numpy as np

# Data from user
matrix_sizes = [100, 1000, 10000]
threads = [2, 4, 8]

# OpenMP times
openmp_times = {
    2: [0.002143, 3.034254, 6801.892763],
    4: [0.001114, 2.084169, 4878.898177],
    8: [0.000786, 1.323485, 3063.285704]
}

# MPI times
mpi_times = {
    2: [0.001351, 1.888740, 3600.45709],
    4: [0.001178, 1.449268, 3270.616247],
    8: [0.000591, 0.957053, 1367.392024]
}

# Create a plot
plt.figure(figsize=(10, 6))

# Plot OpenMP data
for num_threads in threads:
    plt.plot(matrix_sizes, openmp_times[num_threads], marker='o', label=f'OpenMP {num_threads} threads')

# Plot MPI data
for num_threads in threads:
    plt.plot(matrix_sizes, mpi_times[num_threads], marker='s', linestyle='--', label=f'MPI {num_threads} processes')

# Log scale for better visualization
plt.xscale('log')
plt.yscale('log')

# Labels and title
plt.xlabel('Matrix Size (N)')
plt.ylabel('Time Taken (seconds)')
plt.title('OpenMP vs MPI: Time Taken for Matrix Multiplication')
plt.legend()

# Show plot
plt.grid(True)
plt.tight_layout()
plt.show()
