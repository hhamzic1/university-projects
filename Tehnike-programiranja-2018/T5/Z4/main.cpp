
//PROFESOR JE REKAO DA JE KOPIRANJE DOZVOLJENO IZ TRECEG U CETVRTI NA HABERU

#include <algorithm>
#include <iostream>
#include <cmath>
#include <deque>

using std::deque;

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
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>n;
	deque<int> dek(n);
	std::cout<<"Unesite elemente: ";
	std::for_each(dek.begin(), dek.end(), [](int &x){std::cin>>x;});
	
	std::cout<<"Najveci element deka je "<<*std::max_element(dek.begin(), dek.end())<<"\n";
	std::cout<<"Najmanji element deka se pojavljuje "<<std::count(dek.begin(),dek.end(),*std::min_element(dek.begin(),dek.end()))<<" puta u deku\n";
	
	std::cout<<"U deku ima "<<std::count_if(dek.begin(),dek.end(), [](int x)->bool{if(sqrt(x)-int(sqrt(x))<=1e-10) return true; else return false;})<<" brojeva koji su potpuni kvadrati\n";
	
	deque<int> duzineCifara(n);
	std::transform(dek.begin(),dek.end(), duzineCifara.begin(), [](int broj) {if(broj==0) return 1; else return int(log10(std::abs(broj)))+1;});
	auto it=duzineCifara.begin();
	auto p = std::find(duzineCifara.begin(), duzineCifara.end(), *std::min_element(duzineCifara.begin(),duzineCifara.end()));
	std::cout<<"Prvi element sa najmanjim brojem cifara je "<<dek.at(p-it)<<"\n"; // index broja u pocetnom nizu
	
	deque<int> bezTrocifrenih(n);
	auto q=std::remove_copy_if(dek.begin(), dek.end(), bezTrocifrenih.begin(), [](int broj)->bool{
		if(int(log10(abs(broj)))+1==3) return true;
		return false;
	}); //puni niz brojevima koji nisu trocifreni 
	std::cout<<"Elementi koji nisu trocifreni su: ";
	std::for_each(bezTrocifrenih.begin(), q, [](const int &x){std::cout<<x<<" ";});
	
	return 0;
	
}