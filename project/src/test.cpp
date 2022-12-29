
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
}f1;
int main()
{
 /*Eigen::Matrix<double, 10, 10> A;
 A.setZero();
 A(9, 0) = 1.234;
 std::cout << A << std::endl;
  ifstream ifs("package.json");
      Json::Reader reader;
      Json::Value obj;
      reader.parse(ifs, obj);
      cout << " name " << obj["name"].asString() << endl;
    cout<<f1.diff2(1)<<endl;*/
    freopen("../data/test.out","w",stdout);
    vector<double> x;
    for (double i=-1;i<=1;i+=0.5)x.push_back(i);
    ppForm_interpolation test(f1,x,3,1);
    for(double x=-1;x<=1;x+=0.01)
        printf("%lf,",f1(x));
    test.solve();puts("");
    
    for(double x=-1;x<=1;x+=0.01)
        printf("%lf,",test(x));
}