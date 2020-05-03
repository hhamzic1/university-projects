#include <stdexcept>
#include <iostream>
#include <cstring>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <memory>

class Tim
{
	char ime_tima[20];
	int broj_odigranih;
	int broj_pobjeda;
	int broj_nerijesenih;
	int broj_poraza;
	int broj_datih;
	int broj_primljenih;
	int broj_poena;
	public:
	
	Tim(const char ime[]);
	void ObradiUtakmicu(int broj_datih, int broj_primljenih);
	const char *DajImeTima() const {return ime_tima;}
	int DajBrojPoena() const{return broj_poena;}
	int DajGolRazliku() const{return broj_datih-broj_primljenih;}
	void IspisiPodatke() const
	{
		std::cout<<std::setw(20)<<std::left<<ime_tima<<std::setw(4)<<std::right<<std::right<<broj_odigranih<<std::setw(4)<<std::right<<broj_pobjeda<<std::setw(4)<<std::right<<broj_nerijesenih
		<<std::setw(4)<<std::right<<broj_poraza<<std::setw(4)<<std::right<<broj_datih<<std::setw(4)<<std::right<<broj_primljenih<<std::setw(4)<<std::right<<broj_poena<<std::endl;
	}
	
};

Tim::Tim(const char ime[])
{
	if(std::strlen(ime)>20) throw std::range_error("Predugacko ime tima");
	std::strcpy(ime_tima, ime);
	broj_datih=0; broj_nerijesenih=0; broj_odigranih=0; broj_pobjeda=0; broj_poena=0; broj_poraza=0; broj_primljenih=0;
}

void Tim::ObradiUtakmicu(int brdatih, int brprim)
{
	if(brdatih<0 || brprim<0) throw std::range_error("Neispravan broj golova");
	broj_odigranih++;
	if(brdatih>brprim){broj_datih+=brdatih; broj_primljenih+=brprim; broj_pobjeda++; broj_poena+=3;}
	else if(brdatih<brprim){broj_datih+=brdatih; broj_primljenih+=brprim; broj_poraza++;}
	else{broj_datih+=brdatih; broj_primljenih+=brprim; broj_nerijesenih++; broj_poena+=1;}
}

class Liga
{
	std::vector<std::shared_ptr<Tim>> timovi;
    public:
    explicit Liga(){}
    explicit Liga(std::initializer_list<Tim> lista_timova)
    {
    	timovi.resize(lista_timova.size());
        auto it(lista_timova.begin());
        for(int i=0; i<lista_timova.size(); i++) { timovi[i]=std::make_shared<Tim>(it->DajImeTima()); it++;}  //inicijalizacija preko konstruktora klase Tim!
    }
    ~Liga(){}
    Liga(const Liga &l)
    {
        timovi.resize(l.timovi.size());
        for(int i=0; i<l.timovi.size(); i++)
        {
        	timovi[i]=std::make_shared<Tim>(*(l.timovi[i]));
        }
    }
    Liga(Liga &&l)
    {
    	timovi.resize(l.timovi.size());
        for(int i=0; i<l.timovi.size(); i++)
        {
            timovi[i]=std::make_shared<Tim>(*(l.timovi[i]));
        }
        l.timovi.resize(0);
    }
    Liga &operator =(const Liga &l)
    {
        timovi=l.timovi;
        return *this;
    }
    
    Liga &operator =(Liga &&l)
    {
        timovi=l.timovi;
        l.timovi.resize(0);
        return *this;
    }
    
    void DodajNoviTim(const char ime_tima[])
    {
        timovi.push_back(std::make_shared<Tim>(ime_tima));
    }
    
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2);

    void IspisiTabelu()
    {
        std::sort(timovi.begin(), timovi.end(), [](std::shared_ptr<Tim> x, std::shared_ptr<Tim> y)
        {
            if(x->DajBrojPoena()==y->DajBrojPoena())
            {
                if(x->DajGolRazliku()==y->DajGolRazliku())
                {
                    if(strcmp(x->DajImeTima(), y->DajImeTima())<0) return true;
                    else {return false;}
                }
                return x->DajGolRazliku()>y->DajGolRazliku();
            }
            return x->DajBrojPoena()>y->DajBrojPoena();});
            
            for(int i=0; i<timovi.size(); i++) timovi[i]->IspisiPodatke();
    }
};

void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2)
{
    bool postoji=false, postoji2=false;
    int ind1, ind2;
    for(int i=0; i<timovi.size(); i++)
    {
        if(strcmp(timovi[i]->DajImeTima(), tim1)==0) {postoji=true; ind1=i;}
        if(strcmp(timovi[i]->DajImeTima(), tim2)==0) {postoji2=true; ind2=i;}
    }
    if(postoji && postoji2)
    {
        timovi[ind1]->ObradiUtakmicu(rezultat_1, rezultat_2);
        timovi[ind2]->ObradiUtakmicu(rezultat_2, rezultat_1);
    }
    else throw std::logic_error("Tim nije nadjen");
}

int main ()
{
    Liga l1{"Zeljeznicar", "Zrinjski", "Sarajevo", "Jedinstvo", "Borac", "Celik"};
    
    do
    {
        l1.IspisiTabelu();
        char s1[20], s2[20];
        try
        {
            std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
            std::cin.getline(s1,sizeof s1);
            std::cout<<"Unesite ime drugog tima: ";
            std::cin.getline(s2, sizeof s2);
            std::cout<<"Unesite broj postignutih golova za oba tima: ";
            int rez1, rez2;
            std::cin>>rez1>>rez2;
            l1.RegistrirajUtakmicu(s1,s2,rez1,rez2);
        }catch(std::logic_error e) { std::cout<<e.what()<<"\n";}
        catch(std::range_error e){ std::cout<<e.what()<<"\n";}
        catch(std::bad_alloc){ std::cout<<"Problemi sa memorijom"<<"\n";}
        std::cin.ignore(10000,'\n');
    }while(1);
    
	return 0;
}