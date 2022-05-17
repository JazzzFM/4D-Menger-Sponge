#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "Vector4D.hpp"

class Matrix4D {
    private:
       double a[5][5];
       int axis(char);

    public:
       Matrix4D(void);
       Matrix4D(char r0, char r1, char r2, char r3, double u, double v);
       Matrix4D(char r0, char r1, double u);
       Matrix4D(char ty, const Vector4D& t= Vector4D(0.0, 0.0, 0.0, 0.0));
       Matrix4D( double a00, double a01, double a02, double a03,
                 double a10, double a11, double a12, double a13,
                 double a20, double a21, double a22, double a23,
                 double a30, double a31, double a32, double a33);

       const double*  operator[] (int) const;
       Vector4D operator * (const Vector4D& u) const;
       Matrix4D operator * (const Matrix4D& m) const;
       Matrix4D operator + (const Matrix4D& m) const;
};

#endif
