#ifndef VECTOR3DBOX_H
#define VECTOR3DBOX_H

using namespace std;

#include <iostream>
#include "Vector3D.hpp"
#include <math.h>

class Vector3DBox {
       	private:
	 	Vector3D * V;
		int n;
		Vector3D center;
	public:
        	Vector3D  operator [] (int k) const;
        	Vector3DBox();
		Vector3DBox(const Vector3D& v);
		Vector3DBox(double a, double b, double c);
		Vector3D getCenter() const;
		void updateCenter();
		void push(const Vector3D& v);
		void push(double a, double b, double c);
		void replace(int i, const Vector3D& A);
		void replace(int i, double a, double b, double c);
		int getN() const;
		void empty();
};

ostream& operator << (ostream& os, const Vector3DBox& a);

#endif
