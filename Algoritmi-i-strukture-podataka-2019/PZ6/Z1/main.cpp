#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>
using namespace std;
template <typename Tip>
void bubble_sort(Tip *niz, int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++) 
        {
            if(niz[j]>niz[j+1])
            {
                Tip temp=niz[j];
                niz[j]=niz[j+1];
                niz[j+1]=temp;
            }
            
        }
    }
}

template<typename Tip>
void selection_sort(Tip *niz, int n)
{
    int indeks=-1;
    for(int i=0; i<n; i++)
    {
        Tip min=niz[i];
        for(int j=i+1; j<n; j++)
        {
            if(niz[j]<min) {min=niz[j];indeks=j;} 
        }
        
        if(indeks!=i && indeks!=-1)
        {
            Tip temp=niz[i];
            niz[i]=niz[indeks];
            niz[indeks]=temp;
            indeks=-1;
        }
    }
}


template<typename Tip>
void quick_sort(Tip *niz, int n) // n je high l je low
{
    int minimum=0;
    if(n-1<=minimum) return;
    std::swap(niz[minimum], niz[(minimum+n)/2]);
    for(int i=1; i<n; i++)
    {
        if(niz[i]<niz[0]) std::swap(niz[++minimum], niz[i]);
    }
    std::swap(niz[0],niz[minimum]);
    quick_sort(niz,minimum);
    quick_sort(niz+minimum+1,n-minimum-1);
}


template<typename Tip>
void merge_sort(Tip *niz, int n)
{
    if(n>1)
    {
        int sred=n/2;
        int i=0, j=0, k=0;
        Tip *ppola=new Tip[sred];
        Tip *dpola=new Tip[n-sred];
        for(i=0; i<sred; i++) ppola[i]=niz[i];
        for(;i<n;i++) dpola[i-sred]=niz[i];
        merge_sort(ppola,sred);
        merge_sort(dpola,n-sred);
        for(i=0; j<sred && k<n-sred; i++)
        {
            if(ppola[j]<dpola[k]) niz[i]=ppola[j++];
            else{
                niz[i]=dpola[k++];
            }
        }
        for(;j<sred; i++,j++) niz[i]=ppola[j];
        for(;k<n-sred; k++,i++) niz[i]=dpola[k];
        delete[] ppola;
        delete[] dpola;
    }
    
}

void addMemory(int &velicina, int*&niz)
{
    int temp=velicina;
    velicina+=10000;
    int *help = new int[velicina];
    for(int i=0; i<temp; i++) help[i]=niz[i]; //prepisivanje
    delete[] niz;
    niz=help;
    for(int i=0; i<temp; i++) niz[i]=help[i];
}

void generisi(std::string filename, int vel)
{
    ofstream dat;
    dat.open(filename.c_str());
    srand(time(NULL));
    for(int i=0; i<vel; i++) dat<<rand()/1000<<" ";
}




void ucitaj(std::string filename, int *&niz, int &vel)
{
    ifstream dat (filename.c_str());
    int br=0, kap=10000;
    niz=new int[kap];
    while(dat>>br)
    {
        if(vel==kap-1) addMemory(kap,niz);
        niz[vel]=br;
        vel++;
    }
}


void funkcija()
{
    int *niz, velicina=0, choice, brojElemenata;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>brojElemenata;
    generisi("proba.txt",brojElemenata);
    std::cout<<"Elementi uspjesno izgenerisani"<<endl;
    ucitaj("proba.txt",niz,velicina);
    std::cout<<"Izaberite sort:\n1. Bubble sort\n2. Selection sort\n3. QuickSort\n4. Merge sort\n:";
    for(;;)
    {
        std::cin>>choice;
        if(choice>=1 && choice <=4) break;
        std::cout<<"Greska pri odabiru, odaberite broj ponovo: \n";
    }
    
    switch(choice)
    {
        case 1:{
            clock_t tajm1=clock();
            bubble_sort(niz,velicina);
            clock_t tajm2=clock();
            int vrijeme=(tajm2-tajm1)/(CLOCKS_PER_SEC/1000);
            std::cout<<"Vrijeme izvrsavanja: "<<vrijeme<<" ms.\n";
            break;
        }
        case 2:{
            clock_t tajm1=clock();
            selection_sort(niz,velicina);
            clock_t tajm2=clock();
            int vrijeme=(tajm2-tajm1)/(CLOCKS_PER_SEC/1000);
            std::cout<<"Vrijeme izvrsavanja: "<<vrijeme<<" ms.\n";
            break;
        }
        case 3:{
            clock_t tajm1=clock();
            quick_sort(niz,velicina);
            clock_t tajm2=clock();
            int vrijeme=(tajm2-tajm1)/(CLOCKS_PER_SEC/1000);
            std::cout<<"Vrijeme izvrsavanja: "<<vrijeme<<" ms.\n";
            break;
        }
        case 4:{
            clock_t tajm1=clock();
            merge_sort(niz,velicina);
            clock_t tajm2=clock();
            int vrijeme=(tajm2-tajm1)/(CLOCKS_PER_SEC/1000);
            std::cout<<"Vrijeme izvrsavanja: "<<vrijeme<<" ms.\n";
            break;
        }
        default: 
            break;
    }
    
    
    //provjera sorta
    for(int i=0; i<velicina-1; i++)
    {
        if(niz[i]>niz[i+1]) throw std::domain_error("Greška u sortu");
    }
    //i upis u datoteku
    
    
        ofstream izlaz;
        izlaz.open("sort.txt");
        for(int i=0; i<velicina; i++)
        {
            izlaz<<niz[i]<<" ";
        }
        std::cout<<"Uspjesno upisano u datoteku\n";
    

}





int main() 
{
    try{
    funkcija();
    }catch(std::domain_error e)
    {
        std::cout<<e.what();
    }
}
