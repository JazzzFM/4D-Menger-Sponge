#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

using namespace std;

#include <iostream>
#include "Facet.hpp"
#include <math.h>

class Octahedron {
       	private:
	 	Quaternion A, B, C, D, E, F;
		Facet f[8];
	public:
        	Facet  operator [] (int k) const;
        	Octahedron(double radius, const Vector3D& center);
		Octahedron();
};

istream& operator >> (istream& is, Facet& a);
ostream& operator << (ostream& os, const Facet& a);

#endif
