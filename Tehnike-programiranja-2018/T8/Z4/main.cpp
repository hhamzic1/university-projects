//TP 2018/2019: Tutorijal 8, Zadatak 4
#include <iostream>
#include <map>
#include <string>

std::string ZamijeniPremaRjecniku(std::string s, std::map<std::string, std::string> mapa)
{
    for(int i=0; i<s.length(); i++)
    {
        int brojac=0;
        if(s[i]>='a' && s[i]<='z')
        {
            for(int j=i ;; j++)
            {
                if(s[j]<'a' || s[j]>'z') break;
                brojac++;
            }
            std::string novi=s.substr(i,brojac);
            auto p=mapa.find(novi);
            if(p==mapa.end())
            {
                i+=novi.length()-1;
                continue;
            }
            s.erase(i, brojac);
            s.insert(i, p->second);
            i+=p->second.length()-1;
        }
    }
    return s;
}

int main ()
{
	return 0;
}