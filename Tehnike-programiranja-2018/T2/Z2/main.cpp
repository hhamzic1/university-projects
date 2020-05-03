//TP 2017/2018: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>
#include <cmath>
#define eps 0.00001
bool TestPerioda(std::vector<double> q, int p)
{
    bool test=true;
    
    if(p<1 || p>=q.size()) return false;
    else
    {
        for(int i=0; i<q.size(); i++)
        {
            if(i+p<q.size() && fabs(q[i]-q[i+p])>eps)
            {
                test=false;
                break;
            }
        }
    }
    return test;
}
int OdrediOsnovniPeriod(std::vector<double> a)
{
    int period=0;
    
    for(int i=1; i<a.size(); i++) 
    {
        bool ponavljanje=true;
        if(fabs(a[0]-a[i])<eps)
        {
            for(int j=1; j<a.size()-i; j++)
            {
                if(fabs(a[j]-a[i+j])>eps)
                {
                    ponavljanje=false;
                    break;
                }
            }
            if(ponavljanje)
            {
                period=i;
                break;
            }
        }
    }
    if(TestPerioda(a, period)) return period;
    return 0;
}

int main ()
{
	std::vector<double> veka;
	std::cout<<"Unesite slijed brojeva (0 za kraj): ";
	double broj;
	while(1)
	{
	    std::cin>>broj;
	    if(fabs(broj)<eps) break;
	    veka.push_back(broj);
	    
	}
	
	int odgovor=OdrediOsnovniPeriod(veka);
	if(odgovor!=0)
	{
	    std::cout<<"Slijed je periodican sa osnovnim periodom "<<odgovor<<".";
	}
	else
	{
	    std::cout<<"Slijed nije periodican!";
	}
	
	return 0;
}

