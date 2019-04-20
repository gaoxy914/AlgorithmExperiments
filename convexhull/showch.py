import matplotlib.pyplot as plt


x1_values = []
y1_values = []

plt.subplot(2, 2, 1)

with open("point1.txt") as f:
    for line in f:
        x, y = line[1:-2].split(',')
        x1_values.append(x)
        y1_values.append(y)

for i in range(len(x1_values)-1):
    a = [x1_values[i], x1_values[i+1]]
    b = [y1_values[i], y1_values[i+1]]
    # print(a, b)
    plt.plot(a, b, color='r')
    plt.scatter(a, b, color='b')

a = [x1_values[len(x1_values)-1], x1_values[0]]
b = [y1_values[len(x1_values)-1], y1_values[0]]
plt.plot(a, b, color='r')
plt.scatter(a, b, color='b')



#plt.scatter(x1_values, y1_values, s=30, c='b')

plt.subplot(2, 2, 2)

x2_values = []
y2_values = []

with open("point2.txt") as f:
    for line in f:
        x, y = line[1:-2].split(',')
        x2_values.append(x)
        y2_values.append(y)

for i in range(len(x2_values)-1):
    a = [x2_values[i], x2_values[i+1]]
    b = [y2_values[i], y2_values[i+1]]
    # print(a, b)
    plt.plot(a, b, color='r')
    plt.scatter(a, b, color='b')

a = [x2_values[len(x2_values)-1], x2_values[0]]
b = [y2_values[len(x2_values)-1], y2_values[0]]
plt.plot(a, b, color='r')
plt.scatter(a, b, color='b')


plt.subplot(2, 2, 3)

x3_values = []
y3_values = []

with open("point3.txt") as f:
    for line in f:
        x, y = line[1:-2].split(',')
        x3_values.append(x)
        y3_values.append(y)

for i in range(len(x3_values)-1):
    a = [x3_values[i], x3_values[i+1]]
    b = [y3_values[i], y3_values[i+1]]
    # print(a, b)
    plt.plot(a, b, color='r')
    plt.scatter(a, b, color='b')

a = [x3_values[len(x3_values)-1], x3_values[0]]
b = [y3_values[len(x3_values)-1], y3_values[0]]
plt.plot(a, b, color='r')
plt.scatter(a, b, color='b')


plt.show()
