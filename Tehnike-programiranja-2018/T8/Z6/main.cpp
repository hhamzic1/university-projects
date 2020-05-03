//TP 2018/2019: Tutorijal 8, Zadatak 6
#include <iostream>

template<typename Tip>
struct Cvor
{
    Tip element;
    Cvor* veza;
};

template<typename TipElementa>
Cvor<TipElementa> *KreirajPovezanuListu(TipElementa zavrsni)
{
    Cvor<TipElementa> *pocetak=nullptr, *prethodni;
    for(;;)
    {
        TipElementa x;
        std::cin>>x;
        if(x==zavrsni) break;
        Cvor<TipElementa> *novi=new Cvor<TipElementa>{x,nullptr};
        if(!pocetak) pocetak=novi;
        else prethodni->veza=novi;
        prethodni=novi;
        
    }
    return pocetak;
}

template<typename TipElementa>
int BrojElemenata(Cvor<TipElementa> *pocetak)
{
    int brojac=0; 
    for(auto p=pocetak; p!=nullptr; p=p->veza) brojac++;
    return brojac;
}

template<typename TipElementa>
TipElementa SumaElemenata(Cvor<TipElementa> *pocetak)
{
    TipElementa suma={};
    for(auto p=pocetak; p!=nullptr; p=p->veza) 
    {
        suma+=p->element;
    }
    return suma;
}

template<typename TipElementa>
int BrojVecihOd(Cvor<TipElementa> *pocetak, TipElementa prag)
{
    int brojac=0;
    for(auto p=pocetak; p!=nullptr; p=p->veza)
    {
        if(p->element>prag) brojac++;
    }
    return brojac;
}

template<typename TipElementa>
void UnistiListu(Cvor<TipElementa> *pocetak)
{
    auto trenutni=pocetak;
    Cvor<TipElementa> *next;
    while(trenutni!=nullptr)
    {
        next=trenutni->veza;
        delete trenutni;
        trenutni=next;
    }
}

int main ()
{
	std::cout<<"Unesite slijed brojeva (0 za kraj): ";
	Cvor<double> *pocetak=KreirajPovezanuListu<double>(0);
	int vodarit=BrojVecihOd<double>(pocetak,SumaElemenata<double>(pocetak)/BrojElemenata<double>(pocetak));
	std::cout<<"U slijedu ima "<<vodarit<<" brojeva vecih od njihove aritmeticke sredine";
	UnistiListu(pocetak);
	return 0;
}