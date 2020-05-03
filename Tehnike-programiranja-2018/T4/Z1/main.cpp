//TP 2018/2019: Tutorijal 4, Zadatak 1
#include <iostream>
#include <limits>
#include <cmath>
int Cifre(long long int n, int &a, int &b)
{
  
    int min=abs(n%10), max=abs(n%10);
    
    int brojcifri=0;
    int c=0;
    do
    {
        c=abs(n%10);
        
        if(c>max) max=c;
        if(c<min) min=c;
        brojcifri++;
        n/=10;

    }while(n!=0);
    
    a=min;
    b=max;
    
    return brojcifri;
    
    
}


int main ()
{
    std::cout<<"Unesite broj: ";
    long long int n;
    std::cin>>n;
    int a, b;

    auto e=Cifre(n, a, b);
    
    std::cout<<"Broj "<<n<<" ima "<<e<<" cifara, najveca je "<<b<<" a najmanja "<<a<<".";
    return 0;
}