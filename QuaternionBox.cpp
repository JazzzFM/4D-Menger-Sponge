using namespace std;

#include "QuaternionBox.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


QuaternionBox::QuaternionBox() {};
QuaternionBox::QuaternionBox(const Quaternion& v) {
	
	V = (Quaternion *) malloc (1 * sizeof(Quaternion));
	n = 1;
	V[0] = Quaternion(v);

	center = Quaternion(v);

}

QuaternionBox::QuaternionBox(const Vector3D& v) {

        V = (Quaternion *) malloc (1 * sizeof(Quaternion));
        n = 1;
        V[0] = Quaternion(0, v);

        center = Quaternion(0, v);

}

Vector3D QuaternionBox::operator [] (int k) const {
   if (k > n-1)
      	return V[0].V();
   else {
	return V[k].V();
   }
}

Vector3D QuaternionBox::getCenter() const {return center.V();}
int QuaternionBox::getN() const {return n;}
void QuaternionBox::updateCenter() {
	
	center = 0.0 * center;
	for (int i = 0; i < n; i++) 
		center = center + V[i];
	
	center = (1.0/((double) n)) * center;

}

void QuaternionBox::push(const Quaternion& v) {

	if (n == 0) {
	
		V[0] = Quaternion(v);
		n = 1;
	} else {
	
		V = (Quaternion *) realloc(V, sizeof(Quaternion) * (n+1));
		n = n + 1;
		V[n-1] = Quaternion(v);
		updateCenter();
	}
}

void QuaternionBox::push(const Vector3D& v) {

        if (n == 0) {

                V[0] = Quaternion(0, v);
                n = 1;
        } else {

                V = (Quaternion *) realloc(V, sizeof(Quaternion) * (n+1));
                n = n + 1;
                V[n-1] = Quaternion(0, v);
                updateCenter();
        }
}

void QuaternionBox::empty() {
	
        n = 0;
	free(V);
	V = NULL;
}

void QuaternionBox::push(double a, double b, double c) {

        if (n == 0) {

                V[0] = Quaternion(0, Vector3D(a, b, c));
                n = 1;
        } else {

                V = (Quaternion *) realloc(V, sizeof(Quaternion) * (n+1));
                n = n + 1;
                V[n-1] = Quaternion(0, Vector3D(a, b, c));
                updateCenter();
        }
}

void QuaternionBox::replace(int i, const Quaternion& A) {

        V[i] = Quaternion(A);
        updateCenter();
}

void QuaternionBox::replace(int i, const Vector3D& A) {
	
	V[i] = Quaternion(0, A);
	updateCenter();
}

void QuaternionBox::replace(int i, double a, double b, double c) {

        V[i] = Quaternion(0, Vector3D(a, b, c));
        updateCenter();
}

ostream& operator << (ostream& os, const QuaternionBox& a) {
	
	os << "\nCenter := " << a.getCenter() << "\n";
	for (int i = 0; i < a.getN(); i++) {
		os << "[" << a[i] << "]\n";
	}

	return os;
}


