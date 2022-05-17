#ifndef VECTOR4D_H
#define VECTOR4D_H

using namespace std;

#include <iostream>
#include <math.h>

class Vector4D {
       private:
         double u[5];

       public:
         double& operator [] (int k);
         double  operator [] (int k) const;
         Vector4D(double xx=0, double yy= 0, double zz= 0, double tt=0);
         Vector4D(const Vector4D& a);
         double x() const { return u[0]; };
         double y() const { return u[1]; };
	 double z() const { return u[2]; };
	 double t() const { return u[3]; };

         Vector4D& operator = (const Vector4D&);
         Vector4D& operator += (const Vector4D&);
         Vector4D& operator /= (double);
        };


Vector4D operator + (const Vector4D& a, const Vector4D& b);
Vector4D operator - (const Vector4D& a, const Vector4D& b);

Vector4D Cross(const Vector4D& a, const Vector4D& b, const Vector4D& c);

Vector4D operator * (double a, const Vector4D& b);
double   operator * (const Vector4D& a, const Vector4D& b);
Vector4D operator / (const Vector4D& a, const double b);
Vector4D operator - (const Vector4D& a);
bool     operator == (const Vector4D&, const Vector4D& );
bool     operator <  (const Vector4D&, const Vector4D& );
double   abs(const Vector4D& a);
double   infty(const Vector4D& a);
Vector4D unit(const Vector4D& v);
Vector4D zero(const Vector4D& v);

istream& operator >> (istream& is, Vector4D& a);
ostream& operator << (ostream& os, const Vector4D& a);

Vector4D rect(double t, const Vector4D& b, const Vector4D& e);

#endif
