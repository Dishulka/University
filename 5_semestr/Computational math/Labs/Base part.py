import numpy as np
import matplotlib.pyplot as plt


def qubic_spline_coeff(x_nodes, y_nodes):
    matrix1 = np.zeros((len(x_nodes), len(x_nodes)))
    for i in range(len(x_nodes)):
        if (i == 0) or (i == (len(x_nodes) - 1)):
            matrix1[i][i] = 1
        else:
            matrix1[i][i] = 2 * (x_nodes[i + 2 - 1] - x_nodes[i - 1])
            matrix1[i][i - 1] = x_nodes[i + 1 - 1] - x_nodes[i - 1]
            matrix1[i][i + 1] = x_nodes[i + 2 - 1] - x_nodes[i + 1 - 1]
    matrix1 = np.linalg.inv(matrix1)

    matrix2 = np.zeros(len(x_nodes))
    for i in range(1, len(x_nodes) - 1):
        matrix2[i] = 3 / (x_nodes[i + 2 - 1] - x_nodes[i + 1 - 1]) * (y_nodes[i + 2 - 1] - y_nodes[i + 1 - 1])
        matrix2[i] -= 3 / (x_nodes[i + 1 - 1] - x_nodes[i - 1]) * (y_nodes[i + 1 - 1] - y_nodes[i - 1])

    matrixC = matrix1.dot(matrix2)  # Матрица коэффициентов С

    matrixD = []  # Матрица коэффициентов d
    for i in range(len(x_nodes) - 1):
        matrixD.append((matrixC[i + 1] - matrixC[i]) / (3 * (x_nodes[i + 1] - x_nodes[i])))

    matrixB = []  # Матрица коэффициентов b
    for i in range(len(x_nodes) - 1):
        matrixB.append(((y_nodes[i + 1] - y_nodes[i]) / (x_nodes[i + 1] - x_nodes[i])) - (
                    (x_nodes[i + 1] - x_nodes[i]) * (matrixC[i + 1] + 2 * matrixC[i]) / 3))

    qs_coeff = []
    for i in range(len(x_nodes) - 1):
        qs_coeff.append([y_nodes[i], matrixB[i], matrixC[i], matrixD[i]])

    return qs_coeff


def searchIndexSpline(x, x_nodes):
    if (x < x_nodes[0]):
        return 0
    if (x > x_nodes[len(x_nodes) - 1]):
        return len(x_nodes) - 1

    indexSpline = -1
    index = 0
    while (indexSpline == -1):
        if (x >= x_nodes[index]) and (x <= x_nodes[index + 1]):
            indexSpline = index
        index += 1

    return indexSpline


def qubic_spline(x, qs_coeff, x_nodes):
    res = []
    for i in range(len(x)):
        indexSpline = searchIndexSpline(x[i], x_nodes)
        valueY = qs_coeff[indexSpline][0]
        valueY += qs_coeff[indexSpline][1] * (x[i] - x_nodes[indexSpline])
        valueY += qs_coeff[indexSpline][2] * ((x[i] - x_nodes[indexSpline]) ** 2)
        valueY += qs_coeff[indexSpline][3] * ((x[i] - x_nodes[indexSpline]) ** 3)
        res.append(valueY)

    return (res)


def d_qubic_spline(x, qs_coeff, x_nodes):
    res = []
    for i in range(len(x)):
        indexSpline = searchIndexSpline(x[i], x_nodes)
        valueY = qs_coeff[indexSpline][1] + 2 * qs_coeff[indexSpline][2] * (x[i] - x_nodes[indexSpline])
        valueY += 3 * qs_coeff[indexSpline][3] * ((x[i] - x_nodes[indexSpline]) ** 2)
        res.append(valueY)

    return (res)


x_nodes = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]
y_nodes = [3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02]

qs_coeff = qubic_spline_coeff(x_nodes, y_nodes)

x_max = x_nodes[len(x_nodes) - 1]
x_min = x_nodes[0]
x = np.linspace(x_min, x_max, (x_max - x_min)*100, endpoint=True)

#График кубического сплайна
plt.figure(dpi=300)
plt.scatter(x_nodes, y_nodes, color="red", marker="o")
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, qubic_spline(x, qs_coeff, x_nodes), color="blue", linewidth=1.0, label="S(x)", linestyle="-")
plt.savefig('CubicSpline.svg')
plt.legend()

plt.show()

#График первой производной кубического сплайна
plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, d_qubic_spline(x, qs_coeff, x_nodes), color="blue", linewidth=1.0, label="S'(x)", linestyle="-")
plt.savefig('DiffCubicSpline.svg')
plt.legend()

plt.show()
