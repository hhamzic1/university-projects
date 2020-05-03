#include <iostream>


template <class Tip>
class Lista
{
    public:
    Lista(){};
    Lista(const Lista<Tip>&l){};
    virtual ~Lista(){};
    virtual int brojElemenata() const = 0;
    virtual Tip& trenutni() = 0;
    virtual Tip trenutni() const = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const Tip& el) = 0;
    virtual void dodajIza(const Tip& el) = 0;
    virtual Tip& operator[] (int i) = 0;
    virtual Tip operator[] (int i) const = 0;
    
};
template<typename Tip>
struct Cvor
{
    Tip info;
    Cvor* sljedeci=nullptr;
    Cvor* prethodni=nullptr;
    Cvor* krajnji=nullptr;
};

template <typename Tip>
class DvostrukaLista : public Lista<Tip>
{

    Cvor<Tip> *pocetni;
    Cvor<Tip> *trenutnipok;
    Cvor<Tip> *krajnji;
    int brElem;
    
    public:
        DvostrukaLista<Tip>(){pocetni=nullptr; trenutnipok=nullptr; krajnji=nullptr; brElem=0;}
        DvostrukaLista<Tip>(const DvostrukaLista<Tip> &l)
        {
            try
            {
                pocetni=new Cvor<Tip>();
                pocetni->info=l.pocetni->info;
                if(l.pocetni==l.trenutnipok) trenutnipok=pocetni;
                pocetni->sljedeci=new Cvor<Tip>();
                auto p=pocetni->sljedeci;
                p->prethodni = pocetni;
                auto q=l.pocetni->sljedeci;
                while(q!=nullptr)
                {
                    if(q==l.trenutnipok) trenutnipok=p;
                    p->info=q->info;
                    if(q->sljedeci==nullptr){ p->sljedeci=nullptr; krajnji=p; break;}
                    p->sljedeci=new Cvor<Tip>();
                    p->sljedeci->prethodni=p;
                    p=p->sljedeci;
                    q=q->sljedeci;
                }
                
                brElem=l.brElem;
                
            }catch(...){throw std::domain_error("Nema memorije");}
 
        }
        DvostrukaLista(const DvostrukaLista<Tip> &&l)
        {
            pocetni=l.pocetni;
            krajnji=l.krajnji;
            trenutnipok=l.trenutnipok;
            brElem=l.brElem;
            
        }
        ~DvostrukaLista()
        {
            Cvor<Tip> *tren=pocetni;
            Cvor<Tip> *novi;
            while(tren!=NULL)
            {
                novi=tren->sljedeci;
                delete tren;
                tren=novi;
            }
            pocetni=nullptr;
        }
        DvostrukaLista<Tip> &operator=(const DvostrukaLista<Tip> &l)
        {   
            if(&l == this) return *this;
            try{
                pocetni=new Cvor<Tip>();
                pocetni->info=l.pocetni->info;
                if(l.pocetni==l.trenutnipok) trenutnipok=pocetni;
                pocetni->sljedeci=new Cvor<Tip>();
                auto p=pocetni->sljedeci;
                p->prethodni = pocetni;
                auto q=l.pocetni->sljedeci;
                while(q!=nullptr)
                {
                    if(q==l.trenutnipok) trenutnipok=p;
                    p->info=q->info;
                    if(q->sljedeci==nullptr){ p->sljedeci=nullptr; krajnji=p; break;}
                    p->sljedeci=new Cvor<Tip>();
                    p->sljedeci->prethodni=p;
                    p=p->sljedeci;
                    q=q->sljedeci;
                }
                
                brElem=l.brElem;
                return *this;
            }catch(...){throw std::domain_error("Nema memorije");}
            
        }
        DvostrukaLista<Tip> &operator=(const DvostrukaLista<Tip> &&l)
        {
            pocetni=l.pocetni;
            trenutnipok=l.trenutnipok;
            krajnji=l.krajnji;
            brElem=l.brElem;
            l.pocetni=nullptr; l.trenutnipok=nullptr; l.krajnji=nullptr; l.brElem=0;
            return *this;
        }
        int brojElemenata() const {return brElem;}
        Tip &trenutni()
        {
            if(trenutnipok==nullptr) throw std::domain_error("Greška");
            return trenutnipok->info;
        }
        Tip trenutni() const
        {
            if(trenutnipok==nullptr) throw std::domain_error("Greška");
            return trenutnipok->info;
        }
        bool prethodni()
        {
            if(pocetni==nullptr) throw std::domain_error("Greska");
            if(trenutnipok==pocetni) return false;
            trenutnipok=trenutnipok->prethodni;
            return true;
        }
        bool sljedeci()
        {
            if(pocetni ==nullptr) throw std::domain_error("Greska");
            if(trenutnipok->sljedeci==nullptr) return false;
            trenutnipok=trenutnipok->sljedeci;
            return true;
        }
        void obrisi()
        {
            if(pocetni==nullptr) throw std::domain_error("Greska");
            if(pocetni->sljedeci==nullptr)
            {
                delete pocetni;
                pocetni=nullptr; trenutnipok=nullptr; krajnji=nullptr; brElem=0;
                return;
            }
            if(trenutnipok->sljedeci==nullptr)
            {
                auto temp=trenutnipok->prethodni;
                delete trenutnipok;
                trenutnipok=temp;
                trenutnipok->sljedeci=nullptr;
                krajnji=trenutnipok;
                temp=nullptr;
                brElem--;
                return;
            }
            if(pocetni==trenutnipok)
            {
                trenutnipok=pocetni->sljedeci;
                trenutnipok->prethodni=nullptr;
                delete pocetni;
                pocetni=trenutnipok;
                krajnji=trenutnipok;
                brElem--;
                return;
            }
            
            auto temp = trenutnipok->prethodni;
            temp->sljedeci=trenutnipok->sljedeci;
            trenutnipok->prethodni = temp;
            delete trenutnipok;
            trenutnipok=temp->sljedeci;
            brElem--;
            return;
        }
        
