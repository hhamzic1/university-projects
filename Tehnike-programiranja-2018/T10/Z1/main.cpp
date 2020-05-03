
#include <iostream>
#include <stdexcept>
#include <cmath>
class StedniRacun
{
	double stanje;
	public:
	StedniRacun() {stanje=0;}
	StedniRacun(double x);
	void Ulozi(double x);
	void Podigni(double x);
	double DajStanje() const {return stanje;} 
	void ObracunajKamatu(double x);
};

StedniRacun::StedniRacun(double x)
{
	if(x<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
	else stanje=x;
}

void StedniRacun::Ulozi(double x)
{
	if(x<0 && std::abs(x)>stanje) throw std::logic_error("Transakcija odbijena");
	else stanje+=x;
}
void StedniRacun::Podigni(double x)
{
	if(std::abs(x)<=stanje) stanje-=x;
	else throw std::logic_error("Transakcija odbijena");
}
void StedniRacun::ObracunajKamatu(double x)
{
	if(x<0) throw std::logic_error("Nedozvoljena kamatna stopa");
	stanje+=(stanje*x)/100.0;
}

int main ()
{
	StedniRacun ja;
	ja.Ulozi(50);
	ja.ObracunajKamatu(5);
	std::cout<<ja.DajStanje();
	
	return 0;
}