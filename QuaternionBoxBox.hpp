#ifndef QUATERNIONBOXBOX_H
#define QUATERNIONBOXBOX_H

using namespace std;

#include <iostream>
#include "QuaternionBox.hpp"
#include <math.h>

class QuaternionBoxBox {
       	
	private:
	 	QuaternionBox * V;
		int m;
	
	public:
        	QuaternionBox  operator [] (int k) const;
        	QuaternionBoxBox();
		QuaternionBoxBox(const Quaternion& v);
		QuaternionBoxBox(const Vector3D& v);
		QuaternionBoxBox(double a, double b, double c);
		QuaternionBoxBox(const Vector3D& a, const Vector3D& b, const Vector3D& c);
		
		void push(const Quaternion& v);
		void push(const Vector3D& v);
		void push(const Vector3D& a, const Vector3D& b, const Vector3D& c);

		void push(int i, const Quaternion& v);
		void push(int i, const Vector3D& v);
		void push(int i, double a, double b, double c);	

		void replace(int i, const Quaternion& v);
		void replace(int i, const Vector3D& v);
		void replace(int i, double a, double b, double c);
		void replace(int i, int j, const Quaternion& A);
		void replace(int i, int j, const Vector3D& A);
		void replace(int i, int j, double a, double b, double c);
		int getM() const;
		void empty();
};

ostream& operator << (ostream& os, const QuaternionBoxBox& a);

#endif