        void dodajIspred(const Tip &el)
        {
            try
            {
                if(brElem==0)
                {
                    pocetni=new Cvor<Tip>();
                    pocetni->sljedeci=nullptr;
                    pocetni->info=el;
                    pocetni->prethodni=nullptr;
                    trenutnipok=pocetni;
                    krajnji=pocetni;
                    brElem++;
                    return;
                }
                if(brElem==1 || pocetni==trenutnipok)
                {
                    Cvor<Tip> *pok=new Cvor<Tip>();
                    pok->sljedeci=trenutnipok;
                    trenutnipok->prethodni=pok;
                    pok->info=el;
                    pok->prethodni=nullptr;
                    pocetni=pok;
                    brElem++;
                    return;
                }
                
                auto p = trenutnipok->prethodni;
                Cvor<Tip> *pok = new Cvor<Tip>();
                p->sljedeci=pok;
                pok->prethodni=p;
                pok->sljedeci=trenutnipok;
                trenutnipok->prethodni=pok;
                pok->info = el;
                brElem++;
            }catch(...){ throw std::domain_error("Greska"); }
        }
        
        void dodajIza(const Tip &el)
        {
            try
            {
                if(brElem==0)
                {
                    pocetni=new Cvor<Tip>();
                    pocetni->sljedeci=nullptr;
                    pocetni->prethodni=nullptr;
                    pocetni->info=el;
                    trenutnipok=pocetni;
                    krajnji=pocetni;
                    brElem++;
                    return;
                }
                if(brElem==1)
                {
                    Cvor<Tip> *pok=new Cvor<Tip>();
                    pok->sljedeci=nullptr;
                    trenutnipok->sljedeci=pok;
                    pok->prethodni=trenutnipok;
                    pok->info=el;
                    krajnji=pok;
                    brElem++;
                    return;
                }
                
                auto p(trenutnipok->sljedeci);
                if(p==nullptr)
                {
                    Cvor<Tip> *pok=new Cvor<Tip>();
                    pok->sljedeci=nullptr;
                    pok->info=el;
                    trenutnipok->sljedeci=pok;
                    pok->prethodni=trenutnipok;
                    krajnji=pok;
                    brElem++;
                    return;
                }
                Cvor<Tip> *pok=new Cvor<Tip>();
                pok->sljedeci=p;
                p->prethodni=pok;
                pok->info=el;
                trenutnipok->sljedeci=pok;
                pok->prethodni=trenutnipok;
                brElem++;
                
            }catch(...){ throw std::domain_error("Nema memorije");}
            
        }
        
        Tip& operator[] (int i)
        {
            int brojac=0;
            auto pok(pocetni);
            while(brojac!=i)
            {
                pok=pok->sljedeci;
                brojac++;
            }
            return pok->info;
        }
        
        Tip operator[] (int i) const
        {
            int brojac=0;
            auto pok(pocetni);
            while(brojac!=i)
            {
                pok=pok->sljedeci;
                brojac++;
            }
            return pok->info;
        }
        void pocetak()
        {
            if(pocetni==nullptr) throw std::domain_error("Greska");
            trenutnipok=pocetni;
        }
        void kraj()
        {
            if(pocetni==nullptr) throw std::domain_error("Greska");
            trenutnipok=krajnji;
        }
        
