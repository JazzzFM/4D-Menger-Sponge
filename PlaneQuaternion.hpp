#ifndef PLANE_H
#define PLANE_H

using namespace std;

#include <iostream>
#include "Quaternion.hpp"
#include <math.h>

class PlaneQuaternion {
       	private:
	 	Quaternion normal;
		Vector3D point[4], base;
		int m;
	public:
        	Vector3D  operator [] (int k) const;
        	PlaneQuaternion();
		PlaneQuaternion(int m, const Vector3D& a, const Vector3D& b);
		int  linePointIntersection(const Vector3D& r, const Vector3D& a, const Vector3D& b);
		void identiyFrame(const Quaternion& q);
		int checkPoint(const Quaternion& p, const Quaternion& J);
		//Calculates whether a line intersects the plane
		double intersectionLine(const Vector3D& a, const Vector3D& b);
		int equalR(double a, double b);
		void updateOrientation();
};


#endif
