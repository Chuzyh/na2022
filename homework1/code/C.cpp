#include<bits/stdc++.h>
#include "EquationSolver.h"

const double pi=acos(-1);
const double eps =std::numeric_limits<double>::epsilon();

class F1 : public Function
{
public:
    double operator ()(const double &x)const {return x-tan(x);}
    double diff(const double &x)const {return 1-1/(cos(x)*cos(x));}
}f1;

int main()
{
    NewtonSolver solver1(4.5,eps,f1,64);
    double ans = solver1.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f1(ans));
    NewtonSolver solver2(7.7,eps,f1,64);
    ans = solver2.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f1(ans));
    return 0;
}