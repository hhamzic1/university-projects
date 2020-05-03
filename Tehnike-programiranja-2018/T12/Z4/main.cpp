/* 
    TP 16/17 (Tutorijal 12, Zadatak 4)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <complex>
typedef std::complex<int> Kompleksni;

std::ostream &operator <<(std::ostream &tok, Kompleksni c)
{
	if(c.real()!=0)tok<<c.real();
	if(c.imag()==1 && c.real()!=0)tok<<"+"<<"i";
	else if(c.imag()==1 && c.real()==0)tok<<"i";
	else if(c.imag()==-1)tok<<"-"<<"i";
	else if(c.imag()!=0)							
	{
		if(c.imag()>0 && c.real()!=0) tok<<"+"<<c.imag()<<"i";
		else tok<<c.imag()<<"i";
	}
	if(c.real()==0 && c.imag()==0)tok<<0;
	return tok;
}
int main ()
{
	std::cout<<Kompleksni(-1,1);
	return 0;
}