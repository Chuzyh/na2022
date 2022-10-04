#include<bits/stdc++.h>
#include "EquationSolver.h"

const double pi=acos(-1);
const double eps =std::numeric_limits<double>::epsilon();

class F1 : public Function
{
public:
    double operator ()(const double &x)const {return 1.0/x-tan(x);}
}f1;
void solve1()
{
    BisectionSolver solver(0,pi/2,eps,eps,f1,64);
    double ans = solver.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f1(ans));
}


class F2 : public Function
{
public:
    double operator ()(const double &x)const {return 1.0/x-pow(2,x);}
}f2;
void solve2()
{
    BisectionSolver solver(0,1,eps,eps,f2,64);
    double ans = solver.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f2(ans));
}

class F3 : public Function
{
public:
    double operator ()(const double &x)const {return pow(2,-x)+exp(x)+2*cos(x)-6;}
}f3;
void solve3()
{
    BisectionSolver solver(1,3,eps,eps,f3,64);
    double ans = solver.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f3(ans));
}

class F4 : public Function
{
public:
    double operator ()(const double &x)const {return (x*x*x+4*x*x+3*x+5)/(2*x*x*x-9*x*x+18*x-2);}
}f4;
void solve4()
{
    BisectionSolver solver(0,4,eps,eps,f4,64);
    double ans = solver.solve();
    printf("root=%.9lf f(root)=%.9lf\n",ans,f4(ans));
}



int main()
{
    printf("task1:\t1/x-tan(x)\n");
    solve1();
    printf("task2:\t1/x-2^x\n");
    solve2();
    printf("task3:\t2^{-x}+e^x+2cosx-6\n");
    solve3();
    printf("task4:\t(x*x*x+4*x*x+3*x+5)/(2*x*x*x-9*x*x+18*x-2)\n");
    solve4();
    return 0;
}