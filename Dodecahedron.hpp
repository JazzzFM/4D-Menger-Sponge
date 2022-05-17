#ifndef DODECAHEDRON_H
#define DODECAHEDRON_H

using namespace std;

#include <iostream>
#include "Facet.hpp"
#include <math.h>

class Dodecahedron {
       	private:
	 	Quaternion v[20];
		Facet f[8];
	public:
        	Facet  operator [] (int k) const;
        	Dodecahedron(double radius, const Vector3D& center);
		Dodecahedron();
};

class Torus {

	private:
		QuaternionBox q;
		int n;
		FacetBox f;
	public:
		Torus(double R, double r, const Vector3D& c, int N);
		int getN() const;
		Facet  operator [] (int k) const;
		double G1(double u, double v, double R, double r);
        	double G2(double u, double v, double R, double r);
        	double G3(double u, double v, double R, double r);
		int getBoxSize() const;	
};

istream& operator >> (istream& is, Facet& a);
ostream& operator << (ostream& os, const Facet& a);

#endif
