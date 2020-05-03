#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <stdexcept>



const double pi=std::atan(1)*4;
const double eps=std::numeric_limits<double>::epsilon();



class ChebyshevApproximation
{
    std::vector<double> k;
    int m;
    double min, max;
    ChebyshevApproximation(std::vector<double> koeficijenti, double xmin, double xmax) : k(koeficijenti), m(koeficijenti.size()-1), min(xmin), max(xmax){}

  public:
  
  template<typename Tip>
  ChebyshevApproximation(Tip f, double xmin, double xmax, int n)
  {
      if(xmin>=xmax || n<1) throw std::domain_error("Bad parameters");
      std::vector<double> w(n+2);
      std::vector<double> v(n+1);
      k.resize(n+1);
      m=n;
      min=xmin;
      max=xmax;
      for(int i=0; i<=n; i++)
      {
          w[i]=pi*(2*i+1)/(2*n+2);
          v[i]=f((xmin+xmax+(xmax-xmin)*std::cos(w[i]))/2);
      }
      
      for(int l=0; l<=n; l++)
      {
          double s=0;
          for(int i=0; i<=n; i++) s+=v[i]*std::cos(l*w[i]);
          k[l]=2*s/(n+1);
      }
  }
  
  void set_m(int m)
  {
      if(m>k.size()-1 || m<2) throw std::domain_error("Bad order");
      this->m=m;
  }
  
  void trunc(double eps)
  {
      if(eps<0) throw std::domain_error("Bad tolerance");
      for(int i=m; i>=0; i--)
      {
          if(std::abs(k[i])>eps)
          {
              m=i;
              return;
          }
      }
      throw std::domain_error("Bad tolerance");
  }
  
  double operator()(double x) const
  {
      if(x<min || x>max) throw std::domain_error("Bad argument");
      double t=(2*x-min-max)/(max-min);
      double p=1, q=t, s=k[0]/2 + k[1]*t, r;
      for(int c=2; c<=m; c++)
      {
          r=2*t*q-p;
          s+=k[c]*r;
          p=q;
          q=r;
      }
      return s;
  }
  
  ChebyshevApproximation derivative() const
  {
      double mi=4./(max-min);
      std::vector<double> veka(k.size());
      veka[m-1]=mi*m*k[m];
      veka[m-2]=mi*(m-1)*k[m-1];
      for(int c=m-3; c>=0; c--)
      {
          veka[c]=veka[c+2]+mi*(c+1)*k[c+1];
      }
      return ChebyshevApproximation(veka,min,max);
  }
  
  double derivative(double x) const
  {
      if(x<min || x>max) throw std::domain_error("Bad argument");
      double t = (2*x-min-max)/(max-min);
      double p=1, q=4*t, s=k[1]+4*k[2]*t;
      for(int c=3; c<=m; c++)
      {
          double r = c*(2*t*q/(c-1)-p/(c-2));
          s+=k[c]*r;
          p=q;
          q=r;
      }
      
      return 2*s/(max-min);
  }
  
  
  ChebyshevApproximation antiderivative() const
  {
      double mi=(max-min)/4;
      std::vector<double> veka(m+2);
      veka[0]=0;
      for(int i=1; i<=m-1; i++)
      {
          veka[i]=mi/i*(k[i-1]-k[i+1]);
      }
      veka[m]=mi/m*k[m-1];
      veka[m+1]=mi/(m+1)*k[m];
      return ChebyshevApproximation(veka,min,max);
  }
  
  double integrate(double a, double b) const
  {
      if(a>max || a<min || b>max || b<min) throw std::domain_error("Bad interval");
      ChebyshevApproximation fun(this->antiderivative());
      return fun(b)-fun(a);
  }
  
  double integrate() const
  {
      double s=0;
      for(int c=1; c<=(m-1)/2 + 1; c++)
      {
          s+=2*k[2*c]/(1-4*c*c);
      }
      s*=(max-min)/2;
      s+=k[0]*(max-min)/2;
      return s;
  }
};



int main ()
{
	try
	{
	    ChebyshevApproximation c ([](double x){return std::cos(x);}, 0, pi/2, 3);
	    std::cout<<c.integrate(0,pi/2)<<" "<<c.integrate()<<"\n";
	    std::cout<<c(0)<<" "<<c(pi/2)<<"\n";
	    std::cout<<c.derivative(pi/2)<<" "<<c.derivative(0)<<" ";
	}
	catch(std::domain_error e)
	{
	    std::cout<<e.what()<<"\n";
	}
	catch(std::range_error r)
	{
	    std::cout<<r.what()<<"\n";
	}
	catch(...)
	{
	    std::cout<<"nesto ama bas ne valja";
	}
}