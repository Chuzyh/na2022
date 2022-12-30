#include <eigen3/Eigen/Dense>
#include<bits/stdc++.h>
#include <jsoncpp/json/json.h>
#include "spline.h"
using namespace std;
class F : public Function
{
public:
    double operator()(const double &x)const 
    {
        return 1/(1+x*x);
    }
    double diff(const double &x)const 
    {
        return -2*x/(1+x*x)/(1+x*x);
    }
    double diff2(const double &x)const 
    {
        return 2*(3*x*x-1)/pow(1+x*x,3);
    }
}f;

double mx[100];
int main()
{
    ifstream ifs("C.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    vector<double> x1,x2;
    for(int i=0;i<obj["x1"].size();i++)x1.push_back(obj["x1"][i].asDouble());
    for(int i=0;i<obj["x2"].size();i++)x2.push_back(obj["x2"][i].asDouble());
    
    double L=obj["L"].asDouble();
    double R=obj["R"].asDouble();
    freopen("../data/C.out","w",stdout);
    for(double X=L;X<=R;X+=0.001)printf("%lf,",f(X));puts("");
    B_spline_interpolation line1(f,x1,3,1);
    B_spline_interpolation line2(f,x2,1,1);
    line1.solve();
    line2.solve();
    for(double X=L;X<=R;X+=0.001)printf("%lf,",line1(X));puts("");
    for(double X=L;X<=R;X+=0.001)printf("%lf,",line2(X));puts("");
    fclose(stdout);
    freopen("../data/C2.out","w",stdout);
    for(double X=L;X<=R;X+=0.001)printf("%lf,",fabs(f(X)-line1(X)));puts("");
    for(double X=L;X<=R;X+=0.001)printf("%lf,",fabs(f(X)-line2(X)));puts("");
    return 0;
}