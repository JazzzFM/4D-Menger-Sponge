#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "Vector3D.hpp"
#include "Matrix3D.hpp"

Matrix3D::Matrix3D(void)
{
   for (int i=0; i<4; i++)
      {
       for (int j=0; j<4; j++)
          a[i][j]= 0.0;
       a[i][i]= 1.0;
      }
}

Matrix3D::Matrix3D(double a00, double a01, double a02,
                   double a10, double a11, double a12,
                   double a20, double a21, double a22)
{
    a[0][0]= a00; a[0][1]= a01; a[0][2]= a02; a[0][3]= 0.0;
    a[1][0]= a10; a[1][1]= a11; a[1][2]= a12; a[1][3]= 0.0;
    a[2][0]= a20; a[2][1]= a21; a[2][2]= a22; a[2][3]= 0.0;
    a[3][0]= 0.0; a[3][1]= 0.0; a[3][2]= 0.0; a[3][3]= 1.0;
}

Matrix3D::Matrix3D(char ty, double t)
{
   for (int i=0; i<4; i++)
      {
       for (int j=0; j<4; j++)
          a[i][j]= 0.0;
       a[i][i]= 1.0;
      }

   int r, s;
   switch (ty)
      {
       case 'x':  r= 1; s=2;  break;
       case 'y':  r= 0; s=2;  break;
       case 'z':  r= 0; s=1;  break;
      }
    t*= M_PI / 180.0;
    a[r][r]=  cos(t); a[r][s]= -sin(t);
    a[s][r]=  sin(t); a[s][s]=  cos(t);
}

Matrix3D::Matrix3D(char ty, const Vector3D& u)
{
  for (int i=0; i<4; i++)
      {
       for (int j=0; j<4; j++)
           a[i][j]= 0.0;
       a[i][i]= 1.0;
      }

   switch(ty) {
      case 's':  case 'S': a[0][0]= u.x();
                           a[1][1]= u.y();
                           a[2][2]= u.z();
                           break;
      case 't':  case 'T': a[0][3]= u.x();
                           a[1][3]= u.y();
                           a[2][3]= u.z();
                           break;
      case 'i':  case 'I': break;
     }
}

const double* Matrix3D::operator[] (int i) const
{
   return a[i];
}


Vector3D Matrix3D::operator * (Vector3D& u) const
{
    Vector3D r;
    for (int i=0; i<3; i++)
       {
        double s= 0.0;
        for (int j=0; j<4; j++)
            s+= a[i][j] * u[j];
        r[i]= s;
       }
    return r;
}

Matrix3D Matrix3D::operator * (const Matrix3D& m) const
{
    Matrix3D r('i');
    for (int i=0; i<4; i++)
       for (int j=0; j<4; j++)
          {
           double s= 0;
           for (int k=0; k<4; k++)
              s+= a[i][k] * m.a[k][j];
           r.a[i][j]= s;
          }
    return r;
}


Matrix3D Matrix3D::operator + (const Matrix3D& m) const
{
    Matrix3D r('i');

    for (int i=0; i<4; i++)
       for (int j=0; j<4; j++)
           r.a[i][j]= a[i][j] + m.a[i][j];

    return r;
}
