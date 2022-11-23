import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from math import *

plt.switch_backend('agg')
x = np.linspace(0, 1, 200)
C_f = np.zeros([200])
C_A = np.zeros([200])
for i in range(200):
    C_f[i] = x[i] / (exp(x[i]) + 1)
    C_A[i] = np.e / x[i]

plt.plot(x, C_f, label='C_f')
plt.plot(x, C_A, label='C_A')
plt.savefig('./pic/IX.eps')