#ifndef Quaternion_H
#define Quaternion_H

using namespace std;

#include <iostream>
#include "Vector3D.hpp"
#include <math.h>

class Quaternion {
       private:
         double u;
	 Vector3D v;

       public:
         Vector3D& operator [] (int k);
         Vector3D  operator [] (int k) const;
         Quaternion(double xx = 0, const Vector3D& vv = Vector3D(0,0,0));
         Quaternion(const Quaternion& a);
         double r() const { return u; };
         double i() const { return v.x(); };
	 double j() const { return v.y(); };
	 double k() const { return v.z(); };
	 Vector3D V() const {return v;};

         Quaternion& operator  = (const Quaternion&);
         Quaternion& operator += (const Quaternion&);
         Quaternion& operator /= (double);
	
	 Quaternion conjugate() const {
	 	return Quaternion(r(),-V());
	 };

	 Quaternion(const Vector3D& a) {
		        u = 0.0;
		        v = Vector3D(a);
	}


        };


	Quaternion operator + (const Quaternion& a, const Quaternion& b);
	Quaternion operator - (const Quaternion& a, const Quaternion& b);
	Quaternion operator * (const Quaternion& a, const Quaternion& b);
	Quaternion Qan(double theta, const Vector3D& n);
	Quaternion cross(const Quaternion& n, const Quaternion& z);
	Quaternion rotate(const Quaternion& p, const Quaternion& normal, const Quaternion& J);

	Quaternion operator * (const double a, const Quaternion& b);
	istream& operator >> (istream& is, Quaternion& a);
	ostream& operator << (ostream& os, const Quaternion& a);

#endif
