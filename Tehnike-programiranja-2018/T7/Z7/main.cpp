/* 
    TP 16/17 (Tutorijal 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <set>
#include <string>

using std::string;
using std::set;

template<typename tip>
	auto Unija(set<tip> skupA, set<tip> skupB)->set<tip>
	{
		for(auto x : skupB) skupA.insert(x);
		return skupA;
	}
template<typename tip>
	auto Presjek(set<tip> skupA, set<tip> skupB)->set<tip>
	{
		set<tip> presjek;
		for(tip x : skupA)
			{
				if(skupB.count(x)) presjek.insert(x);
			}
			return presjek;
	}
int main ()
{
	set<string> skup1{"Huso", "Voli", "Lamiju"};
	set<string> skup2{"ja", "sam", "Huso"};
	auto unija=Unija(skup1, skup2);
	auto presjek=Presjek(skup1, skup2);
	std::cout<<"unija: ";
	for(string x : unija) std::cout<<x<<" ";
	std::cout<<"\npresjek: ";
	for(string x : presjek) std::cout<<x<<" ";
	return 0;
}