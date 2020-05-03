/* 
    TP 16/17 (Tutorijal 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <list>
#include <algorithm>
#include <set>
#include <string>

using std::list;
using std::multiset;
template<typename tip>
	auto SortirajListu(list<tip> &lista)->list<tip>
	{
		multiset<tip> skup;
		auto it=lista.begin();
		while(it!=lista.end()) skup.insert(*it++);
		
			auto novaLista=lista;
			it=novaLista.begin();
			auto it2=skup.begin();
			while(it!=novaLista.end()) *it++=*it2++;
			lista=novaLista;
			return lista;
		
	}

int main ()
{
	std::cout<<"Koliko ima elemenata: ";
	int n;
	std::cin>>n;
	list<int>lista;
	auto umetac=back_inserter(lista);
	std::cout<<"Unesite elemente: ";
	for(int i=0; i<n; i++)
	{
		int x;
		std::cin>>x;
		*umetac=x;
	}
	auto novaLista=SortirajListu(lista);
	std::cout<<"Sortirana lista: ";
	for(auto x : novaLista) std::cout<<x<<" ";
	return 0;
}