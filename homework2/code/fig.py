import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
plt.switch_backend('agg')
t=pd.read_csv("B.out",header=None)
x=np.arange(-5,5.01,0.01)
plt.figure()
for i in range(0,5):
    yi=t.iloc[i,0:1001]
    plt.plot(x,yi)
l=["n="+str(2+2*i) for i in range(0,4)]
l.insert(5,"true cruve")
plt.legend(l)
plt.savefig('B.eps')