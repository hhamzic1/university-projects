/* 
    TP 16/17 (Tutorijal 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <algorithm>

using std::string;

string IzvrniBezRazmaka(string s)
{
	string izvrnuti;
	
	std::remove_copy(s.rbegin(), s.rend(), back_inserter(izvrnuti),' ');
	return izvrnuti;
}
int main ()
{
	return 0;
}