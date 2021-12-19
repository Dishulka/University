import numpy as np
import matplotlib.pyplot as plt
import statistics as st
from data_source import data


def get_normalized_data_matrix(A):
    m = len(A)
    A_normalized = (np.eye(m) - 1./m * np.ones((m, m))) @ A
    return A_normalized


def pca(A):
    eigenvalues, eigenvectors = np.linalg.eig(A.T @ A)

    standard_deviation = []
    for i in range(len(eigenvalues)):
        standard_deviation.append(np.sqrt(1./(len(A)-1.)) * np.sqrt(eigenvalues[i]))

    return eigenvectors.T, standard_deviation


def plot_data(A, principal_components):
    plt.figure(dpi=300)

    x_bar = [np.mean(A[:, 0]), np.mean(A[:, 1])]
    sigmas = [st.stdev(A[:, 0]), st.stdev(A[:, 1])]
    A_scaled = (A - x_bar) / sigmas

    color = []
    for row in data:
        if row[1] == 'B':
            color.append((0, 1, 0))
        else:
            color.append((1, 0, 0))

    plt.scatter(A_scaled[:, 0], A_scaled[:, 1], c=color)
    plt.plot([0], [0], 'ko', markersize=5)

    max_value = np.max(np.abs(A_scaled))
    for principal_component in principal_components:
        plt.plot([0, max_value / 1.5 * principal_component[0]], [0, max_value * principal_component[1]], linewidth=4)
    plt.xlabel(r'$x_1$')
    plt.ylabel(r'$x_2$')
    plt.grid()
    plt.savefig(f'.\Figures\data.svg')
    plt.show()


def get_data():
    matrix_data = []
    for row in data:
        characteristics = []
        for i in range(2, len(data[0])):
            characteristics.append(row[i])
        matrix_data.append(characteristics)

    return matrix_data



data_patient = get_data()
data_patient = get_normalized_data_matrix(data_patient)

principal_components, standard_deviation = pca(data_patient)

# Зависимость стандартногго отклонения вдоль главных направлений от номера главного направления
plt.figure(dpi=300)
plt.xlabel('i')
plt.ylabel(r'$\sqrt{\nu} \sigma_i$')
plt.grid()
plt.plot(1. + np.arange(len(standard_deviation)), standard_deviation, 'o--')
plt.savefig(f'.\Figures\Standard_deviation.svg')
plt.show()

principal_components_2 = principal_components[:2]
data_patient_k = data_patient @ principal_components_2.T
# Вывод проекций точек на главные направления
plot_data(data_patient_k, principal_components_2 @ principal_components_2.T)
