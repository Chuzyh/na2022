#include<bits/stdc++.h>
using namespace std;

double f(double x)
{
    if(x<0)return 0;
    if(x<1)return x*x/2;
    if(x<2)return x*(2-x)/2+(3-x)*(x-1)/2;
    if(x<3)return (x-3)*(x-3)/2;
    return 0;
    
}
int main()
{
    freopen("./data/e.out","w",stdout);
    for(double x=-1;x<=5;x+=0.01)
    {
        printf("%lf,",f(x));
    }
    return 0;
}