
#include <iostream>

void unesi(char niz[], int velicina)
{
	
	char znak=getchar();
	if(znak=='\n') znak=getchar();
	int karakter=0;
	while(karakter<velicina-1 && znak!='\n')
	{
		*niz=znak;
		karakter++;
		niz++;
		znak=getchar();
	}
	*niz='\0';
}
bool spejs(char p)
{
	if((p>='A' && p<='Z') || (p>='a' && p<='z')) return false;
	else
	{
		return true;
	}
}



int main ()
{
	char recenica[1000];

	
	std::cout<<"Unesite recenicu: ";
	unesi(recenica, 1000);
	
	
	
	
	char *pocetak=recenica;
	char *p=recenica;
	bool kraj=false;
	bool jednarijec=true;
	int brojrijeci=1;
	bool izlaz=false;
	
	while(*p!='\0')
	{
		if(spejs(*p))
		{
			p++;
			continue;
		}
		else
		{
			while(!spejs(*p))
			{
				if(jednarijec==false)brojrijeci++;
				if(brojrijeci==2)
				{
					pocetak=p;
					izlaz=true;
					break;
				}
				
				jednarijec=true;
				p++;
				if(*p=='\0')
				{
					kraj=true;
					break;
				}
				
			}
			if(kraj || izlaz) break;
			else if(spejs(*p))
			{
				jednarijec=false;
				p++;
			}
		}
	}
	std::cout<<"Recenica bez prve rijeci glasi: ";
	
	if(brojrijeci!=2) return 0;
	while(*pocetak!='\0')
	{
		std::cout<<*pocetak;
		pocetak++;
	}
	std::cout<<"\n";
	

	return 0;
}