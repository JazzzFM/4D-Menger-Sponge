using namespace std;

#include "Dodecahedron.hpp"
#include "Quaternion.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>



Dodecahedron::Dodecahedron(double r, const Vector3D& center) {
	
	double gold= (1 + sqrt(5))/2;
	double g1= 1/gold;
	double g2= 1/(gold*gold);
                        
	v[0] =  Quaternion(0.0, Vector3D( center.x() +  g2 * r,  center.y() + 0.0 * r, center.z() +  1.0 * r));
	v[1] =  Quaternion(0.0, Vector3D( center.x() -  g2 * r,  center.y() + 0.0 * r, center.z() +  1.0 * r));
	v[2] =  Quaternion(0.0, Vector3D( center.x() -  g1 * r,  center.y() +  g1 * r, center.z() +   g1 * r));
	v[3] =  Quaternion(0.0, Vector3D( center.x() +  0.0 * r, center.y() + 1.0 * r, center.z() +   g2 * r));
	v[4] =  Quaternion(0.0, Vector3D( center.x() +   g1 * r, center.y() +  g1 * r, center.z() +   g1 * r));
	v[5] =  Quaternion(0.0, Vector3D( center.x() +  0.0 * r, center.y() - 1.0 * r, center.z() +   g2 * r));
	v[6] =  Quaternion(0.0, Vector3D( center.x() +   g1 * r, center.y() -  g1 * r, center.z() +   g1 * r));
	v[7] =  Quaternion(0.0, Vector3D( center.x() -   g1 * r, center.y() -  g1 * r, center.z() +   g1 * r));
	v[8] =  Quaternion(0.0, Vector3D( center.x() +   g2 * r, center.y() + 0.0 * r, center.z() -  1.0 * r));
	v[9] =  Quaternion(0.0, Vector3D( center.x() -   g2 * r, center.y() + 0.0 * r, center.z() -  1.0 * r));
	v[10] = Quaternion(0.0, Vector3D( center.x() -   g1 * r, center.y() -  g1 * r, center.z() -   g1 * r));
	v[11] = Quaternion(0.0, Vector3D( center.x() +  0.0 * r, center.y() - 1.0 * r, center.z() -   g2 * r));
	v[12] = Quaternion(0.0, Vector3D( center.x() +   g1 * r, center.y() -  g1 * r, center.z() -   g1 * r));
	v[13] = Quaternion(0.0, Vector3D( center.x() +   g1 * r, center.y() +  g1 * r, center.z() -   g1 * r));
	v[14] = Quaternion(0.0, Vector3D( center.x() +  0.0 * r, center.y() + 1.0 * r, center.z() -   g2 * r));
	v[15] = Quaternion(0.0, Vector3D( center.x() -   g1 * r, center.y() +  g1 * r, center.z() -   g1 * r));
	v[16] = Quaternion(0.0, Vector3D( center.x() +  1.0 * r, center.y() -  g2 * r, center.z() +  0.0 * r));
	v[17] = Quaternion(0.0, Vector3D( center.x() -  1.0 * r, center.y() +  g2 * r, center.z() +  0.0 * r));
	v[18] = Quaternion(0.0, Vector3D( center.x() -  1.0 * r, center.y() -  g2 * r, center.z() +  0.0 * r));
	v[19] = Quaternion(0.0, Vector3D( center.x() +  1.0 * r, center.y() +  g2 * r, center.z() +  0.0 * r));

}

Dodecahedron::Dodecahedron() {}

