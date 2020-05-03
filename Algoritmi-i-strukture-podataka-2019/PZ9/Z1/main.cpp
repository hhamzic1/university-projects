#include <iostream>
#include <vector>
#include <string>
#include <utility>
template <typename TipKljuca, typename TipVrijednosti>
class Mapa
{
    public:
    Mapa(){};
    virtual ~Mapa(){};
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(TipKljuca kljuc) = 0;
    virtual TipVrijednosti operator[](TipKljuca k) const = 0;
    virtual TipVrijednosti &operator[](TipKljuca k) = 0;
};



template<typename TipKljuca, typename TipVrijednosti>
class HashMapa : public Mapa<TipKljuca, TipVrijednosti>
{
    
  int velicina, brElemenata;
  std::pair<TipKljuca,TipVrijednosti> *pars;
  unsigned int (*hashFun)(TipKljuca k, unsigned int opseg) = 0;
  
public:
  
  HashMapa()
  {
      velicina=1000;
      pars=nullptr;
      brElemenata=0;
  }
  
  HashMapa(HashMapa<TipKljuca,TipVrijednosti> &nova)
  {
      velicina=nova.velicina;
      brElemenata=nova.brElemenata;
      hashFun=nova.hashFun;
      pars=new std::pair<TipKljuca, TipVrijednosti>[velicina];
      for(int i=0; i<nova.velicina; i++)
      {
          pars[i]=nova.pars[i];
      }
  }
  
  HashMapa& operator= (HashMapa<TipKljuca,TipVrijednosti> &nova)
  {
      if(this==&nova) return *this;
      delete[] pars;
      velicina=nova.velicina;
      brElemenata=nova.brElemenata;
      hashFun=nova.hashFun;
      pars=new std::pair<TipKljuca, TipVrijednosti>[velicina];
      for(int i=0; i<nova.velicina; i++)
      {
          pars[i]=nova.pars[i];
      }
      
      return *this;
  }
  
  void definisiHashFunkciju(unsigned int (*hashf)(TipKljuca k, unsigned int opseg))
  {
      if(hashf==nullptr) throw "Neispravna funkcija za haširanje";
      hashFun=hashf;
  }
  
  TipVrijednosti& operator[](TipKljuca k)
  {
      if(hashFun==nullptr) throw "Ne postoji hash funkcija";
      unsigned int uhasher=hashFun(k, velicina);
      if(brElemenata==0)
      {
          pars=new std::pair<TipKljuca, TipVrijednosti>[velicina];
          pars[uhasher].first=k;
          pars[uhasher].second=TipVrijednosti();
          brElemenata++;
          for(int i=0; i<velicina; i++)
          {
              if(i!=uhasher) pars[i].first=TipKljuca();
          }
          return pars[uhasher].second;
      }
      else
      {
          if(pars[uhasher].first==k) return pars[uhasher].second;
          for(int i=uhasher+1; i<velicina; i++) if(pars[i].first==k) return pars[i].second;
          for(int i=0; i<uhasher; i++) if(pars[i].first==k) return pars[i].second;
          for(int i=0; i<velicina; i++)     //ako nema elementa u mapi moramo ga dodat
          {
              if(i!=uhasher && pars[i].first==TipKljuca())
              {
                  pars[i].first=k;
                  pars[i].second=TipVrijednosti();
                  brElemenata++;
                  return pars[i].second;
              }
          }
          if(brElemenata==velicina)
          {
              velicina+=1000;
              std::pair<TipKljuca,TipVrijednosti> *siriVezeniPeskiri = new std::pair<TipKljuca, TipVrijednosti>[velicina];
              for(int i=0; i<brElemenata; i++)
              {
                  siriVezeniPeskiri[i].first=pars[i].first;
                  siriVezeniPeskiri[i].second=pars[i].second;
              }
              
              delete[] pars;
              pars=siriVezeniPeskiri;
              siriVezeniPeskiri=nullptr;
          }
          
          pars[brElemenata].first=k;
          pars[brElemenata].second=TipVrijednosti();
          brElemenata++;
          return pars[brElemenata-1].second;
      }
  }
  
  
  TipVrijednosti operator[] (TipKljuca k) const
  {
      unsigned int uhasher=hashFun(k,velicina);
      if(pars[uhasher].first==k) return pars[uhasher].second;
        for(int i=uhasher+1; i<brElemenata; i++) if(pars[i].first==k) return pars[i].second;
        for(int i=0; i<uhasher; i++) if(pars[i].first==k) return pars[i].second;
        return TipVrijednosti();
        
      
  }
  
