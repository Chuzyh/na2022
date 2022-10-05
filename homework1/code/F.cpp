#include<bits/stdc++.h>
#include "EquationSolver.h"

const double pi=acos(-1);
const double eps =std::numeric_limits<double>::epsilon();

const double L=10,r=1,V=12.4;

class F : public Function
{
private:
    double A,B,C,E;
public:
    F(){}
    F(double l,double h,double D,double beta)
    {
        double sin_beta=sin(beta/180*pi);
        double cos_beta=cos(beta/180*pi);
        double tan_beta=tan(beta/180*pi);
        A=l*sin_beta;
        B=l*cos_beta;
        C=(h+D*0.5)*sin_beta-D*tan_beta*0.5;
        E=(h+D*0.5)*cos_beta-D*0.5;
    }
    double operator()(const double &x)const 
    {
        double sx=sin(x);
        double cx=cos(x);
        return A*sx*cx+B*sx*sx-C*cx-E*sx; 
    }
    double diff(const double &x)const 
    {
        double sx=sin(x);
        double cx=cos(x);
        return A*(-sx*sx+cx*cx)+B*sx*cx*2+C*sx-E*cx; 
    }
} f;
void task1()
{
    F f(89,49,55,11.5);
    NewtonSolver solver(33.0/180*pi,eps,f,64);
    double ans=solver.solve();
    printf("ans=%.9lf\n",ans/pi*180);
}
void task2()
{
    F f(89,49,30,11.5);
    NewtonSolver solver(33.0/180*pi,eps,f,64);
    double ans=solver.solve();
    printf("ans=%.9lf\n",ans/pi*180);
}
void task3()
{
    F f(89,49,55,11.5);
    SecandSolver solver(0,pi*3,eps,eps,f,64);
    double ans=solver.solve();
    printf("ans=%.9lf\n",ans/pi*180);
}
int main()
{
    task1();
    task2();
    task3();
    return 0;
}