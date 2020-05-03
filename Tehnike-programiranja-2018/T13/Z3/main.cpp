/* 
    TP 16/17 (Tutorijal 13, Zadatak 3)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

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

class Fakultet
{
	vector<ApstraktniStudent*> studenti;
	public:
		~Fakultet() {for(int i=0; i<studenti.size(); i++) delete studenti[i];}
		Fakultet()=default;
		Fakultet(const Fakultet &f)
		{
			studenti.resize(f.studenti.size());
			for(int i=0; i<f.studenti.size(); i++)
				studenti[i]=f.studenti[i]->DajKopiju();
		}
		Fakultet(Fakultet &&f)
		{
			studenti=std::move(f.studenti);
		}
		Fakultet &operator =(Fakultet f)
		{
			std::swap(studenti, f.studenti);
			return *this;
		}
		void UpisiStudenta(string ime, string prezime, int br_indeksa)
		{
			for(int i=0; i<studenti.size(); i++)
			{
				if(studenti[i]->DajBrojIndeksa()==br_indeksa)
					throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
			}
			studenti.push_back(new StudentBachelor(ime, prezime, br_indeksa));
		}
		void UpisiStudenta(string ime, string prezime, int br_indeksa, int god_dipl)
		{
			for(int i=0; i<studenti.size(); i++)
			{
				if(studenti[i]->DajBrojIndeksa()==br_indeksa)
				{
					throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
				}
			}
			studenti.push_back(new StudentMaster(ime, prezime, br_indeksa, god_dipl));
		}
		void ObrisiStudenta(int br_indeksa)
		{
			int i;
			for(i=0; i<studenti.size(); i++)
			{
				if(studenti[i]->DajBrojIndeksa()==br_indeksa)
				{
					delete studenti[i];
					studenti.erase(studenti.begin()+i);
					break;
				}
			}
			if(i==studenti.size())
				throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		}
		ApstraktniStudent &operator [](int br_indeksa) const
		{
			for(int i=0; i<studenti.size(); i++)
			{
				if(studenti[i]->DajBrojIndeksa()==br_indeksa)
					return *studenti[i];
			}
			throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		}
		void IspisiSveStudente() const
		{
			auto kopija=studenti;
			std::sort(kopija.begin(), kopija.end(), [](ApstraktniStudent* s1, ApstraktniStudent* s2)->bool {
				if(s1->DajProsjek()==s2->DajProsjek())
					return s1->DajBrojIndeksa()<s2->DajBrojIndeksa();
				return s1->DajProsjek()>s2->DajProsjek();
			});
			for(int i=0; i<kopija.size(); i++) kopija[i]->IspisiPodatke();
		}
};


int main()
{
		Fakultet f1;
		f1.UpisiStudenta("meho", "mehic", 3412);
		f1.UpisiStudenta("ibro", "suta", 1234, 2018);
		f1.UpisiStudenta("whoso", "whosic", 1312);
		
		const Fakultet f4(f1);
		f4.IspisiSveStudente();
		f4[1312].IspisiPodatke();
	return 0;
}