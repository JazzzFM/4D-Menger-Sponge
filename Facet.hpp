#ifndef FACET_H
#define FACET_H

using namespace std;

#include <iostream>
#include "Quaternion.hpp"
#include <math.h>

class Facet {
       	private:
	 	Quaternion A, B, C, N;

	public:
        	Vector3D  operator [] (int k) const;
        	Facet();
		Facet(const Quaternion& a, const Quaternion& b, const Quaternion& c);
		Facet(const Vector3D& a, const Vector3D& b, const Vector3D& c);
		Facet(const Facet& facet);
		void updateFacet(const Vector3D& a, const Vector3D& b, const Vector3D& c);
		Vector3D getCenter();
		void translate(const Vector3D& a);	
};

istream& operator >> (istream& is, Facet& a);
ostream& operator << (ostream& os, const Facet& a);

#endif
