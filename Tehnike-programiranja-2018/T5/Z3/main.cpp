#include <algorithm>
#include <iostream>
#include <cmath>

void unesi(int &x)
{
	std::cin>>x;
}

bool potpunKvadrat(int x)
{
	if(std::sqrt(x)-floor(sqrt(x))<=1e-10) return true;
	return false;
}

int brojCifara(int broj)
{
	if(broj==0) return 1;
	return int(log10(std::abs(broj)))+1;

}

bool Trocifren(int broj)
{
	if(int(log10(abs(broj)))+1==3) return true;
	return false;
}
void Ispisi(const int &x)
{
	std::cout<<x<<" ";
}


int main ()
{
	int n;
	std::cout<<"Unesite broj elemenata (max. 1000): ";
	std::cin>>n;
	int niz[1000];
	std::cout<<"Unesite elemente: ";
	std::for_each(&niz[0], &niz[n], unesi);
	
	std::cout<<"Najveci element niza je "<<*std::max_element(&niz[0], &niz[n])<<"\n";
	std::cout<<"Najmanji element niza se pojavljuje "<<std::count(&niz[0],&niz[n],*std::min_element(&niz[0],&niz[n]))<<" puta u nizu\n";
	
	std::cout<<"U nizu ima "<<std::count_if(&niz[0],&niz[n], potpunKvadrat)<<" brojeva koji su potpuni kvadrati\n";
	
	int duzineCifara[1000];
	std::transform(&niz[0],&niz[n],&duzineCifara[0],brojCifara);
	auto p = std::find(&duzineCifara[0], &duzineCifara[n], *std::min_element(&duzineCifara[0],&duzineCifara[n]));
	std::cout<<"Prvi element sa najmanjim brojem cifara je "<<niz[p-duzineCifara]<<"\n"; // index broja u pocetnom nizu
	
	int bezTrocifrenih[1000];
	auto q=std::remove_copy_if(&niz[0], &niz[n], &bezTrocifrenih[0], Trocifren); //puni niz brojevima koji nisu trocifreni 
	std::cout<<"Elementi koji nisu trocifreni su: ";
	std::for_each(&bezTrocifrenih[0], q, Ispisi);
	
}