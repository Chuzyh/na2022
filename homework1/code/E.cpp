#include<bits/stdc++.h>
#include "EquationSolver.h"

const double pi=acos(-1);
const double eps =std::numeric_limits<double>::epsilon();

const double L=10,r=1,V=12.4;

class F : public Function
{
public:
    double operator () (const double &h) const{return L*(0.5*pi*r*r-r*r*asin(h/r)-h*sqrt(r*r-h*h))-V;}
    double diff (const double &h) const{return L*(-r/sqrt(1.0-h*h/r/r) - sqrt(r*r-h*h)+h*h*2/ sqrt(r*r-h*h));}
} f;

int main()
{
    NewtonSolver solver1(0,eps,f,64);
    BisectionSolver solver2(0,1,eps,eps,f,64);
    SecandSolver solver3(0,1,eps,eps,f,64);
    double ans1=solver1.solve(),ans2=solver2.solve(),ans3=solver3.solve();
    printf("%.9lf %.9lf %.9lf\n",ans1,ans2,ans3);
    return 0;
}