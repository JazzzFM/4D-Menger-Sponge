
using namespace std;

#include "FacetGash.hpp"
#include "FacetBox.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>


FacetGash::FacetGash() {}
FacetGash::FacetGash(const Vector3D& planeH, const Vector3D& planeB) {
	
	//Setting up cut angle with two vectors
	head = Quaternion(0.0, planeH);
	base = Quaternion(0.0, planeB);
	
	//Setting up balde
	blade = PlaneQuaternion(10, head.V(), base.V());
        
	n = 0;
	m = 0;
}


//Update Blade Angle
void FacetGash::updateBlade(const Vector3D& newHead, const Vector3D& newBase) {
	blade = PlaneQuaternion(0, newHead, newBase);
}

//Get Blade data
PlaneQuaternion FacetGash::getBlade() const {return blade;}

//Get Blade Normal
Vector3D FacetGash::getNormal() const {return blade[0];};

//Get Slash Quaternion Coordinates
Vector3D FacetGash::getM(int i, int j) const {return MM[i][j];}

//Auxilary Funstions
int      FacetGash::getN() const {return n;}
int      FacetGash::getM() const {return m;}
double   FacetGash:: getT(int nn) const {return  VV[nn].x();}
double   FacetGash::getT1(int nn) const {return  VV[nn].y();}
double   FacetGash::getT2(int nn) const {return  VV[nn].z();}
Facet    FacetGash::getFacet(int n0) const {return Facets[n0];}
Vector3D FacetGash::getDir(double t) const {return (t*(head.V()-base.V()));}
int 	 FacetGash::checkPoint(const Quaternion& p, const Quaternion& J) {return blade.checkPoint(p, J);}
Vector3D FacetGash::getCutPoint(int i) const {
	
	if (i == 0) return inter0;
	if (i == 1) return inter1;
	if (i == 2) return inter2;
}

//Tell blade to switch orientation
void FacetGash::updateOrientation() {blade.updateOrientation();}

/////////////////////////////////////////////
//
//	
//	MAIN FACET CUTTING ALGORITHM
//
void FacetGash::cutFacet(const Facet& facet0) {

	//We start by copying the facet to be cut
	facet = Facet(facet0[0], facet0[1], facet0[2]);

	//We check if there's an intersection using the sides
	double t  = blade.intersectionLine(facet[0], facet[1]);
	double t1 = blade.intersectionLine(facet[2], facet[1]);
	double t2 = blade.intersectionLine(facet[0], facet[2]);

	//If there's at least one intersection on any of two sides do the following:
	//(*Note we don't care if there's one line intersection so we don't even check)
	if ( (t > -1e-100 && t1 > -1e-100) || (t > -1e-100  && t2 > -1e-100) || (t1 > -1e-100  && t2 > -1e-100)) {
		
		//We calculate the points at intersection with blade and facet
		inter0 = t  * (facet[0] - facet[1]) + facet[1];
		inter1 = t1 * (facet[2] - facet[1]) + facet[1];
		inter2 = t2 * (facet[0] - facet[2]) + facet[2];

		//Checking case for variuos cycles	
		if (n == 0) {
			Facets = FacetBox(facet);
			MM = QuaternionBoxBox(inter0, inter1, inter2);
			VV = Vector3D(t, t1, t2);	
		} else {
		
			Facets.pushFacet(facet);
			MM.push(inter0, inter1, inter2);
			VV.push(t, t1, t2);
		}

		n += 1;
	}

}


//We restart our memory allocation for the next iteration
void FacetGash::restart() {

	Facets.empty();
	MM.empty();
	VV.empty();
	n = 0;
}

//Collecting the two sides of a polytope
void FacetGash::readListC(const Facet& facet, FacetBox * pila) {

	Vector3D A0 = Vector3D(facet[0]);
	Vector3D B0 = Vector3D(facet[1]);
	Vector3D C0 = Vector3D(facet[2]);

	Vector3D J = Vector3D(0, 0, 1);
	Quaternion QJ = Quaternion(0.0, J);
	int aa = checkPoint(A0, QJ);
	int bb = checkPoint(B0, QJ);
	int cc = checkPoint(C0, QJ);

	//Checking which side does the facet belong to
	if (aa == 1 && bb == 1 && cc == 1) {
		pila->pushFacet(facet);
	}
}

