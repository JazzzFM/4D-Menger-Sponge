
using namespace std;

#include "Facet.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


Facet::Facet() {}

Facet::Facet(const Quaternion& a, const Quaternion& b, const Quaternion& c) {
	
	A = Quaternion(a);
	B = Quaternion(b);
	C = Quaternion(c);
	N = Quaternion(0, unit( (B.V()-A.V())) % (C.V()-A.V()) );
}

Facet::Facet(const Vector3D& a, const Vector3D& b, const Vector3D& c) {

        A = Quaternion(0, a);
        B = Quaternion(0, b);
        C = Quaternion(0, c);
        N = Quaternion(0, unit( (b - a)) % (c - a) );
}

Facet::Facet(const Facet& facet) {

        A = Quaternion(0, facet[0]);
        B = Quaternion(0, facet[1]);
        C = Quaternion(0, facet[2]);
        N = Quaternion(0, facet[3]);
}

Vector3D Facet::operator [] (int k) const {
   if (k > 3)
      return Vector3D(0, 0, 0);
   else {
   
   	if (k == 0) return A.V();
	if (k == 1) return B.V();
	if (k == 2) return C.V();
	if (k == 3) return N.V();
   }
}

void Facet::updateFacet(const Vector3D& a, const Vector3D& b, const Vector3D& c) {

	A = Quaternion( 0.0, a);
	B = Quaternion( 0.0, b);
	C = Quaternion( 0.0, c);
	N = Quaternion( 0.0, unit( (b-a) % (c-a) ));

}

Vector3D Facet::getCenter() {
	
	Vector3D tmp = Vector3D(0, 0, 0);	
	tmp = tmp + A.V() + B.V() + C.V();
	tmp = 0.333333 * tmp;

	return tmp;
}

ostream& operator << (ostream& os, const Facet& a) {

   int w= os.width();
   int p= os.precision();
   os << setw(0) << "Facet[ " 
      << setw(w) << setprecision(p) << a[0] << setw(0) << ", " 
      << setw(w) << setprecision(p) << a[1] << setw(0) << ", " 
      << setw(w) << setprecision(p) << a[2] << setw(0) << ", Normal("
      << setw(w) << setprecision(p) << a[3] << setw(0) << ") ] ";
   os.width(w);
   os.precision(p);
   return os;
}

void Facet::translate(const Vector3D& a) {

	Quaternion aa = A + Quaternion(a);
	Quaternion bb = B + Quaternion(a);
	Quaternion cc = C + Quaternion(a);

	updateFacet(aa.V(), bb.V(), cc.V());
}
