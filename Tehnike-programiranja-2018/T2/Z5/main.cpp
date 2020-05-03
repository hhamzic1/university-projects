//TP 2017/2018: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
int main ()
{
    int n;
    double modul, fi;
    const double PI=4*atan(1);
    std::cout<<"Unesi broj elemenata: ";
    std::cin>>n;
    std::cout<<std::endl;
    std::vector<std::complex<double>> elem(n);
    std::complex<double> imp(0,0);
    
    for(int i=0; i<n; i++)
    {
        std::cout<<"Z"<<i+1<<" = ";
        std::cin>>modul;
        
        std::cout<<"fi"<<i+1<<" = ";
        std::cin>>fi;
        fi=fi*(PI/180.);
        
        elem[i]=std::polar(modul,fi);
        
        imp=imp+(1./elem[i]);
        std::cout<<"\n";

    }
    imp=1./imp;
    std::cout<<"Paralelna veza ovih elemenata ima Z = "<<abs(imp)<<" i fi = "<<arg(imp)*(180./PI)<<".";
    return 0;
	
}
