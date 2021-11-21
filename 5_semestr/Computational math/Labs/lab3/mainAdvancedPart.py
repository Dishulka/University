import matplotlib.pyplot as plt
import numpy as np

num_active = 800
num_passive = 200

a = 0.02 + 0.08 * np.random.uniform(low=0, high=1, size=num_passive)
b = 0.25 - 0.05 * np.random.uniform(low=0, high=1, size=num_passive)
c = -65. + 15. * (np.random.uniform(low=0, high=1, size=num_active) ** 2.)
d = 8. - 6. * (np.random.uniform(low=0, high=1, size=num_active) ** 2.)

neurons = []
for i in range(num_active + num_passive):
    if i < num_active:
        neurons.append([
            0.02,
            0.2,
            c[i],
            d[i]
        ])
    else:
        neurons.append([
            a[i - num_active],
            b[i - num_active],
            -65,
            2
        ])

v_curr = []
u_curr = []

for i in range(num_active + num_passive):
    v_curr.append(-65.)
    u_curr.append(v_curr[i] * neurons[i][1])

active_neurons = 0.5 * np.random.uniform(low=0, high=1, size=(num_active + num_passive, num_active))
passive_neurons = -np.random.uniform(low=0, high=1, size=(num_active + num_passive, num_passive))
W = np.hstack((active_neurons, passive_neurons))

I_active = 5. * np.random.uniform(low=0, high=1, size=num_active)
I_passive = 2. * np.random.uniform(low=0, high=1, size=num_passive)
I = np.concatenate((I_active, I_passive), axis=None)

t_0 = 0
t_n = 1000
h = 0.5

impulse_t = []
impulse_y_neuron = []

t = np.arange(start=t_0, stop=t_n, step=h)
for cur in range(len(t)):
    t_cur = t[cur]
    active = []
    for i in range(num_active + num_passive):
        if v_curr[i] >= 30:
            v_curr[i] = neurons[i][2]
            u_curr[i] += neurons[i][3]

            impulse_t.append(t_cur)
            impulse_y_neuron.append(i)

            active.append(True)

        else:
            active.append(False)


    I_cur = I + np.sum(W[:, active], axis=1)

    for i in range(num_active + num_passive):
        v_curr[i] = v_curr[i] + h * (0.04 * v_curr[i] ** 2 + 5 * v_curr[i] + 140 - u_curr[i] + I_cur[i])
        u_curr[i] = u_curr[i] + h * (neurons[i][0] * (neurons[i][1] * v_curr[i] - u_curr[i]))

plt.figure(figsize=(15, 10))
plt.grid()
plt.xlabel('t')
plt.ylabel('N')
plt.scatter(impulse_t, impulse_y_neuron, marker='.', color="green")
plt.savefig('.\Figures\_NeuronNetwork.svg')
plt.show()
