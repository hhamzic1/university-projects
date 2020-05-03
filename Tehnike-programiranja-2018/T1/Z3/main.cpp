//TP 2016/2017: Tutorijal 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <iomanip>
int main ()
{
    int a, b;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;
    
    int i, j;
    int redovi=b-a+1;
    std::cout<<"\n+---------+----------+----------+-----------+"<<"\n";
    std::cout<<"| Brojevi | Kvadrati | Korijeni | Logaritmi |"<<"\n";
    std::cout<<"+---------+----------+----------+-----------+"<<"\n";
    
    for(i=0; i<redovi; i++)
    {
        for(j=0; j<10; j++)
        {
            if(j==0 || j==3 || j==5 || j==7 || j==9)
            {
                std::cout<<"|";
            }
            if(j==1)
            {
                std::cout<<" "<<std::left<<std::setw(8)<<a;
            }
            if(j==4)
            {
                std::cout<<std::right<<std::setw(9)<<std::fixed<<std::setprecision(0)<<std::pow(a,2)<<" ";
            }
            if(j==6)
            {
                std::cout<<std::right<<std::setw(9)<<std::fixed<<std::setprecision(3)<<sqrt(a)<<" ";
            }
            if(j==8)
            {
                std::cout<<std::right<<std::setw(10)<<std::fixed<<std::setprecision(5)<<log(a)<<" ";
            }
            
        }
        std::cout<<"\n";
        a++;
    }
    std::cout<<"+---------+----------+----------+-----------+"<<"\n";
    return 0;
	
}