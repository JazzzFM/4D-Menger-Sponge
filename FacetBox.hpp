#ifndef FACETBOX_H
#define FACETBOX_H

using namespace std;

#include <iostream>
#include "Facet.hpp"
#include <math.h>

class FacetBox {
       	private:
	 	Facet * F;
		int n;
		Vector3D center;
	public:
        	Facet  operator [] (int k) const;
        	FacetBox();
		FacetBox(const Facet& facet);
		Vector3D getCenter() const;
		void updateCenter();
		void push(const Facet& facet);
		void push(const Vector3D& a, const Vector3D& b, const Vector3D& c);
		void pushFacet(const Facet& facet);
		void pushFacet(const Vector3D& A, const Vector3D& B, const Vector3D& C);
		void replaceFacet(int i, const Vector3D& A, const Vector3D& B, const Vector3D& C);
		int getN() const;
		void translate(const Vector3D& t);
		void escFacetBox();
		void empty();

		void push(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d);

};


#endif
