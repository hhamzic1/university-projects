#include <iostream>


template <typename Tip>
struct Cvor
{
    Tip info;
    Cvor* sljedeci=nullptr;
};

template <typename Tip>
class Red
{
    Cvor<Tip> *pocetni;
    Cvor<Tip> *krajnji;
    int brElem;
    public:
        Red(){pocetni=nullptr; krajnji=nullptr; brElem=0;}
        Red(const Red<Tip> &l)
        {
            try
            {
               pocetni=krajnji=nullptr;
               brElem=0;
               auto temp = l.pocetni;
               while(temp!=0)
               {
                   stavi(temp->info);
                   temp=temp->sljedeci;
               }
                
            }catch(...){throw std::domain_error("Nema memorije");}
 
        }
        Red(const Red<Tip> &&l)
        {
            pocetni=l.pocetni;
            krajnji=l.krajnji;
            brElem=l.brElem;
            
        }
        ~Red()
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
        Red<Tip> &operator=(const Red<Tip> &l)
        {
            try
            {
                if(this==&l) return *this;
                pocetni=new Cvor<Tip>();
                pocetni->info=l.pocetni->info;
                pocetni->sljedeci=new Cvor<Tip>();
                auto p=pocetni->sljedeci;
                auto q=l.pocetni->sljedeci;
                while(q!=nullptr)
                {
                    
                    p->info=q->info;
                    if(q->sljedeci==nullptr) {krajnji=p; break;}
                    p->sljedeci=new Cvor<Tip>();
                    p=p->sljedeci;
                    q=q->sljedeci;
                }
                
                krajnji->sljedeci=nullptr; 
                brElem=l.brElem;//doslo je do kraja
                return *this;
                
            }catch(...){throw std::domain_error("Nema memorije");}
 
            
        }
        Red<Tip> &operator=(const Red<Tip> &&l)
        {
            pocetni=l.pocetni;
            krajnji=l.krajnji;
            brElem=l.brElem;
            l.pocetni=nullptr; l.krajnji=nullptr; l.brElem=0;
            return *this;
        }

        void brisi()
        {
            if(pocetni ==nullptr || brElem==0) throw std::domain_error("Red je prazan");
            if(brElem==1)
            {
                delete pocetni;
                pocetni=nullptr; krajnji=nullptr; brElem=0;
                return;
            }
            
            while(pocetni!=nullptr)
            {
                auto *temp = pocetni->sljedeci;
                delete pocetni;
                pocetni=temp;
            }
            pocetni=nullptr; krajnji=nullptr; brElem=0;
           
        }
        
        void stavi(const Tip &el)
        {
            try
            {
                if(brElem==0)
                {
                    pocetni=new Cvor<Tip>();
                    pocetni->sljedeci=nullptr;
                    pocetni->info=el;
                    krajnji=pocetni;
                    brElem++;
                    return;
                }
                auto *pok = new Cvor<Tip>();
                krajnji->sljedeci=pok;
                krajnji=pok;
                krajnji->info = el;
                krajnji->sljedeci=nullptr;
                brElem++;
            
            }catch(...){ throw std::domain_error("Greska"); }
        }
        
        Tip skini()
        {
            try
            {
                if(brElem==0) throw std::domain_error("Red je prazan");
                
                if(brElem==1)
                {
                    Tip temp = pocetni->info;
                    krajnji=nullptr;
                    delete pocetni;
                    pocetni=nullptr;
                    brElem--;
                    return temp;
                }
                
                Tip temp = pocetni->info;
                auto *pok = pocetni->sljedeci;
                delete pocetni;
                pocetni=pok;
                pok=nullptr;
                brElem--;
                return temp;
                
            }catch(...){ throw std::domain_error("Nema memorije");}
            
        }
        
        Tip& celo()
        {
            try
            {
                if(brElem==0) throw std::domain_error("Red je prazan");
                
                return pocetni->info;
                
            }catch(...){ throw std::domain_error("Nema memorije");}
            
        }
        
        int brojElemenata()
        {
            return brElem;
        }

    
};

template <typename T>

bool testBrojElemenata(Red<T> r)
{
    for(int i=0; i<100; i++) r.stavi(i);
    r.celo();
    r.celo();
    r.skini();
    r.skini();
    r.skini();
    r.skini();
    r.skini();
    r.skini();
    if(r.brojElemenata()!=94) return false;
    r.stavi(91);
    r.stavi(1010);
    r.stavi(1111);
    r.stavi(248929);
    r.stavi(-111);
    return (r.brojElemenata()==99);
}


template<typename T>
bool testBrisi(Red<T> r)
{
    for(int i=0; i<100; i++) r.stavi(i);
    r.brisi();
    return (r.brojElemenata()==0);
}

template<typename T>
bool testStavi(Red<T> r)
{
    for(int i=0; i<100; i++)
    {
        r.stavi(i);
        if(r.celo()!=0) return false;
    }
    return true;
}

template<typename T>
bool testSkini(Red<T> r)
{
    T element;
    for(int i=0; i<100; i++)
    {
        r.stavi(i);
        element = r.skini();
        if(element!=i) return false;
    }
    return (r.brojElemenata()==0);
}

template<typename T>
bool testCelo(Red<T> r)
{
    for(int i=1; i<100; i+=2) r.stavi(i);
    r.skini();
    if(r.celo()!=3) return false;
    r.brisi();
    for(int i=100; i>0; i-=2) r.stavi(i);
    r.skini();
    if(r.celo()!=98) return false;
    return true;
}




int main() {
    Red<int> r;
    bool brisi = testBrisi(r), stavi= testStavi(r), skini=testSkini(r), celo=testCelo(r), broj=testBrojElemenata(r);
    brisi ? std::cout<< "Funkcija brisi radi ispravno"<<std::endl : std::cout<< "Funkcija brisi ne radi ispravno"<<std::endl;
    stavi ? std::cout<< "Funkcija stavi radi ispravno"<<std::endl : std::cout<< "Funkcija stavi ne radi ispravno"<<std::endl;
    skini ? std::cout<< "Funkcija skini radi ispravno"<<std::endl : std::cout<< "Funkcija skini ne radi ispravno"<<std::endl;
    celo ? std::cout<< "Funkcija celo radi ispravno"<<std::endl : std::cout<< "Funkcija celo ne radi ispravno"<<std::endl;
    broj ? std::cout<< "Funkcija brojElemenata radi ispravno"<<std::endl : std::cout<< "Funkcija brojElemenata ne radi ispravno"<<std::endl;
    return 0;
    
}
