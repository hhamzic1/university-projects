//TP 2017/2018: Tutorijal 3, Zadatak 6
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
typedef std::vector<std::vector<int>> matrica;

matrica KroneckerovProizvod(std::vector<int> v1, std::vector<int> v2)
{
    int a=v1.size();
    int b=v2.size();

    matrica kron(a, std::vector<int>(b));
    
    for(int i=0; i<v1.size(); i++)
    {
        for(int j=0; j<v2.size(); j++)
        {
            kron[i][j]=v1[i]*v2[j];
        }
    }
    
    return kron;
}

int NajvecaSirina(matrica matra)
{
    int sirina=0;
    int redovi=matra.size();
    
    if(redovi==0) return 0;
    
    
    int temp=0;
    for(int i=0; i<redovi; i++)
    {
        for(int j=0; j<matra[i].size(); j++)
        {
            int c=matra[i][j];
            sirina=0;
            if(c<0) sirina++;  // ako je broj negativan ide ++ u sirini zbog -
            while(c!=0)
            {
                sirina++;
                c/=10;
            }
            if(sirina>temp) temp=sirina;
        }
    }
   
    return temp;
}



int main()
{
	std::cout<<"Unesite broj elemenata prvog vektora: ";
	int n;
	std::cin>>n;
	std::cout<<"Unesite elemente prvog vektora: ";
	std::vector<int> veka1;
	int elem;
	for(int i=0; i<n; i++)
	{
	    std::cin>>elem;
	    veka1.push_back(elem);
	}
	
	std::cout<<"Unesite broj elemenata drugog vektora: ";
	std::cin>>n;
	std::cout<<"Unesite elemente drugog vektora: ";
	std::vector<int> veka2;
	for(int i=0; i<n; i++)
	{
	    std::cin>>elem;
	    veka2.push_back(elem);
	}
	
	auto mat=KroneckerovProizvod(veka1, veka2);
	std::cout<<std::endl;
	int sir=NajvecaSirina(mat)+1;
	
	
	for(int i=0; i<veka1.size(); i++)
	{
	    for(int j=0; j<veka2.size(); j++)
	    {
	        std::cout<<std::right<<std::setw(sir)<<mat[i][j];
	    }
	    std::cout<<"\n";
	}
	
	
	return 0;
}
