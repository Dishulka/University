import numpy as np
import matplotlib.pyplot as plt


def qubic_spline_coeff(x_nodes, y_nodes):
    matrix_1 = np.zeros((len(x_nodes), len(x_nodes)))
    for i in range(len(x_nodes)):
        if (i == 0) or (i == (len(x_nodes) - 1)):
            matrix_1[i][i] = 1
        else:
            matrix_1[i][i] = 2 * (x_nodes[i + 2 - 1] - x_nodes[i - 1])
            matrix_1[i][i - 1] = x_nodes[i + 1 - 1] - x_nodes[i - 1]
            matrix_1[i][i + 1] = x_nodes[i + 2 - 1] - x_nodes[i + 1 - 1]
    matrix_1 = np.linalg.inv(matrix_1)

    matrix_2 = np.zeros(len(x_nodes))
    for i in range(1, len(x_nodes) - 1):
        matrix_2[i] = 3 / (x_nodes[i + 2 - 1] - x_nodes[i + 1 - 1]) * (y_nodes[i + 2 - 1] - y_nodes[i + 1 - 1])
        matrix_2[i] -= 3 / (x_nodes[i + 1 - 1] - x_nodes[i - 1]) * (y_nodes[i + 1 - 1] - y_nodes[i - 1])

    matrix_C = matrix_1.dot(matrix_2)  # Матрица коэффициентов С

    matrix_D = []  # Матрица коэффициентов d
    for i in range(len(x_nodes) - 1):
        matrix_D.append((matrix_C[i + 1] - matrix_C[i]) / (3 * (x_nodes[i + 1] - x_nodes[i])))

    matrix_B = []  # Матрица коэффициентов b
    for i in range(len(x_nodes) - 1):
        matrix_B.append(((y_nodes[i + 1] - y_nodes[i]) / (x_nodes[i + 1] - x_nodes[i])) - (
                (x_nodes[i + 1] - x_nodes[i]) * (matrix_C[i + 1] + 2 * matrix_C[i]) / 3))

    qs_coeff = []
    for i in range(len(x_nodes) - 1):
        qs_coeff.append([y_nodes[i], matrix_B[i], matrix_C[i], matrix_D[i]])

    return qs_coeff


def search_index_spline(x, x_nodes):
    if x < x_nodes[0]:
        return 0
    if x > x_nodes[len(x_nodes) - 1]:
        return len(x_nodes) - 1

    index_spline = -1
    index = 0
    while index_spline == -1:
        if (x >= x_nodes[index]) and (x <= x_nodes[index + 1]):
            index_spline = index
        index += 1

    return index_spline


def qubic_spline(x, qs_coeff, x_nodes):
    res = []
    for i in range(len(x)):
        index_spline = search_index_spline(x[i], x_nodes)
        value_y = qs_coeff[index_spline][0]
        value_y += qs_coeff[index_spline][1] * (x[i] - x_nodes[index_spline])
        value_y += qs_coeff[index_spline][2] * ((x[i] - x_nodes[index_spline]) ** 2)
        value_y += qs_coeff[index_spline][3] * ((x[i] - x_nodes[index_spline]) ** 3)
        res.append(value_y)

    return res


def d_qubic_spline(x, qs_coeff, x_nodes):
    res = []
    for i in range(len(x)):
        index_spline = search_index_spline(x[i], x_nodes)
        value_y = qs_coeff[index_spline][1] + 2 * qs_coeff[index_spline][2] * (x[i] - x_nodes[index_spline])
        value_y += 3 * qs_coeff[index_spline][3] * ((x[i] - x_nodes[index_spline]) ** 2)
        res.append(value_y)

    return res



x_i_nodes = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]
y_i_nodes = [3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02]

qs_coeff = qubic_spline_coeff(x_i_nodes, y_i_nodes)

x_max = x_i_nodes[len(x_i_nodes) - 1]
x_min = x_i_nodes[0]
x = np.linspace(x_min, x_max, (x_max - x_min) * 1000, endpoint=True)

# График кубического сплайна
plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, qubic_spline(x, qs_coeff, x_i_nodes), color="blue", linewidth=1.0, label="S(x)", linestyle="-")
plt.scatter(x_i_nodes, y_i_nodes, color="red", marker="o")
plt.savefig('.\Figures\CubicSpline.svg')
plt.legend()

plt.show()

# График первой производной кубического сплайна
plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, d_qubic_spline(x, qs_coeff, x_i_nodes), color="blue", linewidth=1.0, label="S'(x)", linestyle="-")
plt.savefig('.\Figures\DiffCubicSpline.svg')
plt.legend()

plt.show()
