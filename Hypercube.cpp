using namespace std;

#include "Hypercube.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>



//Facet  operator [] (int k) const;
Hypercube::Hypercube(double R, const Vector4D& c, const Matrix4D& M, double pro) {
	
Vector4D	v0 = Vector4D( R + c.x(), R + c.y(), R + c.z(), R + c.t());
Vector4D	v1 = Vector4D(-R + c.x(), R + c.y(), R + c.z(), R + c.t());
Vector4D	v2 = Vector4D(-R + c.x(),-R + c.y(), R + c.z(), R + c.t());
Vector4D	v3 = Vector4D( R + c.x(),-R + c.y(), R + c.z(), R + c.t());

Vector4D	v4 = Vector4D( R + c.x(), R + c.y(),-R + c.z(), R + c.t());
Vector4D	v5 = Vector4D(-R + c.x(), R + c.y(),-R + c.z(), R + c.t());
Vector4D	v6 = Vector4D(-R + c.x(),-R + c.y(),-R + c.z(), R + c.t());
Vector4D	v7 = Vector4D( R + c.x(),-R + c.y(),-R + c.z(), R + c.t());

Vector4D	v8 =  Vector4D( R + c.x(), R + c.y(), R + c.z(),-R + c.t());
Vector4D	v9 =  Vector4D(-R + c.x(), R + c.y(), R + c.z(),-R + c.t());
Vector4D	v10 = Vector4D(-R + c.x(),-R + c.y(), R + c.z(),-R + c.t());
Vector4D	v11 = Vector4D( R + c.x(),-R + c.y(), R + c.z(),-R + c.t());

Vector4D	v12 = Vector4D( R + c.x(), R + c.y(),-R + c.z(),-R + c.t());
Vector4D	v13 = Vector4D(-R + c.x(), R + c.y(),-R + c.z(),-R + c.t());
Vector4D	v14 = Vector4D(-R + c.x(),-R + c.y(),-R + c.z(),-R + c.t());
Vector4D	v15 = Vector4D( R + c.x(),-R + c.y(),-R + c.z(),-R + c.t());	


         v0 = M * v0;
	 v1 = M * v1;
	 v2 = M * v2;
	 v3 = M * v3;
	 v4 = M * v4;
	 v5 = M * v5;
	 v6 = M * v6;
	 v7 = M * v7;
	 v8 = M * v8;
	 v9 = M * v9;
	 v10 = M * v10;
	 v11 = M * v11;
	 v12 = M * v12;
	 v13 = M * v13;
	 v14 = M * v14;
	 v15 = M * v15;
	 
	 Vector3D G0 = projection3D(v0, pro);
	 Vector3D G1 = projection3D(v1, pro);
	 Vector3D G2 = projection3D(v2, pro);
	 Vector3D G3 = projection3D(v3, pro);
	 Vector3D G4 = projection3D(v4, pro);
	 Vector3D G5 = projection3D(v5, pro);
	 Vector3D G6 = projection3D(v6, pro);
	 Vector3D G7 = projection3D(v7, pro);
	 Vector3D G8 = projection3D(v8, pro);
	 Vector3D G9 = projection3D(v9, pro);
	 Vector3D G10 = projection3D(v10, pro);
	 Vector3D G11 = projection3D(v11, pro);
	 Vector3D G12 = projection3D(v12, pro);
	 Vector3D G13 = projection3D(v13, pro);
	 Vector3D G14 = projection3D(v14, pro);
	 Vector3D G15 = projection3D(v15, pro);

	f[0].push(G8 ,  G9,  G10, G11);
	f[0].push(G11, G10, G14, G15);
	f[0].push(G8 , G11, G15, G12);
	f[0].push(G9 , G13, G14, G10);
	f[0].push(G14, G13, G12, G15);
	f[0].push(G8 , G9,  G13, G12);
	

			f[1].push(G0, G8, G11,  G3); 
                        //f[1].push(G[3], G[11], G[15], G[7]); 
                        f[1].push(G4, G12, G15, G7); 
                        //f[1].push(G[0], G[8], G[12],  G[4]); 
                        //f[1].push(G[8], G[11], G[15],G[12]);
                        f[1].push(G0, G3, G7,   G4); 
                        
			f[2].push(G1, G9, G10,  G2); 
                        //f[2].push(G[2], G[10], G[14], G[6]); 
                        f[2].push(G5, G13, G14, G6); 
                        f[2].push(G1, G9, G13,  G5); 
                        //f[2].push(G[9], G[10], G[14],G[13]);
                        f[2].push(G1, G2, G6,   G5); 
                        
			//f[3].push(G[1], G[9], G[13],  G[5]); 
                        f[3].push(G5, G13, G12, G4); 
                        f[3].push(G4, G12, G8,  G0); 
                        f[3].push(G0, G8, G9,   G1); 
                        //f[3].push(G[8], G[9], G[13], G[12]);
                        f[3].push(G0, G1, G5,   G4); 
                        
			f[4].push(G2, G10, G14, G6); 
                        f[4].push(G6, G14, G15, G7); 
                        f[4].push(G7, G15, G11, G3); 
                        f[4].push(G2, G10, G11, G3); 
                        //f[4].push(G[10], G[11],G[15],G[14]);
                        f[4].push(G2, G6, G7,   G3); 
                        
			//f[5].push(G[5], G[13], G[14], G[6]); 
                        //f[5].push(G[6], G[14], G[15], G[7]); 
                        //f[5].push(G[7], G[15], G[12], G[4]); 
                        //f[5].push(G[4], G[12], G[13], G[5]); 
                        //f[5].push(G[14], G[13],G[12],G[15]);
                        f[5].push(G5, G6, G7,   G4); 
                        
			//f[6].push(G[9], G[8], G[11], G[10]);
                        f[6].push(G1, G2, G3,   G0); 
                        //f[6].push(G[1], G[9], G[10],  G[2]); 
                        //f[6].push(G[2], G[10], G[11], G[3]); 
                        //f[6].push(G[3], G[11], G[8],  G[0]); 
                        //f[6].push(G[0], G[8], G[9],   G[1]); 
                        
			f[7].push(G0, G1, G2,   G3); 
                        f[7].push(G1, G2, G6,   G5); 
                        f[7].push(G6, G5, G4,   G7); 
                        f[7].push(G4, G7, G3,   G0); 
                        f[7].push(G2, G3, G7,   G6); 
                        f[7].push(G0, G1, G5,   G4); 

}


Hypercube::Hypercube() {}

Vector3D Hypercube::projection3D(const Vector4D& vec, double proy) {
	return ((proy)/(proy-vec.t())) * Vector3D(vec.x(), vec.y(), vec.z());
}

FacetBox Hypercube::operator [] (int k) const {
	return f[k];
}

void Hypercube::empty() {
	for (int i = 0; i < 8; i++)
		f[i].empty();
}

//int Hypercube::numFacet() {return f.getN();}
