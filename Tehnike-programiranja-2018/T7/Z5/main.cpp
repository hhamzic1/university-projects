
/* 
    TP 16/17 (Tutorijal 7, Zadatak 4)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <memory>

using std::string;
using std::shared_ptr;
using std::unique_ptr;
typedef shared_ptr<string> sharedNaString;

int main ()
{
	try 
	{
		int broj_recenica;
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>broj_recenica;
		std::cin.ignore(10000, '\n');
		std::cout<<"Unesite recenice:\n";
		shared_ptr<sharedNaString> recenice(new sharedNaString[broj_recenica]{}, [](sharedNaString *p){ delete[] p;});;
		try
		{
			for(int i=0; i<broj_recenica; i++)
			{
		
				recenice.get()[i]=std::make_shared<string>();
				std::getline(std::cin, *recenice.get()[i]);
			}
		}
		catch(std::bad_alloc)
		{
			for(int i=0; i<broj_recenica; i++)
			{
				recenice.get()[i]=nullptr;
			}
				recenice=nullptr;
				throw;
		}
		std::sort(recenice.get(), recenice.get()+broj_recenica, [](sharedNaString s1, sharedNaString s2)->bool{
			return (*s1<*s2);
		});
		std::cout<<"Sortirane recenice: \n";
		for(int i=0; i<broj_recenica; i++)
		{
			std::cout<<*recenice.get()[i]<<"\n";
		}
		for(int i=0; i<broj_recenica; i++) recenice.get()[i]=nullptr;
		recenice=nullptr;
		return 0;
	}
	catch(std::bad_alloc)
	{
		std::cout<<"Problemi s memorijom!";
	}
}
