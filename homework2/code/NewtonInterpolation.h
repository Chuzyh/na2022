#ifndef _NEWTON_H_
#define _NEWTON_H_
#include<bits/stdc++.h>
const double eps=1e-8;
using namespace std;
class Newton_Interpolation
{
private:
    vector<double> x;
    vector<vector<double> > f;
    int n,intered;
    void interpolate()
    {
        for(int i=intered+1;i<n;i++)
            for(int j=1;j<=i;j++)
            {
                f[i].push_back((f[i][j-1]-f[i-1][j-1])/(x[i]-x[i-j]));
            }
        intered=n-1;
    }
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
    void add_node(double &X,double &Y)
    {
        vector<double> tmp;tmp.resize(1);
        tmp[0]=Y;n++;
        f.push_back(tmp);
        x.push_back(X);
    }
    void Hermite_init_and_inter(const vector<double> &X,const vector<vector<double> > &Y)
    {
        if(Y.size()!=X.size())
        {
            puts("error:X and Y not have same size!");
            return;
        }
        n=0;
        for(int i=0;i<X.size();i++)n+=Y[i].size();
        
        f.clear();x.clear();
        
        for(int i=0;i<X.size();i++)
        {
            vector<double> tmp;tmp.clear();
            for(int j=0;j<Y[i].size();j++)
                tmp.push_back(Y[i][j]);
            for(int j=0;j<Y[i].size();j++)
                x.push_back(X[i]),f.push_back(tmp);
        }
        for(int i=0;i<n;i++)
            for(int j=1;j<=i;j++)
            if(fabs(x[i]-x[i-j])>eps)
            {
                if(f[i].size()<=j)f[i].push_back((f[i][j-1]-f[i-1][j-1])/(x[i]-x[i-j]));
                else f[i][j]=((f[i][j-1]-f[i-1][j-1])/(x[i]-x[i-j]));
            }
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