#include<iostream>
#include<string>

template<typename tip>

void UnosBroja(std::string a, std::string b, tip &broj)
{
	
	for(;;)
	{
		std::cout<<a<<"\n";
		char p;
		if(!(std::cin>>broj) || (p=getchar()!='\n'))
		{
			std::cout<<b<<"\n";
			std::cin.clear();
			std::cin.ignore(100000,'\n');
		}
		else break;
	}

}





int main()
{
	double baza;
	UnosBroja("Unesite bazu: ","Neispravan unos, pokusajte ponovo...",baza);
	int eks;
	UnosBroja("Unesite cjelobrojni eksponent: ","Neispravan unos, pokusajte ponovo...",eks);
	double rez=1;
	if(eks>=0)
	{
		for(int i=0; i<eks; i++)
		{
			rez=rez*baza;
		}
	}
	else
	 {
	 	for(int i=0; i<(-1)*eks; i++)
	 	{
	 		rez=rez*(1./baza);
	 	}
	 }
	 std::cout<<baza<<" na "<<eks<<" iznosi "<<rez;
	 return 0;
}
