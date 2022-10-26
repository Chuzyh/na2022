
#include<bits/stdc++.h>
#include "newton.h"
using namespace std;
Newton_Interpolation f;
int main()
{
    freopen("./data/B.out","w",stdout);
    for(int n=2;n<=8;n+=2)
    {
        vector<double> X,Y;
        for(int i=0;i<=n;i++)
        {
            X.push_back(-5.0+10.0*i/n);
            Y.push_back(1.0/(X[i]*X[i]+1));
        }
        f.init(X,Y);
        for(double x=-5;x<=5;x+=0.01)
            printf("%lf,",f(x));
        puts("");
    }
    for(double x=-5;x<=5;x+=0.01)
        printf("%lf,",1.0/(x*x+1));
    return 0;
}