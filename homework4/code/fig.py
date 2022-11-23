import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
plt.switch_backend('agg')
t=pd.read_csv("./data/A.out",header=None)
x=np.arange(0.99,1.01,0.0002)
plt.figure()
for i in range(0,3):
    yi=t.iloc[i,0:101]
    plt.plot(x,yi)

l=[]
l.insert(1,"f(x)")
l.insert(2,"g(x)")
l.insert(3,"h(x)")

plt.legend(l)
plt.savefig('./pic/A.eps')

plt.figure()
f=open('./data/B.out','r')
normal = list(map(float, f.readline().split()))
f.close()
f=open('./data/subB.out','r')
subnormal = list(map(float, f.readline().split()))
f.close()
normal, subnormal = np.asarray(normal), np.asarray(subnormal)
y1 = np.zeros([len(normal)])
y2 = np.zeros([len(subnormal)])
plt.title('normalized FPN')
plt.scatter(normal, y1, marker='.')
plt.savefig('./pic/B.eps')
plt.figure()
plt.title('subnormal FPN')
plt.scatter(subnormal, y2, marker='.')
plt.savefig('./pic/sB.eps')