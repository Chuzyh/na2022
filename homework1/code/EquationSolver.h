#ifndef _EQUATION_SOLVER_H_
#define _EQUATION_SOLVER_H_
#include<bits/stdc++.h>
const double EPS=1e-10;
class Function
{
    public:
        virtual double operator () (const double &x) const =0;
        virtual double diff(const double &x) 
        const{
            return ((*this)(x+EPS)-(*this)(x-EPS))/(EPS*2);
        }
};
class EquationSolver
{
    public:
        virtual double solve(){
            return 0;
        }
};

class BisectionSolver : public EquationSolver
{
private:
    double a,b,del,eps;
    Function & f;
    int M;
public:
    BisectionSolver(double a,double b,double del,double eps,Function & F,int M):
        a(a),b(b),del(del),eps(eps),f(F),M(M) {}
    double solve()
    {
        double L=f(a),R=f(b),len,now,nowf;
        for(int i=1;i<=M;i++)
        {
            len=b-a;
            now=a+len/2;
            nowf=f(now);
            if(fabs(len)<del || fabs(nowf)<eps) break;
            else if(L>0&&nowf<0||L<0&&nowf>0)b=now,R=nowf;
            else a=now,L=nowf;
        }
        return now;
    }
};

class NewtonSolver  : public EquationSolver
{
private:
    double x0,eps;
    Function & f;
    int M;
public:
    NewtonSolver (double x0,double eps,Function & F,int M):
        x0(x0),eps(eps),f(F),M(M) {}
    double solve()
    {
        double x=x0,fx,ne;
        for(int i=1;i<=M;i++)
        {
            fx=f(x);
            if(fabs(fx)<eps)break;
            ne=x-fx/f.diff(x);
            if(fabs(x-ne)<eps)break;
            x=ne;
        }
        return x;
    }
};

class SecandSolver  : public EquationSolver
{
private:
    double x0,x1,del,eps;
    Function & f;
    int M;
public:
    SecandSolver (double x0,double x1,double del,double eps,Function & F,int M):
        x0(x0),x1(x1),del(del),eps(eps),f(F),M(M) {}
    double solve()
    {
        double u=f(x1),v=f(x0),k;
        for(int i=1;i<=M;i++)
        {
            if(fabs(u)>fabs(v))
            {
                std::swap(x0,x1);
                std::swap(u,v);
            }
            k=(x1-x0)/(u-v);
            x0=x1,v=u;
            x1=x1-u*k;
            u=f(x1);
            if(fabs(x1-x0)<del||fabs(u)<eps)break;
        }
        return x1;
    }
};



#endif