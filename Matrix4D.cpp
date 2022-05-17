#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "Vector4D.hpp"
#include "Matrix4D.hpp"


Matrix4D::Matrix4D(void)
{
   for (int i=0; i<5; i++)
      {
       for (int j=0; j<5; j++)
          a[i][j]= 0.0;
       a[i][i]= 1.0;
      }
}

 
int Matrix4D::axis(char n) {

	int echo;
   switch (n)
      {
       case 'x':  echo = 0;
       case 'y':  echo = 1;
       case 'z':  echo = 2;
       case 't':  echo = 3;
      }

   return echo;
}


Matrix4D::Matrix4D(char t0, char t1, char t2, char t3, double u, double v)
{
   for (int i=0; i<5; i++)
      {
       for (int j=0; j<5; j++)
          a[i][j]= 0.0;
       a[i][i]= 1.0;
      }
 
   int r0= axis(t0); 
   int r1= axis(t1); 
   int r2= axis(t2); 
   int r3= axis(t3); 

    u*= M_PI / 180.0; 
    a[r0][r0]=  cos(u); a[r0][r1]= -sin(u);
    a[r1][r0]=  sin(u); a[r1][r1]=  cos(u);

    v*= M_PI / 180.0; 
    a[r2][r2]=  cos(v); a[r2][r3]= -sin(v);
    a[r3][r2]=  sin(v); a[r3][r3]=  cos(v);
}


Matrix4D::Matrix4D(char t0, char t1, double u)
{
   for (int i=0; i<5; i++)
      {
       for (int j=0; j<5; j++)
          a[i][j]= 0.0;
       a[i][i]= 1.0;
      }
 
   int r0= axis(t0); 
   int r1= axis(t1); 

    //u*= M_PI / 180.0; 
    a[r0][r0]=  cos(u); a[r0][r1]= -sin(u);
    a[r1][r0]=  sin(u); a[r1][r1]=  cos(u);
}


Matrix4D::Matrix4D(char ty, const Vector4D& u)
{
   for (int i=0; i<5; i++)
      {
       for (int j=0; j<5; j++)
           a[i][j]= 0.0;
       a[i][i]= 1.0;
      }

   switch (ty) {
     case 's':  case 'S': a[0][0]= u.x();
                          a[1][1]= u.y();
                          a[2][2]= u.z();
                          a[3][3]= u.t();
                          break;
     case 't':  case 'T': a[0][4]= u.x();
                          a[1][4]= u.y();
                          a[2][4]= u.z();
                          a[3][4]= u.t();
                          break;
     case 'i':  case 'I': break;
   }
}

Matrix4D::Matrix4D( double a00, double a01, double a02, double a03,
                    double a10, double a11, double a12, double a13,
                    double a20, double a21, double a22, double a23,
                    double a30, double a31, double a32, double a33)
{
   a[0][0]= a00; a[0][1]= a01; a[0][2]= a02; a[0][3]= a03; a[0][4]= 0.0;
   a[1][0]= a10; a[1][1]= a11; a[1][2]= a12; a[1][3]= a13; a[1][4]= 0.0;
   a[2][0]= a20; a[2][1]= a21; a[2][2]= a22; a[2][3]= a23; a[2][4]= 0.0;
   a[3][0]= a30; a[3][1]= a31; a[3][2]= a32; a[3][3]= a33; a[3][4]= 0.0;
   a[4][0]= 0.0; a[4][1]= 0.0; a[4][2]= 0.0; a[4][3]= 0.0; a[4][4]= 1.0;
}


const double* Matrix4D::operator [] (int i) const
{
    return a[i];
}


Vector4D Matrix4D::operator * (const Vector4D& u) const
{
    Vector4D r;
    for (int i=0; i<5; i++)
      {
       double s= 0.0; 
       for (int j=0; j<5; j++)
          s+= a[i][j] * u[j];
       r[i]= s;
      }
    return r;
}


Matrix4D Matrix4D::operator * (const Matrix4D& m) const
{
    Matrix4D r;
    for (int i=0; i<5; i++)
       for (int j=0; j<5; j++)
          {
           double s= 0.0;
           for (int k=0; k<5; k++)
              s+= a[i][k] * m[k][j];
           r.a[i][j]= s;
          }
    return r;
}

