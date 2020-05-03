#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

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
    
    void addmemory()
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
        if(brElemenata>=velicina-1) addmemory();
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
    
    Tip& operator[](int i)
    {
        if(i<0 || i>=brElemenata) throw "pristup van opsega";
        return *stek[i];
    }
    
    Tip& operator[](int i) const
    {
        if(i<0 || i>=brElemenata) throw "pristup van opsega";
        return *stek[i];
    }
    
};

void pretraga(Stek<vector<int>>& s, int trazeni)
{
    if(s.brojElemenata()==0)
    {
        std::cout<<"Nema elementa";
        return;
    }
    int poc, sred, kraj;
    std::vector<int> temporary=s.vrh();
            poc=0;
            kraj=temporary.size()-1;
            while(poc<=kraj)
            {
                sred=std::floor((poc+kraj)/2);
                if(temporary[sred]<trazeni) poc=sred+1; //nije u tom intervalu shiftamo na drugi interval
                else if(temporary[sred]>trazeni) kraj=sred-1; //nije u tom intervalu 
                else
                {
                    std::cout<<sred<<" "<<s.brojElemenata()-1;
                    return;
                }
            }
    s.skini();
    pretraga(s,trazeni); //rekurzija
    s.stavi(temporary);
            
}

void testic_1()
{
    std::vector<int> veka1, veka2, veka3;
    Stek<vector<int>> stekic;
    veka1.push_back(10);
    veka1.push_back(13);
    veka1.push_back(15);
    veka2.push_back(1227);
    veka2.push_back(1337);
    veka3.push_back(5);
    stekic.stavi(veka1);
    stekic.stavi(veka2);
    stekic.stavi(veka3);
    pretraga(stekic,1337);
}

void testic_2()
{
    std::vector<int> veka1, veka2;
    Stek<vector<int>> s;
    
    for(int i=0; i<100; i++)
    {
        if(i%2==0) veka1.push_back(i);
        else if(i%2!=0) veka2.push_back(i);
    }
    s.stavi(veka1);
    s.stavi(veka2);
    pretraga(s,7);
}

void testic_3()
{
    std::vector<int> veka1, veka2, veka3;
    Stek<vector<int>> s;
    
    for(int i=0; i<10; i++)
    {
        veka1.push_back(i);
        veka2.push_back(i+3);
        veka3.push_back(i+5);
    }
    
    s.stavi(veka1);
    s.stavi(veka2);
    s.stavi(veka3);
    pretraga(s, 7);
}



int main() {
    std::cout << "Test 1 treba ispisati 1 1 a ispisao je "; testic_1(); std::cout<<endl;
    std::cout<<"Test 2 treba ispisati 3 1 a ispisao je "; testic_2(); std::cout<<endl;
    std::cout<<"Test 3 treba ispisati 2 2 a test je ispisao "; testic_3(); std::cout<<endl;
    
}
