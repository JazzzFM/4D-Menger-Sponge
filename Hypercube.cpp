using namespace std;

#include "Hypercube.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>



//Facet  operator [] (int k) const;
Hypercube::Hypercube(double R, const Vector4D& c, const Matrix4D& M, double pro) {

	v[0] = Vector4D( R + c.x(), R + c.y(), R + c.z(), R + c.t());
	v[1] = Vector4D(-R + c.x(), R + c.y(), R + c.z(), R + c.t());
	v[2] = Vector4D(-R + c.x(),-R + c.y(), R + c.z(), R + c.t());
	v[3] = Vector4D( R + c.x(),-R + c.y(), R + c.z(), R + c.t());

	v[4] = Vector4D( R + c.x(), R + c.y(),-R + c.z(), R + c.t());
	v[5] = Vector4D(-R + c.x(), R + c.y(),-R + c.z(), R + c.t());
	v[6] = Vector4D(-R + c.x(),-R + c.y(),-R + c.z(), R + c.t());
	v[7] = Vector4D( R + c.x(),-R + c.y(),-R + c.z(), R + c.t());

	v[8] =  Vector4D( R + c.x(), R + c.y(), R + c.z(),-R + c.t());
	v[9] =  Vector4D(-R + c.x(), R + c.y(), R + c.z(),-R + c.t());
	v[10] = Vector4D(-R + c.x(),-R + c.y(), R + c.z(),-R + c.t());
	v[11] = Vector4D( R + c.x(),-R + c.y(), R + c.z(),-R + c.t());

	v[12] = Vector4D( R + c.x(), R + c.y(),-R + c.z(),-R + c.t());
	v[13] = Vector4D(-R + c.x(), R + c.y(),-R + c.z(),-R + c.t());
	v[14] = Vector4D(-R + c.x(),-R + c.y(),-R + c.z(),-R + c.t());
	v[15] = Vector4D( R + c.x(),-R + c.y(),-R + c.z(),-R + c.t());	

        for (int i = 0; i < 16; i++) {

         	v[i] = M * v[i];
                G[i] = projection3D(v[i], pro);
        }	

	f[0].push(G[8],  G[9],  G[10], G[11]);
	f[0].push(G[11], G[10], G[14], G[15]);
	f[0].push(G[8],  G[11], G[15], G[12]);
	f[0].push(G[9],  G[13], G[14], G[10]);
	f[0].push(G[14], G[13], G[12], G[15]);
	f[0].push(G[8],  G[9],  G[13], G[12]);
	

			f[1].push(G[0], G[8], G[11],  G[3]); 
                        //f[1].push(G[3], G[11], G[15], G[7]); 
                        f[1].push(G[4], G[12], G[15], G[7]); 
                        //f[1].push(G[0], G[8], G[12],  G[4]); 
                        //f[1].push(G[8], G[11], G[15],G[12]);
                        f[1].push(G[0], G[3], G[7],   G[4]); 
                        
			f[2].push(G[1], G[9], G[10],  G[2]); 
                        //f[2].push(G[2], G[10], G[14], G[6]); 
                        f[2].push(G[5], G[13], G[14], G[6]); 
                        f[2].push(G[1], G[9], G[13],  G[5]); 
                        //f[2].push(G[9], G[10], G[14],G[13]);
                        f[2].push(G[1], G[2], G[6],   G[5]); 
                        
			//f[3].push(G[1], G[9], G[13],  G[5]); 
                        f[3].push(G[5], G[13], G[12], G[4]); 
                        f[3].push(G[4], G[12], G[8],  G[0]); 
                        f[3].push(G[0], G[8], G[9],   G[1]); 
                        //f[3].push(G[8], G[9], G[13], G[12]);
                        f[3].push(G[0], G[1], G[5],   G[4]); 
                        
			f[4].push(G[2], G[10], G[14], G[6]); 
                        f[4].push(G[6], G[14], G[15], G[7]); 
                        f[4].push(G[7], G[15], G[11], G[3]); 
                        f[4].push(G[2], G[10], G[11], G[3]); 
                        //f[4].push(G[10], G[11],G[15],G[14]);
                        f[4].push(G[2], G[6], G[7],   G[3]); 
                        
			//f[5].push(G[5], G[13], G[14], G[6]); 
                        //f[5].push(G[6], G[14], G[15], G[7]); 
                        //f[5].push(G[7], G[15], G[12], G[4]); 
                        //f[5].push(G[4], G[12], G[13], G[5]); 
                        //f[5].push(G[14], G[13],G[12],G[15]);
                        f[5].push(G[5], G[6], G[7],   G[4]); 
                        
			//f[6].push(G[9], G[8], G[11], G[10]);
                        f[6].push(G[1], G[2], G[3],   G[0]); 
                        //f[6].push(G[1], G[9], G[10],  G[2]); 
                        //f[6].push(G[2], G[10], G[11], G[3]); 
                        //f[6].push(G[3], G[11], G[8],  G[0]); 
                        //f[6].push(G[0], G[8], G[9],   G[1]); 
                        
			f[7].push(G[0], G[1], G[2],   G[3]); 
                        f[7].push(G[1], G[2], G[6],   G[5]); 
                        f[7].push(G[6], G[5], G[4],   G[7]); 
                        f[7].push(G[4], G[7], G[3],   G[0]); 
                        f[7].push(G[2], G[3], G[7],   G[6]); 
                        f[7].push(G[0], G[1], G[5],   G[4]); 

}


Hypercube::Hypercube() {}

Vector3D Hypercube::projection3D(const Vector4D& vec, double proy) {
	return ((proy)/(proy-vec.t())) * Vector3D(vec.x(), vec.y(), vec.z());
}

FacetBox Hypercube::operator [] (int k) const {
	return f[k];
}

//int Hypercube::numFacet() {return f.getN();}
