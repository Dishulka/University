import numpy as np
import matplotlib.pyplot as plt


def l_i(j, x, x_nodes):
    baseLagrange = 1
    for k in range(len(x_nodes)):
        if j != k:
            baseLagrange *= ((x - x_nodes[k]) / (x_nodes[j] - x_nodes[k]))

    return baseLagrange


def L(x, x_nodes, y_nodes):
    lagrange = []
    for i in range(len(x)):
        valueLagrange = 0
        for j in range(len(y_nodes)):
            valueLagrange += y_nodes[j] * l_i(j, x[i], x_nodes)
        lagrange.append(valueLagrange)

    return lagrange


def generate_vectors(nodes):
    new_nodes = []
    for i in range(1000):
        Z = np.random.normal(0, 1 / 100, len(nodes))
        new_nodes.append(nodes + Z)

    return new_nodes


def calculate_equations(y_nodes_list):
    len_list_nodes = len(y_nodes_list)
    y_nodes_list = np.sort(y_nodes_list, axis=0)

    h_u = y_nodes_list[len_list_nodes - int((len_list_nodes - (len_list_nodes * 0.9)) / 2) - 1]
    h_l = y_nodes_list[int((len_list_nodes - (len_list_nodes * 0.9)) / 2) - 1]
    h_mean = np.mean(y_nodes_list, axis=0)

    res = [h_u, h_l, h_mean]
    return res


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
        return len(x_nodes) - 2

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


x_i_nodes = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]
y_i_nodes = [3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02]

x_new_nodes_list = generate_vectors(x_i_nodes)
y_new_nodes_list = generate_vectors(y_i_nodes)

x_max = x_i_nodes[len(x_i_nodes) - 1]
x_min = x_i_nodes[0]
x = np.linspace(x_min, x_max, (x_max - x_min) * 1000, endpoint=True)

# Lagrange
plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, L(x, x_i_nodes, y_i_nodes), color="blue", linewidth=1.0, label="L(x)", linestyle="-")
plt.scatter(x_i_nodes, y_i_nodes, color="red", marker="o")
plt.savefig('.\Figures\Lagrange.svg')
plt.legend()

plt.show()

# Lagrange 1000 figures X
lagrange_new_nodes_x = []  # Array of Lagrange values for each 1000 x
for x_new_nodes in x_new_nodes_list:
    lagrange_new_nodes_x.append(L(x, x_new_nodes, y_i_nodes))

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

for lagrange_x in lagrange_new_nodes_x:
    plt.plot(x, lagrange_x, zorder=1)
plt.scatter(x_i_nodes, y_i_nodes, color="red", marker="o", zorder=2)
plt.savefig('.\Figures\Lagrange1000FiguresX.svg')
plt.show()

# Confidence strip Lagrange X
equations_lagrange_x = calculate_equations(lagrange_new_nodes_x)

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, equations_lagrange_x[0], color="red", label="h_u", zorder=1)
plt.plot(x, equations_lagrange_x[1], color="green", label="h_l", zorder=1)
plt.plot(x, equations_lagrange_x[2], color="blue", linestyle="--", label="h_m", zorder=1)
plt.fill_between(x, equations_lagrange_x[0], equations_lagrange_x[1], alpha=0.1, color="blue", zorder=0)
plt.scatter(x_i_nodes, y_i_nodes, color="orange", marker="o", zorder=2)
plt.legend()
plt.savefig('.\Figures\ConfidenceStripLagrangeX.svg')
plt.show()

# Lagrange 1000 figures Y
lagrange_new_nodes_y = []  # Array of Lagrange values for each 1000 y
for y_new_nodes in y_new_nodes_list:
    lagrange_new_nodes_y.append(L(x, x_i_nodes, y_new_nodes))

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

for lagrange_y in lagrange_new_nodes_y:
    plt.plot(x, lagrange_y, zorder=1)
