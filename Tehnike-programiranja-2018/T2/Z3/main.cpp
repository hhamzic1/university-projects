
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>n;
    std::cout<<std::endl;
    std::vector<std::complex<double>> elem(n);
    std::complex<double> imp(0,0);

    for(int i=0; i<n; i++) {
        std::cout<<"Z_"<<i+1<<" = ";
        std::cin>>elem[i];
        imp=imp+(1./elem[i]);
    }
    imp=1./imp;
    std::cout<<"\nParalelna veza ovih elemenata ima impedansu Z_ = "<<imp<<".";
    return 0;
}
