#include <iostream>

template<typename Tip>
struct Cvor
{
    Tip info;
    Cvor* sljedeci=nullptr;
    Cvor* prethodni=nullptr;
};


template <typename Tip>
class DvostraniRed
{
    Cvor<Tip> *pocetni;
    Cvor<Tip> *krajnji;
    int brElem;
    public:
        DvostraniRed<Tip>(){pocetni=nullptr; krajnji=nullptr; brElem=0;}
        DvostraniRed<Tip>(const DvostraniRed<Tip> &r)
        {
            try
            {
                
               pocetni=krajnji=nullptr;
               brElem=0;
               auto temp = r.pocetni;
               while(temp!=0)
               {
                   staviNaCelo(temp->info); //red je pa stavljamo na celo kad kopiramo
                   temp=temp->sljedeci;
               }
                
            }catch(...){throw std::domain_error("Nema memorije");}
 
        }
        DvostraniRed<Tip>(const DvostraniRed<Tip> &&r)
        {
            pocetni=r.pocetni;
            krajnji=r.krajnji;
            brElem=r.brElem;
            
        }
        ~DvostraniRed()
        {
            while(brElem) skiniSaVrha();    //skidamo sa vrha sve laganica
        }
        DvostraniRed<Tip> &operator=(const DvostraniRed<Tip> &r)
        {
            try
            {
                if(this==&r) return *this;
                brisi();      //obrisemo citav pocetni red
            
                    auto tempara=r.pocetni;         //stavimo pokazivac na pocetak parametarskog reda
                    while(tempara!=NULL)
                    {       
                        staviNaCelo(tempara->info);     //i ponovo iznova ubacujemo u nas originalni red koji je sad prazan sve elemente reda r
                        tempara=tempara->sljedeci;
                    }
                return *this;
                
            }catch(...){throw std::domain_error("Nema memorije");}
 
            
        }
        DvostraniRed<Tip> &operator=(const DvostraniRed<Tip> &&r)
        {
            pocetni=r.pocetni;
            krajnji=r.krajnji;
            brElem=r.brElem;
            r.pocetni=nullptr; r.krajnji=nullptr; r.brElem=0;
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
        
        void staviNaVrh(const Tip &el)
        {
            try
            {
                if(brElem==0)
                {
                    pocetni=new Cvor<Tip>();
                    pocetni->sljedeci=nullptr;
                    pocetni->prethodni=nullptr;
                    pocetni->info=el;
                    krajnji=pocetni;
                    brElem++;
                    return;
                }
                auto *pok = new Cvor<Tip>();
                krajnji->sljedeci=pok;
                pok->prethodni=krajnji;
                krajnji=pok;
                krajnji->info = el;
                krajnji->sljedeci=nullptr;
                brElem++;
            
            }catch(...){ throw std::domain_error("Greska u stavljanju na vrh"); }
        }
        
        Tip skiniSaVrha()
        {
            try
            {
                if(brElem==0) throw std::domain_error("Red je prazan");
                
                if(brElem==1)
                {
                    Tip temp = krajnji->info;
                    delete krajnji;
                    pocetni=nullptr;
                    krajnji=nullptr;
                    brElem--;
                    return temp;
                }
                
                Tip temp = krajnji->info;
                auto *pok = krajnji->prethodni;
                delete krajnji;
                krajnji=pok;
                krajnji->sljedeci=nullptr;
                pok=nullptr;
                brElem--;
                return temp;
                
            }catch(...){throw std::domain_error("greska u skidanju s vrha");}
        }
        
        
        void staviNaCelo(const Tip &el)
        {
            try
            {
                if(brElem==0)
                {
                    pocetni=new Cvor<Tip>();
                    pocetni->sljedeci=nullptr;
                    pocetni->info=el;
                    krajnji=pocetni;
                    krajnji->prethodni=nullptr;
                    brElem++;
                    return;
                }
                auto *pok = new Cvor<Tip>();
                pok->sljedeci=pocetni;
                pocetni->prethodni=pok;
                pok->prethodni=nullptr;
                pocetni=pok;
                pocetni->info = el;
                brElem++;
            
            }catch(...){ throw std::domain_error("Greska"); }
            
        }
        
        Tip skiniSaCela()
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
                pocetni->prethodni=nullptr;
                pok=nullptr;
                brElem--;
                return temp;
                
            }catch(...){ throw std::domain_error("lose skidanje");}
            
        }
        
        Tip& celo()
        {
            try
            {
                if(brElem==0) throw std::domain_error("Red je prazan");
                
                return pocetni->info;
                
            }catch(...){ throw std::domain_error("lose ocitavanje");}
            
        }
        
        Tip& vrh()
        {
            try
            {
                if(brElem==0) throw std::domain_error("Red je prazan");
                return krajnji->info;
            }catch(...){throw std::domain_error("lose ocitavanje");}
        }
        
        int brojElemenata()
        {
            return brElem;
        }

    
};

template<typename Tip>
bool testNaCelo(DvostraniRed<Tip> red)
{
    for(int i=0; i<11; i++)
    {
        red.staviNaCelo(i);
        if(red.celo()!=i) return false;
    }
    return true;
}

template<typename Tip>
bool testSaCela(DvostraniRed<Tip> red)
{
    Tip hero;
    for(int i=0; i<15; i++)
    {
        red.staviNaCelo(i);
        hero=red.skiniSaCela();
        if(hero!=i) return false;
    }
    return (red.brojElemenata()==0);
}

template<typename Tip>
bool CeloTest(DvostraniRed<Tip> redar)
{
    for(int i=1; i<50; i+=2) redar.staviNaCelo(i);
    redar.skiniSaCela();
    if(redar.celo()!=47) return false;
    while(redar.brojElemenata()) redar.skiniSaCela();
    for(int i=50; i>=1; i=i-2) redar.staviNaCelo(i);
    redar.skiniSaCela();
    if(redar.celo()!=4) return false;
    return true;
}

int main()
{
    DvostraniRed<int> red;
    
    testNaCelo(red) ? std::cout<<"Test NaCelo radi ispravno\n" : std::cout<<"NaCelo ne radi ispravno\n";
    testSaCela(red) ? std::cout<<"Test SaCela radi ispravno\n" : std::cout<<"SaCela ne radi ispravno\n";
    CeloTest(red) ? std::cout<<"Test Celo radi ispravno\n" : std::cout<<"Test Celo ne radi ispravno\n";
    
}
