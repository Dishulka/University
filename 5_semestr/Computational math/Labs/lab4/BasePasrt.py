import numpy as np
import matplotlib.pyplot as plt
from data_source import data


# матрица центрированных данных
def get_normalized_data_matrix(A):
    count_rows = A.shape[0]
    A = (np.eye(count_rows) - 1./count_rows * np.ones((count_rows, count_rows))) @ A
    return A


print(data)


#A = get_normalized_data_matrix(data)


#plt.figure(dpi=300)
#plt.xlabel(r'$x_1$', fontsize=16)
#plt.ylabel(r'$x_2$', fontsize=16)
#plt.grid()

#plt.plot(A[:, 0], A[:, 1], 'o')
#plt.plot([0], [0], 'ro', marksize=20)

#plt.legend()
#plt.show()