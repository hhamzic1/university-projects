/*
    TP 16/17 (Tutorijal 9, Zadatak 5)

	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/ //ZALIJEPLJENO IZ CODE BLOCKSA

#include <iostream>
#include <stdexcept>
class Sat{
		int sekundi;
	public:
		static bool DaLiJeIspravno (int h, int min, int sec){ return (h<=24 && min<=60 && sec<=60 && h>=0 && min>=0 && sec>=0);}
		void Postavi (int h, int min, int sec);
		void PostaviNormalizirano (int h, int min, int sec);
		Sat Sljedeci();
		Sat Prethodni();
		Sat PomjeriZa(int br);
		void Ispisi() const;
		int DajSate() const {return sekundi/3600;}
		int DajMinute ()const {return sekundi%3600/60;}
		int DajSekunde() const {return sekundi-(sekundi/60)*60;}
		friend int BrojSekundiIzmedju(const Sat &s, const Sat &s2);
		static int Razmak(const Sat &s1, const Sat &s2){
			return s1.DajSekunde()+60*s1.DajMinute()+3600*s1.DajSate()-(s2.DajSekunde()+60*s2.DajMinute()+3600*s2.DajSate());
		}

};
int main (){
  	Sat s;
  	s.PostaviNormalizirano(20, 10, 360);
	 s.Ispisi(); std::cout << std::endl;
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

void Sat::Postavi(int h, int min, int sec){
	if(DaLiJeIspravno(h,min,sec))sekundi=sec+60*min+3600*h;
	else throw std::domain_error("Neispravno vrijeme");
}

void Sat::PostaviNormalizirano (int h, int min, int sec){
	while(sec<0){
		sec=60+sec;
		if(min==0){
			min=59;
			if(h==0) h=23;
		}
		else min--;
	}
	if(sec>=60){
		int ostatak_sec(sec/60);
		sec-=ostatak_sec*60;
		min+=ostatak_sec;
	}
	while(min<0){
		min=60+min;
		if(h==0) h=23;
		else h--;
	}
	if(min>=60){
		int ostatak_min(min/60);
		min-=ostatak_min*60;
		h+=ostatak_min;
	}
	while(h<0)h+=24;
	if(h>=24){
		int ostatak_h(h/24);
		h-=ostatak_h*24;
	}
	Postavi(h,min,sec);
}

Sat Sat::Sljedeci(){
	sekundi++;
	PostaviNormalizirano(DajSate(),DajMinute(),DajSekunde());
	return *this;
}

Sat Sat::Prethodni(){
	sekundi--;
	PostaviNormalizirano(DajSate(),DajMinute(),DajSekunde());
	return *this;
}

Sat Sat::PomjeriZa(int br){
	if(br>0){
		for(int i=0;i<br;i++) Sljedeci();
	}
	else{
		for(int i=0;i<-br;i++) Prethodni();
	}
	return *this;
}

void Sat::Ispisi() const{
	if(DajSate()<10)std::cout <<0<< DajSate() <<":";
	else std::cout << DajSate() <<":";
	if(DajMinute()<10)std::cout<<0<<DajMinute()<<":";
	else std::cout << DajMinute() <<":";
	if(DajSekunde()<10)std::cout<<0<<DajSekunde();
	else std::cout << DajSekunde();
}
int BrojSekundiIzmedju(const Sat &s1, const Sat &s2){
	return s1.DajSekunde()+60*s1.DajMinute()+3600*s1.DajSate()-(s2.DajSekunde()+60*s2.DajMinute()+3600*s2.DajSate());
}
