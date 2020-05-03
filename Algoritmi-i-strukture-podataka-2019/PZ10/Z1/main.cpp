#include <iostream>
#include <vector>

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
class MatricaGraf: public UsmjereniGraf<Tip>
{
    struct InfoGrana{
        Tip oznakaCvora;
        double tezina;
        bool egzistira;
    };
    
    vector<vector<InfoGrana>> matrica;
    vector<Tip> oznakaCvorova;
public:
    
    MatricaGraf(int brojCvorova) : UsmjereniGraf<Tip>(brojCvorova)
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








int main() {
UsmjereniGraf<bool> *g = new MatricaGraf<bool>(6);
  g->dodajGranu(0, 1, 2.5);
  g->dodajGranu(1, 2, 1.2);
  g->dodajGranu(1, 3, 0.1);
  g->dodajGranu(3, 3, -4.0);
  g->dodajGranu(2, 4, 3.14);
  g->dodajGranu(2, 3, 2.73);
  g->dodajGranu(3, 5, 1);
  g->dodajGranu(5, 2, -5.0);
  
  vector<Cvor<bool>> bfsObilazak;
  vector<Cvor<bool>> dfsObilazak;
  bfs(g,bfsObilazak, g->dajCvor(0));
  dfs(g,dfsObilazak, g->dajCvor(0));
  for(int i=0; i<bfsObilazak.size(); i++) cout<<bfsObilazak[i].dajRedniBroj()<<", ";
  cout<<"\n";
  for(int i=0; i<dfsObilazak.size(); i++) cout<<dfsObilazak[i].dajRedniBroj()<<", ";
  
  delete g;
}