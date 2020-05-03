
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

class Sat
{
		int sati,minute,sekunde;
		public:
		
		Sat &Sljedeci() {return PomjeriZa(1);}
		Sat &Prethodni() {return PomjeriZa(-1);}
		void Ispisi() const
		{
			std::cout<<std::setfill('0')<<std::setw(2)<<sati<<":"<<std::setw(2)<<minute<<":"<<std::setw(2)<<sekunde;
		}
		int DajSate() const{return Sat::sati;}
		int DajMinute() const{return Sat::minute;}
		int DajSekunde() const{return Sat::sekunde;}
		friend int BrojSekundiIzmedju(Sat s1, Sat s2);
		static int Razmak(Sat s1, Sat s2)
		{
			int broj;
			broj=(s1.sati*3600+s1.minute*60+s1.sekunde)-(s2.sati*3600+s2.minute*60+s2.sekunde);
			return broj;
		}

	static bool DaLiJeIspravno(int sat, int min, int sek)
	{
		if(sat<0 || sat>23 || min<0 || min>59 || sek<0 || sek>59) return false;
		return true;
	}
	
	void Postavi(int x, int y, int z)
	{
		if(!DaLiJeIspravno(x,y,z)) throw std::domain_error("Neispravno vrijeme");
		else
		{
			Sat::sati=x; Sat::minute=y; Sat::sekunde=z;
		}
	}
	
	void PostaviNormalizirano(int x, int y, int z)
	{
		if(x<0) x=24-std::abs(x%24);
		
		if(y<0)
		{
			y=60-std::abs(y%60);
			x--;
		}
		if(z<0)
		{
			if(y==0)
			{
				if(x==0) x=23;
				else x--;
				y=59;
			}
			else
			{
				y--;
				z=60-std::fabs(z%60);
			}
		}
		if(z>59)
		{
			y+=z/60;
			z=z%60;
		}
		if(y>59)
		{
			x+=y/60;
			y=y%60;
		}
		if(x>24) x=x%24;
		Sat::sati=x; Sat::minute=y; Sat::sekunde=z;
	}
	
	Sat &PomjeriZa(int broj)
	{
		if(broj>0)
		{
			sekunde+=broj;
			if(sekunde>=60)
			{
				minute+=sekunde/60;
				sekunde=sekunde%60;
			}
			if(minute>=60)
			{
				sati+=minute/60;
				minute=minute%60;
			}
			if(sati>23) sati=sati%24;
		}
		if(broj<0)
		{
			sekunde+=broj;
			if(sekunde<0)
			{
				minute--;
				minute+=sekunde/60;
				sekunde=60+sekunde%60;
			}
			if(minute<0)
			{
				sati--;
				sati+=minute/60;
				minute=60+minute%60;
			}
			if(sati<0) sati=24+sati%24;
		}
		return *this;
	}
};

int BrojSekundiIzmedju(Sat s1, Sat s2)
{
	return Sat::Razmak(s1,s2);
}

int main ()
{
	std::cout<<Sat::DaLiJeIspravno(10,15,30)<<"\n";
	std::cout<<Sat::DaLiJeIspravno(-10,15,30)<<"\n";
	Sat s1;
	s1.Postavi(5,5,5);
	s1.Ispisi();
	std::cout<<"\n";
	s1.Postavi(22,30,20);
	s1.Ispisi();
	std::cout<<"\n";
	s1.PostaviNormalizirano(24,60,60);
	s1.Ispisi();
	std::cout<<"\n";
	s1.Postavi(0,0,1);
	s1.Sljedeci();
	s1.Ispisi();
	std::cout<<"\n";
	s1.PomjeriZa(5);
	s1.Ispisi();
	std::cout<<"\n";
	Sat s2;
	s2.Postavi(0,0,0);
	std::cout<<Sat::Razmak(s1,s2);
	return 0;
}