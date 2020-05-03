/* 
    TP 16/17 (Tutorijal 13, Zadatak 4)
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


class Student
{
	ApstraktniStudent *p_student;
	void Test() const
	{
		if(!p_student) throw std::logic_error("Nespecificiran student!");
	}
	public:
		Student(): p_student(nullptr) {}
		~Student() {delete p_student;}
		Student(const ApstraktniStudent &student): p_student(student.DajKopiju()){}
		Student(const Student &student)
		{
			if(!student.p_student) p_student=nullptr;
			else p_student=student.p_student->DajKopiju();
		}
		Student(Student &&student)
		{
			p_student=student.p_student; student.p_student=nullptr;
		}
		Student &operator =(const Student &student)
		{
			ApstraktniStudent *p_novi(nullptr);
			if(student.p_student != nullptr) p_novi=student.p_student->DajKopiju();
			delete p_student;
			p_student=p_novi;
			return *this;
		}
		Student &operator =(Student &&student)
		{
			std::swap(p_student, student.p_student);
			return *this;
		}
		string DajIme() const{return p_student->DajIme();}
		string DajPrezime() const{return p_student->DajPrezime();}
		int DajBrojIndeksa() const{return p_student->DajBrojIndeksa();}
		int DajBrojPolozenih() const{return p_student->DajBrojPolozenih();}
		double DajProsjek() const {return p_student->DajProsjek();}
		void RegistrirajIspit(int ocjena)
		{
			p_student->RegistrirajIspit(ocjena);
		}
		void PonistiOcjene(){p_student->PonistiOcjene();}
		void IspisiPodatke() const {p_student->IspisiPodatke();}
};



int main ()
{
	return 0;
}