#ifndef HYPERCUBE_H
#define HYPERCUBE_H

using namespace std;

#include <iostream>
#include "Facet.hpp"
#include "FacetBox.hpp"
#include "Vector4D.hpp"
#include "Matrix4D.hpp"
#include <math.h>

class Hypercube {
       	private:
	 	Vector4D v[16];
		Vector3D G[16];
		FacetBox f[8];
	public:
        	FacetBox  operator [] (int k) const;
        	Hypercube(double radius, const Vector4D& center, const Matrix4D& M, double pro);
		Hypercube();
		Vector3D projection3D(const Vector4D& vec, double proy);
		int numFacet();
};

ostream& operator << (ostream& os, const Facet& a);

#endif
