//NA 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <limits>

double eps=std::numeric_limits<double>::epsilon();

int binarnaPretraga(const std::vector<std::pair<double,double>> &veka, double x, int l, int h)
{
    while(l<=h)
    {
        int sred=(l+h)/2;
        if(x>veka[sred].first && x<=veka[sred+1].first) return sred;
        else if(veka[sred].first>=x && veka[sred+1].first>x) return binarnaPretraga(veka, x, l, sred-1);
        else return binarnaPretraga(veka,x,sred+1, h);
    }
}

class AbstractInterpolator
{
protected:
    std::vector<std::pair<double,double>> veka;
    mutable int indeks=1;
    int Locate(double x) const
    {
        if(veka[0].first>=x) return 0; //nije u intervalu
        if(x>veka[veka.size()-1].first) return veka.size();
        if(x>=veka[indeks-1].first && x<veka[indeks-1].first) return indeks;
        indeks=binarnaPretraga(veka,x,0,veka.size()-1)+1;
        return indeks;
    }
public:
    AbstractInterpolator(const std::vector<std::pair<double, double>> &data)
    {
        veka=data;
        std::sort(veka.begin(), veka.end(), [](std::pair<double,double> br1, std::pair<double,double> br2){return br1.first<br2.first;});
        for(int i=0; i<data.size()-1; i++)
        {
         if(std::abs(data[i].first - data[i+1].first)<eps) throw std::domain_error("Invalid data set");   
        }
    }
    virtual double operator()(double x) const = 0;
};


double linijaKrozDvijeTacke(std::pair<double,double> tacka1, std::pair<double,double> tacka2, double x)
{
    return ((tacka2.first-x)/(tacka2.first-tacka1.first))*tacka1.second + ((x-tacka1.first)/(tacka2.first-tacka1.first))*tacka2.second;
}

class LinearInterpolator : public AbstractInterpolator
{
    public:
    LinearInterpolator(const std::vector<std::pair<double,double>> &data) : AbstractInterpolator(data){}
    double operator()(double x) const override
    {
        int k=Locate(x);
        if(k>=veka.size()) return linijaKrozDvijeTacke(veka[veka.size()-2], veka[veka.size()-1],x);
        else if(k<=1) return linijaKrozDvijeTacke(veka[0],veka[1],x);
        else return linijaKrozDvijeTacke(veka[k-1], veka[k], x);
    }
};

class PolynomialInterpolator : public AbstractInterpolator
{
    private:
    std::vector<double> temp;
    public:
    PolynomialInterpolator(const std::vector<std::pair<double,double>> &data) : AbstractInterpolator(data)
    {
        temp.resize(veka.size());
        temp[0]=veka[veka.size()-1].second;
        for(int i = 1; i<veka.size(); i++)
        {
            for(int j=veka.size(); j>=i+1; j--)
            {
                veka[j-1].second=(veka[j-1].second - veka[j-2].second)/(veka[j-1].first-veka[j-i-1].first);
            }
            temp[i]=veka[veka.size()-1].second;
        }
    }
    
    double operator()(double x) const override
    {
        double p=veka[0].second;
        double q=1;
        for(int i=1; i<veka.size(); i++)
        {
            q=q*(x-veka[i-1].first);
            p=p+veka[i].second*q;
        }
        return p;
    }
    
    void AddPoint(const std::pair<double,double> &p)
    {
        for(int i=0; i<veka.size(); i++)
        {
            if(std::abs(p.first-veka[i].first)<eps) throw std::domain_error("Invalid point");
        }
        veka.emplace_back(p);
        int k=veka.size();
        temp.resize(k);
        for(int i=1; i<k; i++)
        {
            double tTemp=temp[i-1];
            temp[i-1]=veka[k-1].second;
            veka[k-1].second=(veka[k-1].second-tTemp)/(veka[k-1].first - veka[k-i-1].first);
        }
        temp[k-1]=veka[k-1].second;
    }
    
    std::vector<double> GetCoefficients() const
    {
        int k=veka.size();
        std::vector<double> w(k+1);
        std::vector<double> p(k+1);
        w[0]=1;
        for(int i=1; i<=k; i++)
        {
            for(int j=0; j<=i; j++)
            {
                p[j]=p[j]+veka[i-1].second*w[j];
            }
            w[i]=w[i-1];
            for(int j=i-1; j>0; j--)
            {
                w[j]=w[j-1]-veka[i-1].first*w[j];
            }
            w[0]=w[0]*(-1)*veka[i-1].first;
        }
        
        p.erase(p.begin()+p.size()-1);
        return p;
    }
};

class PiecewisePolynomialInterpolator : public AbstractInterpolator
{
    private:
    int o;
    public:
    PiecewisePolynomialInterpolator(const std::vector<std::pair<double,double>> &data, int order) : AbstractInterpolator(data)
    {
        if(order>data.size() || order<1) throw std::domain_error("Invalid order");
        o=order;
    }
    
