#include <cmath>
#include <iomanip>
#include <iostream>
#define PI 4*atan(1)

double visak(double rad)
{
	while(rad>=2*PI) rad-=2*PI;
	while(rad<0) rad+=2*PI;
	return rad;
}

int sekunde(double rad)
{
	return rad*360*60*60/(2*PI);
}

class Ugao
{
	double rad;
	public:
	Ugao(double radijani=0){rad=visak(radijani);}
	Ugao(int stepeni, int minute, int sekunde){rad=visak((stepeni+minute/60.+sekunde/3600.)*PI/180);}
	void Postavi(double radijani){rad=visak(radijani);}
	void Postavi(int stepeni, int minute, int sekunde){rad=visak((stepeni+ minute/60. + sekunde/3600.)*PI/180);}
	double DajRadijane() const{return rad;}
	void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)
	{
		stepeni=int(180*rad/PI);
		minute=int(180*rad/PI*60);
		sekunde=int(180*rad/PI*3600);
	}
	int DajStepene() const{return sekunde(rad)/3600;}
	int DajMinute() const{return (sekunde(rad)/60)%60;}
	int DajSekunde() const{return sekunde(rad)%60;}
	void Ispisi() const{std::cout<<std::fixed<<std::setprecision(5)<<rad;}
	void IspisiKlasicno() const{std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec ";}
	Ugao &SaberiSa(const Ugao &u)
	{
		rad=visak(rad+u.DajRadijane()+5e-8);
		return *this;
	}
	Ugao &PomnoziSa(double x)
	{
		rad=visak(rad*x);
		return *this;
	}
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2)
{
	return visak(u1.DajRadijane()+u2.DajRadijane());
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x)
{
	return visak(u.DajRadijane()*x);
}

int main ()
{
	Ugao u(20,25,12), v(300, 600, 200), f(59, 59, 59), g;
	f.Postavi(100);
	v.Postavi(200,400,300);
	u.SaberiSa(f);
	u.PomnoziSa(0.69);
	u.IspisiKlasicno(); std::cout<<"\n";
	const Ugao u1(u);
	std::cout<<u1.DajRadijane()<<" "<<u1.DajStepene()<<" "<<u1.DajMinute();
	std::cout<<std::endl;
	f=ZbirUglova(u1,u);
	
	return 0;
}