Facet Dodecahedron::operator [] (int k) const {
   if (k > 35)
      return Facet();
   else {
   
	if (k == 0) return Facet(v[19], v[14], v[3 ]);
	if (k == 1) return Facet(v[19], v[13], v[14]);
	if (k == 2) return Facet(v[19], v[ 4], v[ 3]);

	if (k == 3) return Facet(v[19], v[13], v[8 ]);
	if (k == 4) return Facet(v[19], v[8 ], v[12]);
	if (k == 5) return Facet(v[19], v[12], v[16]);

	if (k == 6) return Facet(v[4 ], v[19], v[16]);
	if (k == 7) return Facet(v[16], v[0 ], v[4 ]);
	if (k == 8) return Facet(v[0 ], v[16], v[6 ]);

	if (k == 9) return Facet(v[0 ], v[2 ], v[3 ]);
	if (k ==10) return Facet(v[0 ], v[1 ], v[2 ]);
	if (k ==11) return Facet(v[0 ], v[3 ], v[4 ]);

	if (k ==12) return Facet(v[2 ], v[17], v[15]);
	if (k ==13) return Facet(v[2 ], v[15], v[14]);
	if (k ==14) return Facet(v[2 ], v[14], v[3 ]);

	if (k ==15) return Facet(v[8 ], v[13], v[14]);
	if (k ==16) return Facet(v[8 ], v[14], v[15]);
	if (k ==17) return Facet(v[8 ], v[15], v[9 ]);

	if (k ==18) return Facet(v[ 5], v[6 ], v[12]);
	if (k ==19) return Facet(v[11], v[5 ], v[12]);
	if (k ==20) return Facet(v[ 6], v[16], v[12]);

	if (k ==21 ) return Facet(v[8  ],  v[9 ], v[12]);
	if (k ==22 ) return Facet(v[9  ],  v[10], v[12]);
	if (k ==23 ) return Facet(v[10 ],  v[11], v[12]);

	if (k ==24 ) return Facet(v[9  ],  v[15], v[10]);
	if (k ==25 ) return Facet(v[15 ],  v[17], v[10]);
	if (k ==26 ) return Facet(v[17 ],  v[18], v[10]);

	if (k ==27 ) return Facet(v[18 ],  v[ 7], v[10]);
	if (k ==28 ) return Facet(v[7  ],  v[ 5], v[10]);
	if (k ==29 ) return Facet(v[5  ],  v[11], v[10]);

	if (k ==30 ) return Facet(v[18 ],  v[17], v[2 ]);
	if (k ==31 ) return Facet(v[7  ],  v[18], v[2 ]);
	if (k ==32 ) return Facet(v[1  ],  v[7 ], v[2 ]);

	if (k ==33 ) return Facet(v[0  ],  v[7 ], v[1 ]);
	if (k ==34 ) return Facet(v[0  ],  v[5 ], v[7 ]);
	if (k ==35 ) return Facet(v[0  ],  v[6 ], v[5 ]);


   }
}

Torus::Torus(double R, double r, const Vector3D& c, int N) {
	
	n = 20;
	double PI = 3.14159265358979;
	double dx = (2 * PI) / ((double) n);
	double dy = (2 * PI) / ((double) n);

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) {
			
			double u1 = (i * dx);
			double v1 = (j * dy);

			double u2 = (i * dx) + dx;
			double v2 = (j * dy);

			double u3 = (i * dx) + dx;
			double v3 = (j * dy) + dy;

			double u4 = (i * dx);
			double v4 = (j * dy) + dy;
			
			Vector3D a1 = Vector3D(G1(u1, v1, R, r), G2(u1, v1, R, r), G3(u1, v1, R, r));
			Vector3D a2 = Vector3D(G1(u2, v2, R, r), G2(u2, v2, R, r), G3(u2, v2, R, r));
			Vector3D a3 = Vector3D(G1(u3, v3, R, r), G2(u3, v3, R, r), G3(u3, v3, R, r));
			Vector3D a4 = Vector3D(G1(u4, v4, R, r), G2(u4, v4, R, r), G3(u4, v4, R, r));

			f.push(Facet(a1, a2, a3));
			f.push(Facet(a3, a4, a1));			

		}
		
		cout << "\n\n Torus Box size " << f.getN() << endl;	

}

double Torus::G1(double u, double v, double R, double r) {
	double g = ( R + (r*cos(v)) ) * cos(u);
	return g;
}

double Torus::G2(double u, double v, double R, double r){

	double g = ( R + (r*cos(v)) ) * sin(u);
	return g;
}

double Torus::G3(double u, double v, double R, double r) {
                  
	double g = r * sin(v);
	return g;
}

int Torus::getN() const {return n;}


Facet  Torus::operator [] (int k) const {
	return f[k];
}

int Torus::getBoxSize() const {return f.getN();}



