#include<bits/stdc++.h>
using namespace std;

class FPN
{
private:
    int beta,p,L,U;
public:
    FPN(int _beta,int _p,int _L,int _U):
        beta(_beta),p(_p),L(_L),U(_U) {};

    void get_UFL_OFL()
    {
        double UFL=pow(beta,L),OFL=pow(beta,U)*(beta-pow(beta,1-p));
        cout<<"UFL="<<UFL<<" OFL="<<OFL<<endl;
    }
    vector<double> get_normal()
    {
        vector<double> re;
        for(int i=L;i<=U;i++)
        {
            for(int j=0;j<(1<<(p-1));j++)
            {
                re.push_back(((double)j/(1<<(p-1))+1)*pow(beta,i));
                re.push_back(-((double)j/(1<<(p-1))+1)*pow(beta,i));
                
            }
        }
        re.push_back(0);
        sort(re.begin(),re.end());
        return re;
    }
    void print_normal()
	{
		vector<double> all_num=get_normal();
		cerr << "normalized FPN system size:"<<all_num.size() << endl;
		for (int i = 0; i < all_num.size(); i++)
			cout << all_num[i] << " ";
		cout << endl;
	}
    vector<double> get_subnormal()
    {
        vector<double> re;
        for(int i=L;i<=L;i++)
        {
            for(int j=1;j<(1<<(p-1));j++)
            {
                re.push_back(((double)j/(1<<(p-1)))*pow(beta,i));
                re.push_back(-((double)j/(1<<(p-1)))*pow(beta,i));
                
            }
        }
        sort(re.begin(),re.end());
        return re;
    }
    void print_subnormal()
	{
		vector<double> all_num=get_subnormal();
		cerr << "subnormal FPN system size:"<<all_num.size() << endl;
		for (int i = 0; i < all_num.size(); i++)
			cout << all_num[i] << " ";
		cout << endl;
	}
};
int main()
{
    FPN F(2,3,-1,1);
    F.get_UFL_OFL();

    freopen("./data/B.out","w",stdout);
    F.print_normal();
    freopen("./data/subB.out","w",stdout);
    F.print_subnormal();
    return 0;
}