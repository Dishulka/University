import numpy as np
import scipy
from scipy.optimize import fsolve
import matplotlib.pyplot as plt

I = 5


def f_1(v, u):
    return 0.04 * v * v + 5 * v + 140 - u + I


def f_2(v, u, mode):
    return mode[0] * (mode[1] * v - u)


def euler(t_0, t_n, f, h, mode):
    m = int((t_n - t_0) / h)

    v = [mode[2]]
    u = [mode[1] * v[0]]

    for i in range(m):
        v.append(v[i] + h * f[0](v[i], u[i]))
        u.append(u[i] + h * f[1](v[i], u[i], mode))

        if v[i + 1] >= 30:
            v[i + 1] = mode[2]
            u[i + 1] += mode[3]

    result = [v, u]

    return result


def implicit_euler_for_v(v, v_i, u_i, f, h):
    return v - v_i - h * f[0](v_i, u_i)


def implicit_euler_for_u(u, v_i, u_i, f, h, mode):
    return u - u_i - h * f[1](v_i, u_i, mode)


def implicit_euler(t_0, t_n, f, h, mode):
    m = int((t_n - t_0) / h)

    v = [mode[2]]
    u = [mode[1] * v[0]]

    for i in range(m):
        v.append(scipy.optimize.fsolve(implicit_euler_for_v, v[i], args=(v[i], u[i], f, h))[0])
        u.append(scipy.optimize.fsolve(implicit_euler_for_u, u[i], args=(v[i], u[i], f, h, mode))[0])

        if v[i + 1] >= 30:
            v[i + 1] = mode[2]
            u[i + 1] += mode[3]

    result = [v, u]

    return result


def runge_kutta(t_0, t_n, f, h, mode):
    m = int((t_n - t_0) / h)

    v = [mode[2]]
    u = [mode[1] * v[0]]

    for i in range(m):
        k_v1 = h * f[0](v[i], u[i])
        k_u1 = h * f[1](v[i], u[i], mode)

        k_v2 = h * f[0](v[i] + (k_v1 / 2), u[i] + (h / 2))
        k_u2 = h * f[1](v[i] + (h / 2), u[i] + (k_u1 / 2), mode)

        k_v3 = h * f[0](v[i] + (k_v2 / 2), u[i] + (h / 2))
        k_u3 = h * f[1](v[i] + (h / 2), u[i] + (k_u2 / 2), mode)

        k_v4 = h * f[0](v[i] + k_v3, u[i] + h)
        k_u4 = h * f[1](v[i] + h, u[i] + k_u3, mode)

        v.append(v[i] + (1 / 6) * (k_v1 + 2 * k_v2 + 2 * k_v3 + k_v4))
        u.append(u[i] + (1 / 6) * (k_u1 + 2 * k_u2 + 2 * k_u3 + k_u4))

        if v[i + 1] >= 30:
            v[i + 1] = mode[2]
            u[i + 1] += mode[3]

    result = [v, u]

    return result


h = 0.5
t_0 = 0
t_n = 100

modeTS = [0.02, 0.2, -65, 6]
modePS = [0.02, 0.25, -65, 6]
modeC = [0.02, 0.2, -50, 2]
modeFS = [0.1, 0.2, -65, 2]
modes = [modeTS, modePS, modeC, modeFS]

f = [f_1, f_2]
t = np.linspace(t_0, t_n, int((t_n - t_0) / h) + 1)

for i in range(4):
    v_1 = euler(t_0, t_n, f, h, modes[i])[0]
    v_2 = implicit_euler(t_0, t_n, f, h, modes[i])[0]
    v_3 = runge_kutta(t_0, t_n, f, h, modes[i])[0]

    plt.figure(dpi=300)
    plt.xlabel('t')
    plt.ylabel('v')
    plt.grid()

    plt.plot(t, v_1, linewidth=1.0, label="euler", linestyle="-")
    plt.plot(t, v_2, linewidth=1.0, label="implicit euler", linestyle="--")
    plt.plot(t, v_3, linewidth=1.0, label="runge-kutta", linestyle="-")
    plt.legend()
    plt.savefig(f'.\Figures\Trajectory{i+1}.svg')
    plt.show()
