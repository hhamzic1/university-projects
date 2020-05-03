/* 
    TP 16/17 (Tutorijal 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <cmath>

class Lik
{
	public:
	virtual ~Lik(){}
	virtual void IspisiSpecificnosti() const =0;
	virtual double DajObim() const =0;
	virtual double DajPovrsinu() const =0;
	void Ispisi() const
	{
		IspisiSpecificnosti();
		std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<std::endl;
	}
};

class Krug: public Lik
{
	double r;
	static constexpr double PI=3.141592653589793;
	public:
	Krug (double pol)
	{
		if(pol<=0) throw std::domain_error("Neispravni parametri");
		r=pol;
	}
	virtual double DajObim() const {return 2*PI*r;}
	virtual double DajPovrsinu() const{return r*r*PI;}
	virtual void IspisiSpecificnosti() const
	{
		std::cout<<"Krug poluprecnika "<<r<<std::endl;
	}
};

class Pravougaonik: public Lik
{
	double a,b;
	public:
		Pravougaonik(double a1, double b1)
		{
			if(a1<=0||b1<=0) throw std::domain_error("Neispravni parametri");
			a=a1; b=b1;
		}
		virtual double DajObim() const{return 2*a+2*b;}
		virtual double DajPovrsinu() const{return a*b;}
		virtual void IspisiSpecificnosti() const
		{
			std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<std::endl;
		}
};

class Trougao: public Lik
{
	double a,b,c;
	public:
		Trougao(double a1, double b1, double c1)
		{
			if(a1<=0 || b1<=0 || c1<=0) throw std::domain_error("Neispravni parametri");
			if(a1+b1<=c1) throw std::domain_error("Neispravni parametri");
			if(a1+c1<=b1) throw std::domain_error("Neispravni parametri");
			if(c1+b1<=a1) throw std::domain_error("Neispravni parametri");
			a=a1; b=b1; c=c1;
		}
		virtual double DajObim()const {return a+b+c;}
		virtual double DajPovrsinu() const
		{
			double s=(a+b+c)/2;
			return sqrt(s*(s-a)*(s-b)*(s-c));
		}
		virtual void IspisiSpecificnosti() const
		{
			std::cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<std::endl;
		}
};
int main ()
{
	std::cout<<"Koliko zelite likova: ";
	int n; std::cin>>n;
	std::vector<std::shared_ptr<Lik>> likovi(n);
	for(int i=0; i<n; i++)
	{
		std::cin.clear();
		std::cin.ignore(10000,'\n');
		std::cout<<"Lik "<<i+1<<": ";
		char slovo, zarez(',');
		std::cin>>slovo;
		if(slovo=='P')
		{
			double a,b;
			std::cin>>a>>zarez>>b;
			if(!std::cin || zarez!=',' || std::cin.peek()!='\n')
			{
				std::cout<<"Pogresni podaci, ponovite unos!\n";
				i--;
				continue;
			}
			try
			{
				likovi[i]=std::make_shared<Pravougaonik>(a,b);
			}
			catch(std::domain_error e)
			{
				std::cout<<"Pogresni podaci, ponovite unos!\n";
				i--;
				continue;
			}
		}
		else if(slovo== 'K')
		{
			double r;
			std::cin>>r;
			if(!std::cin || std::cin.peek()!='\n')
			{
				std::cout<<"Pogresni podaci, ponovite unos!\n";
				i--;
				continue;
			}
			try
			{
				likovi[i]=std::make_shared<Krug>(r);
			}
			catch(std::domain_error e)
			{
				std::cout<<"Pogresni podaci, ponovite unos!\n";
				i--;
				continue;
			}
		}
		else if(slovo=='T')
		{
			double a,b,c;
			char znak='0';
			std::cin>>a>>znak; if(znak==',') std::cin>>b>>znak>>c;
			if(!std::cin || znak!=',' || std::cin.peek()!='\n')
			{
				std::cout<<"Pogresni podaci, ponovite unos!\n";
				i--;
				continue;
			}
			try{
				likovi[i]=std::make_shared<Trougao>(a,b,c);
			}
			catch(std::domain_error e)
			{
				std::cout<<"Pogresni podaci, ponovite unos!\n";
				i--;
				continue;
			}
		}
		else
		{
			std::cout<<"Pogresni podaci, ponovite unos!\n";
			i--;
		}
	
	}
	std::cout<<std::endl;
	
	for(auto x:likovi) x->Ispisi();
	return 0;
}