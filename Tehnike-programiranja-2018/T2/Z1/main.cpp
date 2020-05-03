//TP 2017/2018: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
bool DaLiJeProst(int n)
{
    
    bool prost=true;
    if(n==2) return true;
    if(n<=1 || n%2==0) return false;
    
    for(long int i=3; i*i<=n ; i+=2)
    {
      
        if(n%i==0)
        {
            prost=false;
            break;
        }

    }
    return prost;
}
std::vector<int> ProstiBrojeviUOpsegu(int a, int b)
{
    long int i;
    
    std::vector<int> veka;
    for(i=a; i<=b; i++)
    {
        if(DaLiJeProst(i))
        {
            veka.push_back(i);
        }
    }
    return veka;
}
int main ()
{
    int a, b;
    
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;
    
    auto c=ProstiBrojeviUOpsegu(a, b);
    if(c.size()!=0)
    {
        std::cout<<"Prosti brojevi u rasponu od "<<a<<" do "<<b<<" su: ";
        for(int i=0; i<c.size(); i++)
        {
            if(i<c.size()-1)
            {
                std::cout<<c[i]<<", ";
            }
            else
            {
                std::cout<<c[i];
            }
        }
    }
    else
    {
        std::cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!";
    }
    std::cout<<"\n";
	return 0;
}
