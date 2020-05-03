//TP 2018/2019: Tutorijal 4, Zadatak 2
#include <iostream>

void IzvrniString(std::string &rec)
{
  
    for(int i=0; i<rec.length()/2; i++)
    {
        char pomocna=rec.at(i);
        char &a=rec.at(i);
        char &b=rec.at(rec.length()-i-1);
        a=b;
        b=pomocna;
  
    }
    
}




int main ()
{
    std::cout<<"Unesi string: ";
    std::string recenica;
    
    std::getline(std::cin, recenica);
    
    IzvrniString(recenica);
    
    std::cout<<"Izvrnuti string je: "<<recenica;
    
    
    
	return 0;
}