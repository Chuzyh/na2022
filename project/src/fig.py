import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
plt.switch_backend('agg')
t=pd.read_csv("../data/A.out",header=None)
x=np.arange(-1,1.001,0.001)
plt.figure()
for i in range(0,6):
    yi=t.iloc[i,0:20001]
    plt.plot(x,yi)
l=["true cruve","N=6","N=11","N=21","N=41","N=81"]
plt.legend(l)
plt.savefig('../pic/A.eps')


t=pd.read_csv("../data/A2.out",header=None)
plt.figure()
n=len(t.columns)
X=t.iloc[0,0:n]
Y=t.iloc[1,0:n]
Y=np.log(Y)
Y1=np.log(1/X/X)
Y2=np.log(1/X/X/X)

plt.plot(X,Y)
plt.plot(X,Y1)
plt.plot(X,Y2)
l=["log max error","log N^-2","log N^-3"]
plt.legend(l)
plt.savefig('../pic/A2.eps')


t=pd.read_csv("../data/A3.out",header=None)
plt.figure()
n=len(t.columns)
X=t.iloc[0,0:n]
Y=t.iloc[1,0:n]

plt.plot(X,Y)
l=["log max error ratio"]
plt.legend(l)
plt.savefig('../pic/A3.eps')

t=pd.read_csv("../data/C.out",header=None)
x=np.arange(-5,5.0001,0.001)
plt.figure()
for i in range(0,3):
    yi=t.iloc[i,0:10001]
    plt.plot(x,yi)
l=["true cruve","cubic B-spline","linear B-spline"]
plt.legend(l)
plt.savefig('../pic/C.eps')

t=pd.read_csv("../data/C2.out",header=None)
x=np.arange(-5,5.0001,0.001)
plt.figure()
for i in range(0,2):
    yi=t.iloc[i,0:10001]
    plt.plot(x,yi)
l=["error of cubic B-spline","error of linear B-spline"]
plt.legend(l)
plt.savefig('../pic/C2.eps')

t=pd.read_csv("../data/E.out",header=None)
plt.figure()
for i in range(0,3):
    x=t.iloc[i*2,0:1001]
    yi=t.iloc[i*2+1,0:1001]
    plt.plot(x,yi)
l=["N=10","N=40","N=160"]
plt.legend(l)
plt.savefig('../pic/E.eps')

t=pd.read_csv("../data/E2.out",header=None)
plt.figure()
for i in range(0,3):
    x=t.iloc[i*2,0:1001]
    yi=t.iloc[i*2+1,0:1001]
    plt.plot(x,yi)
l=["N=10","N=40","N=160"]
plt.legend(l)
plt.savefig('../pic/E2.eps')