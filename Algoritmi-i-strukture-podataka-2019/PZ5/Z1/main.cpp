#include <iostream>


int fib_petlja (int n) 
{
    if (n<=1) return n; // 0 i 1
    int pretprosli(0), prosli(1), rezultat;
    
        for (int i(2); i<=n; i++) 
        {
        rezultat = pretprosli+prosli;
        pretprosli = prosli;
        prosli = rezultat;
        }
        
    return rezultat;
}

int fib2_0 (int n, int prvi=0, int drugi=1, int sljedeci=0, int brojac=0) {
    sljedeci=prvi+drugi;
    prvi=drugi;
    drugi=sljedeci;
    brojac++;
    if(brojac==n-1) return sljedeci;
    return fib2_0(n,prvi, drugi, sljedeci, brojac);
}



int nzd(int x, int y)
{
    if(y==0) return x;
    return nzd(y,x%y);
}





int main() {
    std::cout << fib2_0(5)<<std::endl;
    std::cout<<nzd(12,144);
}
