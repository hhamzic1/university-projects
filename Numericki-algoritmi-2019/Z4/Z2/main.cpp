#include <vector>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <cmath>


const double pi = 4*std::atan(1);

template<typename Tip>
std::pair<double, bool> RombergIntegration(Tip f, double a, double b, double eps=1e-8, int nmax=1000000, int nmin=50)
{
   if(eps<0 || nmin<0 || nmax<0 || nmax<nmin) throw std::domain_error("Bad parameter");
   int velikoN=2;
   double h=(b-a)/velikoN;
   double s=(f(a)+f(b))/2;
   double istaro = s;
   std::vector<double> velikoi;
   for(int i=1; velikoN<=nmax; i++)
   {
       for(int j=1; j<=velikoN/2; j++)
       {
           s+=f(a+(2*j-1)*h);
       }
       velikoi.push_back(h*s);
       double p=4;
       for(int k=velikoi.size()-2; k>=0; k--)
       {
           velikoi[k]=(p*velikoi[k+1]-velikoi[k])/(p-1);
           p=p*4;
       }
       if(velikoN>=nmin && std::abs(velikoi[0]-istaro)<=eps) return {velikoi[0],true};
       istaro=velikoi[0];
       h=h/2;
       velikoN=velikoN*2;
   }
   return {istaro, false};
}



template<typename Tip>
std::pair<double, bool> TanhSinhIntegration(Tip f, double a, double b, double eps=1e-8, int nmax=1000000, int nmin=20, double range = 3.5)
{
    if(eps<0 || nmax<nmin || nmin<0 || range<0) throw std::domain_error("Bad parameter");
    int sign=1;
    if(a>b) 
    {
        sign*=-1;
        std::swap(a,b);
    }
    
    auto pokf=[&](double t) { 
        double tone=std::cosh(pi*std::sinh(t)/2);
        double ttwo=(b+a)/2+(b-a)/2*std::tanh(pi*std::sinh(t)/2);
        double d=std::cosh(t)*f(ttwo)/(tone*tone);
        if(!std::isfinite(d)) return 0.;
        return (b-a)*pi/4*d;};
        
    double nveliko=2, h=(2*range)/nveliko, s=(pokf(-range)+pokf(range))/2, istaro=s;
    while(nveliko<nmax)
    {
        for(int i=1; i<=nveliko/2; i++)
        {
            s+=pokf(-range+(2*i-1)*h);
        }
        double iveliko=h*s;
        if(nveliko>nmin && std::fabs(iveliko-istaro)<=eps) return {sign*iveliko, true};
        istaro=iveliko;
        nveliko*=2;
        h/=2;
    }
    
    return {sign*istaro, false};
}



std::pair<double, bool> operator +(std::pair<double,bool> p1, std::pair<double,bool> p2)
{
    bool b = p1.second && p2.second;
    return {p1.first+p2.first, b};
}


template<typename Tip>
std::pair<double,bool> AdaptiveTemp(Tip f, double a, double b, double eps, double f1, double f2, double f3, int maxdepth)
{
    if(!std::isfinite(f1)) f1=0;
    if(!std::isfinite(f2)) f2=0;
    if(!std::isfinite(f3)) f3=0;
    double t = (a+b)/2, i1=(b-a)*(f1+4*f3+f2)/6, f4=f((a+t)/2), f5=f((t+b)/2);
    if(!std::isfinite(f4)) f4=0;
    if(!std::isfinite(f5)) f5=0;
    double i2=(b-a)*(f1+4*f4+2*f3+4*f5+f2)/12;
    if(std::abs(i1-i2)<=eps) return {i2,true};
    if(maxdepth<=0) return {i2, false};
    return AdaptiveTemp(f,a,t,eps,f1,f3,f4,maxdepth-1) + AdaptiveTemp(f,t,b,eps,f3,f2,f5,maxdepth-1);
}


template<typename Tip>
std::pair<double, bool> AdaptiveIntegration (Tip f, double a, double b, double eps=1e-10, int maxdepth=30, int nmin=1)
{
    if(eps<0 || maxdepth<0 || nmin<0) throw std::domain_error("Bad parameter");
    std::pair<double,bool> paric{0,true};
    double h=(b-a)/nmin;
    for(int i=1; i<=nmin; i++)
    {
        paric=paric+AdaptiveTemp(f,a,a+h,eps,f(a),f(a+h),f(a+h/2),maxdepth);
        a=a+h;
    }
    return paric;
        
}



int main ()
{
	auto f = [](double x) {return x==0 ? 0:1/std::sqrt(x);};
	std::pair<double,bool> a = TanhSinhIntegration(f,0,1);
	std::cout<<a.first<<"\n";
	a=TanhSinhIntegration(f,0,1,1e-8,1000000);
	std::cout<<a.first<<std::endl;
	
	std::pair<double,bool> b= RombergIntegration(f,0,1);
	std::cout<<b.first<<"\n";
	a=TanhSinhIntegration(f,0,1,1e-8,1000000);
	std::cout<<b.first<<std::endl;
	
	std::pair<double,bool> c = AdaptiveIntegration(f,0,1);
	std::cout<<c.first<<"\n";
	a=TanhSinhIntegration(f,0,1,1e-8,1000000);
	std::cout<<c.first<<std::endl;
	
	
}