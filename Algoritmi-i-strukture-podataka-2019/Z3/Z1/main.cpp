#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void counting(std::vector<int> &v, int s)
{
    int h[10]={0};
    std::vector<int> ret=v;
    for(int i=0; i<v.size(); i++) h[(v[i]/s)%10]++;
    for(int i=1; i<10; i++) h[i]+=h[i-1];
    for(int i=v.size()-1; i>=0; i--)
    {
        ret[h[(v[i]/s)%10]-1]=v[i];
        h[(v[i]/s)%10]--;
    }
    for(int i=0; i<v.size(); i++) v[i]=ret[i];
}

int gMax(std::vector<int> &v)
{
    int m=v[0];
    for(int i=1; i<v.size(); i++) if(v[i]>m) m = v[i];
    return m;
}

void radixSort(std::vector<int> &v)
{
    int m=gMax(v);
    for(int i=1; m/i>0; i=i*10) counting(v, i);
}


bool isLeaf(std::vector<int> &v, int indeks)
{
    return (indeks>=v.size()/2 && indeks<v.size());
}

void rebuildDown(std::vector<int> &v, int indeks)
{
    while(isLeaf(v,indeks)!=true)
    {
        int veci=2*indeks+1;
        int dd=2*indeks+2;
        if(dd<v.size() && v[dd]>v[veci]) veci=dd;
        if(v[indeks]>v[veci]) return;
        std::swap(v[indeks], v[veci]);
        indeks=veci;
    }
}

void rebuildUp(std::vector<int> &v, int indeks)
{
    while(indeks!=0 && v[indeks]>v[(indeks-1)/2])
    {
        std::swap(v[indeks], v[(indeks-1)/2]);
        indeks=(indeks-1)/2;
    }
}

void stvoriGomilu(std::vector<int> &v)
{
    for(int i = v.size()/2; i>=0; i--)
    {
        for(int j=i; j<v.size()/2;)
        {
            int left=2*j+1;
            int right=2*j+2;
            if(right<v.size() && v[left]<v[right]) left=right;
            if(v[j]<=v[left])
            {
                std::swap(v[j],v[left]);
                j=left;
            }else break;
        }
    }
}


void umetniUGomilu(std::vector<int> &v, int umetnuti, int &velicina)
{
    v.push_back(umetnuti);
    velicina++;
    rebuildUp(v, velicina-1);
}

int izbaciPrvi(std::vector<int> &v, int &velicina)
{
    if(velicina<=0) return -1;
    int first=v.front();
    velicina--;
    std::swap(v[0], v[velicina]);
    std::vector<int> tempV(velicina);
    for(int i=0; i<tempV.size(); i++) tempV[i]=v[i];
    stvoriGomilu(tempV);
    for(int i=0; i<tempV.size(); i++) v[i]=tempV[i];
    return first;
}

void gomilaSort(std::vector<int> &v)
{
    stvoriGomilu(v);
    auto p=v.begin(), k=v.end();
    int vel=v.size();
    
    while(p!=k)
    {
        std::vector<int> tempV(p, k--);
        izbaciPrvi(tempV, vel);
        for(int i=0; i<tempV.size(); i++) v[i]=tempV[i];
    }
}



int main() {
    std::vector<int> veka={1,5,7,2,3,4,10,-2};
    gomilaSort(veka);
    for(int i=0; i<veka.size(); i++) std::cout<<veka[i]<<" ";
}
