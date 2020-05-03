#include <stdexcept>
#include <iostream>
#include <cstring>
#include <string.h>
#include <iomanip>
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


int main ()
{
	Tim t1("FK Velez");
	Tim t2("FK Svinjski");
	Tim t3("FK Zeljeznicar");
	
	t1.ObradiUtakmicu(3,0);
	t1.ObradiUtakmicu(3,1);
	t1.ObradiUtakmicu(2,2);
	t2.ObradiUtakmicu(0,5);
	t2.ObradiUtakmicu(0,2);
	t2.ObradiUtakmicu(1,3);
	t3.ObradiUtakmicu(1,1);
	t3.ObradiUtakmicu(4,1);
	t3.ObradiUtakmicu(0,1);
	
	t1.IspisiPodatke();
	
	t2.IspisiPodatke();
	
	t3.IspisiPodatke();
	
	return 0;
}