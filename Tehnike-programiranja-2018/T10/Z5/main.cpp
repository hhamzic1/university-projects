#include <cmath>
#include <iomanip>
#include <iostream>
#define PI 4*atan(1)


void PostaviNormalizirano(int &h, int &min, int &sec)
{
	while(sec<0)
	{
		sec=60+sec;
		if(min==0)
		{
			min=59;
			if(h==0) h=59;
		}
		else min--;
	}
	if(sec>60)
	{
		int ostatak_sec(sec/60);
		sec-=ostatak_sec*60;
		min+=ostatak_sec;
	}
	while(min<0)
	{
		min=60+min;
		if(h==0) h=59;
		else h--;
	}
	if(min>60)
	{
		int ostatak_min(min/60);
		min-=ostatak_min*60;
		h+=ostatak_min;
	}
	
	while(h<0) h+=360;
	
	if(h>360)
	{
		int ostatak_h(h/360);
		h-=ostatak_h*360;
	}
}

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
	int step, min, sec;
	public:
	Ugao(double radijani=0)
	{
		double rad=visak(radijani);
		step=sekunde(rad)/3600;
		min=(sekunde(rad)/60)%60;
		sec=sekunde(rad)%60;
		PostaviNormalizirano(step, min, sec);
	}
	Ugao(int stepeni, int minute, int sekunde)
	{
		step=stepeni; min=minute; sec=sekunde;
		PostaviNormalizirano(step,min,sec);
	}
	void Postavi(double radijani)
	{
		double rad=visak(radijani);
		step=sekunde(rad)/3600;
		min=(sekunde(rad)/60)%60;
		sec=sekunde(rad)%60;
		PostaviNormalizirano(step, min, sec);
	}
	void Postavi(int stepeni, int minute, int sekunde)
	{
		step=stepeni; min=minute; sec=sekunde; PostaviNormalizirano(step,min,sec);
		
	}
	double DajRadijane() const{return visak((step+min/60. +sec/3600.)*PI/180);}
	void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)
	{
		stepeni=step;
		minute=min;
		sekunde=sec;
	}
	int DajStepene() const{return step;}
	int DajMinute() const{return min;}
	int DajSekunde() const{return sec;}
	void Ispisi() const{std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane();}
	void IspisiKlasicno() const{std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec ";}
	Ugao &SaberiSa(const Ugao &u)
	{
		double rad=visak(DajRadijane()+u.DajRadijane()+5e-8);
		step=sekunde(rad)/3600;
		min=(sekunde(rad)/60)%60;
		sec=sekunde(rad)%60;
		return *this;
	}
	Ugao &PomnoziSa(double x)
	{
		double rad=visak(DajRadijane()*x);
		step=sekunde(rad)/3600;
		min=(sekunde(rad)/60)%60;
		sec=sekunde(rad)%60;
		PostaviNormalizirano(step,min,sec);
		return *this;
	}
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2)
{
	return visak(u1.DajRadijane()+u2.DajRadijane()+5e-8);
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

