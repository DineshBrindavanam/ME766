import matplotlib.pyplot as plt
import numpy as np
import csv

# Read the data from the CSV file
n_values = []
trap_errors = []
mc_errors = []

with open('convergence_data.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile)
    next(csvreader)  # Skip the header
    for row in csvreader:
        n_values.append(int(row[0]))
        trap_errors.append(float(row[1]))
        mc_errors.append(float(row[2]))

# Convert to numpy arrays
n_values = np.array(n_values)
trap_errors = np.array(trap_errors)
mc_errors = np.array(mc_errors)

# Create the plot
plt.figure(figsize=(10, 6))
plt.loglog(n_values, trap_errors, 'b-o', label='Trapezoidal Rule')
plt.loglog(n_values, mc_errors, 'r-o', label='Monte Carlo')

# Add reference lines
plt.loglog(n_values, 1/n_values**2, 'k--', label='O(1/N²)')
plt.loglog(n_values, 1/np.sqrt(n_values), 'g--', label='O(1/√N)')

plt.xlabel('Number of Points (N)')
plt.ylabel('Absolute Error')
plt.title('Convergence Study: Trapezoidal Rule vs Monte Carlo')
plt.legend()
plt.grid(True)

# Add text about expected convergence rates
plt.text(0.5, 0.5, 'Expected convergence rates:\nTrapezoidal: O(1/N²)\nMonte Carlo: O(1/√N)', 
         transform=plt.gca().transAxes, bbox=dict(facecolor='white', alpha=0.8))

plt.savefig('convergence_plot.png')
plt.show()