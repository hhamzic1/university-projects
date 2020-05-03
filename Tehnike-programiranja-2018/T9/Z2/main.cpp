//TP 2018/2019: Tutorijal 8, Zadatak 1
#include <iostream>
#include <cmath>


class Vektor3d
{
    double koordinate[3];
public:
void Postavi(double x, double y, double z)
{
    Vektor3d::koordinate[0]=x; Vektor3d::koordinate[1]=y; Vektor3d::koordinate[2]=z;
}

void Ocitaj(double &x, double &y, double &z) const
{
    x=Vektor3d::koordinate[0]; y=Vektor3d::koordinate[1]; z=Vektor3d::koordinate[2];
}

void Ispisi() const
{
    std::cout<<"{"<<koordinate[0]<<","<<koordinate[1]<<","<<koordinate[2]<<"}";
}

void PostaviX(double x) {Vektor3d::koordinate[0]=x;}
void PostaviY(double y) {Vektor3d::koordinate[1]=y;}
void PostaviZ(double z) {Vektor3d::koordinate[2]=z;}

double DajX() const{return koordinate[0];}
double DajY() const{return koordinate[1];}
double DajZ() const{return koordinate[2];}
double DajDuzinu() const {return std::sqrt(koordinate[0]*koordinate[0]+koordinate[1]*koordinate[1]+koordinate[2]*koordinate[2]);}

Vektor3d &PomnoziSaSkalarom(double s)
{
    koordinate[0]*=s; koordinate[1]*=s; koordinate[2]*=s;
    return *this;
}

Vektor3d &SaberiSa(const Vektor3d &v)
{
    koordinate[0]+=v.koordinate[0]; koordinate[1]+=v.koordinate[1]; koordinate[2]+=v.koordinate[2];
    return *this;
}

friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);

};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2)
{
    Vektor3d v3;
    v3.koordinate[0]=v1.koordinate[0]+v2.koordinate[0];
    v3.koordinate[1]=v1.koordinate[1]+v2.koordinate[1];
    v3.koordinate[2]=v1.koordinate[2]+v2.koordinate[2];
    return v3;
}


int main ()
{
	return 0;
}