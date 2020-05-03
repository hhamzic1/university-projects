//TP 2017/2018: Tutorijal 3, Zadatak 8
#include <iostream>
#include <vector>
#include <stdexcept>
bool jelrazmak(char p)
{
    if(p==' ') return true;
    else
    {
        return false;
    }
}

std::string IzdvojiRijec(std::string recenica, int n)
{   
    if(n<=0) throw std::range_error("Pogresan redni broj rijeci!");
    recenica.push_back(' ');
    
    std::vector<std::string> kontenjer(1);
    bool jednarijec=true;
    int redbroj=0;              // varijabla koja sadrzi broj rijeci u recenici 
    
    for(int i=0; i<recenica.length(); i++)    //dio koda koji smjesta u vektor stringova svaku rijec u recenici
    {
        
           if(jelrazmak(recenica.at(i))) continue;
           
           else
           {
               while(!jelrazmak(recenica.at(i)) && i<recenica.length()-1)
               {
        
                   jednarijec=true;
                   if(jednarijec)
                   {
                    kontenjer.at(redbroj).push_back(recenica.at(i));   //puni se string u nasem vektoru sa karakterima iz recenice/stringa
             
                   }
                   i++;
               }
               
               if(jelrazmak(recenica.at(i)))
                 {
                     jednarijec=false;
                     redbroj++;
                     kontenjer.resize(redbroj+1);
                     
                 }
                 
           }
            
    
    }
    
    if(n>redbroj) throw std::range_error("Pogresan redni broj rijeci!");
    else
    {
    return kontenjer.at(n-1);
    }
}


int main ()
{
	int n;
	
	std::cout<<"Unesite redni broj rijeci: ";
	std::cin>>n;
	std::cin.ignore(100000,'\n');
	
	std::cout<<"Unesite recenicu: ";
	std::string rec;
	
	std::getline(std::cin, rec);
	try
	{
    	auto stringo=IzdvojiRijec(rec, n);
    	std::cout<<"Rijec na poziciji "<<n<<" je "<<stringo;
	}
	catch(std::range_error izuzetak)
	{
	    std::cout<<"IZUZETAK: "<<izuzetak.what();
	}
	
	return 0;

}
