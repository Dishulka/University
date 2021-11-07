import numpy as np
import scipy
from scipy.optimize import fsolve
import matplotlib.pyplot as plt


def composite_simpson(a, b, n, function):
    if n % 2 != 0:
        n = n + 1

    x = np.linspace(a, b, n + 1)
    h = (b - a) / 2

    result = function(x[0])
    for i in range(1, n):
        if i % 2 == 0:
            result += (2 * function(x[i]))
    for i in range(1, n):
        if i % 2 != 0:
            result += (4 * function(x[i]))

    result += function(x[-1])
    result *= h / 3.
    return result


def composite_trapezoid(a, b, n, function):
    x = np.linspace(a, b, n + 1)
    h = (b - a) / 2

    result = function(x[0])
    for i in range(1, n):
        result += 2 * function(x[i])
    result += function(x[-1])
    result *= h / 2.

    return result


def t_from_x(t, x):
    C = 1.03439984

    return C * (t - (np.sin(2 * t) / 2)) - x


def y_x(x_root):
    C = 1.03439984

    t = scipy.optimize.fsolve(t_from_x, 0, x_root)
    return C * (1 / 2 - (np.cos(2 * t) / 2))


def diff_y_t(x_root):
    t = scipy.optimize.fsolve(t_from_x, 0, x_root)

    C = 1.03439984

    y_t = C * np.sin(2 * t)
    x_t = C * (1 - np.cos(2 * t))

    return y_t / x_t


def functional(x_root):
    g = 9.806

    return np.sqrt((1 + diff_y_t(x_root) ** 2) / (2 * g * y_x(x_root)))


def error_for_Simpson(a, b, h):
    result = []
    for i in range(len(h)):
        result.append((b - a) * (h[i] ** 4) / 180)
    return result


def error_for_trapezoid(a, b, h):
    result = []
    for i in range(len(h)):
        result.append((b - a) * (h[i] ** 2) / 12)
    return result


a = 0.001
b = 2
h = []
for i in range(3, 10000):
    h.append((b - a) / i)

plt.figure(dpi=300)
plt.grid()
plt.xlabel('h')
plt.ylabel('E', rotation=0)
h_scaling = np.linspace(0.01, 2, 100)
plt.loglog(h_scaling, h_scaling ** 2, linewidth=4, label=r'$O(h^2)$')
plt.loglog(h_scaling, h_scaling ** 4, '-k', linewidth=4, label=r'$O(h^4)$')
plt.loglog(h, error_for_Simpson(a, b, h), 'o', label='composite Simpson')
plt.loglog(h, error_for_trapezoid(a, b, h), 'o', label='composite Trapezoid')
plt.legend()

plt.savefig('.\Plots\GraphHmel.svg')
plt.show()











