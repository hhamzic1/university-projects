#include <cmath>
#include <iomanip>
#include <iostream>

int brojcifara(int broj)
{
	if(broj==0) return 1;
	else 
	{
		return int(log10(std::abs(broj)))+1;
	}
}

double TrapeznoPravilo(double (*f)(double), double a, double b, int n)
{
	double suma=0;
	for(int k=1; k<n; k++)
	{
		suma+=f(a+((b-a)/n)*k);
	}
		double integral=(b-a)/n * (0.5*f(a) + 0.5*f(b) + suma);
		
		if(integral <=1e-10) integral=0;
		return integral;
	
}



int main ()
{
	const double PI = 4*atan(1);
	int n;
	std::cout<<"Unesite broj podintervala: ";
	std::cin>>n;
	std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:\n";
	
	double integral1, integral2, integral3;
	
	integral1=TrapeznoPravilo(std::sin,0,PI,n);
	std::cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::setprecision(6-brojcifara(integral1))<<std::fixed<<integral1<<"\n";
	
	integral2=TrapeznoPravilo([](double x)-> double{return x*x*x;},0,10,n);
	std::cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::setprecision(6-brojcifara(integral2))<<integral2<<"\n";
	
	integral3=TrapeznoPravilo([](double x)-> double{return 1/x;}, 1,2,n);
	std::cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::setprecision(6-brojcifara(integral3))<<integral3;
	
	return 0;
	
	
}