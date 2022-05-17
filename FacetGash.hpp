#ifndef FACETGASH_H
#define FACETGASH_H

using namespace std;

#include <iostream>
#include "PlaneQuaternion.hpp"
#include "Facet.hpp"
#include "FacetBox.hpp"
#include "Vector3DBox.hpp"
#include "QuaternionBoxBox.hpp"
#include <math.h>

class FacetGash {
       	private:
	 	Quaternion * * M;
		Quaternion head, base;
		PlaneQuaternion blade;
		int n, m;
		Vector3D inter0, inter1, inter2;
		Facet facet;
		Vector3D * V;
		Facet * facets;
		
		
		FacetBox Facets;
		QuaternionBoxBox MM;
		Vector3DBox VV;

	public:
        	Vector3D  operator [] (int k) const;
		FacetGash();
		FacetGash(const Vector3D& planeH, const Vector3D& planeB);
		void updateBlade(const Vector3D& newHead, const Vector3D& newBase);
		PlaneQuaternion getBlade() const;
                Vector3D getNormal () const;
                Vector3D getM(int i, int j) const;
                int getN() const;
                int getM() const;
                double  getT(int nn) const;
                double getT1(int nn) const;
                double getT2(int nn) const;
                Facet getFacet(int n0) const;
                Facet returnFacet(int i) const;
		Vector3D getDir(double t) const;
                int checkPoint(const Quaternion& p, const Quaternion& J);
                Vector3D getCutPoint(int i) const;
		void updateOrientation();
                void cutFacet(const Facet& facet0);
		void restart();
		void readListC(const Facet& facet, FacetBox * pila);
		void readList(FacetBox * pila);
		int  linePointIntersection(const Vector3D& r, const Vector3D& a, const Vector3D& b);
		void auxFun(int a, int b, int aa, int bb, int cc, int i, const Vector3D& A0, const Vector3D& B0, const Vector3D& C0, FacetBox * pila );
		void checkR (const Vector3D& r0, const Vector3D& r1, const Vector3D& A0, const Vector3D& B0, const Vector3D& C0, FacetBox * pila);
		QuaternionBoxBox getMM() const;
		Vector3DBox getVV() const;
		FacetBox getFacets() const;
		void escFacetGash();
		int checkFacet(const Facet& facet);
};

ostream& operator << (ostream& os, const FacetGash& a);

#endif

