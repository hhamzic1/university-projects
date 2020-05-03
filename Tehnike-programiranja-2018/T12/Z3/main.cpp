/* 
    TP 16/17 (Tutorijal 12, Zadatak 3)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <vector>
#include <string>

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

std::ostream &operator <<(std::ostream &tok, Dani d)
{
	std::vector<std::string> v{"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"}; 
	tok<<v[d];		//d se konvertuje u int
	return tok;
}
Dani &operator ++(Dani &d)
{
	return d=Dani((int(d)+1)%7);
}
Dani operator ++(Dani &d, int)
{
	Dani pomocni(d); ++d; return pomocni;
}
int main ()
{
	for(Dani d=Ponedjeljak; d<=Nedjelja; d++)
	{
		std::cout<<d<<std::endl;
		if(d==Nedjelja) break;
	}
	return 0;
}