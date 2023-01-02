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
        return 1/(1+25*x*x);
    }
    double diff(const double &x)const 
    {
        return -50*x/(1+25*x*x)/(1+25*x*x);
    }
    double diff2(const double &x)const 
    {
        return 50*(75*x*x-1)/pow(1+25*x*x,3);
    }
}f;

double mx[100];
int main()
{
    ifstream ifs("A.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    //cout << " name " << obj["L"].asDouble() << endl;
    double L=obj["L"].asDouble();
    double R=obj["R"].asDouble();
    double cond=obj["condition"].asInt();
    double ord=obj["order"].asInt();
    freopen("../data/A.out","w",stdout);
    for(double X=-1;X<=1;X+=0.001)printf("%lf,",f(X));puts("");
    for(int i=0;i<obj["n"].size();i++)
    {
        vector<double> x;
        for (int j=0;j<obj["n"][i].asInt();j++)x.push_back(L+(R-L)/(obj["n"][i].asInt()-1)*j);
        B_spline_interpolation line(f,x,ord,cond);
        line.solve();
        for(double X=-1;X<=1;X+=0.001)printf("%lf,",line(X)),mx[i]=max(mx[i],fabs(f(X)-line(X)));

        puts("");
    }
    fclose(stdout);
    freopen("../data/A2.out","w",stdout);
    for(int i=0;i<obj["n"].size();i++)
    {
        printf("%d,",obj["n"][i].asInt());
    }puts("");
    for(int i=0;i<obj["n"].size();i++)
    {
        printf("%.10lf,",mx[i]);
    }fclose(stdout);
    freopen("../data/A3.out","w",stdout);
    for(int i=1;i<obj["n"].size();i++)
    {
        printf("%d,",i);
    }puts("");
    for(int i=1;i<obj["n"].size();i++)
    {
        printf("%.10lf,",mx[i-1]/mx[i]);
    }
    return 0;
}