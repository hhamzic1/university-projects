#include <stdexcept>
#include <iostream>

int **KreirajTrougao(int n)
{
    if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
    
    try
    {
        int **nizpok=new int*[n]{};
        for(int i=0; i<n; i++)
        {
            try
            {
                int duzreda=i*2+1;
                nizpok[i]=new int[duzreda];
                for(int j=0; j<duzreda; j++)
                {
                    nizpok[i][j]=j+1-i;
                    nizpok[i][duzreda-j-1]=j+1-i;
                }
            }
            catch(std::bad_alloc)
            {
                for(int i=0; i<n; i++) delete[] nizpok[i];
                delete[] nizpok;
                throw;
            }
        }
        
        return nizpok;
    }
    catch(std::bad_alloc)
    {
        throw;
    }
}




int main ()
{
	try
	{
	    std::cout<<"Koliko zelite redova: ";
	    int n;
	    std::cin>>n;
	    int **trougao=KreirajTrougao(n);
	    
	    for(int i=0; i<n; i++)
	    {
	        for(int j=0; j<i*2+1; j++)
	        {
	            std::cout<<trougao[i][j]<<" ";
	            
	        }
	        std::cout<<"\n";
	    }
	    for(int i=0; i<n; i++) delete[] trougao[i];
	    delete[] trougao;
	    return 0;
	}
	catch(std::bad_alloc)
	{
	    std::cout<<"Izuzetak: Nedovoljno memorije!";
	}
	catch(std::domain_error e)
	{
	    std::cout<<"Izuzetak: "<<e.what();
	}
	
	return 0;
}