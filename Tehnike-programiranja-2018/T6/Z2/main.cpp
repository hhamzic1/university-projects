#include <vector>
#include <iostream>
#include <type_traits>
#include <stdexcept>

template<typename itertip>
auto KreirajIzvrnutiNiz(itertip p1, itertip p2) -> typename std::remove_reference<decltype(*p1)>::type*
{
    int duzina=0;
    itertip p=p1;
    
    while(p!=p2)
    {
        p++;
        duzina++;
    }
    
    p=p1;
    
    auto dinamicki=new typename std::remove_reference<decltype(*p1)>::type[duzina];
        
        for(int i=0; i<duzina; i++)
        {
            dinamicki[duzina-i-1]=*p++;
        }
        return dinamicki;
}


int main ()
{
	try
	{
	    int n;
	    std::cout<<"Koliko zelite elemenata: ";
	    std::cin>>n;
	    std::vector<double> vek(n);
	    std::cout<<"Unesite elemente: ";
	    
	    for(int i=0; i<n; i++) std::cin>>vek.at(i);
	    
	    std::cout<<"Kreirani niz: ";
	    double *p=KreirajIzvrnutiNiz(vek.begin(), vek.end());
	    
	    for(int i=0; i<n; i++) std::cout<<p[i]<<" ";
	    
	    delete[] p;

	}
	catch(std::bad_alloc)
	{
	    std::cout<<"Nedovoljno memorije!";
	}
	
	return 0;
}