    template<class T2>      //friend klasa iterator kako bi mogli pristupiti listi prilikom racunanja maximuma
    friend class iter;      //Rečeno je da se List kao apstraktna klasa ne smije mijenjati, al ovdje da ne bi radili ružni upcast
};                          //dodaćemo klasu iterator, preko koje ćemo manipulisati sa listom

template<typename Tip>
class iter
{
    DvostrukaLista<Tip> *dlpok;     //pokazivac na tu listu
    Cvor<Tip>* trenutniIterator;    //pokazivac na elemenat te liste
public:
    iter(const Lista<Tip> &lista)
    {
        dlpok=(DvostrukaLista<Tip>*) &lista; //pokazivac na tu listu;
        trenutniIterator = dlpok->pocetni; //iterator na pocetak
    }
    
    Tip trenutni() const
    {
        return trenutniIterator->info;
    }
    
    Tip& trenutni()
    {
        return trenutniIterator->info;
    }
    
    void pocetak()
    {
        trenutniIterator = dlpok->pocetni;
    }
    
    bool sljedeci()
    {
        if(dlpok->brojElemenata() == 0) throw "Lista je prazna";
        if(trenutniIterator == dlpok->krajnji) return false;
        trenutniIterator = trenutniIterator->sljedeci;
        return true;
    }
};

template<typename Tip>
Tip dajMaksimum(const Lista<Tip> &n)
{
    iter<Tip> it = n;
    Tip max = it.trenutni(), tren = it.trenutni(); //pretpostavljamo da je max prvi element
    it.pocetak(); //krecemo od pocetka;
    while(it.sljedeci())
    {
        if(it.trenutni() > max) max = it.trenutni();
    }
    it.trenutni()=tren;
    return max;
}

bool testMaksimuma()
{
    Lista<int> *listic;
    listic = new DvostrukaLista<int>();
    
    int maksimum;
    for(int i=0; i<100; i++) listic->dodajIspred(1);
    maksimum=dajMaksimum(*listic);
    if(maksimum!=1)
    {
        delete listic;
        return false;
    }
    while(listic->brojElemenata()) listic->obrisi();
    
    for(int i=1; i<=100; i++) listic->dodajIspred(i*i);
    maksimum=dajMaksimum(*listic);
    if(maksimum!=10000)
    {
        delete listic;
        return false;
    }
    
    while(listic->brojElemenata()) listic->obrisi();
    
    for(int i=0; i>-100; i--) listic->dodajIspred(i);
    
    maksimum=dajMaksimum(*listic);
    if(maksimum!=0){
        delete listic;
        return false;
    }
    return true;
}

bool test()
{
    
    Lista<int> *lista;
    lista = new DvostrukaLista<int>();
    
    for(int i=1; i<=50; i++)
    {
        lista->dodajIza(i);
        lista->dodajIspred(i);
    }
    
    for(int i=0; i<49; i++)
    {
        if((*lista)[i] != ((*lista)[99-i]-1))
        {
            throw "Metode dodajIspred i dodajIza ne rade kako treba";
            return false;
        }
    }
    
    if((*lista)[50]!=1)
    {
        throw "Operator [] ne radi kako treba";
        return false;
    }
    return true;
    
}

void testIzuzeci()
{
    Lista<int> *lista;
    lista = new DvostrukaLista<int>();
    
    while(lista->brojElemenata()>0) lista->obrisi();
    
    try{
        lista->sljedeci();
    }catch(...){
        std::cout<<"Uspjesno uhvacen izuzetak\n";
    }
    
    try{
        lista->prethodni();
    }catch(...){
        std::cout<<"Uspjesno uhvacen izuzetak\n";
    }
    
    try{
        lista->obrisi();
    }catch(...){
        std::cout<<"Uspjesno uhvacen izuzetak\n";
    }
    
    try{
        lista->trenutni();
    }catch(...){
        std::cout<<"Uspjesno uhvacen izuzetak\n";
    }
    
    try{
        lista->pocetak();
    }catch(...){
        std::cout<<"Uspjesno uhvacen izuzetak\n";
    }
    
    try{
        lista->kraj();
    }catch(...){
        std::cout<<"Uspjesno uhvacen izuzetak\n";
    }
}



int main() {
    
    testMaksimuma();
    try
    {
        testMaksimuma() ? std::cout<<"Max radi kako treba\n" : std::cout<<"Max ne radi kako treba"<<std::endl;
        test() ? std::cout<<"Test uspjesan\n" : std::cout<<"Test nije uspjesan"<<std::endl;
        std::cout<<"Test izuzetaka:\n";
        testIzuzeci();
   
    }catch(...){
        
    }
    return 0;
    
}
