#include<bits/stdc++.h>
using namespace std;

double f(double x)
{
    double re=0;
    re+=x*x*x*x*x*x*x*x;
    re+=x*x*x*x*x*x*x*(-8);
    re+=x*x*x*x*x*x*28;
    re+=x*x*x*x*x*(-56);
    re+=x*x*x*x*70;
    re+=x*x*x*(-56);
    re+=x*x*28;
    re+=x*(-8);
    re+=1;
    return re;
}
double g(double x)
{
    return  (((((((x - 8)*x + 28)*x - 56)*x + 70)*x - 56)*x + 28)*x - 8)*x + 1;
}
double h(double x)
{
    return (x-1)*(x-1)*(x-1)*(x-1)*(x-1)*(x-1)*(x-1)*(x-1);
}
int main()
{
    int tot=0;
    freopen("./data/A.out","w",stdout);
    for(double x=0.99;x<=1.01;x+=0.0002)
        printf("%.18lf,",f(x)),tot++;
    puts("");
    for(double x=0.99;x<=1.01;x+=0.0002)
        printf("%.18lf,",g(x));
    puts("");
    for(double x=0.99;x<=1.01;x+=0.0002)
        printf("%.18lf,",h(x));
    puts("");
    
    cerr<<tot<<endl;
    return 0;
}