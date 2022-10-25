
#include<bits/stdc++.h>
#include "newton.h"
using namespace std;
Newton_Interpolation f;
int main()
{
    vector<double> X,Y;
    for(int i=0;i<10;i++)X.push_back(i),Y.push_back(i*i);
    f.init(X,Y);
    for(int i=11;i<=100;i++)cout<<f.estimate(i)<<endl;
    return 0;
}