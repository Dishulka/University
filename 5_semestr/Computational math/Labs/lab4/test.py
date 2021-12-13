import numpy as np
import matplotlib.pyplot as plt


def get_some_data(dim):
    X = np.random.multivariate_normal([3., 2.], [[5., 2.], [2., 3.]], size=1000)
    return X


def get_normalized_data_matrix(A):
    count_rows = A.shape[0]
    A = (np.eye(count_rows) - 1./count_rows * np.ones((count_rows, count_rows))) @ A
    return A


A = get_some_data(2)

plt.figure(dpi=300)
plt.xlabel(r'$x_1$', fontsize=16)
plt.ylabel(r'$x_2$', fontsize=16)
plt.grid()

test1 = A[:, 0]
test2 = A[:, 1]

plt.plot(A[:, 0], A[:, 1], 'o')
plt.plot([0], [0], 'ro', markersize=20)


plt.show()