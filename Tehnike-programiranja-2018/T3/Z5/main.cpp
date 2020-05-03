
#include <iostream>
#include <deque>
#include <cmath>
std::deque<int> IzdvojiElemente(std::deque<int> vek, bool sta)
{
    
    if(sta)
    {
        std::deque<int>parni;
        for(int i=vek.size()-1; i>=0; i--)
        {
            unsigned c=std::abs(vek[i]);
            int suma=0;
            while(c>0)
            {
                suma+=c%10;
                c/=10;
            }
            if(suma%2==0)
            {
                parni.push_front(vek[i]);
            }
          
        }
        return parni;
    }
    else
    {
        std::deque<int> neparni;
        for(int i=vek.size()-1; i>=0; i--)
        {
            unsigned int c=std::abs(vek[i]);
            int suma=0;
            while(c>0)
            {
                suma+=c%10;
                c/=10;
                
            }
            if(suma%2!=0)
            {
                neparni.push_front(vek[i]);
            }
        }
        
        return neparni;
    }

}
int main ()
{
    int n;
    int elem;

        std::cout<<"Koliko zelite unijeti elemenata: ";
        std::cin>>n;
        if(n<=0)
        {
            std::cout<<"Broj elemenata mora biti veci od 0!";
            return 0;
        }
    std::deque<int> veka;
    std::cout<<"Unesite elemente: ";
    for(int i=0; i<n; i++)
    {
        
        std::cin>>elem;
        veka.push_back(elem);
    }
    
   auto par=IzdvojiElemente(veka, true);
   auto nepar=IzdvojiElemente(veka, false);
   for(int i=0; i<par.size(); i++)
   {
       if(i<par.size()-1) std::cout<<par[i]<<",";
       
       else std::cout<<par[i];
       
   }
   std::cout<<std::endl;
   for(int i=0; i<nepar.size(); i++)
   {
       if(i<nepar.size()-1)  std::cout<<nepar[i]<<",";
       
       else  std::cout<<nepar[i];
       
   }
   
    return 0;
}
