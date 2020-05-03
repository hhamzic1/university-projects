#include <algorithm>
#include <vector>
#include <iostream>
using std::vector;

int suma(int n)
{
	if(n==0)
	{
		return 0;
	}
	return(std::abs(n%10)+suma(std::abs(n/10)));
}

bool sumacifara(int x, int y)
{

	if(suma(x)==suma(y)) return y>x;
	return suma(y)>suma(x);
	
}


int main ()
{
	int m;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>m;
	vector<int> v(m);
	std::cout<<"Unesite elemente: ";
	std::for_each(v.begin(), v.end(), [](int &x){std::cin>>x;});
	
	std::sort(v.begin(), v.end(), sumacifara);
	std::cout<<"Niz sortiran po sumi cifara glasi: ";
	std::for_each(v.begin(), v.end(), [](const int &x){std::cout<<x<<" ";});
	
	std::cout<<"\nUnesite broj koji trazite: ";
	int n;
	std::cin>>n;
	
	if(std::binary_search(v.begin(), v.end(),n,sumacifara))
	{
		auto it=std::lower_bound(v.begin(), v.end(),n,sumacifara);
		std::cout<<"Trazeni broj nalazi se na poziciji "<<it-v.begin();
	}
	else
	{
		std::cout<<"Trazeni broj ne nalazi se u nizu!";
	}
	return 0;
	
}