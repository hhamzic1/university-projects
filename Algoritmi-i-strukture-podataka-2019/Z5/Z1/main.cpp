#include <iostream>
#include <vector>

//PZ10

using namespace std;

template<typename Tip>
class Grana;

template<typename Tip>
class Cvor;

template<typename Tip>
class GranaIterator;




template<typename Tip>
class UsmjereniGraf
{
    public:
    UsmjereniGraf(int brCvorova){}
    virtual ~UsmjereniGraf(){}
    virtual int dajBrojCvorova() const = 0;
    virtual void postaviBrojCvorova(int brojCvorova) = 0;
    virtual void dodajGranu(int polazniCvor, int dolazniCvor, double tezinaGrane)=0;
    virtual void obrisiGranu(int polazniCvor, int dolazniCvor) = 0;
    virtual double dajTezinuGrane(int polazniCvor, int dolazniCvor) = 0;
    virtual void postaviTezinuGrane(int polazniCvor, int dolazniCvor, double tezina) = 0;
    virtual bool postojiGrana(int polazniCvor, int dolazniCvor) = 0;
    virtual void postaviOznakuCvora(int cvor, Tip oznaka) = 0;
    virtual Tip dajOznakuCvora(int cvor) const = 0;
    virtual void postaviOznakuGrane(int polazniCvor, int dolazniCvor, Tip oznaka) = 0;
    virtual Tip dajOznakuGrane(int polazniCvor, int dolazniCvor) const = 0;
    Grana<Tip> dajGranu(int polazniCvor, int dolazniCvor)
    {
        return Grana<Tip>(this, polazniCvor, dolazniCvor);
    }
    
    Cvor<Tip> dajCvor(int cvor)
    {
        return Cvor<Tip>(this,cvor);
    }
    
    virtual GranaIterator<Tip> dajGranePocetak() = 0;
    virtual GranaIterator<Tip> dajGraneKraj() = 0;
    virtual GranaIterator<Tip> dajSljedecuGranu(int polazniCvor, int dolazniCvor) = 0;
};

template<typename Tip>
class Grana
{
    UsmjereniGraf<Tip>* usmjereniGraf;
    bool postojiGrana;
    int polazniCvor;
    int dolazniCvor;
public:
    
    Grana(UsmjereniGraf<Tip> *usmjereniGraf, int polazniCvor, int dolazniCvor) : usmjereniGraf(usmjereniGraf), polazniCvor(polazniCvor), dolazniCvor(dolazniCvor){}
    
    double dajTezinu() const
    {
        return usmjereniGraf->dajTezinuGrane(polazniCvor, dolazniCvor);
    }
    
    Tip dajOznaku() const
    {
        return usmjereniGraf->dajOznakuGrane(polazniCvor, dolazniCvor);
    }
    
    void postaviOznaku(Tip oznakaGrane)
    {
        return usmjereniGraf->postaviOznakuGrane(polazniCvor, dolazniCvor, oznakaGrane);
    }
    
    double dajTezinu()
    {
        return usmjereniGraf->dajTezinuGrane(polazniCvor, dolazniCvor);
    }
    
    void postaviTezinu(double tezinaGrane)
    {
        return usmjereniGraf->postaviTezinuGrane(polazniCvor, dolazniCvor, tezinaGrane);
    }
    
    Cvor<Tip> dajPolazniCvor() const
    {
        return usmjereniGraf->dajCvor(polazniCvor);
    }
    
    Cvor<Tip> dajDolazniCvor() const
    {
        return usmjereniGraf->dajCvor(dolazniCvor);
    }
};


template<typename Tip>
class Cvor
{
    UsmjereniGraf<Tip> *usmjereniGraf;
    int redniBroj;
public:
    Cvor(UsmjereniGraf<Tip>* usmjereniGraf, int redniBroj):usmjereniGraf(usmjereniGraf), redniBroj(redniBroj){}
    Tip dajOznaku() const
    {
        return usmjereniGraf->dajOznakuCvora(redniBroj);
    }
    
