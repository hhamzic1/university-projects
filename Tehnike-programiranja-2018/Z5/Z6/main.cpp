//TP 2018/2019: Zadaća 5, Zadatak 6
#include <iostream>
#include <fstream>
#include <functional>
#include <ios>
template <typename TipElementa>
class DatotecniKontejner
{
    std::fstream tok;
    public: 
        DatotecniKontejner(const std::string &ime_datoteke)
        {
            
            tok(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
            if(!tok) throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
        }
        void DodajNoviElement(const TipElementa &element);
        int DajBrojElementa();
        TipElementa DajElement(int pozicija);
        void IzmijeniElement(int pozicija, const TipElementa &element);
        void Sortiraj(std::function<bool(const TipElementa &, const TipElementa &)> kriterij = std::less<TipElementa>());
};
int main ()
{
	return 0;
}