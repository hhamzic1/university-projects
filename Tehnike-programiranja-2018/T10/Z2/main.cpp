/* 
    TP 16/17 (Tutorijal 10, Zadatak 2)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <iomanip>
class Krug
{
	double r;
	public:
	explicit Krug(double x){ if(x<=0) throw std::domain_error("Neispravan poluprecnik"); else r=x;}
	void Postavi(double x) { if(x<=0) throw std::domain_error("Neispravan poluprecnik"); else r=x;}
	double DajPoluprecnik() const {return r;}
	double DajObim() const {return 2*r*4*atan(1);}
	double DajPovrsinu() const {return r*r*4*atan(1);}
	void Skaliraj(double x);
	void Ispisi() const { std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();}
};

void Krug::Skaliraj(double x)
{
	if(x<=0) throw std::domain_error("Neispravan faktor skaliranja");
	else r*=x;
}

class Valjak
{
	Krug baza;
	double visina;
	public:
	Valjak(double r, double x): baza(r){ if(r<0) throw std::domain_error("Neispravan poluprecnik"); if(x<0) throw std::domain_error("Neispravna visina"); else visina=x;}
	void Postavi(double r, double x){ if(r<0) throw std::domain_error("Neispravan poluprecnik"); if(x<0) throw std::domain_error("Neispravna visina"); else{visina=x; baza.Postavi(r);}}
	Krug DajBazu() const {return baza;}
	double DajPoluprecnikBaze() const {return baza.DajPoluprecnik();}
	double DajVisinu() const {return visina;}
	double DajPovrsinu() const{ return 2*DajPoluprecnikBaze()*4*atan(1)*visina+2*DajPoluprecnikBaze()*DajPoluprecnikBaze()*4*atan(1);}
	double DajZapreminu() const{ return DajPoluprecnikBaze()*DajPoluprecnikBaze()*4*atan(1)*visina;}
	void Skaliraj(double x);
	void Ispisi() const { std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnikBaze()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();}
};

void Valjak::Skaliraj(double x)
{
	if(x<=0) throw std::domain_error("Neispravan faktor skaliranja");
	else
	{
		visina*=x;
		baza.Skaliraj(x);
	}
}

int main ()
{
	Krug k(2);
	k.Ispisi();
	Valjak v(5,2);
	std::cout<<std::endl;
	v.Ispisi();
	return 0;
}