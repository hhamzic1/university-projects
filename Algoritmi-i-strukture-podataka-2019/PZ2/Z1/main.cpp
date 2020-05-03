#include <iostream>
#include <stdexcept>

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


template <class T>
class NizLista : public Lista<T>
{
    int velicina=10000, trenutniElement=0, brElemenata=0;
    T **nizLista;
public:
    NizLista<T>()
    {
        velicina=10000;
        trenutniElement=0;
        brElemenata=0;
        nizLista=new T*[velicina];
    }
    void dodajMemorije()
    {
        velicina+=10000;
        T** pomocni(new T*[velicina]);
        int tempBr=brElemenata, tempTrenutni=trenutniElement;
        for(int i=0; i<brElemenata; i++) pomocni[i]=new T(*nizLista[i]);
        while(brElemenata>0) obrisi();
        delete[] nizLista;
        
        nizLista=pomocni;
        brElemenata=tempBr;
        trenutniElement=tempTrenutni;
        for(int i=0; i<brElemenata; i++) nizLista[i]=pomocni[i];
    }
    NizLista(const NizLista &nl)
    {
        velicina=nl.velicina;
        trenutniElement=nl.trenutniElement;
        brElemenata=nl.brElemenata;
        nizLista=new T*[velicina];
        for(int i=0; i<nl.brElemenata; i++)
        {
            auto el=*nl.nizLista[i];
            nizLista[i]=new T(el);
        }
    }
    NizLista& operator= (const NizLista &nl)
    {
        if(this == &nl) return *this;
        while(brElemenata>0) obrisi();
        delete[] nizLista;
        velicina=nl.velicina;
        trenutniElement=nl.trenutniElement;
        brElemenata=nl.brElemenata;
        nizLista=new T*[velicina];
        for(int i=0; i<nl.brElemenata; i++)
        {
            auto el=*nl.nizLista[i];
            nizLista[i]=new T(el);
        }
        return *this;
    }
    ~NizLista<T>()
    {
        for(int i=0; i<brElemenata; i++) delete nizLista[i];
        delete[] nizLista;
        brElemenata=0;
    }
    int brojElemenata() const
    {
        return brElemenata;
    }
    bool prethodni()
    {
        if(brElemenata==0) throw "Lista ima nula elemenata!";
        if(trenutniElement==0) return false;
        trenutniElement--;
        return true;
    }
    bool sljedeci()
    {
        if(brElemenata==0) throw "Lista ima nula elemenata!";
        if(trenutniElement>=brElemenata-1) return false;
        trenutniElement++;
        return true;
    }
    void pocetak()
    {
        if(brElemenata==0) throw "Lista ima nula elemenata!";
        trenutniElement=0;
    }
    void kraj()
    {
        if(brElemenata==0) throw "Lista ima nula elemenata!";
        trenutniElement=brElemenata-1;
    }
    void dodajIspred(const T& el)
    {
        if(brElemenata>=velicina-1) dodajMemorije();
        if(brElemenata==0)
        {
            nizLista[0]=new T(el);
            trenutniElement=0;
            brElemenata++;
        } else {
            brElemenata++;
            for(int i=brElemenata-1; i>trenutniElement; i--) nizLista[i]=nizLista[i-1];
            nizLista[trenutniElement++]=new T(el);
        }
    }
    void dodajIza(const T& el)
    {
        if(brElemenata>=velicina-1) dodajMemorije();
        if(brElemenata==0)
        {
            nizLista[0]=new T(el);
            trenutniElement=0;
            brElemenata++;
        } 
        else if (trenutniElement==brElemenata-1)
        {
           brElemenata++;
           nizLista[trenutniElement+1]=new T(el);
        }
        else
        {
            brElemenata++;
            for(int i=brElemenata-1; i>trenutniElement; i--) nizLista[i]=nizLista[i-1];
            nizLista[trenutniElement+1]=new T(el);
        }
    }
    void obrisi()
    {
        if(brElemenata==0) throw "Lista ima nula elemenata!";
        delete nizLista[trenutniElement];
        for(int i=trenutniElement; i<brElemenata; i++) nizLista[i]=nizLista[i+1];
        brElemenata--;
        if(trenutniElement==brElemenata) trenutniElement--;
    }
    T& operator[](int i)
    {
        if(i<0 || i>=brElemenata) throw "Pristup van opsega";
        return *nizLista[i];
    }
    T operator[] (int i) const
    {
        if(i<0 || i>=brElemenata) throw "Pristup van opsega";
        return *nizLista[i];
    }
    T& trenutni()
    {
        if(brElemenata==0) throw "Lista ima nula elemenata!";
        return *nizLista[trenutniElement];
    }
    T trenutni() const
    {
        if(brElemenata==0) throw "Lista ima nula elemenata!";
        return *nizLista[trenutniElement];
    }
    
};

