#include <iostream>
#include <utility>
#include <vector>
#include <string>
template <typename TipKljuca, typename TipVrijednosti>
class Mapa
{
    public:
    Mapa(){};
    virtual ~Mapa(){};
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(TipKljuca kljuc) = 0;
    virtual TipVrijednosti operator[](const TipKljuca k) const = 0;
    virtual TipVrijednosti &operator[](TipKljuca k) = 0;
};



// znaci stablo je organizovano po kljucu

template<typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa: public Mapa<TipKljuca,TipVrijednosti>
{
  
  struct Cvor
  {
      TipKljuca key;
      TipVrijednosti value;
      Cvor* desni=nullptr;
      Cvor* lijevi=nullptr;
      Cvor* parent=nullptr;
      Cvor(TipKljuca k1, TipVrijednosti p1, Cvor* desni1, Cvor* lijevi1, Cvor* parent1): key(k1), value(p1), desni(desni1), lijevi(lijevi1), parent(parent1){}
     
  };
  
  Cvor* root;
  int brElemenata;
  
  void tempObrisi(Cvor* r)
  {
      if(r!=nullptr)
      {
          tempObrisi(r->desni);
          tempObrisi(r->lijevi);
          delete r;
      }
  }
  
  Cvor* nadjiCvor(const TipKljuca &k, Cvor* r) const
  {
      if(r==nullptr || k==r->key) return r;
      else if(k>r->key) r=nadjiCvor(k, r->desni);
      else
      {
          r=nadjiCvor(k, r->lijevi);
      }
  }
  
  Cvor* NadjiMax(Cvor* r)
  {
      if(r->desni == nullptr) return r;
      NadjiMax(r->desni);
  }
  
  Cvor* obrisiCvor(Cvor* &r, TipKljuca k)  //rekurzija at her peak, ugl stvara se bruku ovih r->lijevi r->desni pokazivaca al sve OK radi! GLAVNA FUNKCIJA
  {
      if(r==nullptr) return r;
      else if(k>r->key) r->desni=obrisiCvor(r->desni, k);     //lociramo trazeni cvor
      else if(k<r->key) r->lijevi=obrisiCvor(r->lijevi, k);
      else
      {
          if(r->desni==nullptr && r->lijevi==nullptr) //kad je cvor koji se briše list, odnosno nema djece
          {
              delete r;
              r=nullptr;
          }
          else if(r->desni==nullptr)        //po jedno dijete
          {
              Cvor* temp = r;
              r=r->lijevi;          //u liniju 69 ili 70 će vratiti/prespojiti izbrisani element
              delete temp;
          }
          else if(r->lijevi == nullptr)  //po jedno dijete
          {
              Cvor* temp=r;
              r=r->desni;
              delete temp;
          }
          else      // dvoje djece
          {
              Cvor *temp=NadjiMax(r->lijevi); //nadjemo maximum u lijevom podstablu i swappamo ga sa elementom koji se brise
              r->key=temp->key;
              r->value=temp->value;     
              r->lijevi=obrisiCvor(r->lijevi, temp->key); //brisemo maximum u lijevom podstablu elementa koji se brise
          }
      }
      return r;
  }
  
  Cvor* dodajCvor(TipKljuca k, TipVrijednosti t, Cvor* &r, Cvor* roditelj)
  {
      if(r==nullptr)
      {
          r=new Cvor(k, t, nullptr, nullptr, r);
          brElemenata++;
          return r;
      }
      else if(k>r->key) return dodajCvor(k, t, r->desni, r); //dodajemo desno od roota
      else return dodajCvor(k,t,r->lijevi, r);              //dodajemo lijevo od roota
  }
  
  void iskopirajMapu(Cvor* &first, Cvor* second, Cvor* roditelj)
  {
      if(second==nullptr) return;
      first=new Cvor(second->key, second->value, nullptr, nullptr, roditelj);
      iskopirajMapu(first->desni, second->desni, first);
      iskopirajMapu(first->lijevi, second->lijevi, first);
  }
  
  
public:

  BinStabloMapa()
  {
      root=nullptr;
      brElemenata=0;
  }
  
  ~BinStabloMapa()
  {
      this->obrisi();
  }
  
  BinStabloMapa(const BinStabloMapa<TipKljuca,TipKljuca> &temp)
  {
      iskopirajMapu(root, temp.root, nullptr);
      brElemenata=temp.brElemenata;
  }
  
  BinStabloMapa& operator=(const BinStabloMapa<TipKljuca,TipVrijednosti> &temp)
  {
      if(this==&temp) return *this;
      this->obrisi();
      iskopirajMapu(root, temp.root, nullptr);
      brElemenata=temp.brElemenata;
      return *this;
  }
  
  void obrisi()
  {
      tempObrisi(root);
      brElemenata=0;
      root=nullptr;
  }
  
  void obrisi(TipKljuca k)
  {
      obrisiCvor(root, k);
      brElemenata--;
  }
  
  TipVrijednosti operator[](const TipKljuca k) const
  {
      Cvor* temp=nadjiCvor(k, root);
      if(temp==nullptr) return TipVrijednosti();
      return temp->value;
  }
  
  TipVrijednosti& operator[](TipKljuca k)
  {
      Cvor* temp=nadjiCvor(k, root);
      if(temp==nullptr) temp = dodajCvor(k, TipVrijednosti(), root, nullptr);
      return temp->value;
  }
  
  int brojElemenata() const
  {
      return brElemenata;
  }
 
};


