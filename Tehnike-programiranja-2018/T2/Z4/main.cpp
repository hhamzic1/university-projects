//TP 2017/2018: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
int main ()
{
    int n;
    double re, im;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>n;
    std::cout<<std::endl;
    std::vector<std::complex<double>> elem(n);
    std::complex<double> imp(0,0);
    
    for(int i=0; i<n; i++)
    {
        std::cout<<"R"<<i+1<<" = ";
        std::cin>>re;
        
        std::cout<<"X"<<i+1<<" = ";
        std::cin>>im;
        
        elem[i]=std::complex<double>(re,im);
        
        imp=imp+(1./elem[i]);
        std::cout<<std::endl;

    }
    imp=1./imp;
    std::cout<<"\nParalelna veza ovih elemenata ima R = "<<std::real(imp)<<" i X = "<<std::imag(imp)<<".";
    return 0;
}