template <typename Tip>
struct Cvor
{
    Tip info;
    Cvor* sljedeci=nullptr;
};
//haha

template <typename Tip>
class JednostrukaLista : public Lista<Tip>
{
    Cvor<Tip> *pocetni;
    Cvor<Tip> *trenutnipok;
    int brElem;
    public:
        JednostrukaLista(){pocetni=nullptr; trenutnipok=nullptr; brElem=0;}
        JednostrukaLista(const JednostrukaLista<Tip> &l)
        {
            try
            {
                pocetni=new Cvor<Tip>();
                pocetni->info=l.pocetni->info;
                if(l.pocetni==l.trenutnipok) trenutnipok=pocetni;
                pocetni->sljedeci=new Cvor<Tip>();
                auto p=pocetni->sljedeci;
                auto q=l.pocetni->sljedeci;
                while(q!=nullptr)
                {
                    if(q==l.trenutnipok) trenutnipok=p;
                    p->info=q->info;
                    p->sljedeci=new Cvor<Tip>();
                    p=p->sljedeci;
                    q=q->sljedeci;
                }
                
                p=nullptr;
                brElem=l.brElem;
                
            }catch(...){throw std::domain_error("Nema memorije");}
 
        }
        JednostrukaLista(const JednostrukaLista<Tip> &&l)
        {
            pocetni=l.pocetni;
            trenutnipok=l.trenutnipok;
            brElem=l.brElem;
            
        }
        ~JednostrukaLista()
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
        JednostrukaLista<Tip> &operator=(const JednostrukaLista<Tip> &l)
        {
            try
            {
                pocetni=new Cvor<Tip>();
                pocetni->info=l.pocetni->info;
                if(l.pocetni==l.trenutnipok) trenutnipok=pocetni;
                pocetni->sljedeci = new Cvor<Tip>();
                auto p = pocetni->sljedeci;
                auto q = l.pocetni->sljedeci;
                while(q!=nullptr)
                {
                    if(q==l.trenutnipok) trenutnipok=p;
                    p->info=q->info;
                    p->sljedeci = new Cvor<Tip>();
                    p=p->sljedeci;
                    q=q->sljedeci;
                }
                
                p=nullptr;
                brElem=l.brElem;
                return *this;
                
                
                
            }catch(...){throw std::domain_error("Nema memorije");}
            
        }
        JednostrukaLista<Tip> &operator=(const JednostrukaLista<Tip> &&l)
        {
            pocetni=l.pocetni;
            trenutnipok=l.trenutnipok;
            brElem=l.brElem;
            l.pocetni=nullptr; l.trenutnipok=nullptr; l.brElem=0;
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
            auto p(pocetni);
            while(p->sljedeci!=trenutnipok) p=p->sljedeci;
            trenutnipok=p;
            p=nullptr;
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
            if(pocetni ==nullptr) throw std::domain_error("Greska");
            if(pocetni->sljedeci==nullptr)
            {
                delete pocetni;
                pocetni=nullptr; trenutnipok=nullptr; brElem=0;
                return;
            }
            if(trenutnipok->sljedeci==nullptr)
            {
                auto p(pocetni);
                while(p->sljedeci!=trenutnipok) p=p->sljedeci;
                delete trenutnipok;
                trenutnipok=nullptr;
                trenutnipok=p; trenutnipok->sljedeci=nullptr;
                p=nullptr;
                brElem--;
                return;
            }
            if(pocetni==trenutnipok)
            {
                trenutnipok=pocetni->sljedeci;
                delete pocetni;
                pocetni=trenutnipok;
                brElem--;
                return;
            }
            
            auto p=pocetni;
            while(p->sljedeci!=trenutnipok) p=p->sljedeci;
            p->sljedeci=trenutnipok->sljedeci;
            delete trenutnipok;
            trenutnipok=p->sljedeci;
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
                    trenutnipok=pocetni;
                    brElem++;
                    return;
                }
                if(brElem==1 || pocetni==trenutnipok)
                {
                    Cvor<Tip> *pok=new Cvor<Tip>();
                    pok->sljedeci=trenutnipok;
                    pok->info=el;
                    pocetni=pok;
                    brElem++;
                    return;
                }
                auto p(pocetni);
                while(p->sljedeci!=nullptr && p->sljedeci!=trenutnipok) p=p->sljedeci;
                
