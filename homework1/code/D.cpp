#include<bits/stdc++.h>
#include "EquationSolver.h"

const double pi=acos(-1);
const double eps =std::numeric_limits<double>::epsilon();

class F1 : public Function
{
public:
    double operator ()(const double &x)const {return sin(x/2)-1;}
}f1;
void solve1()
{
    SecandSolver solver(0,pi/2,eps,eps,f1,64);
    double ans = solver.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f1(ans));
}


class F2 : public Function
{
public:
    double operator ()(const double &x)const {return exp(x)-tan(x);}
}f2;
void solve2()
{
    SecandSolver solver(1,1.4,eps,eps,f2,64);
    double ans = solver.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f2(ans));
}

class F3 : public Function
{
public:
    double operator ()(const double &x)const {return x*x*x-12*x*x+3*x+1;}
}f3;
void solve3()
{
    SecandSolver solver(0,-0.5,eps,eps,f3,64);
    double ans = solver.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f3(ans));
}




int main()
{
    printf("task1:\tsin(x/2)-1\n");
    solve1();
    printf("task2:\t1/x-2^x\n");
    solve2();
    printf("task3:\t2^{-x}+e^x+2cosx-6\n");
    solve3();
    return 0;
}