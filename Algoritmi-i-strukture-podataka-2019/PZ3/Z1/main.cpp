#include <iostream>

template<class Tip>
class Stek{
    int velicina=10000, vrhSteka=0, brElemenata=0;
    Tip** stek;
public:
    Stek<Tip>()
    {
        velicina=10000;
        vrhSteka=0;
        brElemenata=0;
        stek = new Tip*[velicina];
    }
    Stek (const Stek &s)
    {
        if(&s == this) return;
        velicina=s.velicina;
        vrhSteka=s.vrhSteka;
        brElemenata=s.brElemenata;
        stek = new Tip*[velicina];
        for(int i=0; i<s.brElemenata; i++)
        {
            auto el = *s.stek[i]; //dobijamo element
            stek[i] = new Tip(el); // stavljamo u novi stek
        }
    }
    Stek &operator= (const Stek &s)
    {
        if(&s != this) //destruktivna samododjela
        {
            while(brElemenata>0) skini();
            delete[] stek;
            velicina=s.velicina;
            vrhSteka=s.vrhSteka;
            brElemenata=s.brElemenata;
            stek = new Tip*[velicina];
            for(int i=0; i<s.brElemenata; i++)
            {
                auto el = *s.stek[i]; //dobijamo element
                stek[i] = new Tip(el); // stavljamo u novi stek
            }
        }
        return *this;
    }
    int brojElemenata()
    {
        return brElemenata;
    }
    ~Stek<Tip>()
    {
        for(int i=0; i<brElemenata; i++) delete stek[i];
        delete[] stek;
        brElemenata=0;
        vrhSteka=0;
    }
    void brisi()
    {
        if(brElemenata==0) throw "Stek prazan";
        for(int i=0; i<brElemenata; i++) delete stek[i];
        brElemenata=0; 
        vrhSteka=0;
    }
    
    void dodajMemorije()
    {
        velicina+=10000;
        Tip** pom= new Tip*[velicina];
        int temp_brElem=brElemenata, temp_vrhSteka=vrhSteka;
        for(int i=0; i<brElemenata; i++) pom[i] = new Tip(*stek[i]);
        while(brElemenata>0) skini();
        delete[] stek;
        
        stek=pom;
        brElemenata=temp_brElem;
        vrhSteka=temp_vrhSteka;
        for(int i=0; i<brElemenata; i++) stek[i]=pom[i];
    }
    
    void stavi(const Tip& el)
    {
        if(brElemenata>=velicina-1) dodajMemorije();
        if(brElemenata==0)
        {
            stek[0]=new Tip(el);
            vrhSteka=0;
        }
        else
        {
            for(int i=brElemenata; i>vrhSteka; i--) stek[i]=stek[i-1];
            stek[vrhSteka++] = new Tip(el);
        }
        brElemenata++;
    }
    
    Tip skini()
    {
        if(brElemenata==0) throw "Stek nema elemenata";
        Tip prethodniVrh;
        int pocetak=vrhSteka;
        if(brElemenata>1){
            prethodniVrh=*stek[vrhSteka-1];
            pocetak--;
            delete stek[vrhSteka-1];
        }
        else
        {
            prethodniVrh=*stek[vrhSteka];
            delete stek[vrhSteka];
        }
        for(int i=pocetak; i<brElemenata-1; i++) stek[i]=stek[i+1];
        brElemenata--;
        if(vrhSteka==brElemenata && brElemenata!=0) vrhSteka--;
        return prethodniVrh;
    }
    
    Tip &vrh()
    {
        if (brElemenata==0) throw "Stek nema elemenata";
        if(brElemenata>1) return *stek[vrhSteka-1];
        return *stek[vrhSteka];
    }
};

bool testic(bool el)
{
    Stek<int> s;
    for(int i = 0; i<100; i++)
    {
        try
        {
            s.stavi(i);
        }catch(...){
            return false;
        }
    }
    s.skini();
    s.skini();
    if(s.vrh()!=97) return false;
    s.brisi();
    if(s.brojElemenata()!=0) return false;
    
    Stek<int> s1;
    for(int i = 100; i>0; i--)
    {
        s.stavi(i);
        s.skini();
    }
    if(s.brojElemenata()!=0) return false;
    return true;
    
    
}

int main() {
    try{
    testic(true)? std::cout<<"Test uspješan" : std::cout<<"Test nije uspješan";
    }catch(...)
    {
        std::cout<<"Izuzetak koji nije uhvaćen";
    }
}
