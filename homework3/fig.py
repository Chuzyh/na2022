import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
plt.switch_backend('agg')
t=pd.read_csv("./data/e.out",header=None)
x=np.arange(-1,5.01,0.01)
plt.figure()
for i in range(0,1):
    yi=t.iloc[i,0:601]
    plt.plot(x,yi)
plt.savefig('./pic/e.eps')