    void postaviOznaku(Tip oznakaCvora)
    {
        return usmjereniGraf->postaviOznakuCvora(redniBroj, oznakaCvora);
    }
    
    int dajRedniBroj() const
    {
        return redniBroj;
    }
};

template<typename Tip>
class GranaIterator
{
    UsmjereniGraf<Tip>* usmjereniGraf;
    int polazniCvor, dolazniCvor;
public:
    
    GranaIterator(UsmjereniGraf<Tip>* usmjereniGraf, int polazniCvor, int dolazniCvor): usmjereniGraf(usmjereniGraf), polazniCvor(polazniCvor), dolazniCvor(dolazniCvor){}
    Grana<Tip> operator*()
    {
        return Grana<Tip>(usmjereniGraf, polazniCvor, dolazniCvor);
    }
    
    bool operator == (const GranaIterator& gi) const
    {
        return (usmjereniGraf==gi.usmjereniGraf && polazniCvor==gi.polazniCvor && dolazniCvor==gi.dolazniCvor);
    }
    
    bool operator !=(const GranaIterator& gi) const
    {
        return !(*this==gi);
    }
    
    GranaIterator& operator ++(int)
    {
        GranaIterator temp(*this);
        ++(*this);
        return temp;
    }
    
    GranaIterator& operator ++()
    {
        if(polazniCvor==-1 && dolazniCvor==-1) throw "Iterator izlazi van opsega";
        GranaIterator<Tip> og = usmjereniGraf->dajSljedecuGranu(polazniCvor, dolazniCvor);
        polazniCvor=og.polazniCvor;
        dolazniCvor=og.dolazniCvor;
        return *this;
    }
    
    Cvor<Tip> dajPolazniCvor() const
    {
        return usmjereniGraf->dajCvor(polazniCvor);
    }
    
    Cvor<Tip> dajDolazniCvor() const
    {
        return usmjereniGraf->dajCvor(dolazniCvor);
    }
    
    double dajTezinu()
    {
        return usmjereniGraf->dajTezinuGrane(polazniCvor, dolazniCvor);
    }
};


template<typename Tip>
class ListaGraf: public UsmjereniGraf<Tip>
{
    struct InfoGrana{
        Tip oznakaCvora;
        double tezina;
        bool egzistira;
    };
    
    std::vector<std::vector<InfoGrana>> matrica;
    std::vector<Tip> oznakaCvorova;
public:
    
    ListaGraf(int brojCvorova) : UsmjereniGraf<Tip>(brojCvorova)
    {
        postaviBrojCvorova(brojCvorova);
    }
    
    void postaviOznakuCvora(int cvor, Tip oznakaCvora)
    {
        oznakaCvorova[cvor]=oznakaCvora;
    }
    
    Tip dajOznakuCvora(int cvor) const
    {
        return oznakaCvorova[cvor];
    }
    
    void postaviOznakuGrane(int polazniCvor, int dolazniCvor, Tip oznakaCvora)
    {
        matrica[polazniCvor][dolazniCvor].oznakaCvora=oznakaCvora;
    }
    
    Tip dajOznakuGrane(int polazniCvor, int dolazniCvor) const
    {
        return matrica[polazniCvor][dolazniCvor].oznakaCvora;
    }
    
    GranaIterator<Tip> dajSljedecuGranu(int polazniCvor, int dolazniCvor)
    {
        for(int i= polazniCvor; i<matrica.size(); i++)
        {
            for(int j=0; j<matrica.size(); j++)
            {
                if(i==polazniCvor && j<=dolazniCvor) continue;
                if(matrica[i][j].egzistira) return GranaIterator<Tip>(this,i,j);
            }
        }
        return GranaIterator<Tip>(this,-1,-1);
    }
    
    int dajBrojCvorova() const
    {
        return matrica.size();
    }
    
    void postaviBrojCvorova(int brojCvorova)
    {
        if(brojCvorova < matrica.size()) throw "Ne moze se smanjit broj cvorova";
        InfoGrana og;
        og.egzistira=false;
        for(int i=0; i<matrica.size(); i++) matrica[i].resize(brojCvorova, og);
        vector<InfoGrana> newRow(brojCvorova, og);
        matrica.resize(brojCvorova, newRow);
        oznakaCvorova.resize(brojCvorova);
    }
    
