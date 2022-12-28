#include<bits/stdc++.h>
using namespace std;
const double EPS=1e-7;
class Function
{
    public:
        virtual double operator () (const double &x) const =0;
        virtual double diff(const double &x) 
        const{
            return ((*this)(x+EPS)-(*this)(x-EPS))/(EPS*2);
        }
        virtual double diff2(const double &x) 
        const{
            return ((*this).diff(x+EPS)-(*this).diff(x-EPS))/(EPS*2);
        }
};
class Interpolation
{
public:
    virtual void solve() = 0;
    virtual double operator () (const double &x) const =0;
};
class Polynomial : public Function
{
private:
    vector<double> Co;
    int n;
public:
    Polynomial(){n = 0;}
    Polynomial(const Polynomial & p):Co(p.Co), n(p.n) {}
    Polynomial(const double &x){n=0;Co.push_back(x);}
    Polynomial(const vector<double> _Co,const int _n): Co(_Co), n(_n){}
    double operator() (const double &x)const
    {
        int n=Co.size();double re=0;
        for(int i=n-1;i>=0;i--)re=Co[i]+re*x;
        return re;
    }
};
class B_spline_base : public Function
{
private:
    vector<double> t;
    int k;
public:
    B_spline_base(vector<double> _t,int _k): t(_t),k(_k)
    {
        if(k!=t.size()-2)cerr<<"error: wrong order or t's size!"<<endl,exit(-1);
    }
    double operator() (const double &x)const
    {
        if(k==1)
        {
            if(x<t[1])return max(0.0,(x-t[0])/(t[1]-t[0]));
            else return max(0.0,(t[2]-x)/(t[2]-t[1]));
        }
        vector<double> t1(t.begin(), t.end() - 1);
        vector<double> t2(t.begin() + 1, t.end());
        B_spline_base B1(t1,k-1);
        B_spline_base B2(t2,k-1);
        return (x-t[0])*B1(x)/(t[k]-t[0])+(t[k+1]-x)/(t[k+1]-t[1]);
    }
};

class ppForm_base
{
protected:
    vector<double> t;
    vector<Polynomial> P;
public:
    ppForm_base() {}
    
    ppForm_base(const vector<double> &_x,const vector<Polynomial> &_P){P=_P;t=_x;}
    void update(vector<double> _t,vector<Polynomial> _P){t=_t;P=_P;}
    double operator () (const double &x)const
    {
        if(t.size()==0)cerr<<"error: not uninitialized!"<<endl,exit(-1);
        if(x<t.front()||x>t.back())cerr<<"error: can't interpolate!"<<endl,exit(-1);
        for(int i=0;i<t.size();i++)
            if(x<=t[i+1])return P[i](x);
        return P[t.size()-1](x);
    }
};
class ppForm_interpolation : public Interpolation
{
private:
    ppForm_base P;
    Function &f;  //待插值函数
    int n,condition,order;//condition 边值条件；order 基函数阶数
    vector<double> x;
public:
    ppForm_interpolation(Function &_f,vector<double> &_x,int _order,int _condi):f(_f),x(_x),order(_order),condition(_condi)
    {
        if (!(condition>=1&&condition<=3||order==1))cerr<<"error: unavailable condition!"<<endl,exit(-1);
        if (!(order==1||order==3))cerr<<"error: unavailable order!"<<endl,exit(-1);
        n=x.size();
    }
    void solve()
    {
        if(order==3)
        {

        }else
        {
            vector<double> t(x);
            vector<Polynomial> _P;
            int n=x.size();
            for (int i=1;i<n;i++)
            {
                vector<double> Co;
                //cerr<<x[i]<<' '<<x[i-1]<<endl;
                double K=(f(x[i])-f(x[i-1]))/(x[i]-x[i-1]);//斜率
                Co.push_back(f(x[i])-K*x[i]);
                Co.push_back(K);
                Polynomial Po(Co,1);
                //cerr<<f(x[i-1])<<' '<<Po(x[i-1])<<endl;
                _P.push_back(Po);
            }
            P.update(t,_P);
        }
    }
    double operator () (const double &x)const
    {
        return P(x);
    }
};