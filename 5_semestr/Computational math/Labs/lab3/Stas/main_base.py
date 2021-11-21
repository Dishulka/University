import matplotlib.pyplot as plt
import numpy as np

from methods import EulerMethod, ImplicitEulerMethod, RungeKuttaMethod


def f_1(v, u, I):
    return 0.04 * v * v + 5 * v + 140 - u + I


def f_2(v, u, mode):
    return mode['a'] * (mode['b'] * v - u)


if __name__ == '__main__':
    h = 0.5
    t_0 = 0
    t_n = 100
    I = 5

    TS = {
        'a': 0.02,
        'b': 0.2,
        'c': -65,
        'd': 6
    }
    PS = {
        'a': 0.02,
        'b': 0.25,
        'c': -65,
        'd': 6
    }
    C = {
        'a': 0.02,
        'b': 0.2,
        'c': -50,
        'd': 2
    }
    FS = {
        'a': 0.1,
        'b': 0.2,
        'c': -65,
        'd': 2
    }
    modes = [TS, PS, C, FS]

    modeNames = [
        "Tonic spiking",
        "Phasic spiking",
        "Chattering",
        "Fast spiking"
    ]

    f = [f_1, f_2]
    t = np.linspace(t_0, t_n, int((t_n - t_0) / h) + 1)

    for i in range(4):
        v_1 = EulerMethod(t_0, t_n, f, h, modes[i], I)[0]
        v_2 = ImplicitEulerMethod(t_0, t_n, f, h, modes[i], I)[0]
        v_3 = RungeKuttaMethod(t_0, t_n, f, h, modes[i], I)[0]

        plt.figure(dpi=300)
        plt.title(modeNames[i])
        plt.xlabel('t')
        plt.ylabel('v', rotation=0)
        plt.grid()
        plt.scatter(t, v_1, color="blue")
        plt.plot(t, v_1, linewidth=1.0, label="Euler method", linestyle="-", color="blue")
        plt.scatter(t, v_2, marker='.', color="violet")
        plt.plot(t, v_2, linewidth=1.0, label="Implicit Euler method", linestyle="--", color="violet")
        plt.scatter(t, v_3, marker='.', color="red")
        plt.plot(t, v_3, linewidth=1.0, label="Runge-Kutta method", linestyle="-", color="red")
        # plt.savefig('.\Plots\Trajectory'+str(i)+'.svg')
        plt.legend()

        plt.show()
