#include <iostream>
#include <cmath>

int main()
{
    double a, b, c;
    std::cout<<"Unesite tri broja: ";
    std::cin>>a>>b>>c;
    double max=a;
    if(b>a && b>=c) max=b;
    else if(b>a && b<c) max=c;
    else if(c>a && c>=b) max=c;
    else if(c>a && c<b) max=b;
    
    if(max==a)
    {
        if(b+c<=max)
        {
            std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
            return 0;
            
        }
    }
    else if(max==b)
    {
        if(a+c<=max)
        {
            std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
            return 0;
        }
    }
    else if(max==c)
    {
        if(a+b<=max)
        {
            std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
            return 0;
        }
    }
    
    double obim, povrsina, s;
    obim=a+b+c;
    s=obim/2;
    std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<obim<<".\n";
    double heron=s*(s-a)*(s-b)*(s-c);
    povrsina=sqrt(heron);
    std::cout<<"Njegova povrsina iznosi "<<povrsina<<".\n";
    double min, suma;
    double pi=4*atan(1);
    if(max==a)
    {
        if(b<=c) min=b;
        if(b>c) min=c;
    }
    else if(max==b)
    {
        if(a<=c) min=a;
        if(a>c) min=c;
    }
    else if(max==c)
    {
        if(a<=b) min=a;
        if(a>b) min=b;
    }
    
    double ugao, stepeni, minute, sekunde;
    if(min==a)
    {
        suma=b*b+c*c-(a*a);
        ugao=suma/(2*b*c);
        ugao=acos(ugao)*(180.0/pi);
        stepeni=floor(ugao);
        minute=ugao-floor(ugao);
        minute=minute*60;
        sekunde=minute-floor(minute);
        sekunde=sekunde*60;
        std::cout<<"Njegov najmanji ugao ima "<<stepeni<<" stepeni, "<<floor(minute)<<" minuta i "<<floor(sekunde)<<" sekundi.";
    }
    
    else if(min==b)
    {
        suma=a*a + c*c-(b*b);
        ugao=suma/(2*a*c);
        ugao=acos(ugao)*(180.0/pi);
        stepeni=floor(ugao);
        minute=ugao-floor(ugao);
        minute=minute*60;
        sekunde=minute-floor(minute);
        sekunde=sekunde*60;
        std::cout<<"Njegov najmanji ugao ima "<<stepeni<<" stepeni, "<<floor(minute)<<" minuta i "<<floor(sekunde)<<" sekundi.";
    }
    else if(min==c)
    {
        suma=a*a+b*b-(c*c);
        ugao=suma/(2*b*a);
        ugao=acos(ugao)*(180.0/pi);
        stepeni=floor(ugao);
        minute=ugao-floor(ugao);
        minute=minute*60;
        sekunde=minute-floor(minute);
        sekunde=sekunde*60;
        std::cout<<"Njegov najmanji ugao ima "<<stepeni<<" stepeni, "<<floor(minute)<<" minuta i "<<floor(sekunde)<<" sekundi.";
    }
    return 0;

}