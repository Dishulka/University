import numpy as np
import scipy
from scipy.optimize import fsolve
import matplotlib.pyplot as plt

C = 1.03439984
T = 1.75418438
g = 9.806


def composite_simpson(a, b, n, f):
    if n % 2 != 0:
        n = n + 1

    h = (b - a) / 2

    x = np.linspace(a, b, n + 1)
    res = f(x[0])
    for i in range(1, n):
        if i % 2 == 0:
            res += (2 * f(x[i]))
        else:
            res += (4 * f(x[i]))

    res += f(x[n])
    res *= h / 3

    return res


def composite_trapezoid(a, b, n, f):
    h = (b - a) / 2

    x = np.linspace(a, b, n + 1)
    res = f(x[0])
    for i in range(1, n):
        res += 2 * f(x[i])
    res += f(x[n])
    res *= h / 2.

    return res


def find_t_from_x_t(t, x):
    return C * (t - (np.sin(2 * t) / 2)) - x


def y_x(x_root):
    t = scipy.optimize.fsolve(find_t_from_x_t, 0, x_root)
    return C * (1 / 2 - (np.cos(2 * t) / 2))


def diff_function_y_t(x_root):
    t = scipy.optimize.fsolve(find_t_from_x_t, 0, x_root)

    y_t = C * np.sin(2 * t)
    x_t = C * (1 - np.cos(2 * t))

    return y_t / x_t


def functional(x_root):
    return np.sqrt((1 + diff_function_y_t(x_root) ** 2) / (2 * g * y_x(x_root)))


def simpson_error(a, b, h):
    res = []
    for i in range(len(h)):
        res.append((b - a) * (h[i] ** 4) / 180)
    return res


def trapezoid_error(a, b, h):
    res = []
    for i in range(len(h)):
        res.append((b - a) * (h[i] ** 2) / 12)
    return res


a = 0.001
b = 2
n = 100

if (n < 3) or (n > 9999):
    print("n - количество точек. 2 < n < 10000")
    n = 3

for i in range(3, n + 1):
    print("n = ", i)
    print("Integral calculated by simpson:", composite_simpson(0.001, 2, i, functional), ", by trapezoid:",
          composite_trapezoid(0.001, 2, i, functional))

h = []
for i in range(3, 10000):
    h.append((b - a) / i)

# График абсолютной погрешности метода Симпсона от шага интегрирования
plt.figure(dpi=300)
plt.xlabel('h')
plt.ylabel('E')
plt.grid()

h_for_scaling = np.linspace(0.01, 2, 10)
plt.loglog(h_for_scaling, h_for_scaling ** 4, '-k', linewidth=4, label=r'$O(h^4)$')

plt.loglog(h, simpson_error(a, b, h), 'o', label='composite simpson')
plt.legend()
plt.savefig('.\Figures\Simpson.svg')

plt.show()

# График абсолютной погрешности метода трапеций от шага интегрирования
plt.figure(dpi=300)
plt.xlabel('h')
plt.ylabel('E')
plt.grid()

h_for_scaling = np.linspace(0.01, 2, 10)
plt.loglog(h_for_scaling, h_for_scaling ** 2, '-k', linewidth=4, label=r'$O(h^2)$')

plt.loglog(h, trapezoid_error(a, b, h), 'o', label='composite trapezoid')
plt.legend()
plt.savefig('.\Figures\Trapezoid.svg')

plt.show()







