//TP 2016/2017: Tutorijal 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
	double n;
	int i;
	while(1)
	{
	    std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
	    if(!(std::cin>>n) || n<0 || n-floor(n)!=0)
	    {
	        std::cout<<"Niste unijeli prirodan broj!\n";
	        std::cin.clear();
	        std::cin.ignore(10000, '\n');
	        continue;
	    }
	    else if(n==0)
	    {
	        std::cout<<"Dovidjenja!";
	        return 0;
	    }
	    else if(floor(n)==ceil(n))
	    {
	        int b=n;
	        int suma=0;
	        for(i=1; i<n; i++)
	        {
	            if(b%i==0)
	            {
	                suma+=i;
	            }
	        }
	        
	        if(suma<n)
	        {
	            std::cout<<"Broj "<<n<<" je manjkav!\n";
	        }
	        else if(suma==n)
	        {
	           std::cout<<"Broj "<<n<<" je savrsen!\n";
	           
	        }
	        else
	        {
	            std::cout<<"Broj "<<n<<" je obilan!\n";
	        }
	     }
	}
}