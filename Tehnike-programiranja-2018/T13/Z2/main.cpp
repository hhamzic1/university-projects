/* 
    TP 16/17 (Tutorijal 13, Zadatak 2)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>

using std::string;

class ApstraktniStudent
{
	protected:
	string ime;
	string prezime;
	int br_indeksa;
	int broj_polozenih;
	double prosjek;
	
	public:
		ApstraktniStudent(string ime, string prezime, int br_indeksa): ime(ime), prezime(prezime), br_indeksa(br_indeksa), broj_polozenih(0), prosjek(5) {}
		virtual ~ApstraktniStudent() {}
		string DajIme() const {return ime;}
		string DajPrezime() const{return prezime;}
		int DajBrojIndeksa() const{return br_indeksa;}
		int DajBrojPolozenih() const{return broj_polozenih;}
		double DajProsjek() const{return prosjek;}
		void RegistrirajIspit(int ocjena)
		{
			if(ocjena<5 || ocjena >10) throw std::domain_error("Neispravna ocjena");
			if(ocjena==5) return;
			double suma=prosjek*broj_polozenih;
			prosjek=(suma+ocjena)/(++broj_polozenih);
		}
		void PonistiOcjene() {broj_polozenih=0; prosjek=5;}
		virtual void IspisiPodatke() const=0;
		virtual ApstraktniStudent* DajKopiju() const=0;
};

class StudentBachelor: public ApstraktniStudent
{
	public:
		StudentBachelor(string ime, string prezime, int br_indeksa): ApstraktniStudent(ime, prezime, br_indeksa) {}
		void IspisiPodatke() const override
		{
			std::cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nima prosjek "<<DajProsjek()<<".\n";
		}
		ApstraktniStudent* DajKopiju() const override {return new StudentBachelor(*this);}
};

class StudentMaster: public ApstraktniStudent
{
	int god_dipl;
	public:
		StudentMaster(string ime, string prezime, int br_indeksa, int god_dipl):
			ApstraktniStudent(ime,prezime,br_indeksa), god_dipl(god_dipl){}
		ApstraktniStudent* DajKopiju() const override {return new StudentMaster(*this);}
		void IspisiPodatke() const override
		{
			std::cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nzavrsio bachelor studij godine "<<god_dipl<<",ima prosjek "<<DajProsjek()<<".\n";
		}
};
int main ()
{
	return 0;
}