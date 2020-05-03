//TP 2018/2019: Tutorijal 8, Zadatak 1
#include <iostream>
#include <iomanip>
#include <stdexcept>

struct Vrijeme
{
    int sati, minute, sekunde;
};


Vrijeme unesi(Vrijeme v)
{
    void TestirajVrijeme(Vrijeme);
    Vrijeme nova;
    std::cin>>nova.sati;
    std::cin>>nova.minute;
    std::cin>>nova.sekunde;
    TestirajVrijeme(nova);
    return nova;
}

void TestirajVrijeme(Vrijeme v)
{
    if(v.sati<0 || v.sati>23 || v.minute<0 || v.minute>59 || v.sekunde<0 || v.sekunde>59) throw std::domain_error("Neispravno vrijeme");
    return;
}

void IspisiVrijeme(Vrijeme v)
{
    TestirajVrijeme(v);
    std::cout<<std::setfill('0')<<std::setw(2)<<v.sati<<":"<<std::setw(2)<<v.minute<<":"<<std::setw(2)<<v.sekunde<<std::endl;
    
}

Vrijeme SaberiVrijeme(Vrijeme v1, Vrijeme v2)
{
    TestirajVrijeme(v1);
    TestirajVrijeme(v2);
    int sekunde1=v1.sati*3600 + v1.minute*60 + v1.sekunde;
    int sekunde2=v2.sati*3600 + v2.minute*60 + v2.sekunde;
    
    int suma=sekunde1+sekunde2;
    
    Vrijeme nova;
    
    if((suma/3600)>=24)
    {
        int h=(suma/3600)/24;
    
        nova.sati=suma/3600 - 24*h;
        suma=suma-(h*24*3600);
        if(nova.sati==0) suma=0;
    }
    else
    {
        nova.sati=suma/3600;
    }
    suma=suma-nova.sati*3600;
    nova.minute=suma/60;
    suma=suma-nova.minute*60;
    nova.sekunde=suma;
    TestirajVrijeme(nova);
    return nova;
}



int main ()
{
    Vrijeme a, b;
    try
    {
    std::cout<<"Unesite prvo vrijeme (h m s): ";
    auto s=unesi(a);
    std::cout<<"Unesite drugo vrijeme (h m s): ";
    auto k=unesi(b);
    std::cout<<"Prvo vrijeme: ";
    IspisiVrijeme(s);
    std::cout<<"Drugo vrijeme: ";
    IspisiVrijeme(k);
    auto n=SaberiVrijeme(s, k);
    std::cout<<"Zbir vremena: ";
    IspisiVrijeme(n);
    }catch(std::domain_error e){std::cout<<e.what();}
    
	return 0;
}