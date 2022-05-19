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
		FacetBox f[8];
	public:
        	FacetBox  operator [] (int k) const;
        	~Hypercube(){empty();};
		Hypercube(double radius, const Vector4D& center, const Matrix4D& M, double pro);
		Hypercube();
		Vector3D projection3D(const Vector4D& vec, double proy);
		int numFacet();
		void empty();
};

ostream& operator << (ostream& os, const Facet& a);

#endif
