/* 
    TP 16/17 (Tutorijal 12, Zadatak 5)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main ()
{
	std::vector<double> v;
	std::cout<<"Koliko zelite elemenata: ";
	int n; std::cin>>n;
	v.resize(n);
	std::cout<<"Unesite elemente: ";
	for(int i=0; i<n; i++)std::cin>>v[i];
	std::cout<<"Transformirani elementi: ";
	std::transform(v.begin(), v.end(), v.begin(), std::bind(std::divides<double>(), 1, std::placeholders::_1));  //moglo se koristit i bind1st
	for(int i=0; i<n; i++) std::cout<<v[i]<<" ";													//al i ovo je ekvivalnentno, uglavnom citav vektor se transformiše
	return 0;																						//u recipročnu vrijednost pomoću funkcijskog objekta i bind-a
}