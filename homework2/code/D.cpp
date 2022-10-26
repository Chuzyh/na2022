#include<bits/stdc++.h>
#include "NewtonInterpolation.h"
using namespace std;
Newton_Interpolation f;
int main()
{
    vector<double> X{0,3,5,8,13};
    vector<vector<double> > Y{{0,75},{225,77},{383,80},{623,74},{993,72}};
    f.Hermite_init_and_inter(X,Y);
    freopen("./data/D_dis.out","w",stdout);
    for(double x=0;x<=12;x+=0.01)
        printf("%lf,",f(x));
    fclose(stdout);
    freopen("./data/D_speed.out","w",stdout);
    for(double x=0;x<=12;x+=0.01)
        printf("%lf,",(f(x)-f(x-0.01))*100);
    cerr<<f(10)<<' '<<(f(10.01)-f(10-0.01))/0.02<<endl;
    return 0;
}