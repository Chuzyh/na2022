import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
plt.switch_backend('agg')
t=pd.read_csv("./data/B.out",header=None)
x=np.arange(-5,5.01,0.01)
plt.figure()
for i in range(0,5):
    yi=t.iloc[i,0:1001]
    plt.plot(x,yi)
l=["n="+str(2+2*i) for i in range(0,4)]
l.insert(5,"true cruve")
plt.legend(l)
plt.savefig('./pic/B.eps')

t=pd.read_csv("./data/C.out",header=None)
x=np.arange(-1,1.01,0.01)
plt.figure()
for i in range(0,5):
    yi=t.iloc[i,0:201]
    plt.plot(x,yi)
l=["n="+str(5+5*i) for i in range(0,4)]
l.insert(5,"true cruve")
plt.legend(l)
plt.savefig('./pic/C.eps')

t=pd.read_csv("./data/D_dis.out",header=None)
x=np.arange(0,12.01,0.01)
plt.figure()
for i in range(0,1):
    yi=t.iloc[i,0:1201]
    plt.plot(x,yi)
l=["distance"]
plt.legend(l)
plt.savefig('./pic/D_dis.eps')

t=pd.read_csv("./data/D_speed.out",header=None)
x=np.arange(0,12.01,0.01)
plt.figure()
for i in range(0,1):
    yi=t.iloc[i,0:1201]
    plt.plot(x,yi)
l=["speed"]
plt.legend(l)
plt.savefig('./pic/D_speed.eps')

t=pd.read_csv("./data/E_1.out",header=None)
x=np.arange(0,28.01,0.01)
plt.figure()
for i in range(0,2):
    yi=t.iloc[i,0:2801]
    plt.plot(x,yi)
l=["sp"+str(i+1) for i in range(0,2)]
plt.legend(l)
plt.savefig('./pic/E_1.eps')

t=pd.read_csv("./data/E_2.out",header=None)
x=np.arange(0,50.01,0.01)
plt.figure()
for i in range(0,2):
    yi=t.iloc[i,0:5001]
    plt.plot(x,yi)
l=["sp"+str(i+1) for i in range(0,2)]
plt.legend(l)
plt.savefig('./pic/E_2.eps')