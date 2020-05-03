
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <string>

using std::string;

int main ()
{
	try
	{
		int broj_recenica;
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>broj_recenica;
		std::cin.ignore(10000,'\n');
		std::cout<<"Unesite recenice:\n";
		string **recenice=nullptr;
		recenice=new string*[broj_recenica]{};
		for(int i=0; i<broj_recenica; i++)
		{
	
			try
			{
				recenice[i]=new std::string{};
				std::getline(std::cin, *recenice[i]);
			}
			catch(std::bad_alloc)
			{
				for(int i=0; i<broj_recenica; i++) 
					delete recenice[i];
				delete[] recenice;
				throw;
			}
		}
		
		std::sort(recenice, recenice+broj_recenica, [](string *s1, string *s2)->bool{
				return(*s1<*s2);
		});
		
		std::cout<<"Sortirane recenice: \n";
		for(int i=0; i<broj_recenica; i++)
		{
			std::cout<<*recenice[i]<<"\n";
		}
		for(int i=0; i<broj_recenica; i++)
				delete recenice[i];
		
		delete[] recenice;
		return 0;
	}
	catch(std::bad_alloc)
	{
		std::cout<<"Problemi s memorijom!";
	}
}