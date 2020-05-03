#include <iostream>
#include <tuple>

using std::get;

typedef std::tuple<double,double,double> Vektor3d;

void UnesiVektor(Vektor3d &v) 
{
 std::cout << "X = "; std::cin >>get<0>(v);
 std::cout << "Y = "; std::cin >>get<1>(v);
 std::cout << "Z = "; std::cin >>get<2>(v);
}

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2)
{
 return std::make_tuple(get<0>(v1)+get<0>(v2), get<1>(v1)+get<1>(v2), get<2>(v1)+get<2>(v2));
}

Vektor3d VektorskiProizvod(const Vektor3d &v1, const Vektor3d &v2) 
{
 double x1,y1,z1;
 double x2,y2,z2;
 std::tie(x1,y1,z1)=v1;
 std::tie(x2,y2,z2)=v2;
 return std::make_tuple(y1*z2-z1*y2, z1*x2-x1*z2, x1*y2-y1*x2);
}

void IspisiVektor(const Vektor3d &v) 
{
 std::cout << "{" <<get<0>(v)<< "," << get<1>(v) << "," << get<2>(v) << "}";
}


int main() {
 Vektor3d a, b;
 std::cout << "Unesi prvi vektor:\n";
 UnesiVektor(a);
 std::cout << "Unesi drugi vektor:\n";
 UnesiVektor(b);
 std::cout << "Suma ova dva vektora je: ";
 IspisiVektor(ZbirVektora(a, b));
 std::cout << std::endl << "Njihov vektorski prozivod je: ";
 IspisiVektor(VektorskiProizvod(a, b));
 return 0;
}
