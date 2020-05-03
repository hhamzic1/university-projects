#include <type_traits>
#include <stdexcept>
#include <vector>
#include <deque>
#include <iostream>
using std::vector;
using std::deque;

template<typename kontenjer>
 auto KreirajDinamickuKopiju2D(kontenjer mat)->typename std::remove_reference<decltype(mat[0][0])>::type**
{
	try
	{
		auto matrica=new typename std::remove_reference<decltype(mat[0][0])>::type*[mat.size()]{};
		try
		{
			for(int i=0; i<mat.size(); i++)
			{
				matrica[i]=new typename std::remove_reference<decltype(mat[0][0])>::type[mat[i].size()];
			}
			for(int i=0; i<mat.size(); i++)
			{
				for(int j=0; j<mat[i].size(); j++)
				{
					matrica[i][j]=mat[i][j];
				}
			}
		}
		catch(std::bad_alloc)
		{
			for(int i=0; i<mat.size(); i++) delete[] matrica[i];
			delete[] matrica;
			throw;
		}
		return matrica;
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
		vector<deque<int>>matrica(n, deque<int>(n));
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
		for(int i=0; i<n ;i++)delete[] mat[i];
		delete[] mat;
		
	}
	catch(std::bad_alloc)
	{
		std::cout<<"Nedovoljno memorije";
	}
	return 0;
}