    double operator()(double x) const
    {
        int l=Locate(x);
        int m, n;
        if(o%2==0)
        {
            m=l-o/2-1;
            n=l+o/2;
        }
        else
        {
            m=l-(o-1)/2-1;
            n=l+(o+1)/2;
        }
        if(n>=veka.size())
        {
            m=veka.size()-o-1;
            n=veka.size();
        }
        if(m<=0)
        {
            m=0; n=o+1;
        }
        
        double t=0;
        for(int i=m; i<n; i++)
        {
            double r=veka[i].second;
            for(int j=m; j<n; j++)
            {
                if(i!=j) r=r*(x-veka[j].first)/(veka[i].first-veka[j].first);
            }
            t=t+r;
        }
        return t;
    }
};


class SplineInterpolator : public AbstractInterpolator
{
    private:
        std::vector<double> p;
        std::vector<double> q;
        std::vector<double> s;
        public:
            SplineInterpolator(const std::vector<std::pair<double,double>> &data) : AbstractInterpolator(data)
            {
                p.resize(veka.size());
                s.resize(veka.size());
                p[0]=0;
                p[p.size()-1]=0;
                for(int i=1; i<veka.size()-1; i++)
                {
                    s[i]=2*(veka[i+1].first - veka[i-1].first);
                    p[i]=3*((veka[i+1].second - veka[i].second)/(veka[i+1].first - veka[i].first) - (veka[i].second-veka[i-1].second)/(veka[i].first-veka[i-1].first));
                }
                
                for(int i=1; i<veka.size()-2; i++)
                {
                    double koef=(veka[i+1].first - veka[i].first)/s[i];
                    s[i+1]-=koef*(veka[i+1].first - veka[i].first);
                    p[i+1]-=koef*p[i];
                }
                
                p[veka.size()-2]/=s[veka.size()-2];
                for(int i=veka.size()-3; i>=1; i--) p[i]=(p[i]-(veka[i+1].first-veka[i].first)*p[i+1])/s[i];
                
                q.resize(veka.size());
                for(int i=0; i<veka.size()-1; i++)
                {
                    double r=veka[i+1].first-veka[i].first;
                    s[i]=(p[i+1]-p[i])/(3*r);
                    q[i]=(veka[i+1].second - veka[i].second)/r-r*(p[i+1]+2*p[i])/3;
                }
                
            }
            
            double operator()(double x) const
            {
                int i=Locate(x);
                if(i<=0) i=1; 
                if(i>=veka.size()) i=veka.size()-1;
                double t1=x-veka[i-1].first;
                return veka[i-1].second+t1*(q[i-1]+t1*(p[i-1]+s[i-1]*t1));
            }
            
};



class BarycentricInterpolator : public AbstractInterpolator 
{
    private:
        std::vector<double> v;
        int t;
    public:
        BarycentricInterpolator(const std::vector<std::pair<double,double>> &data, int order) : AbstractInterpolator(data)
        {
            if(order>veka.size() || order<0) throw std::domain_error("Invalid order");
            t=order;
            int n=veka.size();
            v.resize(n);
            for(int i=0; i<veka.size(); i++)
            {
                v[i]=0;
                double l; int m,k;
                if(i-t>1) m=i-t;
                else m=1;
                if(i<n-t) k=i;
                else k=n-t-1;
                for(int j=m-1; j<k+1; j++)
                {
                    l=1;
                    for(int c=j; c<j+t; c++)
                    {
                        if(c!=i) l/=(veka[i].first-veka[c].first);
                    }
                    if(j%2==1) l*=(-1);
                }
                v[i]+=l;
            }
        }
        
        double operator()(double x) const override
        {
            double p=0, q=0;
            for(int i=0; i<veka.size(); i++)
            {
                if(std::abs(x-veka[i].first)<eps) return veka[i].second;
                double mi = v[i]/(x-veka[i].first);
                p+=mi*veka[i].second;
                q+=mi;
            }
            return p/q;
        }
        
        std::vector<double> GetWeights() const { return v; }
};


void LinearniTest()
{
    try
    {
        LinearInterpolator l({{1,3}, {3,6}, {2,4}, {5,9}});
        std::cout<<l(2.5)<<" ";
    }
    catch(std::domain_error e) 
    {
        std::cout<<e.what();
        
    }
}

void PolinomniTest()
{
    try
    {
        PolynomialInterpolator p({{1,3}, {3,6}, {5,8}});
        std::cout<<p(2.5)<<" ";
    }
    catch(std::domain_error e)
    {
        std::cout<<e.what();
    }
}

void BaricentricniTest()
{
    try{
 //       std::vector<std::pair<double,double>> veka = {{1,3},{3,6},{5,8}}
        BarycentricInterpolator b({{1,3},{3,6},{5,8}},1);
        std::cout<<b(2.5)<<" ";
    }
    catch(std::domain_error e)
    {
        std::cout<<e.what();
    }
}

void SplineTest()
{
    try{
        SplineInterpolator s({{1,3},{3,6},{5,8}});
        std::cout<<s(2.5)<<" ";
    }
    catch(std::domain_error e)
    {
        std::cout<<e.what();
    }
}

void PicewiseTest()
{
    try{
        PiecewisePolynomialInterpolator p({{1,3},{3,6},{5,8}},1);
        std::cout<<p(2.5)<<" ";
    }
    catch(std::domain_error e)
    {
        std::cout<<e.what();
    }
}


int main ()
{
    LinearniTest();
    PolinomniTest();
    BaricentricniTest();
    SplineTest();
    PicewiseTest();
    return 0;
}
