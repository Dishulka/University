import numpy as np
import matplotlib.pyplot as plt
import statistics as st


def getNormalizedDataMatrix(A):
    m = len(A)
    centerA = (np.eye(m) - 1./m * np.ones((m, m))) @ A
    return centerA


def excludeNullNumbers(num, vec):
    excludeIndex = []
    for i in range(len(num)):
        if abs(num[i]) < 10e-16:
            excludeIndex.append(i)

    num = np.delete(num, excludeIndex)
    vec = np.delete(vec, excludeIndex, 0)

    return num, vec


def principalComponentAnalysis(A):
    selfNumbers, selfVectors = np.linalg.eig(A.T @ A)

    selfNumbers, selfVectors = excludeNullNumbers(selfNumbers, selfVectors)

    for i in range(len(selfNumbers)):
        selfNumbers[i] = np.sqrt(1./(len(A)-1.)) * np.sqrt(selfNumbers[i])

    return selfVectors.T, selfNumbers


def plotData(A, principalComponents, scatter):
    xBar = [np.mean(A[:, 0]), np.mean(A[:, 1])]
    sigmasBar = [st.stdev(A[:, 0]), st.stdev(A[:, 1])]
    ABar = (A - xBar) / sigmasBar

    plt.figure(figsize=(14, 7))

    plt.scatter(ABar[:, 0], ABar[:, 1], c=scatter, s=3)
    plt.plot([0], [0], 'ro', markersize=5)

    maxValue = np.max(np.abs(ABar))
    for principalComponent in principalComponents:
        plt.plot([0, maxValue * principalComponent[0]], [0, maxValue * principalComponent[1]], linewidth=3)

    plt.xlabel(r'$x_1$')
    plt.ylabel(r'$x_2$')
    plt.grid()
    plt.savefig(f'.\Figures\data.svg')
    plt.show()


def plotStandardDeviation(s_d):
    plt.figure(figsize=(14, 7))
    plt.plot(1. + np.arange(len(s_d)), s_d, 'o--')
    plt.xlabel(r'$i$')
    plt.ylabel(r'$\sqrt{\nu} \sigma_i$')
    plt.grid()
    plt.savefig(f'.\Figures\Standard_deviation.svg')
    plt.show()


def readWdbcData():
    with open('wdbc.data', 'r') as f:
        fullData = [[num for num in line.split(',')] for line in f]

    scatter = []
    for row in fullData:
        if row[1] == 'B':
            scatter.append((0, 1, 0))
        else:
            scatter.append((0.5, 0, 1))

    matrix = []
    for row in fullData:
        matrix.append([float(row[i]) for i in range(2, len(fullData[0]))])

    return matrix, scatter


if __name__ == '__main__':
    matrix, scatter = readWdbcData()
    matrix = getNormalizedDataMatrix(matrix)

    mainComponents, standardDeviation = principalComponentAnalysis(matrix)

    plotStandardDeviation(standardDeviation)

    mainComponents2 = mainComponents[:2]
    plotData(matrix @ mainComponents2.T, mainComponents2 @ mainComponents2.T, scatter)
