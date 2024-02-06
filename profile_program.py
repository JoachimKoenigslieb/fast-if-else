import subprocess
import time
import matplotlib.pyplot as plt


subprocess.call([ 'make', ])

sizes = [(2**i) - 1 for i in range(12, 33)]
timings = []
timings_par = []

for s in sizes:
    command = ["./simple", "23", str(s)]  # Command and arguments should be separate items in the list

    start_time = time.time()
    subprocess.call(command)
    end_time = time.time()

    duration = end_time - start_time
    print(f'checked size...', s, 'in', duration, 's')
    timings.append(duration)

for s in sizes:
    command = ["./cpu_parallel", "23", str(s)]  # Command and arguments should be separate items in the list

    start_time = time.time()
    subprocess.call(command)
    end_time = time.time()

    duration = end_time - start_time
    print(f'checked size...', s, 'in', duration, 's')
    timings_par.append(duration)

# Plotting
plt.figure(figsize=(10, 6))  # Optional: you can adjust the figure size
plt.plot(sizes, timings, marker='o')  # Plot sizes vs timings with circle markers
plt.plot(sizes, timings_par, marker='x')  # Plot sizes vs timings with circle markers
plt.legend(['Naive', '8 threads'])
plt.xscale('log')  # Set the x-axis to a logarithmic scale
plt.yscale('log')  # Set the y-axis to a logarithmic scale
plt.xlabel('Size')  # Label for x-axis
plt.ylabel('Time (seconds)')  # Label for y-axis
plt.title('Execution Time vs Size')  # Title for the plot
plt.grid(True, which="both", ls="--")  # Add a grid for better readability, applicable to both logarithmic and linear scales
plt.show()  # Display the plot
