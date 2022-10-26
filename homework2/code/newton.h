#ifndef _NEWTON_H_
#define _NEWTON_H_
#include<bits/stdc++.h>
using namespace std;
class Newton_Interpolation
{
private:
    vector<double> x;
    vector<vector<double> > f;
    int n,intered;
public:
    void init(const vector<double> &X,const vector<double> &Y)
    {
        n=X.size();intered=-1;
        if(Y.size()!=n)
        {
            puts("error:X and Y not have same size!");
            return;
        }
        x=X;f.clear();
        vector<double> tmp;tmp.resize(1);
        for(int i=0;i<n;i++)
        {
            tmp[0]=Y[i];
            f.push_back(tmp);
        }
    }
    void interpolate()
    {
        for(int i=intered+1;i<n;i++)
            for(int j=1;j<=i;j++)
            {
                f[i].push_back((f[i][j-1]-f[i-1][j-1])/(x[i]-x[i-j]));
            }
        intered=n-1;
    }
    double operator()(double X)
    {
        if(intered<n-1)interpolate();
        double re=0,tmp=1;
        for(int i=0;i<n;i++)
        {
            re+=f[i][i]*tmp;
            tmp*=X-x[i];
        }
        return re;
    }
};
#endif