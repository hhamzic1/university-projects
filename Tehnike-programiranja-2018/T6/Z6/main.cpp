#include <type_traits>
#include <stdexcept>
#include <vector>
#include <deque>
#include <iostream>

using std::vector;
using std::deque;
template<typename kontenjer>
	int brojElemenata(kontenjer mat)
	{
		int brojac=0;
		for(int i=0; i<mat.size(); i++)
		{
			for(int j=0; j<mat[i].size(); j++) brojac++;
		}
		return brojac;
	}
template<typename kontenjer>
	auto KreirajDinamickuKopiju2D(kontenjer mat)->typename std::remove_reference<decltype(mat[0][0])>::type**
	{
		try
		{
			auto kopija = new typename std::remove_reference<decltype(mat[0][0])>::type*[mat.size()]{};
		    try
		    {
		    	kopija[0]=new typename std::remove_reference<decltype(mat[0][0])>::type[brojElemenata(mat)];
		    	for(int i=1; i<mat.size(); i++)
		    	{
		    		kopija[i]=kopija[i-1]+mat[i-1].size();
		    	}
		    	for(int i=0; i<mat.size(); i++)
		    	{
		    		for(int j=0; j<mat[i].size(); j++)
		    		{
		    			kopija[i][j]=mat[i][j];
		    		}
		    	}
		    }
		    catch(std::bad_alloc)
		    {
		    	delete[] kopija[0];
		    	delete[] kopija;
		    	throw;
		    }
		    return kopija;
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
		std::cout<<"Unesite broj redova kvadratne matrice: ";
		int n;
		std::cin>>n;
		vector<deque<int>>matrica(n,deque<int>(n));
		std::cout<<"Unesite elemente matrice: ";
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				std::cin>>matrica.at(i).at(j);
			}
		}
		
		int **mat=KreirajDinamickuKopiju2D(matrica);
		
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				std::cout<<mat[i][j]<<" ";
			}
			std::cout<<"\n";
		}
		
		delete[] mat[0];
		delete[] mat;
	}
	catch(std::bad_alloc)
	{
		std::cout<<"Nedovoljno memorije";
	}
	return 0;
}