template<typename TipKljuca, typename TipVrijednosti>
class NizMapa: public Mapa<TipKljuca,TipVrijednosti>
{
    std::pair<TipKljuca,TipVrijednosti>* niz;
    int brElemenata=0;
    int kapacitet;
    
    public:
    NizMapa()
    {
        niz = new std::pair<TipKljuca,TipVrijednosti>[1000];
        kapacitet=1000;
        brElemenata=0;
    }
    
    NizMapa(const NizMapa<TipKljuca,TipVrijednosti> &l)
    {
        kapacitet=l.kapacitet;
        brElemenata=l.brElemenata;
        niz=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i=0; i<brElemenata; i++)
        {
            niz[i].first=l.niz[i].first;
            niz[i].second=l.niz[i].second;
        }
        
    }
    
    NizMapa operator= (NizMapa<TipVrijednosti,TipKljuca> &m)
    {
        if(this==&m) return *this;
        
        delete[] niz;
        brElemenata=m.brElemenata;
        kapacitet=m.kapacitet;
        niz=new std::pair<TipKljuca, TipVrijednosti>[kapacitet];
        for(int i=0; i<brElemenata; i++)
        {
            niz[i].first=m.niz[i].first;
            niz[i].second=m.niz[i].second;
            
        }
        return *this;
        
    }
    
    ~NizMapa()
    {
        this->obrisi();
    }
    
    int brojElemenata() const
    {
        return brElemenata;
    }
    
    void obrisi()
    {
        delete[] niz; niz=nullptr; brElemenata=0;
    }
    
    void obrisi(TipKljuca kljuc)
    {
        int n = this->brojElemenata();
        for(int i=0; i<n; i++)
        {
            if(niz[i].first==kljuc)
            {
                for(int j=i; j<n-1; j++)
                {
                    niz[j]=niz[j+1];
                }
                brElemenata--;
                return;
            }
        }
    }
    
    TipVrijednosti operator[](TipKljuca k) const
    {
        int n=this->brojElemenata();
        for(int i=0; i<n; i++)
        {
            if(niz[i].first==k)
            {
                return niz[i].second;
            }
        }
        
        return TipVrijednosti();
    }
    
    TipVrijednosti& operator [](TipKljuca k)
    {
        if(brElemenata==0)
        {
            delete[] niz;
            niz=nullptr;
            kapacitet=1000;
            niz=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
            niz[0].first=k;
            niz[0].second=TipVrijednosti();
            brElemenata++;
            return niz[0].second;
        }
        int n=this->brojElemenata();
        for(int i=0; i<n; i++)
        {
            if(niz[i].first==k)
            {
                return niz[i].second;
            }
        }
        
        if(brElemenata==kapacitet-1)
        {
            int tempVel=kapacitet+1000;
            auto tempNiz=niz;
            tempNiz=new std::pair<TipKljuca, TipVrijednosti>[tempVel];
            for(int i=0; i<n;i++) tempNiz[i]=niz[i]; //prepisivanje
            this->obrisi();
            niz=tempNiz;
            brElemenata=n;
            kapacitet=tempVel;
            tempNiz=nullptr;
        }
        niz[brElemenata].first=k;
        niz[brElemenata].second=TipVrijednosti();
        brElemenata++;
        return niz[brElemenata-1].second;
        
    }
    
    
};



int main() {
    std::vector<int> randomize;
    for(int i=0; i<=3000; i++) randomize.push_back(rand()%300);
    BinStabloMapa<int,int> treeMapa;
    NizMapa<int,int> nMapa;
    
    clock_t tajm1=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      treeMapa[randomize[i]]=i*3;
    }
    clock_t tajm2=clock();
    int sum1=(tajm2-tajm1)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za dodavanje 3000 elemenata u BinStabloMapu, bilo je potrebno "<<sum1<<" ms.\n";
    
    clock_t tajm3=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      nMapa[randomize[i]]=i*3;
    }
    clock_t tajm4=clock();
    int sum2=(tajm4-tajm3)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za dodavanje 3000 elemenata u NizMapu, bilo je potrebno "<<sum2<<" ms.\n";
    
    clock_t tajm5=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      treeMapa[randomize[i]];
    }
    clock_t tajm6=clock();
    int sum3=(tajm6-tajm5)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za pristup elementima BinStabloMape bilo je potrebno "<<sum3<<" ms.\n";
    
    clock_t tajm7=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      nMapa[randomize[i]];
    }
    clock_t tajm8=clock();
    int sum4=(tajm8-tajm7)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za pristup elementima NizMape bilo je potrebno "<<sum4<<" ms.\n";
    
    //rezultati su ocekivani, jer je pristup elementima u BinStabloMapi O(logn) kao i njihovo dodavanje, dok je kod NizMape O(n). Razlika je primjetna pri velikoj kolicini podataka.
    
}
