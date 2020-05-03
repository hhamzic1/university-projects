#include <algorithm>
#include <stdexcept>
#include <deque>
#include <iostream>

using std::deque;

template <typename itertip>

auto SumaBloka(itertip p1, itertip p2) ->decltype(*p1+*p1)
{
	if(p2-p1==0) throw std::range_error("Blok je prazan");
	
	decltype(*p1+*p2) sumaBloka=*p1;
	itertip p=p1+1;
	while(p!=p2)
	{
		sumaBloka+=*p;
		p++;
	}
	return sumaBloka;
}

int main ()
{
	int n;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>n;
	deque<double> dek(n);
	std::cout<<"Unesite elemente: ";
	std::for_each(dek.begin(), dek.end(), [](double &x){std::cin>>x;});
	
	try
	{
		double suma=SumaBloka(dek.begin(), dek.end());
		std::cout<<"Suma bloka je: "<<suma;
	}
	catch(std::range_error e)
	{
		std::cout<<e.what();
	}
	
	
	return 0;
}