import matplotlib.pyplot as plt

x_values = []
y1_values = []
y2_values = []

with open("time.txt") as f:
    for line in f:
        x, y1, y2 = line.strip().split(" ")
        x_values.append(x)
        y1_values.append(y1)
        y2_values.append(y2)

plt.plot(x_values, y1_values, marker='o', label='greedy')
plt.plot(x_values, y2_values, marker='s', color='r', label='lp')

plt.xlabel("|X| = |F|")
plt.ylabel("time(s)")

plt.legend()

plt.savefig("qw.jpg")

plt.show()
