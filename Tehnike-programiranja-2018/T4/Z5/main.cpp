#include <vector>
#include <iostream>
#include <string>

template <typename bilosta>
bilosta Presjek(bilosta x, bilosta y)
{
    
    auto v=x;
    v.resize(0);
    
    for(int i=0; i<x.size(); i++)
    {
        bool ponavljanje=false;
        for(int j=0; j<y.size(); j++)
        {
            if(x.at(i)==y.at(j))
            {
                ponavljanje=true;
                break;
            }
        }
        if(ponavljanje)
        {
            bool isti=false;
            for(int k=0; k<v.size(); k++)
            {
                if(x.at(i)==v.at(k))
                {
                    isti=true;
                    break;
                }
            }
            if(isti==false)
            {
                v.push_back(x.at(i));
            }
        }
    }
    
    return v;
    
    
}

bool jelrazmak(char p)
{
    if(p==' ') return true;
    else
    {
        return false;
    }
}




int main()
{
    std::cout<<"Test za realne brojeve...";
    std::cout<<"\nUnesite broj elemenata prvog vektora: ";
    int n;
    std::cin>>n;
    std::cout<<"Unesite elemente prvog vektora: ";
    std::vector<int> veka(n);
    int elem;
   for(int i=0; i<n; i++)
    {
        
        std::cin>>elem;
        veka.at(i)=elem;
    }
    
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>n;
    std::cout<<"Unesite elemente drugog vektora: ";
    std::vector<int> veka2(n);
    
    for(int i=0; i<veka2.size(); i++)
    {
        std::cin>>elem;
        veka2.at(i)=elem;
    }
    
    auto rez=Presjek(veka, veka2);
    std::cout<<"Zajednicki elementi su: ";
    for(int i=0; i<rez.size(); i++)
    {
        std::cout<<rez.at(i)<<" ";
    }
    
    std::cout<<"\n";
    std::cout<<"\nTest za stringove...";
    std::cout<<"\nUnesite broj elemenata prvog vektora: ";
    std::cin>>n;
    std::cin.ignore(100000,'\n');
    std::vector<std::string> rec(n);
    int k=0;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    while(k<rec.size())
    {
        std::getline(std::cin, rec.at(k));
        k++;
    }
    
    k=0;
    
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>n;
    std::cin.ignore(100000,'\n');
    std::vector<std::string> rec1(n);
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    
    while(k<rec1.size())
    {
        std::getline(std::cin, rec1.at(k));
        k++;
    }
    
    auto string=Presjek(rec, rec1);
    std::cout<<"Zajednicki elementi su:\n";
    
    for(int i=0; i<string.size(); i++)
    {
        std::cout<<string.at(i)<<"\n";
    }
    
	return 0;
}