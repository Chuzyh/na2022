#include<bits/stdc++.h>
#include "NewtonInterpolation.h"
using namespace std;
Newton_Interpolation sp1,sp2;
vector<double> X,Y1,Y2;
int main()
{
    int n=7;
    double x,y1,y2;
    freopen("./data/E.in","r",stdin);
    for(int i=1;i<=n;i++)scanf("%lf%lf%lf",&x,&y1,&y2),sp1.add_node(x,y1),sp2.add_node(x,y2),X.push_back(x),Y1.push_back(y1),Y2.push_back(y2);
    freopen("./data/E_1.out","w",stdout);
    for(double x=0;x<=30;x+=0.01)
        printf("%lf,",sp1(x));
    puts("");
    for(double x=0;x<=30;x+=0.01)
        printf("%lf,",sp2(x));
    puts("");
    fclose(stdout);

    for(int i=1;i<=3;i++)X.erase(X.begin()),Y1.erase(Y1.begin()),Y2.erase(Y2.begin());
    sp1.init(X,Y1);
    sp2.init(X,Y2);
    
    freopen("./data/E_2.out","w",stdout);
    for(double x=0;x<=50;x+=0.01)
        printf("%lf,",sp1(x));
    puts("");
    for(double x=0;x<=50;x+=0.01)
        printf("%lf,",sp2(x));
    puts("");
    return 0;
}