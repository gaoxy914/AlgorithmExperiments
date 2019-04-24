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

plt.plot(x_values, y1_values, marker='o', label='quicksort')
plt.plot(x_values, y2_values, marker='s', color='r', label='c++ stl sort')

#plt.title("int32 test", fontsize=24)
#plt.xlabel("count(x200000)")
plt.title("x% 1 test", fontsize=24)
plt.xlabel("x(%)")
plt.ylabel("time(ms)")

plt.legend()

plt.savefig('curve.jpg')

plt.show()