                Cvor<Tip> *pok=new Cvor<Tip>();
                pok->sljedeci=trenutnipok;
                pok->info=el;
                p->sljedeci=pok;
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
                    pocetni->info=el;
                    trenutnipok=pocetni;
                    brElem++;
                    return;
                }
                if(brElem==1)
                {
                    Cvor<Tip> *pok=new Cvor<Tip>();
                    pok->sljedeci=nullptr;
                    trenutnipok->sljedeci=pok;
                    pok->info=el;
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
                    brElem++;
                    return;
                }
                
                Cvor<Tip> *pok=new Cvor<Tip>();
                pok->sljedeci=p;
                pok->info=el;
                trenutnipok->sljedeci=pok;
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
            auto p(trenutnipok);
            while(p->sljedeci!=nullptr) p=p->sljedeci;
            trenutnipok=p;
        }
    
};

bool testic(bool niz)
{
    Lista<int> *lista=nullptr;
    if(niz) lista=new NizLista<int>();
    else lista=new JednostrukaLista<int>();
    
    for(int i=1; i<=50; i++)
    {
        lista->dodajIza(i);
        lista->dodajIspred(i);
    }
    
    for(int i=0; i<49; i++)
    {
        if((*lista)[i]!=((*lista)[99-i]-1))
        {
            throw "Metode dodajIspred i dodajIza ne dodaju elemente kako treba!";
            delete[] lista;
            return false;
        }
    }
    
    if((*lista)[50]!=1)
    {
        throw "Operator [] ne radi kako treba!";
        return false;
    }
    
    int brElem=lista->brojElemenata(), trenutniElem=lista->trenutni(); //ocekuje se 100 i 1
    if(brElem!=100 || trenutniElem!=1)
    {
        throw "Metode brojElemenata i trenutni element ne rade kako treba";
        return false;
    }
    
    for(int i=0; i<99; i++) lista->sljedeci();
    //pomjeranje trenutnog na kraj liste
    int handle=lista->trenutni();
    lista->kraj();
    int realend=lista->trenutni();
    if(handle!=realend)
    {
        throw "Rucno pomjeranje na kraj ne odgovara pravom kraju!";
        return false;
    }
    
    lista->pocetak();
    //provjera prethodni i sljedeci
    
    bool povrPrethodni=lista->prethodni();
    lista->kraj();
    bool povrSljedeci=lista->sljedeci();
    if((povrPrethodni!=povrSljedeci)!=false)
    {
        throw "Metode prethodni i sljedeci dozvoljavaju prekoracenja prilikom pomjeranja";
        return false;
    }
    
    //edge slucajevi brisanja
    
    lista->pocetak();
    lista->obrisi();
    lista->kraj();
    lista->obrisi();
    lista->pocetak();
    if((*lista)[0]!=2 || (*lista)[97]!=3 || lista->brojElemenata()!=98)
    {
        throw "lose brisanje elemenata u metodi obrisi";
        return false;
    }
    lista=nullptr;
    return true;
}

int main()
{
    try 
    {
        testic(true) ? std::cout<<"\nTest NizLista je uspjesan" : std::cout<<"\nIma grešaka u NizLista";
        testic(false) ? std::cout<<"\nTest JednostrukaLista je uspjesan" : std::cout<<"\nIma gresaka u JednostrukaLista";
        
    }catch (...) {

    }
    
}