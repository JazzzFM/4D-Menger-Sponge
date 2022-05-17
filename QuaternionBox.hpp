#ifndef QUATERNIONBOX_H
#define QUATERNIONBOX_H

using namespace std;

#include <iostream>
#include "Quaternion.hpp"
#include <math.h>

class QuaternionBox {
       	private:
	 	Quaternion * V;
		int n;
		Quaternion center;
	public:
        	Vector3D  operator [] (int k) const;
        	QuaternionBox();
		QuaternionBox(const Quaternion& v);
		QuaternionBox(const Vector3D& v);
		QuaternionBox(double a, double b, double c);
		Vector3D getCenter() const;
		void updateCenter();
		void push(const Quaternion& v);
		void push(const Vector3D& v);
		void push(double a, double b, double c);
		void replace(int i, const Quaternion& A);
		void replace(int i, const Vector3D& A);
		void replace(int i, double a, double b, double c);
		int getN() const;
		void empty();
};

ostream& operator << (ostream& os, const QuaternionBox& a);

#endif
