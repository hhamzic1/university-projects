//TP 2017/2018: Tutorijal 3, Zadatak 7
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
typedef std::vector<std::vector<int>> matrica;

int NajvecaSirina(matrica matra)
{
    int sirina=0;
    int temp=0;
    for(int i=0; i<matra.size(); i++)
    {
        for(int j=0; j<matra[i].size(); j++)
        {
            int c=matra[i][j];
            sirina=0;
            while(c>0)
            {
                sirina++;
                c/=10;
            }
            if(sirina>temp) temp=sirina;
        }
    }
    
    return temp;
    
}

matrica PascalovTrougao(int n)
{
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    
    matrica p(n, std::vector<int>(0));
    if(n==0) return matrica(0);
  
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<=i; j++)
        {
            p[i].push_back(0);
            
        }
    }
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<p[i].size(); j++)
        {
            if(j==0 || j==i)
            {
                p[i][j]=1;
                
            }
            else
            {
                p[i][j]=p[i-1][j]+p[i-1][j-1];
            }
        }
    }
    
    return p;
    
}

int main ()
{
    std::cout<<"Unesite broj redova: ";
    int n;
    std::cin>>n;
    std::cout<<"\n";
	auto matra=PascalovTrougao(n);
	int sirina=NajvecaSirina(matra);
	
	for(int i=0; i<matra.size(); i++)
	{
	    for(int j=0; j<matra[i].size(); j++)
	    {
	        std::cout<<std::right<<std::setw(sirina+1)<<matra[i][j];
	    }
	    std::cout<<"\n";
	}
}