plt.scatter(x_i_nodes, y_i_nodes, color="red", marker="o", zorder=2)
plt.savefig('.\Figures\Lagrange1000FiguresY.svg')
plt.show()

# Confidence strip Lagrange Y
equations_lagrange_y = calculate_equations(lagrange_new_nodes_y)

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, equations_lagrange_y[0], color="red", label="h_u", zorder=1)
plt.plot(x, equations_lagrange_y[1], color="green", label="h_l", zorder=1)
plt.plot(x, equations_lagrange_y[2], color="blue", linestyle="--", label="h_m", zorder=1)
plt.fill_between(x, equations_lagrange_y[0], equations_lagrange_y[1], alpha=0.1, color="blue", zorder=0)
plt.scatter(x_i_nodes, y_i_nodes, color="orange", marker="o", zorder=2)
plt.legend()
plt.savefig('.\Figures\ConfidenceStripLagrangeY.svg')
plt.show()

# cubic splines 1000 figures X
cubic_coeff_new_x = []  # Array of coefficients values for each 1000 x
for x_new_nodes in x_new_nodes_list:
    cubic_coeff_new_x.append(qubic_spline_coeff(x_new_nodes, y_i_nodes))

cubic_new_nodes_x = []
for i in range(len(y_new_nodes_list)):
    cubic_new_nodes_x.append(qubic_spline(x, cubic_coeff_new_x[i], x_new_nodes_list[i]))

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

for cubic_x in cubic_new_nodes_x:
    plt.plot(x, cubic_x, zorder=1)
plt.scatter(x_i_nodes, y_i_nodes, color="red", marker="o", zorder=2)
plt.savefig('.\Figures\Cubic1000FiguresX.svg')
plt.show()

# Confidence strip cubic splines Lagrange X
equations_cubic_x = calculate_equations(cubic_new_nodes_x)

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, equations_cubic_x[0], color="red", label="h_u", zorder=1)
plt.plot(x, equations_cubic_x[1], color="green", label="h_l", zorder=1)
plt.plot(x, equations_cubic_x[2], color="blue", linestyle="--", label="h_m", zorder=1)
plt.fill_between(x, equations_cubic_x[0], equations_cubic_x[1], alpha=0.1, color="blue", zorder=0)
plt.scatter(x_i_nodes, y_i_nodes, color="orange", marker="o", zorder=2)
plt.legend()
plt.savefig('.\Figures\ConfidenceStripCubicX.svg')
plt.show()

# cubic splines 1000 figures Y
cubic_coeff_new_y = []  # Array of coefficients values for each 1000 y
for y_new_nodes in y_new_nodes_list:
    cubic_coeff_new_y.append(qubic_spline_coeff(x_i_nodes, y_new_nodes))

cubic_new_nodes_y = []
for i in range(len(y_new_nodes_list)):
    cubic_new_nodes_y.append(qubic_spline(x, cubic_coeff_new_y[i], x_i_nodes))

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

for cubic_y in cubic_new_nodes_y:
    plt.plot(x, cubic_y, zorder=1)
plt.scatter(x_i_nodes, y_i_nodes, color="red", marker="o", zorder=2)
plt.savefig('.\Figures\Cubic1000FiguresY.svg')
plt.show()

# Confidence strip cubic splines  Y
equations_cubic_y = calculate_equations(cubic_new_nodes_y)

plt.figure(dpi=300)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.plot(x, equations_cubic_y[0], color="red", label="h_u", zorder=1)
plt.plot(x, equations_cubic_y[1], color="green", label="h_l", zorder=1)
plt.plot(x, equations_cubic_y[2], color="blue", linestyle="--", label="h_m", zorder=1)
plt.fill_between(x, equations_cubic_y[0], equations_cubic_y[1], alpha=0.1, color="blue", zorder=0)
plt.scatter(x_i_nodes, y_i_nodes, color="orange", marker="o", zorder=2)
plt.legend()
plt.savefig('.\Figures\ConfidenceStripCubicY.svg')
plt.show()