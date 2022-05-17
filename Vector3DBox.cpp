using namespace std;

#include "Vector3DBox.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


Vector3DBox::Vector3DBox() {};
Vector3DBox::Vector3DBox(const Vector3D& v) {
	
	V = (Vector3D *) malloc (1 * sizeof(Vector3D));
	n = 1;
	V[0] = Vector3D(v);

	center = Vector3D(v);

}

Vector3D Vector3DBox::operator [] (int k) const {
   if (k > n-1)
      	return V[0];
   else {
	return V[k];
   }
}

Vector3D Vector3DBox::getCenter() const {return center;}
int Vector3DBox::getN() const {return n;}
void Vector3DBox::updateCenter() {
	
	center = 0.0 * center;
	for (int i = 0; i < n; i++) 
		center = center + V[i];
	
	center = (1.0/((double) n)) * center;

}

void Vector3DBox::push(const Vector3D& v) {

	if (n == 0) {
	
		V[0] = Vector3D(v);
		n = 1;
	} else {
	
		V = (Vector3D *) realloc(V, sizeof(Vector3D) * (n+1));
		n = n + 1;
		V[n-1] = Vector3D(v);
		updateCenter();
	}
}

void Vector3DBox::empty() {
	
	V = (Vector3D *) realloc(V, sizeof(Vector3D) * (1));
        n = 0;
	free(V);
	V = NULL;
}

void Vector3DBox::push(double a, double b, double c) {

        if (n == 0) {

                V[0] = Vector3D(a, b, c);
                n = 1;
        } else {

                V = (Vector3D *) realloc(V, sizeof(Vector3D) * (n+1));
                n = n + 1;
                V[n-1] = Vector3D(a, b, c);
                updateCenter();
        }
}

void Vector3DBox::replace(int i, const Vector3D& A) {
	
	V[i] = Vector3D(A);
	updateCenter();
}

void Vector3DBox::replace(int i, double a, double b, double c) {

        V[i] = Vector3D(a, b, c);
        updateCenter();
}

ostream& operator << (ostream& os, const Vector3DBox& a) {
	
	os << "\nVectorBox data:\n\nCenter := " << a.getCenter() << "\n";
	for (int i = 0; i < a.getN(); i++) {
		os << "[" << a[i] << "]\n";
	}

	return os;
}


