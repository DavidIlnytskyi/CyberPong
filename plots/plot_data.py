import numpy as np
import matplotlib.pyplot as plt
import re
import pandas as pd

def parse_data(path):
	data = []
	with open(path, "r") as file:
		for line in file.readlines():
			numbers = [int(re.findall("[0-9]+", number)[0]) for number in line.split()]
			if len(numbers)==8:
					data.append(numbers)
	data = np.array(data)
	return data[:, :2], data[:, 2:4], data[:, 4:6], data[:, 6:]

def plot_data(data, title, i):
	plt.title(title)
	plt.plot(data[:, 0], label="Actual speed", solid_capstyle='round', lw=2.5)
	plt.plot(data[:, 1], label="Desired speed", solid_capstyle='round', lw=2.5)
	plt.xlabel("Time")
	plt.ylabel("RPM")
	if i == 0:
		plt.legend(frameon=True, shadow=True,  bbox_to_anchor=(1.3, 1.3), loc="upper right")

def plot_all_data(data):
	plt.style.use("ggplot")
	plt.rcParams["figure.autolayout"] = True
	top_ax = plt.subplot(3, 1, 1)
	plt.title("Speed differences")

	for i in range(len(data)):
		plt.subplot(3, 2, i+3)
		label = ["Left", "Right", "Top", "Bottom"][i]
		top_ax.plot(data[i][:, 1]-data[i][:, 0], label=label)
		plot_data(data[i], label+" motor", i)
	top_ax.legend(frameon=False)
	plt.show()

if __name__ == "__main__":
	filename = "teraterm.log"
	plot_all_data(parse_data(filename))
