//NA 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <utility>

template<typename FunType>
std::pair<double, bool> Limit(FunType f, double x0, double h=0, double eps=1e-8, double nmax=20)
{
    if(nmax<3 || eps<=0 || nmax>30) throw std::domain_error("Invalid parameters");
    if(std::abs(h)<eps)
    {
        if(1<x0) h = std::abs(x0)*0.001;
        else h=0.001;
    }
    std::vector<double> zaY(nmax,0);
    double t;
    double y_inf=std::numeric_limits<double>::infinity();
    for(int i=0; i<nmax; i++)
    {
        zaY[i]=f(x0+h);
        t=2;
        for(int j=i-1; j>=0; j--)
        {
            zaY[j]=(t*zaY[j+1]-zaY[j])/(t-1);
            t=t*2;
        }
        if(std::fabs(zaY[0]-y_inf)<eps) return std::pair<double, bool>(zaY[0], true);
        y_inf=zaY[0];
        h=h/2;
    }
    
    return std::pair<double,bool>(zaY[0], false);
    
}

void testLimes() //broj e limes klasicni Bernulijev!
{
    int br=0;
    for(int i=1; i<=100000; i*=10)
    {
        std::cout<<"Iteracija "<<++br<<": "<<Limit([](double x){return std::pow((1+1/x),x);}, i).first<<std::endl;
    }
}
int main ()
{
    testLimes();
}
