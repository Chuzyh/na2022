#include<bits/stdc++.h>
#include "NewtonInterpolation.h"
using namespace std;
Newton_Interpolation f;
const double pi=acos(-1);
double F(double x){return 1.0/(1+25*x*x);}
int main()
{
    freopen("./data/C.out","w",stdout);
    for(int n=5;n<=20;n+=5)
    {
        vector<double> X,Y;
        for(int i=0;i<n;i++)
        {
            X.push_back(cos((2.0*(i+1)-1)/2/n*pi));
            Y.push_back(F(X[i]));
        }
        f.init(X,Y);
        for(double x=-1;x<=1;x+=0.01)
            printf("%lf,",f(x));
        puts("");
    }
    for(double x=-1;x<=1;x+=0.01)
        printf("%lf,",F(x));
    return 0;
}