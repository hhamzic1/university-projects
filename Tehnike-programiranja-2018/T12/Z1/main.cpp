/* 
    TP 16/17 (Tutorijal 12, Zadatak 1)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
class Sat
{
	int sati, minuta, sekundi;
	public:
	Sat(){sati=0; minuta=0; sekundi=0;}
	Sat(int h, int min, int sec){PostaviNormalizirano(h,min,sec);}
	static bool DaLiJeIspravno(int h, int min, int sec){ return (h<=24 && min<=60 && sec<=60 && h>=0 && min>=0 && sec>=0);}
	void Postavi(int h, int min, int sec);
	void PostaviNormalizirano(int h, int min , int sec);
	Sat &operator ++();  //obični operator inkrementacije kao član klase izveden
	Sat &operator --();
	Sat operator +=(int br);			//poziva se nad objektima
	Sat operator -=(int br){return operator +=(-br);}
	friend std::ostream &operator <<(std::ostream &tok, const Sat &s)
	{
		if(s.sati<10)tok<<0<<s.sati<<":";
		else tok<<s.sati<<":";
		if(s.minuta<10)tok<<0<<s.minuta<<":";
		else tok<<s.minuta<<":";
		if(s.sekundi<10)tok<<0<<s.sekundi;
		else tok<<s.sekundi;
		return tok;
	}
	int DajSate() const {return sati;}
	int DajMinute() const{return minuta;}
	int DajSekunde() const{return sekundi;}
	friend int operator -(const Sat &s, const Sat &s2);
	Sat operator +(int n)
	{
		Sat s(sati, minuta, sekundi+n);
		return s;
	}
	Sat operator -(int n)
	{
		Sat s(sati,minuta,sekundi-n);
		return s;
	}
	Sat operator --(int)
	{
		Sat s(sati,minuta,sekundi);
		sekundi--;
		if(sekundi<0) sekundi=59, minuta--;
		if(minuta<0) minuta=59, sati--;
		if(sati<0) sati=23;
		return s;
	}
	Sat operator ++(int)
	{
		Sat s(sati,minuta,sekundi);
		sekundi++;
		if(sekundi==60) sekundi=0, minuta++;
		if(minuta==60)minuta=0, sati++;
		if(sati==24) sati=0;
		return s;
	}
};

void Sat::Postavi(int h, int min, int sec)
{
	if(DaLiJeIspravno(h,min,sec)){sati=h; minuta=min; sekundi=sec;}
	else throw std::domain_error("Neispravno vrijeme");
}
Sat Sat::operator +=(int br)
{
	if(br>0)
	{
		for(int i=0; i<br; i++) this->operator ++();
	}
	else
	{
		for(int i=0; i<-br; i++) this->operator --();
	}
	return *this;
}

int operator -(const Sat &s1, const Sat &s2)
{
	int sec1(s1.DajSate()*3600+s1.DajMinute()*60+s1.DajSekunde());
	int sec2(s2.DajSate()*3600+s2.DajMinute()*60+s2.DajSekunde());
	return sec1-sec2;
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
	if(sec>60){
		int ostatak_sec(sec/60);
		sec-=ostatak_sec*60;
		min+=ostatak_sec;
	}
	while(min<0){
		min=60+min;
		if(h==0) h=23;
		else h--;
	}
	if(min>60){
		int ostatak_min(min/60);
		min-=ostatak_min*60;
		h+=ostatak_min;
	}
	

	while(h<0)h+=24;

	if(h>24){
		int ostatak_h(h/24);
		h-=ostatak_h*24;
	}
	
	sati=h;
	minuta=min;
	sekundi=sec;
}

Sat &Sat::operator++()
{
	sekundi++;
	if(sekundi==60) sekundi=0, minuta++;
	if(minuta==60) minuta=0, sati++;
	if(sati==24) sati=0;
	return *this;
}
Sat &Sat::operator --()
{
	sekundi--;
	if(sekundi<0) sekundi=59, minuta--;
	if(minuta<0)minuta=59, sati--;
	if(sati<0) sati=23;
	return *this;
}

int main()
{
	Sat s1(10,4,39);
	std::cout<<s1<<std::endl;
	Sat s2(25,150,290);
	std::cout<<s2<<std::endl;
	++s1;
	std::cout<<s1<<std::endl;
	return 0;
}