  virtual ~HashMapa<TipKljuca, TipVrijednosti>()
  {
      this->obrisi();
  }
  
  void obrisi()
  {
      delete[] pars;
      velicina=1000;
      brElemenata=0;
  }
  
  void obrisi(const TipKljuca k)
  {
      if(brElemenata==0) throw "Nema elemenata u mapi";
      unsigned int uhasher = hashFun(k, velicina);
      int ind = brElemenata;
      if(pars[uhasher].first==k) ind = uhasher;
      else
      {
          for(int i=0; i<velicina; i++)
          {
              if(i!=uhasher && pars[i].first==k)
              {
                  ind=i;
                  break;
              }
          }
      }
      
      if(ind==brElemenata) throw "Nema kljuca u mapi";
      pars[ind].first=TipKljuca();
      pars[ind].second=TipVrijednosti();
      brElemenata--;
  }
  
  int brojElemenata() const
  {
      return brElemenata;
  }
    
    
};


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



unsigned int hfun(int u, unsigned int max)
{
  int s = 130103;
  s=((s<<9) + 17*s);
  return s%max;
}






int main() {
      std::vector<int> randomize;
    for(int i=0; i<=3000; i++) randomize.push_back(rand()%300);
    BinStabloMapa<int,int> treeMapa;
    NizMapa<int,int> nMapa;
    HashMapa<int,int> hMapa;
    hMapa.definisiHashFunkciju(hfun);
    
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
    
    
    clock_t tajm11=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      hMapa[randomize[i]]=i*3;
    }
    clock_t tajm12=clock();
    int sum6=(tajm12-tajm11)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za dodavanje 3000 elemenata u hashMapu, bilo je potrebno "<<sum6<<" ms.\n";
    
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
    
     clock_t tajm9=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      hMapa[randomize[i]];
    }
    clock_t tajm10=clock();
    int sum5=(tajm10-tajm9)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za pristup elementima hashMape bilo je potrebno "<<sum5<<" ms.\n";
    
    //brisanje
    
    clock_t tajm13=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      try {
            treeMapa.obrisi(randomize[i]);
        } catch(...) {}
    }
    clock_t tajm14=clock();
    int sum7=(tajm14-tajm13)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za brisanje elemenata iz BinStabloMape bilo je potrebno "<<sum7<<" ms.\n";
    
    
    clock_t tajm15=clock();
    for(int i=0; i<randomize.size(); i++)
    {
       try {
            nMapa.obrisi(randomize[i]);
        } catch(...) {}
    }
    clock_t tajm16=clock();
    int sum8=(tajm16-tajm15)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za brisanje elemenata iz NizMape bilo je potrebno "<<sum8<<" ms.\n";
    
    
    
    clock_t tajm17=clock();
    for(int i=0; i<randomize.size(); i++)
    {
    
      try {
            hMapa.obrisi(randomize[i]);
        } catch(...) {}
    }
    clock_t tajm18=clock();
    int sum9=(tajm18-tajm17)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za brisanje elemenata iz HashMape bilo je potrebno "<<sum9<<" ms.\n";
    
    
    
    /*
      rezultati su ocekivani jer za dodavanje u BST je O(logn) a u nizMapu O(n), razlika
      bi drasticnije rasla sa povecavanjem broja elemenata koji se unose.
      Sto se tice HashMape ocito je da zbog velikog broja kolizija, dodavanje pristup i brisanje
      traje duze vec kod ostalih izvedbi Mapa.
    */
}
