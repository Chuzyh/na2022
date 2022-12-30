#include<bits/stdc++.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
using namespace Eigen;
using namespace std;
const double EPS=1e-7;
class Function
{
    public:
        virtual double operator () (const double &x) const =0;
        virtual double diff(const double &x) 
        const{
            return ((*this)(x+EPS)-(*this)(x-EPS))/(EPS*2);
        }
        virtual double diff2(const double &x) 
        const{
            return ((*this).diff(x+EPS)-(*this).diff(x-EPS))/(EPS*2);
        }
};
class Interpolation
{
public:
    virtual void solve() = 0;
    virtual double operator () (const double &x) const =0;
};
class Polynomial : public Function
{
private:
    vector<double> Co;
    double x_0;
public:
    Polynomial(){}
    Polynomial(const Polynomial & p):Co(p.Co), x_0(p.x_0) {}
    Polynomial(const vector<double> &_Co,const double _x_0): Co(_Co), x_0(_x_0){}
    double operator() (const double &x)const
    {
        int n=Co.size();double re=0;double _x=x-x_0;
        for(int i=n-1;i>=0;i--)re=Co[i]+re*_x;
        return re;
    }
    double X0(){return x_0;}
};
class B_spline_base : public Function
{
private:
    vector<double> t;
    int k;
public:
    B_spline_base(){}
    B_spline_base(vector<double> _t,int _k): t(_t),k(_k)
    {
        if(k!=t.size()-2)cerr<<"error: wrong order or t's size!"<<endl,exit(-1);
    }
    void update(vector<double> _t,int _k){t=_t;k=_k;}
    
    double operator() (const double &x)const
    {
        if(k==1)
        {
            if(x<t[1])return max(0.0,(x-t[0])/(t[1]-t[0]));
            else return max(0.0,(t[2]-x)/(t[2]-t[1]));
        }
        vector<double> t1(t.begin(), t.end() - 1);
        vector<double> t2(t.begin() + 1, t.end());
        B_spline_base B1(t1,k-1);
        B_spline_base B2(t2,k-1);
        return (x-t[0])*B1(x)/(t[k]-t[0])+(t[k+1]-x)*B2(x)/(t[k+1]-t[1]);
    }
};

class ppForm_spline
{
private:
    vector<double> t;
    vector<Polynomial> P;
public:
    ppForm_spline() {}
    
