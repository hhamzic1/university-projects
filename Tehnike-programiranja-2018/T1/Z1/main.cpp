//TP 2016/2017: Tutorijal 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
	int a,b,c,d;
	std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
	std::cin>>a>>b>>c;
	std::cout<<"Unesite sirinu plocice u centimetrima: ";
	std::cin>>d;
	int pbazena;
	int pplocice;
	
	pbazena=2*(a*c+b*c)+a*b;
	pbazena=pbazena*10000;
	pplocice=d*d;
	
	if((a*100)%(d)!=0 || (b*100)%(d)!=0 || (c*100)%(d)!=0)
	{
	    std::cout<<"\nPoplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm\nnije izvodljivo bez lomljenja plocica!";
	    
	}
	else
	{
	    std::cout<<"\nZa poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm\npotrebno je "<<pbazena/pplocice<<" plocica.";
	}
	return 0;
}