using namespace std;

#include "QuaternionBoxBox.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


QuaternionBoxBox::QuaternionBoxBox() {};
QuaternionBoxBox::QuaternionBoxBox(const Quaternion& v) {
	
	V = (QuaternionBox *) malloc (1 * sizeof(QuaternionBox));
	m = 1;
	V[0] = QuaternionBox(v);

}

QuaternionBoxBox::QuaternionBoxBox(const Vector3D& v) {

        V = (QuaternionBox *) malloc (1 * sizeof(QuaternionBox));
        m = 1;
        V[0] = QuaternionBox(Quaternion(v));

}

QuaternionBoxBox::QuaternionBoxBox(const Vector3D& a, const Vector3D& b, const Vector3D& c) {

        V = (QuaternionBox *) malloc (1 * sizeof(QuaternionBox));
        m = 1;
        V[0] = QuaternionBox(a);
	V[0].push(b);
	V[0].push(c);

}

QuaternionBoxBox::QuaternionBoxBox(double a, double b, double c) {

        V = (QuaternionBox *) malloc (1 * sizeof(QuaternionBox));
        m = 1;
        V[0] = QuaternionBox(Quaternion(0, Vector3D(a, b, c)));

}

QuaternionBox QuaternionBoxBox::operator [] (int k) const {
   if (k > m - 1)
      	return V[0];
   else {
	return V[k];
   }
}

int QuaternionBoxBox::getM() const {return m;}

void QuaternionBoxBox::push(const Quaternion& v) {

	if (m == 0) {
	
		V[0] = QuaternionBox(v);
		m = 1;
	} else {
	
		V = (QuaternionBox *) realloc(V, sizeof(QuaternionBox) * (m+1));
		m = m + 1;
		V[m-1] = QuaternionBox(v);
	}
}

void QuaternionBoxBox::push(const Vector3D& v) {

        if (m == 0) {

                V[0] = QuaternionBox(v);
                m = 1;
        } else {

                V = (QuaternionBox *) realloc(V, sizeof(QuaternionBox) * (m+1));
                m = m + 1;
                V[m-1] = QuaternionBox(v);
        }
}

void QuaternionBoxBox::push(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
	
	if (m == 0) {

                V[0] = QuaternionBox(a);
		V[0].push(b);
		V[0].push(c);
                m = 1;
        } else {

                V = (QuaternionBox *) realloc(V, sizeof(QuaternionBox) * (m+1));
                m = m + 1;
                V[m-1] = QuaternionBox(a);
		V[m-1].push(b);
		V[m-1].push(c);
        }
}

void QuaternionBoxBox::push(int i, const Vector3D& v) {V[i].push(v);}
void QuaternionBoxBox::push(int i, const Quaternion& v) {V[i].push(v);}
void QuaternionBoxBox::push(int i, double a, double b, double c) {V[i].push(a, b, c);}

void QuaternionBoxBox::empty() {
	
	for (int i = 0; i < m; i++)
		V[i].empty();

        m = 0;
	free(V);
	V = NULL;
}

ostream& operator << (ostream& os, const QuaternionBoxBox& a) {
	
	os << "\n\nQuaternionBoxBox data:{ \n\n\n" ;
	for (int i = 0; i < a.getM(); i++) {
		os << "List-->(" << i << ")" << a[i] << "\n\n";
	}

	os << "}\n\n";

	return os;
}


