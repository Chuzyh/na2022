#include <eigen3/Eigen/Dense>
#include<bits/stdc++.h>
#include <jsoncpp/json/json.h>
#include "spline.h"
using namespace std;
class X : public Function
{
public:
    double operator()(const double &x)const 
    {
        return sqrt(3)*sin(x);
    }
}f1;
class Y : public Function
{
public:
    double operator()(const double &x)const 
    {
        return 2.0/3*(sqrt(3)*cos(x)+sqrt(sqrt(3)*fabs(sin(x))));
    }
}f2;

const double pi=acos(-1);
double mx[100];
vector<vector<double> > data;
int main()
{
    ifstream ifs("E.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    
    freopen("../data/E.out","w",stdout);
    for (int i=0;i<obj["n"].size();i++)
    {
        int n=obj["n"][i].asInt();data.clear();
        for(int j=0;j<=n;j++)
        {
            double theta=pi*2*j/n;
            data.push_back(vector<double>{f1(theta),f2(theta)});
        }
        curve_spline C(data,3,1,1000,0);
        C.solve();
        data=C.get_result();
        for(int i=0;i<data.size();i++)
        {
            printf("%lf,",data[i][0]);
        }
        puts("");
        for(int i=0;i<data.size();i++)
        {
            printf("%lf,",data[i][1]);
        }
        puts("");
    }
    fclose(stdout);
    freopen("../data/E2.out","w",stdout);
    for (int i=0;i<obj["n"].size();i++)
    {
        int n=obj["n"][i].asInt();data.clear();
        for(int j=0;j<=n;j++)
        {
            double theta=pi*2*j/n;
            data.push_back(vector<double>{f1(theta),f2(theta)});
        }
        curve_spline C(data,1,1,1000,0);
        C.solve();
        data=C.get_result();
        for(int i=0;i<data.size();i++)
        {
            printf("%lf,",data[i][0]);
        }
        puts("");
        for(int i=0;i<data.size();i++)
        {
            printf("%lf,",data[i][1]);
        }
        puts("");
    }
    
    return 0;
}