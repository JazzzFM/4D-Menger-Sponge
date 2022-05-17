
using namespace std;

#include "PlaneQuaternion.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


PlaneQuaternion::PlaneQuaternion() {}

PlaneQuaternion::PlaneQuaternion(int m, const Vector3D& a, const Vector3D& b) {
	
	//DEFINE THE NORMAL
	this->normal = Quaternion(0.0, Vector3D(0, 0, 1));
        this->point[0] = unit(Vector3D( 1, 0, 0));
	this->point[1] = unit(Vector3D( 0, 1, 0));
	this->point[2] = unit(Vector3D(-1, 0, 0));
	this->point[3] = unit(Vector3D( 0,-1, 0));
	this->base = Vector3D(b);
	//DEFINE THE DIFFERENCE VECTOR (v = a-b)
	Quaternion J = Quaternion(0.0, unit(a-b));

	//CHECK OF v coincides with (0, 0, 1)
	int ll = linePointIntersection(J.V(), Vector3D(0, 0, 1), Vector3D(0, 0, 0)); 
	
	//Rotate
	if (ll != 1) {
		
		base = Vector3D(b);
		Quaternion N = Quaternion(0, normal.V());
		normal = rotate(normal, a, b, N);
		Quaternion p0 = rotate(Quaternion(point[0]), a, b, N);
		Quaternion p1 = rotate(Quaternion(point[1]), a, b, N);
		Quaternion p2 = rotate(Quaternion(point[2]), a, b, N);
		Quaternion p3 = rotate(Quaternion(point[3]), a, b, N);

		point[0] = Vector3D(p0.V());
                point[1] = Vector3D(p1.V());
                point[2] = Vector3D(p2.V());
                point[3] = Vector3D(p3.V());

	}
		

}	

//Fetch PlaneQuaternion Data
Vector3D PlaneQuaternion::operator [] (int k) const {
   if (k > 5)
      return Vector3D(0, 0, 0);
   else {
   
   	if (k == 0) return normal.V();
	if (k == 1) return base;
	if (k == 2) return point[0];
	if (k == 3) return point[1];
	if (k == 4) return point[2];
	if (k == 5) return point[3];
   }
}


int  PlaneQuaternion::linePointIntersection(const Vector3D& r, const Vector3D& a, const Vector3D& b) {

	Vector3D cro = (a-r) % (b-r);
	if (cro == Vector3D(0, 0, 0)) return 1;
	else return 0;
}


//void PlaneQuaternion::identiyFrame(const Quaternion& q) {
//
//	this->normal = q.conjugate() * this->normal;
//	Quaternion Point = Quaternion(0.0, point[0]);
//	Point = q.conjugate() * Point;
//
//	Quaternion Base = Quaternion(0.0, base);
//	Base = q.conjugate() * Base;
//
//	point[0] = Vector3D(Point.V());
//}

int PlaneQuaternion::checkPoint(const Quaternion& p, const Quaternion& J) {

	Quaternion P = Quaternion(0.0, p.V());
        P = P - Quaternion(0.0, this->base);
        Vector3D tau = unit(unit(normal.V()) % unit(J.V()));
        double phi = acos(unit(normal.V()) * unit(J.V()));

        Quaternion tauQ = Qan(phi, tau);
        Quaternion p0 = tauQ * P * tauQ.conjugate();

        if (p0.V().z() >= 0.0) return 1;
        else return 0;
}

int PlaneQuaternion::equalR(double a, double b) {

	int epsilon = 1e-20;
	double cc = (a - b) * (a - b);

	if (sqrt(cc) < epsilon)
		return 1;
	else
		return 0;
}


double PlaneQuaternion::intersectionLine(const Vector3D& a, const Vector3D& b) { 

	double A = this->normal.V().x();
	double B = this->normal.V().y();
	double C = this->normal.V().z();

	double X0 = this->base.x();
	double Y0 = this->base.y();
	double Z0 = this->base.z();
	
	double D = Vector3D(A, B, C) * Vector3D(X0, Y0, Z0);
	double Dpr = Vector3D(A, B, C) * b;
	double Dps = Vector3D(A, B, C) * (a-b);

	double t = (D - Dpr) / Dps;

	if (0.0 < t && t < 1.0 ) return t;
	else {
		if (equalR(t, 0.0) == 1) return t;
		if (equalR(t, 1.0) == 1) return t;
		if (t < 0.0 || 1.0 < t) return -10000.0;
	}
}

void PlaneQuaternion::updateOrientation() {
	this->normal = Quaternion(this->normal.r(), -1.0 * this->normal.V());
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

