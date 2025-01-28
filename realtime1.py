import matplotlib.pyplot as plt
import numpy as np
import random

# Function to simulate the real-time process of ethanol production efficiency with varying parameters
def simulate_real_time():
    # Define different sugar and yeast types for random selection
    sugar_types = ['glucose', 'sucrose', 'fructose', 'maltose', 'lactose']
    yeast_types = ['Saccharomyces cerevisiae', 'Kluyveromyces lactis', 'Zymomonas mobilis', 'Schizosaccharomyces pombe']

    # Randomly simulate parameter values at each time step
    sugar_type = random.choice(sugar_types)
    yeast_type = random.choice(yeast_types)
    sugar_amount = random.uniform(80.0, 120.0)  # sugar amount in grams
    yeast_amount = random.uniform(20.0, 40.0)  # yeast amount in grams
    fermentation_time = random.uniform(40.0, 60.0)  # fermentation time in hours
    distillation_temp = random.uniform(20.0, 40.0)  # distillation temperature in Celsius

    # Define sugar and yeast efficiencies
    sugar_efficiency = {'glucose': 1.2, 'sucrose': 1.1, 'fructose': 1.3, 'maltose': 1.0, 'lactose': 0.8}
    yeast_efficiency = {'Saccharomyces cerevisiae': 1.0, 'Kluyveromyces lactis': 0.8, 'Zymomonas mobilis': 1.1, 'Schizosaccharomyces pombe': 0.9}

    # Calculate the efficiency based on the selected parameters
    sugar_factor = sugar_efficiency.get(sugar_type, 0.9)
    yeast_factor = yeast_efficiency.get(yeast_type, 0.8)
    fermentation_factor = 1.3 if 45 <= fermentation_time <= 55 else 0.7
    distillation_factor = 1.2 if 25 <= distillation_temp <= 35 else 0.5

    # Calculate total efficiency
    efficiency = (sugar_factor * yeast_factor * fermentation_factor * distillation_factor) * 100
    return efficiency, sugar_type, yeast_type, sugar_amount, yeast_amount, fermentation_time, distillation_temp

# Function to plot the real-time simulation
def plot_real_time_simulation():
    fig, ax = plt.subplots(figsize=(10, 6))
    time_steps = []
    efficiencies = []
    sugar_types = []
    yeast_types = []
    sugar_amounts = []
    yeast_amounts = []
    fermentation_times = []
    distillation_temps = []

    for t in range(100):  # Simulate 100 time steps
        efficiency, sugar_type, yeast_type, sugar_amount, yeast_amount, fermentation_time, distillation_temp = simulate_real_time()
        
        time_steps.append(t)
        efficiencies.append(efficiency)
        sugar_types.append(sugar_type)
        yeast_types.append(yeast_type)
        sugar_amounts.append(sugar_amount)
        yeast_amounts.append(yeast_amount)
        fermentation_times.append(fermentation_time)
        distillation_temps.append(distillation_temp)

        # Clear the plot for real-time updates
        ax.clear()

        # Plot efficiency over time
        ax.plot(time_steps, efficiencies, label="Efficiency", color='b')
        ax.set_xlabel('Time Step')
        ax.set_ylabel('Efficiency (%)')
        ax.set_title('Real-Time Ethanol Production Efficiency')
        ax.legend(loc='upper left')

        # Add secondary plots for sugar amount, yeast amount, and fermentation time
        ax2 = ax.twinx()
        ax2.plot(time_steps, sugar_amounts, label="Sugar Amount (grams)", color='r', linestyle='--')
        ax2.plot(time_steps, yeast_amounts, label="Yeast Amount (grams)", color='g', linestyle='-.')
        ax2.plot(time_steps, fermentation_times, label="Fermentation Time (hrs)", color='purple', linestyle=':')

        # Set the range for the secondary y-axis (for sugar, yeast, fermentation time)
        ax2.set_ylabel('Amount / Time')
        ax2.set_ylim([0, max(max(sugar_amounts), max(yeast_amounts), max(fermentation_times)) * 1.1])

        # Set limits for efficiency on the primary y-axis
        ax.set_ylim([0, 120])

        ax2.legend(loc='upper right')

        plt.pause(0.1)  # Pause to simulate real-time updates

    plt.show()

# Run the real-time simulation plot
plot_real_time_simulation()
