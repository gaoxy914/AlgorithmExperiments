import matplotlib.pyplot as plt

x_values = []
y1_values = []
#y2_values = []

with open("time.txt") as f:
    for line in f:
        x, y1 = line.strip().split(" ")
        x_values.append(x)
        y1_values.append(y1)
        #y2_values.append(y2)

plt.plot(x_values, y1_values, marker='o', label='enumerate')
#plt.plot(x_values, y1_values, marker='s', color='r', label='graham_scan')
#plt.plot(x_values, y2_values, marker='x', color='g', label='divide and conquer')

plt.xlabel("Q's size")
plt.ylabel("time(s)")

plt.legend()

plt.savefig('1.jpg')

plt.show()
