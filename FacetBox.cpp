using namespace std;

#include "FacetBox.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


FacetBox::FacetBox() {n = 0;};
FacetBox::FacetBox(const Facet& facet) {
	
	F = (Facet *) malloc (1 * sizeof(Facet));
	n = 1;
	F[0] = Facet(facet);

	Vector3D tmp = Vector3D(facet[0] + facet[1] + facet[2]);
	center = Vector3D(0.333333333333333 * tmp);

}

Facet FacetBox::operator [] (int k) const {
   if (k > n-1)
      	return F[0];
   else {
	return F[k];
   }
}

Vector3D FacetBox::getCenter() const {return center;}
int FacetBox::getN() const {return n;}
void FacetBox::updateCenter() {
	
	center = 0.0 * center;
	for (int i = 0; i < getN(); i++) 
		center = center + F[i].getCenter();
	
	center = (1.0/((double) getN())) * center;

}

void FacetBox::push(const Facet& facet) {

	if (n == 0) {
		F = (Facet *) malloc (1 * sizeof(Facet));
		F[0] = Facet(facet[0], facet[1], facet[2]);
                n = 1;
	} else {
		F = (Facet *) realloc(F, sizeof(Facet) * (n+1));
                n = n + 1;
                F[n-1] = Facet(facet[0], facet[1], facet[2]);
                updateCenter();
	}
}

void FacetBox::push(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d) {
	
	if (n == 0) {
                F = (Facet *) malloc (2 * sizeof(Facet));
                F[0] = Facet(a, b, c);
		F[1] = Facet(c, d, a);
                n = 2;

        } else {
                F = (Facet *) realloc(F, sizeof(Facet) * (n+2));
                
		n = n + 1;
                F[n-1] = Facet(a, b, c);

		n = n + 1;
                F[n-1] = Facet(c, d, a);

                updateCenter();
        }

}


void FacetBox::push(const Vector3D& a, const Vector3D& b, const Vector3D& c) {

        if (n == 0) {
                F = (Facet *) malloc (1 * sizeof(Facet));
                F[0] = Facet(a, b, c);
                n = 1;
        } else {
                F = (Facet *) realloc(F, sizeof(Facet) * (n+1));
                n = n + 1;
                F[n-1] = Facet(a, b, c);
                updateCenter();
        }
}

void FacetBox::pushFacet(const Facet& facet) {

	if (n == 0) {
	
		F[0] = Facet(facet[0], facet[1], facet[2]);
		n = 1;
	} else {
	
		F = (Facet *) realloc(F, sizeof(Facet) * (n+1));
		n = n + 1;
		F[n-1] = Facet(facet[0], facet[1], facet[2]);
		updateCenter();
	}
}

void FacetBox::pushFacet(const Vector3D& A, const Vector3D& B, const Vector3D& C) {

	if (n == 0) {
		
		 F[0] = Facet(A, B, C);
		 n = 1;
	} else {
	
		F = (Facet *) realloc(F, sizeof(Facet) * (n+1));
		n = n + 1;
		F[n-1] = Facet(A, B, C);
	}

	updateCenter();

}


void FacetBox::replaceFacet(int i, const Vector3D& A, const Vector3D& B, const Vector3D& C) {
	
	F[i] = Facet(A, B, C);
	updateCenter();
}

ostream& operator << (ostream& os, const FacetBox& a) {

	os << "\n\nFacetBox data:\n";
	for (int i = 0; i < a.getN(); i++)
		os << a[i] << "\n";
	os << "\n";
	return os;
}

void FacetBox::empty() {
	
	if (getN() != 0) {
        	n = 0;
        	free(F);
        	F = NULL;
	}
}

void FacetBox::translate(const Vector3D& t) {
	
	if (n != 0)
		for (int i = 0; i < n; i++)
			F[i].translate(t);

}
