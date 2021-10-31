import numpy as np
import scipy
from scipy.misc import derivative
from scipy.optimize import fsolve
import matplotlib.pyplot as plt


def compositeSimpson(a: float, b: float, n: int, func) -> float:
    if n % 2 != 0:
        n = n + 1

    x = np.linspace(a, b, n + 1)
    h: float = abs(a - b) / 2

    result: float = func(x[0])
    for xIn in x[2:-1:2]:
        result = result + 2 * func(xIn)
    for xIn in x[1::2]:
        result = result + 4 * func(xIn)
    result = result + func(x[-1])
    result = result * h / 3.
    return result


def compositeTrapezoid(a: float, b: float, n: int, func) -> float:
    if n % 2 != 0:
        n = n + 1

    x = np.linspace(a, b, n + 1)
    h: float = abs(a - b) / 2

    result: float = func(x[0])
    for xIn in x[1:-1:1]:
        result = result + 2 * func(xIn)
    result = result + func(x[-1])
    result = result * h / 2.

    return result


def yFromX(x: float) -> float:
    def xFromTForRoot(t: float, x: float) -> float:
        C: float = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C: float = 1.03439984
    t = scipy.optimize.fsolve(func=xFromTForRoot, x0=0, args=x)
    return C * (0.5 - 0.5 * np.cos(2 * t))


def yFromX(x: float) -> float:
    def xFromTForRoot(t: float, x: float) -> float:
        C: float = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C: float = 1.03439984
    t = scipy.optimize.fsolve(func=xFromTForRoot, x0=0, args=x)
    return C * (0.5 - 0.5 * np.cos(2 * t))


def deritativeParametr(x: float) -> float:
    def xFromTForRoot(t: float, x: float) -> float:
        C: float = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C: float = 1.03439984
    t: float = scipy.optimize.fsolve(func=xFromTForRoot, x0=0, args=x)

    xt: float = C * (1 - np.cos(2 * t))
    yt: float = C * np.sin(2 * t)

    return yt / xt


def FunctionalParametr(x: float) -> float:
    g: float = 9.80665
    return np.sqrt((1 + deritativeParametr(x) ** 2) / (2 * g * yFromX(x)))


def FunctionalSciPy(x: float) -> float:
    g: float = 9.80665
    return np.sqrt((1 + derivative(func=yFromX, x0=x, n=1, dx=0.0000001) ** 2) / (2 * g * yFromX(x)))


def errrorCompositeSimpson(a, b, h):
    error = []
    for i in range(len(h)):
        error.append((b - a) * (h[i] ** 4) / 180)
    return error


def errorCompositeTrapezoid(a, b, h):
    error = []
    for i in range(len(h)):
        error.append((b - a) * (h[i] ** 2) / 12)
    return error


if __name__ == '__main__':
    # Formulas composite Simpson and composite Trapezoid for n - points (n = 100)
    # 2 methods:  FunctionalSciPy(import derivative) FunctionalParametr(own function for derivative)
    print("Simpson = ", compositeSimpson(0.001, 2, 100, FunctionalSciPy))
    print("Simpson = ", compositeSimpson(0.001, 2, 100, FunctionalParametr))

    print("Trapezoid = ", compositeTrapezoid(0.001, 2, 100, FunctionalSciPy))
    print("Trapezoid = ", compositeTrapezoid(0.001, 2, 100, FunctionalParametr))


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
    plt.loglog(h_scaling, h_scaling ** 2, linewidth=4, label=r'$O(h^2)$', color='red')
    plt.loglog(h_scaling, h_scaling ** 4, '-k', linewidth=4, label=r'$O(h^4)$')
    plt.loglog(h, errrorCompositeSimpson(a, b, h), 'o', label='composite Simpson')
    plt.loglog(h, errorCompositeTrapezoid(a, b, h), 'o', label='composite Trapezoid')
    plt.legend()
    plt.savefig('.\Plots\Error_From_Step.svg')

    plt.show()





