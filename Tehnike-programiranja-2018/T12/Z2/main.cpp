/* 
    TP 16/17 (Tutorijal 12, Zadatak 2)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <set>
template <typename tip>
std::set<tip> operator *(std::set<tip> s1, std::set<tip> s2)
{
	std::set<tip> skup;
	for(auto x : s1)
	{
		if(s2.find(x)!=s2.end())skup.insert(x);		//presjek
	}
	return skup;
}
template <typename tip2>
std::set<tip2> operator +(std::set<tip2> s1, std::set<tip2> s2)
{
	std::set<tip2> skup;
	for(auto x : s1) skup.insert(x);
	for(auto x : s2) skup.insert(x);			//unija
	return skup;
}
template <typename tip>
std::ostream &operator <<(std::ostream &tok, const std::set<tip> &s)
{
	tok<<"{";
	for(auto it=s.begin(); it!=s.end(); it++)
	{
		if(it==(--s.end())) tok<<*it;
		else tok<<*it<<",";
	}
	tok<<"}";
	
}
template <typename tip>
std::set<tip> operator +=(std::set<tip> &s1, std::set<tip> s2)
{
	for(auto x:s2)s1.insert(x);
	return s1;
}
template <typename tip>
std::set<tip> operator *=(std::set<tip> &s1, std::set<tip> s2)
{
	std::set<tip> skup;
	for(auto x:s1)
	{
		if(s2.find(x)!=s2.end()) skup.insert(x);
	}
	s1=skup;
	return s1;
}
template <typename tip1, typename tip2>
std::set<std::pair<tip1,tip2>> operator %(std::set<tip1> s1, std::set<tip2> s2)
{
	std::set<std::pair<tip1,tip2>> par;
	for(auto x:s1)
	{
		for(auto y:s2)
		{
			par.insert(std::make_pair(x,y));			//Dekartov proizvod classic
		}
	}
	return par;
}

template <typename tip1, typename tip2>
std::ostream &operator <<(std::ostream &tok, const std::pair<tip1,tip2> &s)
{
	tok<<"("<<s.first<<","<<s.second<<")";		//ispis za parove
	return tok;
}
template <typename tip1, typename tip2>
std::ostream &operator <<(std::ostream &tok, const std::set<std::pair<tip1, tip2>> &s)
{
	tok<<"{";
	int i=0; 
	for(auto x:s)
	{
		if(i==s.size()-1) tok<<x;			//ispis za set parova
		else tok<<x<<",";	//tok<<x poziva ispis za parove
		i++;
	}
	tok<<"}";
	return tok;
}
int main ()
{
	std::set<char> s3{'A', 'B'};
	std::set<int>s4{1,2,3};
	std::cout<<s3 % s4<<std::endl;
	return 0;
}