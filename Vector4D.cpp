
using namespace std;

#include "Vector4D.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


Vector4D::Vector4D(double xx, double yy, double zz, double tt)
{
   u[0]= xx;
   u[1]= yy;
   u[2]= zz;
   u[3]= tt;
   u[4]= 1.0;
}

Vector4D::Vector4D(const Vector4D& a)
{
   u[0]= a.x();
   u[1]= a.y();
   u[2]= a.z();
   u[3]= a.t();
   u[4]= 1.0;
}

double& Vector4D::operator [] (int i) 
{
   if (i==4)
      return u[4]= 1.0;
   else
      return u[i];
}

double Vector4D::operator [] (int i) const
{
   if (i==4)
      return 1.0;
   else
      return u[i];
}

Vector4D& Vector4D::operator = (const Vector4D& a)
{
   u[0]= a.x();
   u[1]= a.y();
   u[2]= a.z();
   u[3]= a.t();
   return *this;
}

Vector4D& Vector4D::operator += (const Vector4D& a)
{
   return *this= *this + a;
}

Vector4D& Vector4D::operator /= (double a)
{
   return *this= *this / a;
}

Vector4D operator + (const Vector4D& a, const Vector4D& b)
{
   return Vector4D( a.x()+b.x(), a.y()+b.y(), a.z()+b.z(), a.t()+b.t() );
}

Vector4D operator - (const Vector4D& a, const Vector4D& b)
{
   return Vector4D( a.x()-b.x(), a.y()-b.y(), a.z()-b.z(), a.t()-b.t() );
}

double det3(double a1, double a2, double a3,
            double b1, double b2, double b3,
            double c1, double c2, double c3 )
{
   return a1 * (b2*c3 - b3*c2) 
        - a2 * (b1*c3 - b3*c1)
        + a3 * (b1*c2 - b2*c1);
}

bool operator < (const Vector4D& a, const Vector4D& b)
{
   if (a.t() < b.t())
      return true;
   if (a.t() > b.t())
      return false;

   if (a.z() < b.z())
      return true;
   if (a.z() > b.z())
      return false;

   if (a.y() < b.y())
      return true;
   if (a.y() > b.y())
      return false;

   if (a.x() < b.x())
      return true;

   return false;
}


Vector4D Cross (const Vector4D& a, const Vector4D& b, const Vector4D& c)
{
   return Vector4D(
                   det3(
                        a.y(), a.z(), a.t(),
                        b.y(), b.z(), b.t(),
                        c.y(), c.z(), c.t()
                       ),
                  -det3(
                        a.x(), a.z(), a.t(),
                        b.x(), b.z(), b.t(),
                        c.x(), c.z(), c.t()
                       ),
                   det3(
                        a.x(), a.y(), a.t(),
                        b.x(), b.y(), b.t(),
                        c.x(), c.y(), c.t()
                       ),
                  -det3(
                        a.x(), a.y(), a.z(),
                        b.x(), b.y(), b.z(),
                        c.x(), c.y(), c.z()
                       )
           );
}

Vector4D operator * (const double a, const Vector4D& b)
{
   return Vector4D( a * b.x(), a * b.y(), a * b.z(), a * b.t() );
}

double operator * (const Vector4D& a, const Vector4D& b)
{
   return a.x() * b.x() + a.y() * b.y() + a.z() * b.z() + a.t() * b.t();
}

Vector4D operator / (const Vector4D& a, const double b)
{
   return Vector4D( a.x()/b, a.y()/b, a.z()/b, a.t()/b );
}

Vector4D operator - (const Vector4D& a)
{
   return Vector4D(-a.x(), -a.y(), -a.z(), -a.t());
}

static double test(double t) {

	static double echo;
    	if (fabs(t) <= 1E-8)
    		echo = 0.0;

    	if (t < -1E-8)
    		echo = -1.0;
		
   	 if (t > 1E-8)
        	echo = 1.0;

	return echo;
}

double abs(const Vector4D& a) {
   double x= fabs(a.x()), y= fabs(a.y()), z= fabs(a.z()), t= fabs(a.t());
   double u= x+y+z+t;
   if (test(u) <= 0.0)
      return 0.0;
   x/= u;
   y/= u;
   z/= u;
   t/= u;
   return u*sqrt(x*x + y*y + z*z + t*t);
}

Vector4D unit(const Vector4D& v)
{
   double n= abs(v);
   return test(n)==0.0 ? Vector4D(0.0, 0.0, 0.0, 0.0) : v/n;
}

static double zero(double x)
{
   if (abs(x) < 1E-15)
      return 0;
   else
   if (x==0.0 && signbit(x)==1)
      return -x;
   else
      return x;
}

Vector4D zero(const Vector4D& u)
{
   return Vector4D(zero(u.x()), zero(u.y()), zero(u.z()), zero(u.t()));
}


istream& operator >> (istream& is, Vector4D& a)
{
   int c;
   double x, y, z, t;

   while ((c=is.get()) != EOF && c != '(')
       ;
   if (c==EOF)
      {
       a= Vector4D(0,0,0);
       return is;
      }

   is >> x;

   while ((c=is.get()) != EOF && c != ',')
       ;
   if (c==EOF)
      {
       a= Vector4D(x,0,0);
       return is;
      }

   is >> y;

   while ((c=is.get()) != EOF && c != ',')
       ;
   if (c==EOF)
      {
       a= Vector4D(x,y,0);
       return is;
      }

   is >> z;

   while ((c=is.get()) != EOF && c != ',')
       ;
   if (c==EOF)
      {
       a= Vector4D(x,y,z);
       return is;
      }

   is >> t;

   while ((c=is.get()) != EOF && c != ')')
       ;
   a= Vector4D(x,y,z,t);

   return is;
}

ostream& operator << (ostream& os, const Vector4D& a)
{
   int w= os.width();
   int p= os.precision();
   os << setw(0) << "(" 
      << setw(w) << setprecision(p) << a.x() << setw(0) << ", " 
      << setw(w) << setprecision(p) << a.y() << setw(0) << ", " 
      << setw(w) << setprecision(p) << a.z() << setw(0) << ", " 
      << setw(w) << setprecision(p) << a.t() << setw(0) << ") ";
   os.width(w);
   os.precision(p);
   return os;
}

Vector4D rect(double t, const Vector4D& b, const Vector4D& e)
{
   return b + t * (e-b);
}

double infty(const Vector4D& a)
{
   return fabs(a.x()) + fabs(a.y()) + fabs(a.z()) + fabs(a.t());  
}

bool  operator == (const Vector4D& a, const Vector4D& b)
{
   return test(abs(a-b))==0.0;        
}
