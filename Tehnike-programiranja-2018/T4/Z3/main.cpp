//TP 2018/2019: Tutorijal 4, Zadatak 3
#include <iostream>
#include <vector>
#include <cctype>


bool jelrazmak(char p)
{
    if(p==' ' || p=='\n') return true;
    else
    {
        return false;
    }
}

void IzdvojiKrajnjeRijeci(std::vector<std::string> veka, std::string &c, std::string &d)
{
	if(veka.size()==0)
	{
		c="";
		d="";
		return;
	}
		
		std::string prva=veka.at(0);

		std::string zadnja=veka.at(0);
		
		std::string pravaprva;
		std::string pravazadnja;
		
		
	
		for(int i=0; i<veka.size(); i++)
		{
			std::string value1=veka.at(i);
			std::string temp=veka.at(i);
			for(int i=0; i<temp.size(); i++)
			{
				temp.at(i)=std::toupper(temp.at(i));
			}
			for(int i=0; i<prva.size(); i++)
			{
				prva.at(i)=std::toupper(prva.at(i));
			}
			if(temp<=prva) 
			{
				prva=value1;
				pravaprva=value1;
			}
		}
		
		for(int i=0; i<veka.size(); i++)
		{
			std::string value=veka.at(i);
			std::string temp=veka.at(i);
			for(int i=0; i<temp.size(); i++)
			{
				temp.at(i)=std::toupper(temp.at(i));
			}
			for(int i=0; i<zadnja.size(); i++)
			{
				zadnja.at(i)=std::toupper(zadnja.at(i));
			}
			if(temp>=zadnja) 
			{
				zadnja=value;
			    pravazadnja=value;
			}	
		}
		
		c=pravaprva;
		d=pravazadnja;
		
	
}

void ZadrziDuplikate(std::vector<std::string> &a)
{
	std::vector<std::string> veka;
	
	for(int i=0; i<a.size(); i++)  //prolazimo kroz prvi vektor
	{
		bool ponavljanje=false;     //ponavljanje na false
		for(int j=i+1; j<a.size(); j++)  //prolazimo kroz isti vektor drugom petljom od elementa
		{
			
			if(a.at(i)==a.at(j))  //ako nadjemo isti element
			{
				ponavljanje=true;  //ponavljanje je true
				break;
			}
		}
		if(ponavljanje)  //ako je ponavljanje true udje se ovdje
		{
			bool isti=false;		//isti su false
			for(int k=0; k<veka.size(); k++)	//provjerava se da li u novom vektoru ima isti element, da ne dupliramo
			{
				if(a.at(i)==veka.at(k))
				{
					isti=true;
					break;
				}
			}
			if(isti==false) //upisat ce se u novi vektor taj element iz a koji je imao svog dvojnika
			{
				veka.push_back(a.at(i));
			}
		}
		
	}
	
	a=veka;
	
	
}




int main ()
{
	std::cout<<"Koliko zelite unijeti rijeci: ";
	int n;
	std::cin>>n;
	std::cin.ignore(10000000,'\n');
	
	std::vector<std::string> veka(n);
    int elem;
    int i=0;
    std::cout<<"Unesite rijeci: ";
	while(i<n)
	{
	    elem=getchar();
	    
	    if(jelrazmak(elem)) continue;
	    
	    else
	    {
	    	while(!jelrazmak(elem))
	    	{
	    		veka.at(i).push_back(elem);
	    		elem=getchar();
	    	}
	    	
	    	i++;
	    }
	}

	std::string a;
	std::string b;
	IzdvojiKrajnjeRijeci(veka, a, b);
	ZadrziDuplikate(veka);
	
	std::cout<<"Prva rijec po abecednom poretku je: "<<a<<"\nPosljednja rijec po abecednom poretku je: "<<b;
	std::cout<<"\nRijeci koje se ponavljaju su: ";
	for(int i=0; i<veka.size(); i++)
	{
		std::cout<<veka[i]<<" ";
	}
	
	return 0;
}