int FacetGash::checkFacet(const Facet& facet) {

	Vector3D A0 = Vector3D(facet[0]);
        Vector3D B0 = Vector3D(facet[1]);
        Vector3D C0 = Vector3D(facet[2]);

        Vector3D J = Vector3D(0, 0, 1);
        Quaternion QJ = Quaternion(0.0, J);
        int aa = checkPoint(A0, QJ);
        int bb = checkPoint(B0, QJ);
        int cc = checkPoint(C0, QJ);

	if (aa == 1 && bb == 1 && cc == 1)
		return 1;
	else 
		return 0;
}

void FacetGash::readList(FacetBox * pila) {


	Vector3D center = Vector3D(0, 0, 0);
	int n = 0;

	Vector3D pp;
	if (getT (0) > -1e-100) pp = Vector3D(getM(0, 0));
	if (getT1(0) > -1e-100) pp = Vector3D(getM(0, 1));
	if (getT2(0) > -1e-100) pp = Vector3D(getM(0, 2));;

	//We iterate through the facets that touch the plane
	for (int i = 0; i < getN(); i++) {

		//Check which vertices of the facet are in the correct side of the plane in R3
		Facet facet = Facet(getFacet(i));
		Vector3D A0 = Vector3D(getFacet(i)[0]);
		Vector3D B0 = Vector3D(getFacet(i)[1]);
		Vector3D C0 = Vector3D(getFacet(i)[2]);
		Vector3D J = Vector3D(0, 0, 1);
		Quaternion QJ = Quaternion(0.0, J);
		int aa = checkPoint(A0, QJ);
		int bb = checkPoint(B0, QJ);
       		int cc = checkPoint(C0, QJ);


		if ( getT(i) >-1e-7 && getT1(i) >-1e-7) {

			auxFun(0, 1, aa, bb, cc, i, A0, B0, C0, pila);
			pila->push(getM(i, 0), getM(i, 1), pp);
		}

		if ( getT(i) >-1e-7 && getT2(i) >-1e-7) {

			auxFun(0, 2, aa, bb, cc, i, A0, B0, C0, pila);
			pila->push(getM(i, 0), getM(i, 2), pp);
		}

		if (getT2(i) >-1e-7 && getT1(i) >-1e-7) {

			auxFun(1, 2, aa, bb, cc, i, A0, B0, C0, pila);
			pila->push(getM(i, 1), getM(i, 2), pp);
		}

	}
}


int  FacetGash::linePointIntersection(const Vector3D& r, const Vector3D& a, const Vector3D& b) {

	Vector3D cro = (a-r) % (b-r);
	if (cro == Vector3D(0, 0, 0)) return 1;
	else return 0;
}

void FacetGash::auxFun(int a, int b, int aa, int bb, int cc, int i, const Vector3D& A0, const Vector3D& B0, const Vector3D& C0, FacetBox * pila ) {

	Vector3D r0 = Vector3D(getM(i, a));
	Vector3D r1 = Vector3D(getM(i, b));

	if (aa == 1 && bb == 0 && cc == 0) {
		pila->push(r0, r1, A0);
	}

	if (aa == 0 && bb == 1 && cc == 0) {
		pila->push(r0, r1, B0);
	}

	if (aa == 0 && bb == 0 && cc == 1) {
		pila->push(r0, r1, C0);
	}

	if (aa == 0 && bb == 1 && cc == 1) {
		checkR (r0, r1, A0, B0, C0, pila);
	}

	if (aa == 1 && bb == 0 && cc == 1) {
		checkR (r0, r1, B0, A0, C0, pila);
	}

	if (aa == 1 && bb == 1 && cc == 0) {
		checkR (r0, r1, C0, A0, B0, pila);
	}

}


void FacetGash::checkR (const Vector3D& r0, const Vector3D& r1, const Vector3D& A0, const Vector3D& B0, const Vector3D& C0, FacetBox * pila) {

	int l = linePointIntersection(r0, B0, A0);
	int l0 = linePointIntersection(r0, C0, A0);

	if ( l == 1) {

		pila->push(r0, B0, C0);
		pila->push(C0, r1, r0);
	}

	if ( l0 == 1) {

		pila->push(r1, B0, C0);
		pila->push(C0, r1, r0);
	}
}

QuaternionBoxBox FacetGash::getMM() const {return MM;}
Vector3DBox      FacetGash::getVV() const {return VV;}
FacetBox         FacetGash::getFacets() const {return Facets;}


ostream& operator << (ostream& os, const FacetGash& a) {

        os << "\nFacetGash Data: \n";
	os << a.getFacets();
	os << a.getVV();
	os << a.getMM();
	os << "\n\n\n";
        return os;
}
