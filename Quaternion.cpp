
using namespace std;

#include "Quaternion.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


Quaternion::Quaternion(double xx, const Vector3D& w) {

	u = xx;
	v = Vector3D(w);
}

Quaternion::Quaternion(const Quaternion& a)
{
	u = a.r();
	v = a.V();
}

Vector3D Quaternion::operator [] (int k) const {
   if (k > 1)
      return Vector3D(0, 0, 0);
   else {

        if (k == 0) return v;
   }
}

Quaternion& Quaternion::operator = (const Quaternion& a)
{
   u = a.r();
   v = a.V();
   return *this;
}

Quaternion& Quaternion::operator += (const Quaternion& a)
{
   return *this= *this + a;
}

//Quaternion& Quaternion::operator /= (double a)
//{
//   return *this= *this / a;
//}

Quaternion operator + (const Quaternion& a, const Quaternion& b) {

	return Quaternion( a.r()+b.r(), Vector3D(a.i()+b.i(), a.j()+b.j(), a.k()+b.k()) );
}

Quaternion operator - (const Quaternion& a, const Quaternion& b) {

        return Quaternion( a.r()-b.r(), Vector3D(a.i()-b.i(), a.j()-b.j(), a.k()-b.k()) );
}

Quaternion operator * (const Quaternion& a, const Quaternion& b) {
	
	return Quaternion(
				(a.r() * b.r()) - (a.V() * b.V()),
		       		(a.r() * b.V())     + (b.r() * a.V()) + cruz(a.V(), b.V()));		
}

Quaternion operator * (const double a, const Quaternion& b) {
   return Quaternion( b.r(), a * Vector3D(b.V()) );
}


ostream& operator << (ostream& os, const Quaternion& a) {

   int w= os.width();
   int p= os.precision();
   os << setw(0) << "(" 
      << setw(w) << setprecision(p) << a.r() << setw(0) << ",  (" 
      << setw(w) << setprecision(p) << a.i() << setw(0) << ", " 
      << setw(w) << setprecision(p) << a.j() << setw(0) << ", " 
      << setw(w) << setprecision(p) << a.k() << setw(0) << ") )";
   os.width(w);
   os.precision(p);
   return os;
}

Quaternion Qan(double theta, const Vector3D& n) {

                if (sqrt(theta * theta) < 1e-10)
                        return Quaternion(0.0, n);
                else
                        return Quaternion(cos(0.5 * theta), sin(0.5 * theta) * unit(n));
};

Quaternion cross(const Quaternion& n, const Quaternion& z) {

                Vector3D m = (1.0/(n.V() * z.V())) * (n.V() % z.V());
                return Quaternion(0.0, m);
        }

int  line(const Vector3D& r, const Vector3D& a, const Vector3D& b) {

                        Vector3D cro = (a-r) % (b-r); 
                        if (cro == Vector3D(0, 0, 0)) return 1;
                        else return 0;
}

Quaternion rotate(const Quaternion& p, const Vector3D& a, const Vector3D& b, const Quaternion& normal) {

	//The diference Vector = a - b;
	Quaternion difference = Quaternion( 0.0, unit(a-b));

	int ll = line(unit(a-b), Vector3D(0, 0, 1), Vector3D(0, 0, 0));

	if (ll != 1) {
		

		Vector3D tau = unit(unit(normal.V()) % unit(difference.V()));
		double phi =   acos(unit(normal.V()) * unit(difference.V()));
	
		//tau = eigenvector for space
		Quaternion tauQ = Qan(phi, tau);

		//Rotate p with respect to the eigenvector
		Quaternion p1 = tauQ * p * tauQ.conjugate();
		
		//translate p1
		return  (p1 + Quaternion(0, b));
		
	} else { return p;}


}





