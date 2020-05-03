
#include <iostream>
#include <stdexcept>
#include <cmath>
class StedniRacun
{
	double stanje;
	static int brojacsvih;
	static int brojacaktivnih;
	public:
	StedniRacun() {stanje=0; brojacsvih++; brojacaktivnih++;}
	StedniRacun(const StedniRacun &x)
	{
		if(x.stanje<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
		stanje=x.stanje;
		brojacaktivnih++;
		brojacsvih++;
	}
	
	explicit StedniRacun(double x);
	void Ulozi(double x);
	void Podigni(double x);
	double DajStanje() const {return stanje;} 
	void ObracunajKamatu(double x);
	static int DajBrojKreiranih() {return brojacsvih;}
	static int DajBrojAktivnih() {return brojacaktivnih;}
	~StedniRacun(){brojacaktivnih--;}
};

StedniRacun::StedniRacun(double x)
{
	if(x<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
	else{ stanje=x;
	brojacsvih++;
	brojacaktivnih++;}
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

int StedniRacun::brojacaktivnih(0);
int StedniRacun::brojacsvih(0);

int main ()
{
	StedniRacun s1, s2(100);
	{StedniRacun s3(50);}
	std::cout<<StedniRacun::DajBrojKreiranih()<<" "<<StedniRacun::DajBrojAktivnih()<<std::endl;
	
	return 0;
}