    GranaIterator<Tip> dajGranePocetak()
    {
        GranaIterator<Tip> og(this, 0,-1);
        return ++og;
    }
    
    GranaIterator<Tip> dajGraneKraj()
    {
        GranaIterator<Tip> og(this,-1,-1);
        return og;
    }
    
    void dodajGranu(int polazniCvor, int dolazniCvor, double tezina)
    {
        InfoGrana og;
        og.tezina=tezina;
        og.egzistira=true;
        matrica[polazniCvor][dolazniCvor]=og;
    }
    
    
    void obrisiGranu (int polazniCvor, int dolazniCvor)
    {
        matrica[polazniCvor][dolazniCvor].egzistira=false; //samo je ukinemo I guess
    }
    
    void postaviTezinuGrane(int polazniCvor, int dolazniCvor, double tezina)
    {
        matrica[polazniCvor][dolazniCvor].tezina=tezina;
    }
    
    bool postojiGrana(int polazniCvor, int dolazniCvor)
    {
        return matrica[polazniCvor][dolazniCvor].egzistira;
    }
    
    double dajTezinuGrane(int polazniCvor, int dolazniCvor)
    {
        return matrica[polazniCvor][dolazniCvor].tezina;
    }
    
    
};

template<typename Tip>
void bfs(UsmjereniGraf<Tip> *usmjereniGraf, vector<Cvor<Tip>>&obilazak, Cvor<Tip> c)
{
    bool posjecen = false;
    for(int i=0; i<obilazak.size(); i++)
    {
        if(c.dajRedniBroj()==obilazak[i].dajRedniBroj())
        {
            posjecen=true; //ako je posjecen nije od interesa
            break;
        }
    }
    if(!posjecen) obilazak.push_back(c); //ako nije posjecen posjecujemo ga i idemo rekurzivno dalje
    int brojCvorova=usmjereniGraf->dajBrojCvorova();
    for(int i=0; i<brojCvorova; i++)
    {
        if(posjecen==false) bfs(usmjereniGraf, obilazak, usmjereniGraf->dajCvor(i));
    }
}


template<typename Tip>
void dfs(UsmjereniGraf<Tip> *usmjereniGraf, vector<Cvor<Tip>> &obilazak, Cvor<Tip> c)
{
    bool posjecen=false;
    for(int i=0; i<obilazak.size(); i++)
    {
        if(c.dajRedniBroj()==obilazak[i].dajRedniBroj())
        {
            posjecen=true; //ako je posjecen nije od interesa, i idemo rekurzivno dublje u graf
            break;
        }
    }
    if(!posjecen) obilazak.push_back(c); //ako nije posjecen, posjecujemo ga
    int brojCvorova = usmjereniGraf->dajBrojCvorova();
    for(int i=0; i<brojCvorova; i++)
    {
        if(usmjereniGraf->postojiGrana(c.dajRedniBroj(),i) && !posjecen) dfs(usmjereniGraf, obilazak, usmjereniGraf->dajCvor(i));
    }
}




//PZ9
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
class HashMapaLan : public Mapa<TipKljuca, TipVrijednosti>
{
    
  int velicina, brElemenata;
  std::pair<TipKljuca,TipVrijednosti> *pars;
  unsigned int (*hashFun)(TipKljuca k, unsigned int opseg) = 0;
  
public:
  
  HashMapaLan()
  {
      velicina=1000;
      pars=nullptr;
      brElemenata=0;
  }
  
  HashMapaLan(HashMapaLan<TipKljuca,TipVrijednosti> &nova)
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
  
  HashMapaLan& operator= (HashMapaLan<TipKljuca,TipVrijednosti> &nova)
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
  
  virtual ~HashMapaLan<TipKljuca, TipVrijednosti>()
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
int main() {
    std::cout << "Zadaća 5, Zadatak 1";
    return 0;
}
