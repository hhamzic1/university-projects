#include <iostream>

template <typename pocetni, typename odrediste>

odrediste RazmijeniBlokove(pocetni c1, pocetni c2, odrediste mjesto)
{
	
	while(c1!=c2)
	{
		auto pomocna=*c1;
		*c1++=*mjesto;
		*mjesto++=pomocna;
		
	}
	
	return mjesto;
}



int main ()
{
	//CIJELI
	int a[]{1,2,3,4,5}, b[]{6,7,8,9,10};
	RazmijeniBlokove(std::begin(a), std::end(a), std::begin(b));
	std::cout<<"Prvi niz: ";
	for(int x : a) std::cout<<x<<" ";
	std::cout<<"\nDrugi niz: ";
	for(int x : b) std::cout<<x<<" ";
	std::cout<<std::endl;
	
	//STRINGOVI
	std::string c[]{"ja", "sam", "prvi", "string"}, d[]{"ja","sam","drugi","string"};
	RazmijeniBlokove(std::begin(c), std::end(c), std::begin(d));
	std::cout<<"Prvi niz: ";
	for(std::string x : c) std::cout<<x<<" ";
	std::cout<<"\nDrugi niz: ";
	for(std::string x : d) std::cout<<x<<" ";
	return 0;
}