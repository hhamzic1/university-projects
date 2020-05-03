
#include <iostream>
#include <limits>
#include <stdexcept>
#include <cmath>
#include <iomanip>

template<typename tip>
tip *GenerirajStepeneDvojke(int n)
{
	if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
	tip max=std::numeric_limits<tip>::max();
	tip test=1;
	for(int i=1; i<n; i++) test*=2;
	
	if(test>max) throw std::overflow_error("Prekoracen dozvoljeni opseg");
	
	try
	{
		tip *p=new tip[n];
		for(int i=0; i<n; i++)
		 {
		 	tip pomocna=1;
		 	for(int j=1; j<=i; j++)
		 	{
		 		if(pomocna*2>max || pomocna*2<=0 || std::isinf(pomocna))
		 		{
		 			delete[] p;
		 			throw std::overflow_error("Prekoracen dozvoljeni opseg");
		 		}
		 		
		 		pomocna*=2;
		 	}
		 	p[i]=pomocna;
		 }
		 
		return p;
	}
	catch(std::bad_alloc)
	{
		throw std::runtime_error("Alokacija nije uspjela");
	}
}


int main ()
{
	int n;
	std::cout<<"Koliko zelite elemenata: ";
	std::cin>>n;
	try
	{
		long double *p=GenerirajStepeneDvojke<long double>(n);
		for(int i=0; i<n;i++)
		
		std::cout<<std::setprecision(std::numeric_limits<long double>::max_digits10)<<p[i]<<" ";
		delete[] p;
	}
	catch(std::domain_error d)
	{
		std::cout<<"Izuzetak: "<<d.what();
	}
	catch(std::runtime_error r)
	{
		std::cout<<"Izuzetak: "<<r.what();
	}
	
	return 0;
}