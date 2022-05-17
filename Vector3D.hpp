#ifndef VECTOR3D_H
#define VECTOR3D_H

using namespace std;

#include <iostream>
#include <math.h>

class Vector3D {
       protected:
         double u[4];


       public:
         double& operator [] (int k);
         double  operator [] (int k) const;

         Vector3D(double xx=0, double yy= 0, double zz= 0);
         Vector3D(const Vector3D& a);
         double x() const { return u[0]; };
         double y() const { return u[1]; };
	     double z() const { return u[2]; };

         Vector3D& operator =  (const Vector3D&);
         Vector3D& operator += (const Vector3D& a);

        };


Vector3D operator + (const Vector3D& a, const Vector3D& b);
Vector3D operator - (const Vector3D& a, const Vector3D& b);
Vector3D operator % (const Vector3D& a, const Vector3D& b);
Vector3D operator * (double a, const Vector3D& b);
double   operator * (const Vector3D& a, const Vector3D& b);
Vector3D operator / (const Vector3D& a, const double b);
Vector3D operator - (const Vector3D& a);

bool     operator == (const Vector3D&, const Vector3D& );
double   abs(const Vector3D& a);
double   infty(const Vector3D& a);
Vector3D unit(const Vector3D& v);
Vector3D centerM4(const Vector3D& a0, const Vector3D& a1, const Vector3D& a2, const Vector3D& a3);
Vector3D cPenta(Vector3D a0, Vector3D a1, Vector3D a2, Vector3D a3, Vector3D a4);
Vector3D cDodeca(Vector3D a[]);
Vector3D centerM8(const Vector3D& a0, const Vector3D& a1, const Vector3D& a2, const Vector3D& a3,
                  const Vector3D& a4, const Vector3D& a5, const Vector3D& a6, const Vector3D& a7);
Vector3D cruz(const Vector3D& a, const Vector3D& b);
istream& operator >> (istream& is, Vector3D& a);
ostream& operator << (ostream& os, const Vector3D& a);

Vector3D line(double t, Vector3D& b, Vector3D& e);

#endif