    ppForm_spline(const vector<double> &_x,const vector<Polynomial> &_P){P=_P;t=_x;}
    void update(vector<double> _t,vector<Polynomial> _P){t=_t;P=_P;}
    double operator () (const double &x)const
    {
        if(t.size()==0)cerr<<"error: not uninitialized!"<<endl,exit(-1);
        if(x<t.front()||x>t.back())cerr<<"error: can't interpolate!"<<endl,exit(-1);
        //return P[1](x);
        for(int i=0;i<t.size()-1;i++)
            if(x<=t[i+1])return P[i](x);
        return P[t.size()-1](x);
    }
};
class Discrete_function : public Function
{
private:
    vector<double> x,f,fd,fd2;
public:
    Discrete_function(vector<double> &x,vector<double> &f):x(x),f(f){}
    Discrete_function(vector<double> &x,vector<double> &f,vector<double> &fd):x(x),f(f),fd(fd){}
    Discrete_function(vector<double> &x,vector<double> &f,vector<double> &fd,vector<double> &fd2):x(x),f(f),fd(fd),fd2(fd2){}
    double operator()(const double &_x)const
    {
        for(int i=0;i<x.size();i++)
        if(fabs(x[i]-_x)<EPS)return f[i];
        cerr<<"error: no this point!"<<endl,exit(-1);
    }
    double diff(const double &_x)const
    {
        for(int i=0;i<x.size();i++)
        if(fabs(x[i]-_x)<EPS)return fd[i];
        cerr<<"error: no this point!"<<endl,exit(-1);
    }
    double diff2(const double &_x)const
    {
        for(int i=0;i<x.size();i++)
        if(fabs(x[i]-_x)<EPS)return fd2[i];
        cerr<<"error: no this point!"<<endl,exit(-1);
    }
};
class ppForm_interpolation : public Interpolation
{
private:
    ppForm_spline P;
    Function &f;  //待插值函数
    int n,condition,order;//condition 边值条件；order 基函数阶数
    vector<double> x;
public:
    ppForm_interpolation(Function &_f,vector<double> &_x,int _order,int _condi):f(_f),x(_x),order(_order),condition(_condi)
    {
        if (!(condition>=1&&condition<=3||order==1))cerr<<"error: unavailable condition!"<<endl,exit(-1);
        if (!(order==1||order==3))cerr<<"error: unavailable order!"<<endl,exit(-1);
        n=x.size();
    }
    void solve()
    {
        if(order==3)
        {
            SparseMatrix<double> A(n,n);
            vector<Triplet<double> > a;
            MatrixXd b(n,1);
            b=MatrixXd::Zero(n,1);
            for(int i=1;i<n-1;i++)
            {
                double lam=(x[i+1]-x[i])/(x[i+1]-x[i-1]);
                double miu=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
                a.push_back(Triplet<double>(i,i-1,lam));
                a.push_back(Triplet<double>(i,i,2));
                a.push_back(Triplet<double>(i,i+1,miu));
                b(i,0)=(f(x[i+1])-f(x[i]))/(x[i+1]-x[i])*miu*3+(f(x[i])-f(x[i-1]))/(x[i]-x[i-1])*lam*3;
            }
            if(condition==1)
            {
                a.push_back(Triplet<double>(0,0,1));
                a.push_back(Triplet<double>(n-1,n-1,1));
                b(0,0)=f.diff(x[0]);
                //cerr<<b(0,0)<<endl;
                b(n-1,0)=f.diff(x[n-1]);
                //cerr<<b(n-1,0)<<endl;
            }else
            {
                a.push_back(Triplet<double>(0,0,4));
                a.push_back(Triplet<double>(0,1,2));
                a.push_back(Triplet<double>(n-1,n-2,2));
                a.push_back(Triplet<double>(n-1,n-1,4));
            
                b(0,0)=(f(x[1])-f(x[0]))/(x[1]-x[0])*6;
                b(n-1,0)=(f(x[n-1])-f(x[n-2]))/(x[n-1]-x[n-2])*6;
                if(condition==2)
                {
                    b(0,0)-=f.diff2(x[0])*(x[1]-x[0]);
                    b(n-1,0)-=f.diff2(x[n-1])*(x[n-1]-x[n-2]);
                }
            }
            
            A.setFromTriplets(a.begin(),a.end());
            A.makeCompressed();
            //cerr<<A<<endl;
            //cerr<<b<<endl;
            SparseLU<SparseMatrix<double> > Solver;
            Solver.compute(A);
            VectorXd X=Solver.solve(b);

            vector<Polynomial> _P;
            for (int i=1;i<n;i++)
            {
                vector<double> Co;
                double K=(f(x[i])-f(x[i-1]))/(x[i]-x[i-1]);
                Co.push_back(f(x[i-1]));
                Co.push_back(X(i-1));
                Co.push_back((K*3-X(i-1)*2-X(i))/(x[i]-x[i-1]));
                //Co.push_back((X(i-1)+X(i)-K*2)/((t[i]-t[i-1])*(t[i]-t[i-1])));
                Co.push_back((X(i-1)+X(i)-K*2)/pow(x[i]-x[i-1],2));
                
                //cerr<<"new poly"<<Co[0]<<' '<<Co[1]<<" "<<Co[2]<<' '<<Co[3]<<' '<<x[i-1]<<endl;
                Polynomial Po(Co,x[i-1]);
                _P.push_back(Po);//cerr<<i<<" x_0 "<<Po.X0()<<endl;
            }
             P.update(x,_P);
        }else
        {
            vector<double> t(x);
            vector<Polynomial> _P;
            int n=x.size();
            for (int i=1;i<n;i++)
            {
                vector<double> Co;
                //cerr<<x[i]<<' '<<x[i-1]<<endl;
                double K=(f(x[i])-f(x[i-1]))/(x[i]-x[i-1]);//斜率
                Co.push_back(f(x[i])-K*x[i]);
                Co.push_back(K);
                Polynomial Po(Co,0);
                //cerr<<f(x[i-1])<<' '<<Po(x[i-1])<<endl;
                _P.push_back(Po);
            }
            P.update(t,_P);
        }
    }
    double operator () (const double &x)const
    {
        return P(x);
    }
};
class B_spline_interpolation : public Interpolation
{
private:
    vector<B_spline_base> B;
    vector<double> Co;
    Function &f;  //待插值函数
    int n,condition,order;//condition 边值条件；order 基函数阶数
    vector<double> x,front_point,end_point;
public:
    B_spline_interpolation(Function &_f,vector<double> &_x,int _order,int _condi):f(_f),x(_x),order(_order),condition(_condi)
    {
        if (!(condition>=1&&condition<=3||order==1))cerr<<"error: unavailable condition!"<<endl,exit(-1);
        if (!(order==1||order==3))cerr<<"error: unavailable order!"<<endl,exit(-1);
        n=x.size();
        
        double del=(x[1]-x[0]);
        if(order==3)
        {
            front_point={x[0]-del*3,x[0]-del*2,x[0]-del};
            end_point={x[n-1]+del,x[n-1]+del*2,x[n-1]+del*3};
        }else
        {
            front_point={x[0]-del};
            end_point={x[n-1]+del};
        }
        x.insert(x.begin(),front_point.begin(),front_point.end());
        x.insert(x.end(),end_point.begin(),end_point.end());
        for(int i=2-order;i<n+1;i++)
        {
            vector<double> X(x.begin()+i-2+order,x.begin()+i+2*order);
            B_spline_base Bi(X,order);
            B.push_back(Bi);
        }
    }
    void solve()
    {
        if(order==3)
        {
            SparseMatrix<double> A(n+2,n+2);
            vector<Triplet<double> > a;
            MatrixXd b(n+2,1);
            b=MatrixXd::Zero(n+2,1);
            for(int i=1;i<n+1;i++)
            {
                a.push_back(Triplet<double>(i,i-1,B[i-1](x[i+2])));
                a.push_back(Triplet<double>(i,i,B[i](x[i+2])));
                a.push_back(Triplet<double>(i,i+1,B[i+1](x[i+2])));
                b(i,0)=f(x[i+2]);
            }
            
            if(condition==1)
            {
                B_spline_base B0({x[1],x[2],x[3],x[4]},2);
                B_spline_base B1({x[2],x[3],x[4],x[5]},2);
                B_spline_base Bn_minus1(vector<double>(x.end()-6, x.end()-2),2);
                B_spline_base Bn(vector<double>(x.end()-5, x.end()-1),2);
                
                a.push_back(Triplet<double>(0,0,-B0(x[3])*3/(x[4]-x[1])));
                a.push_back(Triplet<double>(0,1,B0(x[3])*3/(x[4]-x[1])-B1(x[3])*3/(x[5]-x[2])));
                a.push_back(Triplet<double>(0,2,B1(x[3])*3/(x[5]-x[2])));

                a.push_back(Triplet<double>(n+1,n-1,-Bn_minus1(x[n+2])*3/(x[n+3]-x[n])));
                a.push_back(Triplet<double>(n+1,n,Bn_minus1(x[n+2])*3/(x[n+3]-x[n])-Bn(x[n+2])*3/(x[n+4]-x[n+1])));
                a.push_back(Triplet<double>(n+1,n+1,Bn(x[n+2])*3/(x[n+4]-x[n+1])));
                
                b(0,0)=f.diff(x[3]);
                b(n+1,0)=f.diff(x[n+2]);
            }else
            {
                a.push_back(Triplet<double>(0,0,(x[4]-x[2])/(x[4]-x[1])*6));
                a.push_back(Triplet<double>(0,1,-(x[4]-x[2])/(x[4]-x[1])*6-(x[4]-x[2])/(x[5]-x[2])*6));
                a.push_back(Triplet<double>(0,2,(x[4]-x[2])/(x[5]-x[2])*6));
                
                a.push_back(Triplet<double>(n+1,n-1,(x[n+3]-x[n+1])/(x[n+3]-x[n])*6));
                a.push_back(Triplet<double>(n+1,n,-(x[n+3]-x[n+1])/(x[n+3]-x[n])*6-(x[n+3]-x[n+1])/(x[n+4]-x[n+1])*6));
                a.push_back(Triplet<double>(n+1,n+1,(x[n+3]-x[n+1])/(x[n+4]-x[n+1])*6));
                if(condition==2)b(0,0)=f.diff2(x[3]),b(n+1,0)=f.diff2(x[n+2]);
                
            }
            A.setFromTriplets(a.begin(),a.end());
            A.makeCompressed();
            //cerr<<"ok"<<endl;
            //cerr<<A<<endl;
            //cerr<<b<<endl;
            SparseLU<SparseMatrix<double> > Solver;
            Solver.compute(A);
            VectorXd X=Solver.solve(b);
            Co.resize(n+2);
            for(int i=0;i<n+2;i++)Co[i]=X(i,0);
            //cerr<<"ok"<<endl;
        }else
        {
            for(int i=0;i<n;i++)Co.push_back(f(x[i+1]));
        }
    }
    double operator () (const double &x)const
    {
        double re=0;
        for(int i=0;i<Co.size();i++)re+=Co[i]*B[i](x);
        return re;
    }
};
class curve_spline  : public Interpolation
{
private:
    vector<vector<double> > data,result;
    int order,condition,type,k,n,number_of_point;
    vector<double> cumulative_chordal_length;
public:
    curve_spline(std::vector<vector<double> > _data,int _order,int _condi,int _num,int _ty):type(_ty),data(_data),order(_order),condition(_condi),number_of_point(_num)
    {
        if (!(condition>=1&&condition<=3||order==1))cerr<<"error: unavailable condition!"<<endl,exit(-1);
        if (!(order==1||order==3))cerr<<"error: unavailable order!"<<endl,exit(-1);
        k=data[0].size();
        n=data.size();
    }
    double dis(vector<double> x,vector<double> y)
    {
        double re=0;
        if(x.size()!=y.size())cerr<<"error: different dimention!"<<endl,exit(-1);
        for(int i=0;i<k;i++)re+=(x[i]-y[i])*(x[i]-y[i]);
        return sqrt(re);
    }
    void solve()
    {
        cumulative_chordal_length.push_back(0);
        for(int i=1;i<n;i++)cumulative_chordal_length.push_back(cumulative_chordal_length[i-1]+dis(data[i],data[i-1]));
        vector<Discrete_function> F;double del=cumulative_chordal_length[n-1]/number_of_point;
        for(int i=0;i<k;i++)
        {
            vector<double> f,fd,fd2;fd.resize(n);fd2.resize(n);
            for(int j=0;j<n;j++)f.push_back(data[j][i]);
            for(int j=1;j<n-1;j++)fd[j]=(f[i+1]-f[i-1])/(cumulative_chordal_length[i+1]-cumulative_chordal_length[i-1]);
            for(int j=1;j<n-1;j++)fd2[j]=(fd[i+1]-fd[i-1])/(cumulative_chordal_length[i+1]-cumulative_chordal_length[i-1]);
            
            F.push_back(Discrete_function(cumulative_chordal_length,f,fd,fd2));
        }
        result.resize(number_of_point);
        if(type==0)
        {
            for(int i=0;i<k;i++)
            {
                
                B_spline_interpolation B(F[i],cumulative_chordal_length,order,condition);
                B.solve();
                for(int j=0;j<number_of_point;j++) result[j].push_back(B(j*del));  
            }
        }else
        {
            for(int i=0;i<k;i++)
            {
                ppForm_interpolation B(F[i],cumulative_chordal_length,order,condition);
                B.solve();
                for(int j=0;j<number_of_point;j++) result[j].push_back(B(j*del));  
            }
        }
    }
    vector<vector<double> > get_result(){return result;}
    double operator() (const double &x)const
    {
        cerr<<"error: not supported operator!"<<endl,exit(-1);
    }
};