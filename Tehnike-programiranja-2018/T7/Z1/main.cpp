
#include <iostream>
#include <cstring>
#include <stdexcept>

int main ()
{
	try
	{
		int broj_recenica;
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>broj_recenica;
		std::cin.ignore(10000,'\n');
		std::cout<<"Unesite recenice:\n";
		char **recenice(new char*[broj_recenica]{});
		for(int i=0; i<broj_recenica; i++)
		{
			char radni_prostor[1000];
			std::cin.getline(radni_prostor, sizeof radni_prostor);
			try
			{
				recenice[i]=new char[std::strlen(radni_prostor)+1];
			}
			catch(std::bad_alloc)
			{
				for(int i=0; i<broj_recenica; i++) delete[] recenice[i];
				delete[] recenice;
				throw;
			}
			std::strcpy(recenice[i], radni_prostor);
		}
		for(int i=0; i<broj_recenica; i++)
		{
			for(int j=i; j<broj_recenica; j++)
			{
				if(strcmp(recenice[j],recenice[i])<0)
				{
					std::swap(recenice[i], recenice[j]);
					i--;
					break;
				}
			}
		}
		
		std::cout<<"Sortirane recenice: \n";
		for(int i=0; i<broj_recenica; i++)
		{
			std::cout<<recenice[i]<<"\n";
		}
		for(int i=0; i<broj_recenica; i++)
		{
			delete[] recenice[i];
		}
		delete[] recenice;
		return 0;
	}
	catch(std::bad_alloc)
	{
		std::cout<<"Problemi s memorijom!";
	}
}