using namespace std;

#include "Octahedron.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>



Octahedron::Octahedron(double r, const Vector3D& center) {
	
	A = Quaternion(0, Vector3D(center.x() + r, center.y()    , center.z()    ));
	B = Quaternion(0, Vector3D(center.x()    , center.y() + r, center.z()    ));
	C = Quaternion(0, Vector3D(center.x()    , center.y()    , center.z() + r));
	D = Quaternion(0, Vector3D(center.x() - r, center.y()    , center.z()    ));
	E = Quaternion(0, Vector3D(center.x()    , center.y() - r, center.z()    ));
	F = Quaternion(0, Vector3D(center.x()    , center.y()    , center.z() - r));

	f[0] = Facet(A, B, C);
	f[1] = Facet(B, D, C);
	f[2] = Facet(D, E, C);
	f[3] = Facet(E, A, C);
	f[4] = Facet(B, A, F);
	f[5] = Facet(A, E, F);
	f[6] = Facet(E, D, F);
	f[7] = Facet(D, B, F);

}

Octahedron::Octahedron() {}

Facet Octahedron::operator [] (int k) const {
   if (k > 7)
      return Facet();
   else {
   
   	if (k == 0) return f[0];
	if (k == 1) return f[1];
	if (k == 2) return f[2];
	if (k == 3) return f[3];
	if (k == 4) return f[4];
	if (k == 5) return f[5];
	if (k == 6) return f[6];
	if (k == 7) return f[7];
   }
}

//ostream& operator << (ostream& os, const Facet& a) {
//
//   int w= os.width();
//   int p= os.precision();
//   os << setw(0) << "Facet[ " 
//      << setw(w) << setprecision(p) << a[0] << setw(0) << ", " 
//      << setw(w) << setprecision(p) << a[1] << setw(0) << ", " 
//      << setw(w) << setprecision(p) << a[2] << setw(0) << ", Normal("
//      << setw(w) << setprecision(p) << a[3] << setw(0) << ") ] ";
//   os.width(w);
//   os.precision(p);
//   return os;
//}

