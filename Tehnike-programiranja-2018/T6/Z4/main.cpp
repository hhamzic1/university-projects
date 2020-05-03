#include <stdexcept>
#include <iostream>

int **KreirajTrougao(int n)
{
    if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
    
    try
    {
        int **nizpok=new int*[n]{};
        try
        {
             nizpok[0]=new int[n*n];           
        }
        catch(std::bad_alloc)
        {
            delete[] nizpok;
            throw;
        }
        
        nizpok[0][0]=1;
        int duzreda=1;
        for(int i=1; i<n; i++)
        {
            try
            {
                nizpok[i]=nizpok[i-1]+duzreda;
                duzreda=i*2+1;
                for(int j=0; j<duzreda; j++)
                {
                    nizpok[i][j]=j+1-i;
                    nizpok[i][duzreda-j-1]=j+1-i;
                }
            }
            catch(std::bad_alloc)
            {
                delete[] nizpok[0];
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
	    delete[] trougao[0];
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
}