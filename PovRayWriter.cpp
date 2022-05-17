#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "Vector3D.hpp"
#include "Vector4D.hpp"
#include "Matrix3D.hpp"
#include "Matrix4D.hpp"
#include <bits/stdc++.h>
#include <string>
#include "Quaternion.hpp"
#include "Facet.hpp"

using namespace std;


class GreatCircle {

	private:
		Vector3D r[30];
		double R;
		Vector3D center;
		Vector3D axe;
		double angle;
		double theta;
		int m;
	public:
		GreatCircle(){};
		GreatCircle(int m, double R, const Quaternion& center, const Vector3D& axe, double angle, double theta) {
			
			this->m = m;	
			this->R = R;
			this->center = center.V();;
			this->axe = axe;
			this->angle = angle;
			this->theta = theta;

			double interval = (2 * 3.14159265358979)/m;
			Quaternion spin = Qan(angle, axe);

			for (int i = 0; i < m; i += 2) {
				
				double u0 = i * interval;
				double u1 = (i + 1) * interval;

				r[i] = Vector3D(  R * cos(u0) * sin(theta), R * cos(theta), R * sin(u0) * sin(theta));
				r[i+1] = Vector3D(R * cos(u1) * sin(theta), R * cos(theta), R * sin(u1) * sin(theta));

				Quaternion r0 = Quaternion(0, r[i]);
				Quaternion r1 = Quaternion(0, r[i+1]);

				r0 = spin.conjugate() * r0 * spin;
				r1 = spin.conjugate() * r1 * spin;

				r[i] = r0.V();
				r[i+1] = r1.V();	
			}
		}

		int equalR(double a, double b) {

		        int epsilon = 1e-20;
		        double cc = (a - b) * (a - b);
		
		        if (sqrt(cc) < epsilon)
		                return 1;
		        else
		                return 0;
		}
		
		GreatCircle(int m, double R, const Quaternion& center, const Vector3D& axe, double angle, double theta, int q) {

                        this->m = m;
                        this->R = R;
                        this->center = center.V();;
                        this->axe = axe;
                        this->angle = angle;

			Vector3D D = axe;
                	double longitud = abs(D);
                	double X = D.x();
                	double Y = D.z();
                	double Z = D.y();

                	if (equalR(X, 0.0) == 1) X = 0.00001;

                	double YDX = Y/X;

                	double anglePhi = atan(YDX);
                	double angleTheta = acos(Z/longitud);

                if (X < 0.0) anglePhi += 3.14159265358979;

                        double interval = (2 * 3.14159265358979)/m;
                        Quaternion spinI = Qan(angleTheta, Vector3D(0, 0, 1));
			Quaternion spinJ = Qan(anglePhi, Vector3D(0, 1, 0));

                        for (int i = 0; i < m; i += 2) {

                                double u0 = i * interval;
                                double u1 = (i + 1) * interval;

                                r[i] = Vector3D(  R * cos(u0) * sin(theta), R * cos(theta), R * sin(u0) * sin(theta));
                                r[i+1] = Vector3D(R * cos(u1) * sin(theta), R * cos(theta), R * sin(u1) * sin(theta));

                                Quaternion r0 = Quaternion(0, r[i]);
                                Quaternion r1 = Quaternion(0, r[i+1]);

                                r0 = spinI.conjugate() * r0 * spinI;
                                r1 = spinI.conjugate() * r1 * spinI;
				
				r0 = spinJ.conjugate() * r0 * spinJ;
                                r1 = spinJ.conjugate() * r1 * spinJ;

                                r[i] = r0.V();
                                r[i+1] = r1.V();
                        }
                }

		/*
		 Vector3D D = a - d;
                double longitud = abs(D);
                double X = D.x();
                double Y = D.z();
                double Z = D.y();

                if (equalRealS(X, 0.0) == 1) X = 0.00001;

                double YDX = Y/X;

                double anglePhi = atan(YDX);
                double angleTheta = acos(Z/longitud);

                if (X < 0.0) anglePhi += 3.14159265358979;
		 * */

		int getM() const {
			return m;
		}

		Vector3D getR(int n) const {
			return r[n];
		}

		Vector3D getAxe() const {
			return axe;
		}

		void updateRotation(double newAngle, const Vector3D& newAxe) {
			

			this->angle = newAngle;
			this->axe = newAxe;
			
			Quaternion spin = Qan(angle, axe);

			for (int i = 0; i < m; i += 2) {

                                Quaternion r0 = Quaternion(0, r[i]);
                                Quaternion r1 = Quaternion(0, r[i+1]);

                                r0 = spin.conjugate() * r0 * spin;
                                r1 = spin.conjugate() * r1 * spin;

                                r[i] = r0.V();
                                r[i+1] = r1.V();
                        }
		}
		
		void updateRotation2(double newAngle, const Vector3D& newAxe) {


                        Quaternion spin = Qan(newAngle, newAxe);

                        for (int i = 0; i < m; i += 2) {

                                Quaternion r0 = Quaternion(0, r[i]);
                                Quaternion r1 = Quaternion(0, r[i+1]);

                                r0 = spin.conjugate().conjugate() * r0 * spin.conjugate();
                                r1 = spin.conjugate().conjugate() * r1 * spin.conjugate();

                                r[i] = r0.V();
                                r[i+1] = r1.V();
                        }
                }

		void updateTheta(double newTheta, double up) {
			
			this->theta = newTheta;

                        Vector3D D = axe;
                        double longitud = abs(D);
                        double X = D.x();
                        double Y = D.z();
                        double Z = D.y();

                        if (equalR(X, 0.0) == 1) X = 0.00001;

                        double YDX = Y/X;

                        double anglePhi = atan(YDX);
                        double angleTheta = acos(Z/longitud);

                if (X < 0.0) anglePhi += 3.14159265358979;

                        double interval = (2 * 3.14159265358979)/m;
                        Quaternion spinI = Qan(angleTheta, Vector3D(0, 0, 1));
                        Quaternion spinJ = Qan(anglePhi, Vector3D(0, 1, 0));

                        for (int i = 0; i < m; i += 2) {

                                double u0 = i * interval;
                                double u1 = (i + 1) * interval;

                                r[i] = Vector3D(  R * cos(u0) * sin(theta), R * cos(theta) + up, R * sin(u0) * sin(theta));
                                r[i+1] = Vector3D(R * cos(u1) * sin(theta), R * cos(theta) + up, R * sin(u1) * sin(theta));

                                Quaternion r0 = Quaternion(0, r[i]);
                                Quaternion r1 = Quaternion(0, r[i+1]);

                                r0 = spinI.conjugate() * r0 * spinI;
                                r1 = spinI.conjugate() * r1 * spinI;

                                r0 = spinJ.conjugate() * r0 * spinJ;
                                r1 = spinJ.conjugate() * r1 * spinJ;

                                r[i] = r0.V();
                                r[i+1] = r1.V();
                        }
                }

};


class Branch{
	private:
		Vector3D position;
		Vector3D parent;
		Vector3D dir;
		int null;
		int count;
	public:

		Branch(){null = 0; count = 0;}
		Branch(const Vector3D& parent, const Vector3D& pos, const Vector3D& direction) {
			
			this->position = Vector3D(pos);
			this->parent = Vector3D(parent);
			this->dir = Vector3D(direction);
			null = 1;
			count = 0;
		}

		Branch(const Branch& oldBranch) {
			
			this->position = Vector3D(oldBranch.getPosition());
			this->parent = Vector3D(oldBranch.getParent());
			this->dir = Vector3D(oldBranch.getDirection());
			this->null = oldBranch.getNull();
			this->count = oldBranch.getCount();
		}

		Vector3D getPosition() const {return position;}
		Vector3D getParent() const {return parent;}
		Vector3D getDirection() const {return dir;}
		void updateDirection(double s) {dir = s * dir;}
		void escBranch() {
			cout << "\n parent := " << parent;
			cout << "\n position := " << position;
			cout << "\n direction := " << dir;
			cout << "\n null := " << null;
			cout << "\n count := " << count << endl << endl;
		}

		int getNull() const {return null;}
		int getCount() const {return count;}
		void addCount() {count++;}
		void addDir(const Vector3D& v) {
			dir = dir + v;
		}

		Branch nextBranch() {
			
			Vector3D nextPos = position + dir;
			return Branch(position, nextPos, dir);
		}

		void resetBranch() {
			this->count = 0;
		}
};

class TruncatedCube {

        private:
                Vector3D Center;
                double radio;
                Vector3D data[8];
                int edges[12][2];
        public:
                TruncatedCube() {};
                TruncatedCube(const Vector3D& Center, double radio) {

                        cout << "\n\nRendering truncated cube\n\n";
                        this->Center = Vector3D(Center);
                        this->radio = radio;

                        cout << "       center := " << this->Center << "\n";
                        cout << "       radius := " << this->radio << "\n";

                        data[0] = Vector3D( 1, 1, 1); //Top floor
                        data[1] = Vector3D(-1, 1, 1);
                        data[2] = Vector3D(-1,-1, 1);
                        data[3] = Vector3D( 1,-1, 1);

                        data[4] = Vector3D( 1, 1,-1); //bottom floor
                        data[5] = Vector3D(-1, 1,-1);
                        data[6] = Vector3D(-1,-1,-1);
                        data[7] = Vector3D( 1,-1,-1);

                        edges[0][0] = 0;        edges[0][1] = 1;
                        edges[1][0] = 1;        edges[1][1] = 2;
                        edges[2][0] = 2;        edges[2][1] = 3;
                        edges[3][0] = 3;        edges[3][1] = 0;
                        edges[4][0] = 0;        edges[4][1] = 4;
                        edges[5][0] = 1;        edges[5][1] = 5;
                        edges[6][0] = 2;        edges[6][1] = 6;

                        edges[7][0] = 3;        edges[7][1] = 7;
                        edges[8][0] = 4;        edges[8][1] = 5;
                        edges[9][0] = 5;        edges[9][1] = 6;
                        edges[10][0] = 6;        edges[10][1] = 7;
                        edges[11][0] = 7;        edges[11][1] = 4;

                };

                int getEdge(int i, int p) {

                        int ret;
                        if (p == 0) ret = edges[i][0];
                        else
                                ret = edges[i][1];

                        return ret;
                }

                Vector3D getData(int i) const{

                        return data[i];
                }

};

class Tree {
	
	private:
		Vector3D leaf[500];
		int numLeaf;
		Branch branches[10000];
		int currentBranch;
		Vector3D root;
		int numRoot;
		double max_dist;
		double min_dist;
		int leafOn[500];
	
	public:
		Tree(Vector3D attractor[], const Vector3D& Root, double maxD, double minD, int Nleafs) {
			
			root = Vector3D(Root.x(), Root.y(), Root.z());
			max_dist = maxD;
			min_dist = minD;
			cout << "\n\n			Space Colonizing Tree 123\n\n";


// _____                ____       _   _   _       
//|_   _| __ ___  ___  / ___|  ___| |_| | | |_ __  
//  | || '__/ _ \/ _ \ \___ \ / _ \ __| | | | '_ \ 
//  | || | |  __/  __/  ___) |  __/ |_| |_| | |_) |
//  |_||_|  \___|\___| |____/ \___|\__|\___/| .__/ 
//                                          |_|   
//
			//STEP 1: fill leafs
			numLeaf = Nleafs;
			Vector3D centerOfMass = Vector3D(0.0, 0.0, 0.0);
			for (int i = 0; i < numLeaf; i++) {
				Vector3D temp = Vector3D(attractor[i].x(), attractor[i].y(), attractor[i].z());
				leaf[i] = Vector3D(temp);
				centerOfMass += leaf[i];
			}
			centerOfMass = (1.0/((double) numLeaf)) * centerOfMass;	
			//STEP 2: define first branch
			Vector3D up = unit(Vector3D(0.0, 1.0, 0.0));//unit(centerOfMass);
			up = 0.1 * up;
                	Vector3D pos = Vector3D(Root.x(), Root.y() + 0.01, Root.z());
                	branches[0] = Branch(Root, pos, up);
                	branches[0].escBranch();
			currentBranch = 0;
			//STEP 3: Setup the root of the Tree
			setRoot();

			
			
			
			max_dist = 0.6;			
			cout << "\n\n-->Grow branches" << endl;
                        for (int i = 0; i < numLeaf; i++)
                                leafOn[i] = 0;

                        int cccount = 0;
			int J;
                        while (cccount < 100 ) {
                                cout << "\n Cycle := " << cccount;
                        for (int i = 0; i < numLeaf; i++) {
                                if (leafOn[i] == 0) {
                                //cout << "\n leaf["<< i << "] is off " << leafOn[i];           
                                Branch closestBranch = Branch();
                                Vector3D hojita = Vector3D(leaf[i]);
				//cout << "\n hojita := " << hojita;
                                double record = max_dist;
				//cout << "\n record :=" << record << "	currentBranch := " << currentBranch;
                                for (int j = 0; j < currentBranch; j++) {

                                        double d = abs(hojita - branches[j].getPosition());
					//cout << "\n d := " << d << "	min_dist := " << min_dist << "	record := " << record;
                                        if (d < min_dist) {
                                                leafOn[i] = 1;
                                                j += 1000000;
                                                //cout << "\n-->Case d < min_dist";
                                        } else {
                                                if (d < record) {
                                                        closestBranch = Branch(branches[j]);
							Vector3D newDir = hojita - branches[j].getPosition();
                                        		newDir = unit(newDir);
							newDir = 0.1 * newDir;
                                        		branches[j].addDir(newDir);
                                        		branches[j].addCount();
                                                        record = d;
							//branches[j].addCount();
                                                }
                                        }
                                }//branch iteration done

                        }

                        }//leaf iteration done

                        int numBranches = currentBranch;
                        for (int i = 0; i < numBranches; i++) {
                                Branch branch = Branch(branches[i]);
				cout << "\n branch count := " << branch.getCount();
                                if (branch.getCount() > 0) {
					branch.updateDirection(1.0/(double)(branch.getCount()+1));

					if (currentBranch < 960*10){
						branches[currentBranch + 1] = branch.nextBranch();
                                        	currentBranch += 1;
                                        	cout << "\n-->Added new Branch--------------" << currentBranch;
					}else{break;}
                                	
				}

                                branch.resetBranch();

                        }

                                cccount += 1;
				if (currentBranch > 960*10) break;
                        }//while done  
			



			
		}


		Vector3D getLeaf(int i) const {return leaf[i];}
		int getNumLeaf() const {return numLeaf;}
		Vector3D getRoot() const {return root;}
		int getCurrentBranch() const {return currentBranch;}
		Branch getBranch(int i) const {return branches[i];}
		void setRoot() {
			
			int found = 0;
			int ret = -1;
			cout << "\n-->Root Set up";
			cout << "\n-->Current branch := " << currentBranch;
			cout << "\n-->Found new branch? " << found << endl;
			
			while (found != 1) {
				Vector3D current = Vector3D(branches[currentBranch].getPosition());
				for (int i = 0; i < numLeaf; i++) {
					double d = abs(current - leaf[i]);
					//cout << "\n d := " << d;
					if (d < max_dist) {
						found = 1;
						cout << "\nFound a leaf near enough! found :=" << found; 
					}
				}

				if (found != 1) {
					branches[currentBranch + 1] = branches[currentBranch].nextBranch();
					currentBranch += 1;
					cout << "\n-->New branch :: currentBranch := " << currentBranch << endl;	
					branches[currentBranch].escBranch();
				}
			}
			this->numRoot = currentBranch;
		}

		int getNumRoot() const {return numRoot;}

};

class CurveSFI0 {
	private:
		Vector3D base, head;
		Vector3D T[6];
		Matrix3D M[6];
	public:
		CurveSFI0(int n) {

			cout << "\n\nReady to Build Cure\n\n";
			
			M[0] = Matrix3D(	0.341,-0.071, 0.0,
                   		 	0.071, 0.341, 0.0,
                   		 	0.000, 0.000, 1.0);

			M[1] = Matrix3D(  0.038,-0.346, 0.0,
                                        0.346, 0.038, 0.0,
                                        0.000, 0.000, 1.0);

			M[2] = Matrix3D(  0.341,-0.071, 0.0,
                                        0.071, 0.341, 0.0,
                                        0.000, 0.000, 1.0);

			M[3] = Matrix3D( -0.234, 0.258, 0.0,
                                       -0.258,-0.234, 0.0,
                                        0.000, 0.000, 1.0);

			M[4] = Matrix3D(  0.173, 0.302, 0.0,
                                       -0.302, 0.173, 0.0,
                                        0.000, 0.000, 1.0);

			M[5] = Matrix3D(  0.341,-0.071, 0.0,
                                        0.071, 0.341, 0.0,
                                        0.000, 0.000, 1.0);

			T[0] = Vector3D(0.0, 0.0, 0.0);
			T[1] = Vector3D(0.341, 0.071, 0.0);
			T[2] = Vector3D(0.379, 0.418, 0.0);
			T[3] = Vector3D(0.720, 0.489, 0.0);
			T[4] = Vector3D(0.486, 0.231, 0.0);
			T[5] = Vector3D(0.659,-0.071, 0.0);
		}

		Vector3D transform(int i, Vector3D v) const {
			Vector3D ret = (M[i] * v) + T[i];
			return ret;
		}
		

};

class Parabola {
	
	private:

		int m;
		double pipi;
		Vector3D points[1600];

	public:

		Parabola(double R, const Vector3D& center, double up) {
			
		//	cout << "\n\n\n PARABOLA\n\n\n";
				
			m = 1600;
			pipi = 3.14159265358979;
			int count = 0;
			for (int i = 0; i < m; i += 2) {
			
				double length = 2 * pipi;
				double sublength = length/m;
				int I = i - (m/2);

				double u0 = (I + (0.0)) * sublength;
                        	double u1 = (I + (1.0)) * sublength;
				
				points[i] =   Vector3D(0.0, -R*u0*u0 + up, u0);
                                points[i+1] = Vector3D(0.0, -R*u1*u1 + up, u1);
				
				points[i] =   (0.15 * points[i]  ) + center;
                        	points[i+1] = (0.15 * points[i+1]) + center;
				
				count += 2;
			}
		}

		int getM() const {return m;}
		Vector3D getPoints(int i) const {return points[i];}
		
};



class POVRayWriter
{
    private:
        //Variables imprescindibles
    string filePath;
    ofstream writer;
    ofstream iniCreator;

        //Control default
    bool defaultFinish;
    bool defaultPigment;

        //Control de finish
    double phongToAdd;
    double ambientToAdd;
    double diffuseToAdd;
    bool finish;
        //Control de pigment
    string colorToAdd;
    string checkerColorToAdd[2];
    double transmitToAdd;
    double filterToAdd;
    bool pigment;
    bool checker;
        //Control de burbujas
    double powerToAdd;
    bool inBlob;
        //Control de vectores
    string nameToUse;
    string indexToUse;
    bool useVector;
        //Control de rotación
    bool rad;
    string rotationToAdd;
    bool rotation;
    double pi;
        //Control de texturas
    string textureToAdd;
    bool texture;


        //Funciones auxiliares
    string rgbToString(int r, int g, int b);
    void writeVectorAtIndex();
    void writeVector(double x, double y, double z);

    public:

    	
	bool ternaryCat(int i, int j){
			if (i < 0) i *= -1;
			if (j < 0) j *= -1;
                           while (i>0 && j>0) {
                                if (i%3==1 && j%3==1)
                                        return true;
                                i/=3;
                                j/=3;
                           }

                        return false;
	}

	bool ternaryCat(int i, int j, int k){

			if (i<0) i*= -1;
			if (j<0) j*= -1;
			if (k<0) k*= -1;
                	while ((i>0 && j>0) || (j>0 && k>0) || (k>0 && i >0)) {
                                if ((i%4==1 && j%4==1) || (j%4==1 && k%4==1) || (k%4==1 && i%4==1))
                                        return true;
                                i/=3;
                                j/=3;
				k/=3;
                           }

                        return false;
	}

	bool ternaryCat(int i, int j, int k, int l){

                        if (i<0) i*= -1;
                        if (j<0) j*= -1;
                        if (k<0) k*= -1;
			if (l<0) l*= -1;
                        while ((i>0 && j>0) || (j>0 && k>0) || (k>0 && i >0) ||
			       (i>0 && l>0) || (l>0 && j>0) || (l>0 && k>0)) {
                                if ((i%3==1 && j%3==1) || (j%3==1 && k%3==1) || (k%3==1 && i%3==1) ||
				    (i%3==1 && l%3==1) || (l%3==1 && j%3==1) || (l%3==1 && k%3==1))
                                        return true;
                                i/=3;
                                j/=3;
                                k/=3;
				l/=3;
                           }

                        return false;
        }

	Vector3D proj(const Vector4D& vec, double proy){
  		return ((proy)/(proy-vec.t())) * Vector3D(vec.x(), vec.y(), vec.z());
	}

	void square(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, const Vector3D& v4,
		   int r, int g, int b) {
		
		TriangleColor( v1, v2, v3, r, g, b);
		TriangleColor( v3, v4, v1, r, g, b);	
	}

	double G1(double u, double v, double R, double r) {
		  double g = ( R + (r*cos(v)) ) * cos(u);
		  return g;
	}

	double G2(double u, double v, double R, double r){

		  double g = ( R + (r*cos(v)) ) * sin(u);
		  return g;
	}

	double G3(double u, double v, double R, double r) {
		  double g = r * sin(v);
		  return g;
	}

	void torusInitL(double R, double r, const Vector3D& c, double X, double Y,int N) {

			double PI = 3.14159265358979;
			
                        double length = 1/((double) N);
			double dr = r/(1 + (double) N);
                        for (int i = 0; i < N; i++){
				cout << "\n round i := " << i;
                                for (int j = 0; j < N; j++)
			       	for (int k = 0; k < N; k++)	{
						
						double rr = (r + (0.1 * r * sin(Y))) - k*dr;

						double x = (2*PI)/((double)N);
                                                double y = (2*PI)/((double)N);

                                                double u1 = (i * x);
                                                double v1 = (j * y) + X;

                                                double u2 = (i * x) + x;
                                                double v2 = (j * y)  + X;

                                                double u3 = (i * x) + x;
                                                double v3 = (j * y) + y + X;

                                                double u4 = (i * x);
                                                double v4 = (j * y) + y  + X;

                                                Vector3D a1 = Vector3D(G1(u1, v1, R, rr), G2(u1, v1, R, rr), G3(u1, v1, R, rr));
                                                Vector3D a2 = Vector3D(G1(u2, v2, R, rr), G2(u2, v2, R, rr), G3(u2, v2, R, rr));
                                                Vector3D a3 = Vector3D(G1(u3, v3, R, rr), G2(u3, v3, R, rr), G3(u3, v3, R, rr));
                                                Vector3D a4 = Vector3D(G1(u4, v4, R, rr), G2(u4, v4, R, rr), G3(u4, v4, R, rr));

						Vector3D a5 = Vector3D(G1(u1, v1, R, rr-dr), G2(u1, v1, R, rr-dr), G3(u1, v1, R, rr-dr));
                                                Vector3D a6 = Vector3D(G1(u2, v2, R, rr-dr), G2(u2, v2, R, rr-dr), G3(u2, v2, R, rr-dr));
                                                Vector3D a7 = Vector3D(G1(u3, v3, R, rr-dr), G2(u3, v3, R, rr-dr), G3(u3, v3, R, rr-dr));
                                                Vector3D a8 = Vector3D(G1(u4, v4, R, rr-dr), G2(u4, v4, R, rr-dr), G3(u4, v4, R, rr-dr));

                                                bool t = ternaryCat(i, j, k);
                                                if (t == false) {
                                                        square(a1, a2, a3, a4, 0, 0, 0);
							square(a8, a7, a6, a5, 0, 0, 0);
							square(a1, a5, a8, a4, 7, 0, 0);
							square(a2, a6, a7, a3, 7, 0, 0);
							square(a1, a5, a6, a2, 7, 0, 0);
							square(a8, a4, a3, a7, 7, 0, 0);
						}
                                }
                        }
        }




	double H1(double u, double v, double R) {
                  double g = R*sin(u)*cos(v);
                  return g;
        }

        double H2(double u, double v, double R){

                  double g = R*sin(u)*sin(v);
                  return g;
        }

        double H3(double u, double v, double R) {
                  double g = R*cos(u);
                  return g;
        }

	void sphereInitL(double R, double r, const Vector3D& c, double X, double Y,int N) {

                        double PI = 3.14159265358979;

                        double length = 1/((double) N);
                        double dr = r/(1 + (double) N);
                        for (int i = 0; i < N; i++){
                                cout << "\n round i := " << i;
                                for (int j = 0; j < N; j++)
                                for (int k = 0; k < N; k++)     {

                                                double RR = (R + (0.1 * R * sin(Y))) - k*dr;

                                                double x = (1*PI)/((double)N);
                                                double y = (2*PI)/((double)N);

                                                double u1 = (i * x);
                                                double v1 = (j * y) + X;

                                                double u2 = (i * x) + x;
                                                double v2 = (j * y)  + X;

                                                double u3 = (i * x) + x;
                                                double v3 = (j * y) + y + X;

                                                double u4 = (i * x);
                                                double v4 = (j * y) + y  + X;

                                                Vector3D a1 = Vector3D(H1(u1, v1, RR), H2(u1, v1, RR), H3(u1, v1, RR));
                                                Vector3D a2 = Vector3D(H1(u2, v2, RR), H2(u2, v2, RR), H3(u2, v2, RR));
                                                Vector3D a3 = Vector3D(H1(u3, v3, RR), H2(u3, v3, RR), H3(u3, v3, RR));
                                                Vector3D a4 = Vector3D(H1(u4, v4, RR), H2(u4, v4, RR), H3(u4, v4, RR));

                                                Vector3D a5 = Vector3D(H1(u1, v1, RR-dr), H2(u1, v1, RR-dr), H3(u1, v1, RR-dr));
                                                Vector3D a6 = Vector3D(H1(u2, v2, RR-dr), H2(u2, v2, RR-dr), H3(u2, v2, RR-dr));
                                                Vector3D a7 = Vector3D(H1(u3, v3, RR-dr), H2(u3, v3, RR-dr), H3(u3, v3, RR-dr));
                                                Vector3D a8 = Vector3D(H1(u4, v4, RR-dr), H2(u4, v4, RR-dr), H3(u4, v4, RR-dr));

                                                bool t = ternaryCat(i, j, k);
                                                if (t == false) {
                                                        square(a1, a2, a3, a4, 0, 0, 0);
                                                        square(a8, a7, a6, a5, 0, 0, 0);
                                                        square(a1, a5, a8, a4, 7, 0, 0);
                                                        square(a2, a6, a7, a3, 7, 0, 0);
                                                        square(a1, a5, a6, a2, 7, 0, 0);
                                                        square(a8, a4, a3, a7, 7, 0, 0);
                                                }
                                }
                        }
        }

	void Cube(const Vector3D& c, double sx, double sy, double sz, double w, double r, double g, double b) {
		
		Vector3D G[8];

		G[0] = Vector3D( sx + c.x(), sy + c.y(), sz + c.z());
		G[1] = Vector3D(-sx + c.x(), sy + c.y(), sz + c.z());
		G[2] = Vector3D(-sx + c.x(),-sy + c.y(), sz + c.z());
		G[3] = Vector3D( sx + c.x(),-sy + c.y(), sz + c.z());

		G[4] = Vector3D( sx + c.x(), sy + c.y(),-sz + c.z());
                G[5] = Vector3D(-sx + c.x(), sy + c.y(),-sz + c.z());
                G[6] = Vector3D(-sx + c.x(),-sy + c.y(),-sz + c.z());
                G[7] = Vector3D( sx + c.x(),-sy + c.y(),-sz + c.z());

		//square(G[0], G[1], G[2], G[3], r, g, b);
                //square(G[1], G[2], G[6], G[5], r, g, b);
                //square(G[6], G[5], G[4], G[7], r, g, b);
                //square(G[4], G[7], G[3], G[0], r, g, b);
                //square(G[2], G[3], G[7], G[6], r, g, b);
                //square(G[0], G[1], G[5], G[4], r, g, b);

		CylinderI(G[0], G[1], w, 0, 0, 0);
		CylinderI(G[1], G[2], w, 0, 0, 0);
		CylinderI(G[2], G[3], w, 0, 0, 0);
		CylinderI(G[3], G[0], w, 0, 0, 0);

		CylinderI(G[4], G[0], w, 0, 0, 0);
		CylinderI(G[5], G[1], w, 0, 0, 0);
		CylinderI(G[6], G[2], w, 0, 0, 0);
		CylinderI(G[7], G[3], w, 0, 0, 0);

		CylinderI(G[4], G[5], w, 0, 0, 0);
		CylinderI(G[5], G[6], w, 0, 0, 0);
		CylinderI(G[6], G[7], w, 0, 0, 0);
		CylinderI(G[7], G[4], w, 0, 0, 0);
	}

	void CubeBytes(const Vector3D& c, double sx, double sy, double sz, double w, double r, double g, double b, double n, int mod, int iC, int scenes, 
			const Vector3D& position1, const Vector3D& translate, int pull) {

                Vector3D G[8];

                G[0] = Vector3D( sx + c.x(), sy + c.y(), sz + c.z());
                G[1] = Vector3D(-sx + c.x(), sy + c.y(), sz + c.z());
                G[2] = Vector3D(-sx + c.x(),-sy + c.y(), sz + c.z());
                G[3] = Vector3D( sx + c.x(),-sy + c.y(), sz + c.z());

                G[4] = Vector3D( sx + c.x(), sy + c.y(),-sz + c.z());
                G[5] = Vector3D(-sx + c.x(), sy + c.y(),-sz + c.z());
                G[6] = Vector3D(-sx + c.x(),-sy + c.y(),-sz + c.z());
                G[7] = Vector3D( sx + c.x(),-sy + c.y(),-sz + c.z());

                //square(G[0], G[1], G[2], G[3], r, g, b);
                //square(G[1], G[2], G[6], G[5], r, g, b);
                //square(G[6], G[5], G[4], G[7], r, g, b);
                //square(G[4], G[7], G[3], G[0], r, g, b);
                //square(G[2], G[3], G[7], G[6], r, g, b);
                //square(G[0], G[1], G[5], G[4], r, g, b);

                //CylinderI(G[0], G[1], w, 0, 0, 0);
                //CylinderI(G[1], G[2], w, 0, 0, 0);
                //CylinderI(G[2], G[3], w, 0, 0, 0);
                //CylinderI(G[3], G[0], w, 0, 0, 0);

                //CylinderI(G[4], G[0], w, 0, 0, 0);
                //CylinderI(G[5], G[1], w, 0, 0, 0);
                //CylinderI(G[6], G[2], w, 0, 0, 0);
                //CylinderI(G[7], G[3], w, 0, 0, 0);

                //CylinderI(G[4], G[5], w, 0, 0, 0);
                //CylinderI(G[5], G[6], w, 0, 0, 0);
                //CylinderI(G[6], G[7], w, 0, 0, 0);
                //CylinderI(G[7], G[4], w, 0, 0, 0);

		double L = abs(G[0]-G[4]);
		double p = L/n;
		for (int i = 0; i < (int)n; i++) {

			Vector3D pulled2, pulled6, pulled7, pulled3;
			
				pulled2 = Vector3D(G[2]);
                        	pulled2 = piecewiseVector(G[1], pulled2, i, (int)n);

                        	pulled6 = Vector3D(G[6]);
                        	pulled6 = piecewiseVector(G[5], pulled6, i, (int)n);

                        	pulled7 = Vector3D(G[7]);
                        	pulled7 = piecewiseVector(G[4], pulled7, i, (int)n);

                        	pulled3 = Vector3D(G[3]);
                        	pulled3 = piecewiseVector(G[0], pulled3, i, (int)n);
			
				Vector3D pulled02, pulled06, pulled07, pulled03;
				pulled02 = piecewiseVector(G[1], G[2], i+1, (int)n);
				pulled06 = piecewiseVector(G[5], G[6], i+1, (int)n);
				pulled07 = piecewiseVector(G[4], G[7], i+1, (int)n);
				pulled03 = piecewiseVector(G[0], G[3], i+1, (int)n);

			if (i == pull) {
				CylinderI(pulled03 + translate, pulled02 + translate, 0.5*w, 7, 0, 0);
                		CylinderI(pulled02 + translate,  pulled2 + translate, 0.5*w, 7, 0, 0);
                		CylinderI( pulled2 + translate,  pulled3 + translate, 0.5*w, 7, 0, 0);
                		CylinderI( pulled3 + translate, pulled03 + translate, 0.5*w, 7, 0, 0);

                		CylinderI(pulled07 + translate,pulled03 + translate, 0.5*w, 7, 0, 0);
                		CylinderI(pulled06 + translate,pulled02 + translate, 0.5*w, 7, 0, 0);
                		CylinderI( pulled6 + translate, pulled2 + translate, 0.5*w, 7, 0, 0);
                		CylinderI( pulled7 + translate, pulled3 + translate, 0.5*w, 7, 0, 0);

                		CylinderI(pulled07 + translate,pulled06 + translate, w, 7, 0, 0);
                		CylinderI(pulled06 + translate, pulled6 + translate, w, 7, 0, 0);
                		CylinderI( pulled6 + translate, pulled7 + translate, w, 7, 0, 0);
                		CylinderI( pulled7 + translate,pulled07 + translate, w, 7, 0, 0);
			}
				CylinderI(   G[0],    G[1], 0.5*w, 7, 0, 0);
                                CylinderI(   G[1], pulled2, 0.5*w, 7, 0, 0);
                                CylinderI(pulled2, pulled3, 0.5*w, 7, 0, 0);
                                CylinderI(pulled3,    G[0], 0.5*w, 7, 0, 0);

                                CylinderI(   G[4],    G[0], 0.5*w, 7, 0, 0);
                                CylinderI(   G[5],    G[1], 0.5*w, 7, 0, 0);
                                CylinderI(pulled6, pulled2, 0.5*w, 7, 0, 0);
                                CylinderI(pulled7, pulled3, 0.5*w, 7, 0, 0);

                                CylinderI(   G[4],    G[5], w, 7, 0, 0);
                                CylinderI(   G[5], pulled6, w, 7, 0, 0);
                                CylinderI(pulled6, pulled7, w, 7, 0, 0);
                                CylinderI(pulled7,    G[4], w, 7, 0, 0);	
			

			Vector3D cenG = Vector3D(0,0,0);
			cenG = cenG + pulled2 + pulled6 + pulled7 + pulled3;
			cenG = 0.25 * cenG;

			cenG = cenG + Vector3D(0.0, 0.0, 0.0);
			double explode = piecewiseNumber(0.5*scenes, 900, iC, scenes);
			if (i%(int)n == mod) {
			//	square(G[0], G[1], pulled2, pulled3, 0, 0, 0);
                	//	square(G[1], pulled2, pulled6, G[5], 0, 0, 0);
                	//	square(pulled6, G[5], G[4], pulled7, 0, 0, 0);
                	//	square(G[4], pulled7, pulled3, G[0], 0, 0, 0);
                	//	square(pulled2, pulled3, pulled7, pulled6, 0, 0, 0);
                	//	square(G[0], G[1], G[5], G[4], 0, 0, 0);
			//}
			//
				if (i == pull)			
					texReaderBeta("01011.txt", position1, cenG + translate, "Blue", 
					       explode, scenes, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);
				else
                                	texReaderBeta("01011.txt", position1, cenG, "Blue",
                                               explode, scenes, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

			}else {
				if (i == pull)	
					texReaderBeta("01010.txt", position1, cenG + translate, "Blue",
                        	               explode, scenes, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 7, 0);
				else
					texReaderBeta("01010.txt", position1, cenG, "Blue",
                                               explode, scenes, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 7, 0);
			}
		

		}//end for


        }
	
	 void CubeBytes2(const Vector3D& c, double sx, double sy, double sz, double w, double r, double g, double b, double n, int mod, int iC, int scenes,
                        const Vector3D& position1, const Vector3D& translate, int pull) {

                Vector3D G[8];

                G[0] = Vector3D( sx + c.x(), sy + c.y(), sz + c.z());
                G[1] = Vector3D(-sx + c.x(), sy + c.y(), sz + c.z());
                G[2] = Vector3D(-sx + c.x(),-sy + c.y(), sz + c.z());
                G[3] = Vector3D( sx + c.x(),-sy + c.y(), sz + c.z());

                G[4] = Vector3D( sx + c.x(), sy + c.y(),-sz + c.z());
                G[5] = Vector3D(-sx + c.x(), sy + c.y(),-sz + c.z());
                G[6] = Vector3D(-sx + c.x(),-sy + c.y(),-sz + c.z());
                G[7] = Vector3D( sx + c.x(),-sy + c.y(),-sz + c.z());

                double L = abs(G[0]-G[4]);
                double p = L/n;
                for (int i = 0; i < (int)n; i++) {

                        Vector3D pulled2, pulled6, pulled7, pulled3;

                                pulled2 = Vector3D(G[2]);
                                pulled2 = piecewiseVector(G[1], pulled2, i, (int)n);

                                pulled6 = Vector3D(G[6]);
                                pulled6 = piecewiseVector(G[5], pulled6, i, (int)n);

                                pulled7 = Vector3D(G[7]);
                                pulled7 = piecewiseVector(G[4], pulled7, i, (int)n);

                                pulled3 = Vector3D(G[3]);
                                pulled3 = piecewiseVector(G[0], pulled3, i, (int)n);

                                Vector3D pulled02, pulled06, pulled07, pulled03;
                                pulled02 = piecewiseVector(G[1], G[2], i+1, (int)n);
                                pulled06 = piecewiseVector(G[5], G[6], i+1, (int)n);
                                pulled07 = piecewiseVector(G[4], G[7], i+1, (int)n);
                                pulled03 = piecewiseVector(G[0], G[3], i+1, (int)n);

                        if (i == pull) {
                                CylinderI(pulled03 + translate, pulled02 + translate, 0.5*w, r, g, b);
                                CylinderI(pulled02 + translate,  pulled2 + translate, 0.5*w, r, g, b);
                                CylinderI( pulled2 + translate,  pulled3 + translate, 0.5*w, r, g, b);
                                CylinderI( pulled3 + translate, pulled03 + translate, 0.5*w, r, g, b);

                                CylinderI(pulled07 + translate,pulled03 + translate, 0.5*w, r, g, b);
                                CylinderI(pulled06 + translate,pulled02 + translate, 0.5*w, r, g, b);
                                CylinderI( pulled6 + translate, pulled2 + translate, 0.5*w, r, g, b);
                                CylinderI( pulled7 + translate, pulled3 + translate, 0.5*w, r, g, b);

                                CylinderI(pulled07 + translate,pulled06 + translate, w, r, g, b);
                                CylinderI(pulled06 + translate, pulled6 + translate, w, r, g, b);
                                CylinderI( pulled6 + translate, pulled7 + translate, w, r, g, b);
                                CylinderI( pulled7 + translate,pulled07 + translate, w, r, g, b);
                        }

                        Vector3D cenG = Vector3D(0,0,0);
                        cenG = cenG + pulled2 + pulled6 + pulled7 + pulled3;
                        cenG = 0.25 * cenG;

                        cenG = cenG + Vector3D(0.0, 0.0, 0.0);
                        double explode = piecewiseNumber(0.5*scenes, 900, iC, scenes);
                        if (i%(int)n == mod) {
                        //      square(G[0], G[1], pulled2, pulled3, 0, 0, 0);
                        //      square(G[1], pulled2, pulled6, G[5], 0, 0, 0);
                        //      square(pulled6, G[5], G[4], pulled7, 0, 0, 0);
                        //      square(G[4], pulled7, pulled3, G[0], 0, 0, 0);
                        //      square(pulled2, pulled3, pulled7, pulled6, 0, 0, 0);
                        //      square(G[0], G[1], G[5], G[4], 0, 0, 0);
                        //}
                        //
                                if (i == pull)
                                        texReaderBeta("01011.txt", position1, cenG + translate, "Blue",
                                               explode, scenes, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                        }else {
                                if (i == pull)
                                        texReaderBeta("01010.txt", position1, cenG + translate, "Blue",
                                               explode, scenes, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 7, 0);
                        }


                }//end for


        }



	void lattice3D(int a, const Vector3D& center, double radius, double angle) {

                        double s = radius/a;
                        double sr = 0.5 * s;

			double A = 0.01 * radius * cos(angle);

                        for (int i = 0; i < a; i++)
                                for (int j = 0; j < a; j++){
                                        
					double S = (i*i + j*j);
					for (int k = 0; k < a; k++) {
						bool T = ternaryCat(i, j, k);
                                        	if (T == false) {
							
							
							double sx = s;
							double sz = s;
                                                	double sy = s + (0.2 * s * sin(angle));//3*cos(sx*sx + sy*sy);

							Vector3D c = Vector3D(sx * i, sy * j, sz * k) + center;
							square(
								Vector3D(    sx * i,     sy * j, sz * k) + center,
								Vector3D(sx * (i+1),     sy * j, sz * k) + center,
								Vector3D(sx * (i+1), sy * (j+1), sz * k) + center,
								Vector3D(    sx * i, sy * (j+1), sz * k) + center,0, 0, 0);

							square(
                                                                Vector3D(    sx * i,     sy * j, sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1),     sy * j, sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1), sy * (j+0), sz * k) + center,
                                                                Vector3D(    sx * i, sy * (j+0), sz * k) + center,0, 0, 0);

							square(
                                                                Vector3D(sx * (i+1),     sy * j, sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1), sy * (j+1), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1), sy * (j+1), sz * k) + center,
                                                                Vector3D(sx * (i+1), sy * (j+0), sz * k) + center,0, 0, 0);

							square(
                                                                Vector3D(sx * (i+0), sy * (j+0), sz * (k+0)) + center,
                                                                Vector3D(sx * (i+0), sy * (j+0), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+0), sy * (j+1), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+0), sy * (j+1), sz * (k+0)) + center,0, 0, 0);
							
							square(
                                                                Vector3D(sx * (i+0), sy * (j+1), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1), sy * (j+1), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1), sy * (j+1), sz * (k+0)) + center,
                                                                Vector3D(sx * (i+0), sy * (j+1), sz * (k+0)) + center,0, 0, 0);

							square(
                                                                Vector3D(sx * (i+0), sy * (j+0), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+0), sy * (j+1), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1), sy * (j+1), sz * (k+1)) + center,
                                                                Vector3D(sx * (i+1), sy * (j+0), sz * (k+1)) + center,0, 0, 0);

							//Cube(c, 2*sr, 0.4*sr, sr, sr, 0, 0, 0);
                                                }
                                        }
				}
        }

	void hyperCube(const Vector4D& c, double R, double r, double g, double b,
		     const Matrix4D& M, double pro, double size, int cell) {
		
		Vector4D H[16];	
		H[0] = Vector4D( R + c.x(), R + c.y(), R + c.z(), R + c.t());
		H[1] = Vector4D(-R + c.x(), R + c.y(), R + c.z(), R + c.t());
		H[2] = Vector4D(-R + c.x(),-R + c.y(), R + c.z(), R + c.t());
		H[3] = Vector4D( R + c.x(),-R + c.y(), R + c.z(), R + c.t());

		H[4] = Vector4D( R + c.x(), R + c.y(),-R + c.z(), R + c.t());
                H[5] = Vector4D(-R + c.x(), R + c.y(),-R + c.z(), R + c.t());
                H[6] = Vector4D(-R + c.x(),-R + c.y(),-R + c.z(), R + c.t());
                H[7] = Vector4D( R + c.x(),-R + c.y(),-R + c.z(), R + c.t());

		H[8] =  Vector4D( R + c.x(), R + c.y(), R + c.z(),-R + c.t());
                H[9] =  Vector4D(-R + c.x(), R + c.y(), R + c.z(),-R + c.t());
                H[10] = Vector4D(-R + c.x(),-R + c.y(), R + c.z(),-R + c.t());
                H[11] = Vector4D( R + c.x(),-R + c.y(), R + c.z(),-R + c.t());

                H[12] = Vector4D( R + c.x(), R + c.y(),-R + c.z(),-R + c.t());
                H[13] = Vector4D(-R + c.x(), R + c.y(),-R + c.z(),-R + c.t());
                H[14] = Vector4D(-R + c.x(),-R + c.y(),-R + c.z(),-R + c.t());
                H[15] = Vector4D( R + c.x(),-R + c.y(),-R + c.z(),-R + c.t());

		Vector3D G[16];
		for (int i = 0; i < 16; i++) {
		
			H[i] = M * H[i];
			G[i] = proj(H[i], pro);
			G[i] = size * G[i];
		}

		//CELL 1
		if (cell == 0) {
			square(G[8], G[9], G[10], G[11],   r, g, b);
			square(G[11], G[10], G[14], G[15], r, g, b);
			square(G[8], G[11], G[15], G[12],  r, g, b);
			square(G[9], G[13], G[14], G[10],  r, g, b);
			square(G[14], G[13], G[12], G[15], r, g, b);
			square(G[8], G[9], G[13], G[12],   r, g, b);
		}

		if (cell == 1) {
			square(G[0], G[8], G[11], G[3],  r, g, b);
			square(G[3], G[11], G[15], G[7], r, g, b);
			square(G[4], G[12], G[15], G[7], r, g, b);
			square(G[0], G[8], G[12], G[4],  r, g, b);
			square(G[8], G[11], G[15], G[12],r, g, b);
			square(G[0], G[3], G[7], G[4],   r, g, b);
		}
		
		if (cell == 2) {
			square(G[1], G[9], G[10], G[2],   r, g, b);
			square(G[2], G[10], G[14], G[6],  r, g, b);
			square(G[5], G[13], G[14], G[6],  r, g, b);
			square(G[1], G[9], G[13], G[5],   r, g, b);
			square(G[9], G[10], G[14], G[13], r, g, b);
			square(G[1], G[2], G[6], G[5],    r, g, b);
		}
		
		if (cell == 3) {
			square(G[1], G[9], G[13], G[5],  r, g, b);
			square(G[5], G[13], G[12], G[4], r, g, b);
			square(G[4], G[12], G[8], G[0],  r, g, b);
			square(G[0], G[8], G[9], G[1],   r, g, b);
			square(G[8], G[9], G[13], G[12], r, g, b);
			square(G[0], G[1], G[5], G[4],   r, g, b);
		}
		
		if (cell == 4) {
			square(G[2], G[10], G[14], G[6],   r, g, b);
			square(G[6], G[14], G[15], G[7],   r, g, b);
			square(G[7], G[15], G[11], G[3],   r, g, b);
			square(G[2], G[10], G[11], G[3],   r, g, b);
			square(G[10], G[11], G[15], G[14], r, g, b);
			square(G[2], G[6], G[7], G[3],     r, g, b);
		}

		if (cell == 5) {
			square(G[5], G[13], G[14], G[6],   r, g, b);
			square(G[6], G[14], G[15], G[7],   r, g, b);
			square(G[7], G[15], G[12], G[4],   r, g, b);
			square(G[4], G[12], G[13], G[5],   r, g, b);
			square(G[14], G[13], G[12], G[15], r, g, b);
			square(G[5], G[6], G[7], G[4],     r, g, b);
		}
		
		if (cell == 6) {
			square(G[9], G[8], G[11], G[10], r, g, b);
			square(G[1], G[2], G[3], G[0],   r, g, b);
			square(G[1], G[5], G[10], G[2],  r, g, b);
			square(G[2], G[10], G[11], G[3], r, g, b);
			square(G[3], G[11], G[8], G[0],  r, g, b);
			square(G[0], G[8], G[9], G[1],   r, g, b);
		}

		if (cell == 7) {
                        square(G[0], G[1], G[2], G[3], r, g, b);
                        square(G[1], G[2], G[6], G[5], r, g, b);
                        square(G[6], G[5], G[4], G[7], r, g, b);
                        square(G[4], G[7], G[3], G[0], r, g, b);
                        square(G[2], G[3], G[7], G[6], r, g, b);
                        square(G[0], G[1], G[5], G[4], r, g, b);
                }

		if (cell == 8) {
		
		
			square(G[8], G[9], G[10], G[11],   r, g, b);
                        square(G[11], G[10], G[14], G[15], r, g, b);
                        square(G[8], G[11], G[15], G[12],  r, g, b);
                        square(G[9], G[13], G[14], G[10],  r, g, b);
                        square(G[14], G[13], G[12], G[15], r, g, b);
                        square(G[8], G[9], G[13], G[12],   r, g, b);
                        square(G[0], G[8], G[11], G[3],  r, g, b);
                        square(G[3], G[11], G[15], G[7], r, g, b);
                        square(G[4], G[12], G[15], G[7], r, g, b);
                        square(G[0], G[8], G[12], G[4],  r, g, b);
                        square(G[8], G[11], G[15], G[12],r, g, b);
                        square(G[0], G[3], G[7], G[4],   r, g, b);
                        square(G[1], G[9], G[10], G[2],   r, g, b);
                        square(G[2], G[10], G[14], G[6],  r, g, b);
                        square(G[5], G[13], G[14], G[6],  r, g, b);
                        square(G[1], G[9], G[13], G[5],   r, g, b);
                        square(G[9], G[10], G[14], G[13], r, g, b);
                        square(G[1], G[2], G[6], G[5],    r, g, b);
                        square(G[1], G[9], G[13], G[5],  r, g, b);
                        square(G[5], G[13], G[12], G[4], r, g, b);
                        square(G[4], G[12], G[8], G[0],  r, g, b);
                        square(G[0], G[8], G[9], G[1],   r, g, b);
                        square(G[8], G[9], G[13], G[12], r, g, b);
                        square(G[0], G[1], G[5], G[4],   r, g, b);
                        square(G[2], G[10], G[14], G[6],   r, g, b);
                        square(G[6], G[14], G[15], G[7],   r, g, b);
                        square(G[7], G[15], G[11], G[3],   r, g, b);
                        square(G[2], G[10], G[11], G[3],   r, g, b);
                        square(G[10], G[11], G[15], G[14], r, g, b);
                        square(G[2], G[6], G[7], G[3],     r, g, b);
                        square(G[5], G[13], G[14], G[6],   r, g, b);
                        square(G[6], G[14], G[15], G[7],   r, g, b);
                        square(G[7], G[15], G[12], G[4],   r, g, b);
                        square(G[4], G[12], G[13], G[5],   r, g, b);
                        square(G[14], G[13], G[12], G[15], r, g, b);
                        square(G[5], G[6], G[7], G[4],     r, g, b);
                        square(G[9], G[8], G[11], G[10], r, g, b);
                        square(G[1], G[2], G[3], G[0],   r, g, b);
                        square(G[1], G[5], G[10], G[2],  r, g, b);
                        square(G[2], G[10], G[11], G[3], r, g, b);
                        square(G[3], G[11], G[8], G[0],  r, g, b);
                        square(G[0], G[8], G[9], G[1],   r, g, b);
                        square(G[0], G[1], G[2], G[3], r, g, b);
                        square(G[1], G[2], G[6], G[5], r, g, b);
                        square(G[6], G[5], G[4], G[7], r, g, b);
                        square(G[4], G[7], G[3], G[0], r, g, b);
                        square(G[2], G[3], G[7], G[6], r, g, b);
                        square(G[0], G[1], G[5], G[4], r, g, b);
		
		}
		r = 0;
		g = 0;
		b = 0;

		CylinderI(G[0], G[1], 0.1*R, r, g, b);
		CylinderI(G[1], G[2], 0.1*R, r, g, b);
		CylinderI(G[2], G[3], 0.1*R, r, g, b);
		CylinderI(G[3], G[0], 0.1*R, r, g, b);

		CylinderI(G[0], G[4], 0.1*R, r, g, b);
		CylinderI(G[1], G[5], 0.1*R, r, g, b);
		CylinderI(G[2], G[6], 0.1*R, r, g, b);
		CylinderI(G[3], G[7], 0.1*R, r, g, b);

		CylinderI(G[4], G[5], 0.1*R, r, g, b);
                CylinderI(G[5], G[6], 0.1*R, r, g, b);
                CylinderI(G[6], G[7], 0.1*R, r, g, b);
                CylinderI(G[7], G[4], 0.1*R, r, g, b);

		CylinderI(G[0], G[8], 0.1*R, r, g, b);
                CylinderI(G[1], G[9], 0.1*R, r, g, b);
                CylinderI(G[2], G[10],0.1*R, r, g, b);
                CylinderI(G[3], G[11],0.1*R, r, g, b);

		CylinderI(G[4], G[12],0.1*R, r, g, b);
                CylinderI(G[5], G[13],0.1*R, r, g, b);
                CylinderI(G[6], G[14],0.1*R, r, g, b);
                CylinderI(G[7], G[15],0.1*R, r, g, b);

		CylinderI(G[8], G[9], 0.1*R, r, g, b);
                CylinderI(G[9], G[10],0.1*R, r, g, b);
               CylinderI(G[10], G[11],0.1*R, r, g, b);
                CylinderI(G[11], G[8],0.1*R, r, g, b);

	       CylinderI(G[12], G[13],0.1*R, r, g, b);
               CylinderI(G[13], G[14],0.1*R, r, g, b);
               CylinderI(G[14], G[15],0.1*R, r, g, b);
               CylinderI(G[15], G[12],0.1*R, r, g, b);

	       CylinderI(G[12], G[8], 0.1*R, r, g, b);
               CylinderI(G[13], G[9], 0.1*R, r, g, b);
               CylinderI(G[14], G[10],0.1*R, r, g, b);
               CylinderI(G[15], G[11],0.1*R, r, g, b);

		//TriangleColor(center, a, b, 5, 0, 5);
	}

	void lattice4D(int a, int b, int c, int d, const Vector4D& center, double radius, int cell, double angle, int L) {

                        double s = radius/a;
                        double sr = 0.5 * s;

			Matrix4D ZW = Matrix4D(
                                        1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, cos(angle),-sin(angle),
                                        0, 0, sin(angle), cos(angle)
                                        );

                        for (int i = 0; i < a; i++)
		       		for (int j = 0; j < a; j++)
					for (int k = 0; k < a; k++)
						for (int l = L; l < L+1; l++) {

							if (ternaryCat(i, j, k, l) == false) {
                        					Vector4D c = Vector4D(s * i, s * j, s * k, s * l) + center;
								
									double color = piecewiseNumber(7, 0, l, a);
                                					hyperCube(c, sr, 7, color, color, ZW, 20.0, 2, cell);
								
							}
                       				}
       	}

	void drawTree(const Tree& tree, int iC, const Vector3D& vv, const Vector3D& aa, double IC, int numScene) {
		
		Vector3D Aux = Vector3D(tree.getRoot());

		//createStandardSphere(0.3, Aux.x(), Aux.y()-0.2, Aux.z(), "Red");
		if(iC > 896) {
			for (int i = 0; i < tree.getNumLeaf(); i++) {
				Vector3D aux = Vector3D(tree.getLeaf(i));
				//if (i%6 == 0)	texReaderBeta("0N.txt", vv, aux, "Red", iC, numScene, 0.005*0.05, 0.0025);
				//if (i%6 == 1)   texReaderBeta("0M.txt", vv, aux, "Blue", iC, numScene, 0.005*0.05, 0.0025);
				//if (i%6 == 2)   texReaderBeta("0R.txt", vv, aux, "Green", iC, numScene, 0.005*0.05, 0.0025);
				//if (i%6 == 3)   texReaderBeta("0x.txt", vv, aux, "Red", iC, numScene, 0.005*0.05, 0.0025);
				//if (i%6 == 4)   texReaderBeta("0y.txt", vv, aux, "Blue", iC, numScene, 0.005*0.05, 0.0025);
				//if (i%6 == 5)   texReaderBeta("0z.txt", vv, aux, "Green", iC, numScene, 0.005*0.05, 0.0025);
				createStandardSphere(0.025*0.5, aux.x(), aux.y(), aux.z(), "Red");
			}
		}

		for (int i = 0; i < iC*10; i++){
			Vector3D head = Vector3D(tree.getBranch(i).getPosition());
			Vector3D base = Vector3D(tree.getBranch(i).getParent());

			double branchNUM = (double)i;
			double numberOfBranches = (double)(iC * 10);
			double delta = branchNUM/numberOfBranches;
			double width = 1.0 - delta;
                        Cylinder( head, base, 0.01 * width);
		}

	}


	void drawCurveSFI0(const CurveSFI0& curve, const Vector3D& head, const Vector3D& base, int n) {

		if (n == 0) {
			//createStandardSphere(1.01*0.01*0.2, head.x(), head.y(), head.z(), "Red");
			CylinderI(head, base, 0.01*0.05, 2, 0, 4);
			//Cylinder( head, base, 0.01 * 0.2);
		} else {
			
			Vector3D head0 = Vector3D(curve.transform(0, head));
			Vector3D base0 = Vector3D(curve.transform(0, base));
			
			Vector3D head1 = Vector3D(curve.transform(1, head));
			Vector3D base1 = Vector3D(curve.transform(1, base));
			
			Vector3D head2 = Vector3D(curve.transform(2, head));
			Vector3D base2 = Vector3D(curve.transform(2, base));
			
			Vector3D head3 = Vector3D(curve.transform(3, head));
			Vector3D base3 = Vector3D(curve.transform(3, base));
			
			Vector3D head4 = Vector3D(curve.transform(4, head));
			Vector3D base4 = Vector3D(curve.transform(4, base));
			
			Vector3D head5 = Vector3D(curve.transform(5, head));
			Vector3D base5 = Vector3D(curve.transform(5, base));

			drawCurveSFI0(curve, head0, base0, n-1);
			drawCurveSFI0(curve, head1, base1, n-1);
			drawCurveSFI0(curve, head2, base2, n-1);
			drawCurveSFI0(curve, head3, base3, n-1);
			drawCurveSFI0(curve, head4, base4, n-1);
			drawCurveSFI0(curve, head5, base5, n-1);

		}
	}

    POVRayWriter(string path);

    void createIniFile(string path, int frames, int initClock, int endClock);
    void createIniFile(string path, int frames);

    string Clock();

    void addFinishToNextObject(double phong, double ambient, double diffuse);
    void writeFinish();

    void addPigmentToNextObject(string color, double transmit, double filter);
    void addPigmentToNextObject(double transmit, double filter);
    void addPigmentToNextObject(int r, int g, int b, double transmit, double filter);
    void setObjectColorChecker(string c1, string c2);
    void setObjectColorChecker(int r1, int g1, int b1, int r2, int g2, int b2);
    void writePigment();

    void useTextures();
    void addTextureToNextObject(string texture);
    void writeTexture();

    void setDefaultPigment();
    void setDefaultFinish();
    void unsetDefaults();

    void createCamera(double xi, double yi, double zi, double xf, double yf, double zf);
    void createCameraLocationFromVectorArray(double xf, double yf, double zf);
    void createCameraLookingAtFromVectorArray(double xi, double yi, double zi);
    void createCameraFromVectorArray(string vectorLocation, string vectorLookAt, string indexPos, string indexLookingAt);
    void createCameraFromVectorArray(string vectorToUse, string indexPos, string indexLookingAt);

    void createLight(double x, double y, double z, double r, double g, double b);
    void createLight(double x, double y, double z);


    void createSphere(double r, double x, double y, double z);
    void createSphere(double r, const Vector3D& c, double rr, double gg, double bb);
    void createSphere(double r);
    void createPlane(double n1, double n2, double n3, double d);
    void createPlane(double d);
    void createPlane(string plane, double d);
    void createBox(double xi, double yi, double zi, double xf, double yf, double zf);
    void createBoxInitFromVectorArray(double xf, double yf, double zf);
    void createBoxLastFromVectorArray(double xi, double yi, double zi);
    void createBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex);
    void createCylinder(double xi, double yi, double zi, double xf, double yf, double zf, double r);
    void createCylinderInitFromVectorArray(double xf, double yf, double zf, double r);
    void createCylinderLastFromVectorArray(double xi, double yi, double zi, double r);
    void createCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r);
    void createTorus(double middleR, double minorR);
    void createTorus(double x, double y, double z, double middleR, double minorR);

    void createStandardSphere(double r, double x, double y, double z, string color);
    void createStandardSphere(double r, string color);
    void createStandardPlane(double n1, double n2, double n3, double d, string c1, string c2);
    void createStandardPlane(double d, string c1, string c2);
    void createStandardPlane(string plane, double d, string c1, string c2);
    void createStandardBox(double xi, double yi, double zi, double xf, double yf, double zf, string color);
    void createStandardBoxInitFromVectorArray(double xf, double yf, double zf, string color);
    void createStandardBoxLastFromVectorArray(double xi, double yi, double zi, string color);
    void createStandardBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, string color);
    void createStandardCylinder(double xi, double yi, double zi, double xf, double yf, double zf, double r, string color);
    void createStandardCylinderInitFromVectorArray(double xf, double yf, double zf, double r, string color);
    void createStandardCylinderLastFromVectorArray(double xi, double yi, double zi,double r, string color);
    void createStandardCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r, string color);
    void createStandardTorus(double middleR, double minorR, string color);
    void createStandardTorus(double x, double y, double z, double middleR, double minorR, string color);
    void createTriangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
    void createStandardTriangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, string color);

    void Triangle(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    void facet(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    void Square(Vector3D a0, Vector3D a1, Vector3D a2, Vector3D a3, double width, bool T);

    void colorTriangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, string color);
    void colorIco(double r, const Vector3D& center, string color);
    void colorCube(double r, const Vector3D& center, string color);
    void colorCubeI(double r, const Vector3D& center, string color,const Vector3D& gamma);
    Vector3D inversion(Vector3D p, double r);
    void fractal1(const Vector3D& center, double r, int n);
    void polyTrace(Vector3D center[], double width);
    void fractal2(Vector3D center[], int n, double width);
    void menger(const Vector3D& center, double r, int n, const Vector3D& mmm);
    void Edge(const Vector3D& a, const Vector3D& b,
	          double d1, double d2, double d3, double width);
    void Arista(const Vector3D& a, const Vector3D& b, double width);
    void truncatedCubicHoneyComb(const Vector3D& center, double r, double thickness, double iC, double S);
    void smallDodeca(double r, const Vector3D& center, double width);
    void dodecahedron(double r, const Vector3D& center, double width, double angle);
    void Cylinder(const Vector3D& a, const Vector3D& b, double r);
    void Cylinder1(const Vector3D& a, const Vector3D& b, double r);
    void Triangle1(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    void spotLight(const Vector3D& position, const Vector3D& lookAt);
    void createLight(const Vector3D& position);
    void ultra_wide_Camera(const Vector3D& position, const Vector3D& lookAt, double angle);
    void rhombicuboctahedronHoneyComb(const Vector3D& center, double r, double thickness);
    void rhombiHoneyComb(const Vector3D& center, double r, double thickness, int n);
    void torusHoneyComb(double R, double r, int n, int m);
    void facetGlass(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    void dodecahedronTree(double r, const Vector3D& center, double width, int n);
    void Pentagon(const Vector3D& v0, const Vector3D& v1,
    	          const Vector3D& v2, const Vector3D& v3, const Vector3D& v4, double width);

                void Draw1(
                                 double x1, double x2, double x3,
                                 double x4, double x5, double x6,
                                 double x7, double x8, double x9,
                                 double x10, double x11, double x12,
                                 double x13, double x14, double x15,
                                 double x16, double x17, double x18,
                                 double x19, double x20, double x21,
                                 double x22, double x23, double x24,
                                 double x25, double x26, double x27,
                                 double x28, double x29, double x30,
                                 double x31, double x32, double x33,
                                 double x34, double x35, double x36,
                                 double x37, double x38, double x39,
                                 double x40, double x41, double x42,
                                 double x43, double x44, double x45,
                                 double x46, double x47, double x48,
                                 double x49, double x50, double x51,
                                 double x52, double x53, double x54,
                                 double x55, double x56, double x57,
                                 double x58, double x59, double x60,
                                 double   r, double   angle, int n,
                                 double  d1, double  d2, double d3, double width

                       );

        void DrawH(
	                        double x1, double x2, double x3,
                          double x4, double x5, double x6,
                          double x7, double x8, double x9,
				                      double x10, double x11, double x12,
				                          double x13, double x14, double x15,
                                  double x16, double x17, double x18,
                                  double x19, double x20, double x21,
				                              double x22, double x23, double x24,
				                                  double x25, double x26, double x27,
                                          double x28, double x29, double x30,
                                          double x31, double x32, double x33,
				                                      double x34, double x35, double x36,

				  double x37, double x38, double x39,
				 double x40, double x41, double x42,
				 double x43, double x44, double x45,
				 double x46, double x47, double x48,
				 double x49, double x50, double x51,
				 double x52, double x53, double x54,
				 double x55, double x56, double x57,
				 double x58, double x59, double x60,
				 double x61, double x62, double x63,
				 double x64, double x65, double x66,
				 double x67, double x68, double x69,
				 double x70, double x71, double x72,
				 double x73, double x74, double x75,
				 double x76, double x77, double x78,
				 double x79, double x80, double x81,
				 double x82, double x83, double x84,
				 double x85, double x86, double x87,
				 double x88, double x89, double x90,
				 double x91, double x92, double x93,
				 double x94, double x95, double x96,
				 int n, double width, double inv, double dist, int g
				  );
    void dodecaTest();
    void dodecaClass(Vector3D v[], Vector3D M);
    Vector3D inversionNew(Vector3D p, double r, Vector3D gamma);
    Vector3D inversionM(Vector3D p, double r, const Vector3D& gamma);   
    void functionDeclaration(string S);
    void rotTest(double r, const Vector3D& center, double width, double angle);
    Vector3D axeRotation(Vector3D head, Vector3D base, Vector3D I, double width, double angle);
    void cube(double r, Vector3D center, double width, 
		    double angle, int n, 
		    Vector3D gamma, double radi, double rr, double gg, double bb, double trans);
    void torusHoneyComb1(double R, double r, int n, int m);
    void refinamiento(double u0, double v0, double sublength, int m, double R, double r, double width);
    void Manifold(int m, double R, double r, double width);
    void Curve(int n, Vector3D center, double rad, double angle, Vector3D inversion, bool T, double inv);
    void Sphere(int m, double R, Vector3D center, double width);
    void SpherePartition(int m, double R, Vector3D center, double width, int timeI);
    double Cx(double x, double rad);
    double Cy(double x, double rad);
    double Cz(double x, double rad);

    double X(double u, double v, double R, double r);
    double Y(double u, double v, double R, double r);
    double Z(double u, double v, double R, double r);

    void T_Gold_1A();
    void T_Chrome_5A();
    void Plane(string plane, double d);
    void mirrorTexture();
    void swirlTexture();
    void woodTexture();
    void glassTexture1();
    void glassTexture2();
    void glassTexture3();
    void marbleTexture1();
    void photons();

    void startBlob(double threshold);
    void addPowerToNextObjects(double power);
    void finishBlob();
    void writeBlob();

    void startCSG(string CSG);
    void finishCSG();
    string CSGUnion();
    string CSGIntersection();
    string CSGDifference();
    string CSGMerge();


    void setNextObjectPosFromVector(string name, string index);
    void createFullVectorArray(int n, string name, double x[], double y[], double z[]);

    void declareVectorArray(int n, string name);
    void addElementToVectorArray(double x, double y, double z);
    void closeVectorArray();

    void addRotationToNextObject(double x, double y, double z);
    void addRotationToNextObject(string name, string index);
    void writeRotation();
    void useRadians();
    void useDegrees();



    void write(string str);

    void closePOVRayWriter();



    





    void ambientLight(double I) {
    	writer << endl << endl << "global_settings { ambient_light rgb<"<<I<<", "<<I<<", "<<I<<"> }" << endl << endl;
    }

    void createSphereV(double r, const Vector3D& a) {

	    writer << "sphere {" << endl;
	
	    writeVector(a.x(), a.y(), a.z());
	    writer << r << endl;
		
    	    writer << "pigment {White}" << endl;	    
	    writer << "    finish { " << endl;
	    writer << "         ambient 1.0" << endl;
	    writer << "         diffuse 0.0" << endl;
	    writer << "    }" << endl;
	
	    writer << "}" << endl << endl;
	
	    return;
	}


    void createLight(const Vector3D& position, double r, double g, double b) {
	  writer << "light_source {" << endl;
	  writeVector(position.x(), position.y(), position.z());
	  writer << endl << "color rgb <" << r << ", " << g << ", " << b << ">" << endl;
	  writer << "} " << endl << endl;
	
	  return;
    }


    ////////////////////////////////////////
    //
    //		PARABOLA
    //
    ////////////////////////////////////////

    void drawParabola(const Parabola& parabola, string colorS, double width, int bound) {
    		
	//    	cout << "\n\n\n			Preparing to draw curve\n\n\n";
	    	for (int i = 0; i < bound; i++) {

                        //Cylinder(retI, retJ, width);
			Vector3D retI = Vector3D(parabola.getPoints(i));
			Vector3D retJ = Vector3D(parabola.getPoints(i+1));

			if (i+1 < parabola.getM())
                        	createStandardCylinder(retI.x(), retI.y(), retI.z(), retJ.x(), retJ.y(), retJ.z(), width, colorS);
				//createStandardSphere(width, retI.x(), retI.y(), retI.z(), colorS);


    		}//end i
    }

    ////////////////////////////////////////
    //ROTATION TECH ZONE////////////////////
    ////////////////////////////////////////
    //
    double pipi = 3.141592653589793238;

    double THETA, PHI, longitud;

    int equalRealS(double a, double b) {

    	int epsilon = 1e-20;
	double cc = (a - b) * (a - b);

	if (sqrt(cc) < epsilon)
		return 1;
	else
		return 0;
    }

    void sphericCoordinates(const Vector3D& a, const Vector3D& b) {

	Vector3D head = Vector3D(a.x(), a.y(), a.z());
	Vector3D base = Vector3D(b.x(), b.y(), b.z());
	Vector3D D = head - base;

	double longitud = abs(D);

	double X = D.x();
	double Y = D.y();
	double Z = D.z();

	if (equalRealS(X, 0.0) == 1) X = 0.000001;

	double YDX = Y/X;

	this->PHI = atan(YDX);
	this->THETA = acos(Z/longitud);

	//if (X < 0.0) THETA *= -1;
	//YZ = Matrix3D();
    }

    double anglePHI() {return this->PHI;};
    double angleTHETA() {return this->THETA;};
	
	Vector3D anglesVector3D(const Vector3D& a, const Vector3D& b) {
		
		Vector3D D = a - b;
                double longitud = abs(D);
                double X = D.x();
                double Y = D.z();
                double Z = D.y();

                if (equalRealS(X, 0.0) == 1) X = 0.00001;

                double YDX = Y/X;

                double anglePhi = atan(YDX);
                double angleTheta = acos(Z/longitud);

                if (X < 0.0) anglePhi += 3.14159265358979;

		return Vector3D(anglePhi, angleTheta, 0);
	}

    	Vector3D rotateVector3D2(const Vector3D& v, const Vector3D& head,const Vector3D& base) {
		
		Vector3D D = head - base;
		double longitud = abs(D);
		double X = D.x();
		double Y = D.z();
		double Z = D.y();

		if (equalRealS(X, 0.0) == 1) X = 0.00001;
		
		double YDX = Y/X;

		double anglePhi = atan(YDX);
		double angleTheta = acos(Z/longitud);

		if (X < 0.0) anglePhi += 3.14159265358979;
		

		//cout << "\n\n-->ABOUT TO ROTATE";

		//cout << v;
		//cout << "\n\nMATYZ(THETA) := " << angleTheta << "\n";
		
		Vector3D ret = Vector3D(
				(v.x() * cos(angleTheta)) + (-v.y() * sin(angleTheta)) + 0.0,
				(v.x() * sin(angleTheta)) + ( v.y() * cos(angleTheta)) + 0.0,
				               0.0        +                 0.0+ v.z()
				);


		//cout << "\n\nMATYZ(THETA) := " << anglePhi << "\n";
		ret = Vector3D(
                               (ret.x() * cos(anglePhi+pipi)) +     0.0 + (-ret.z() * sin(anglePhi+pipi)),
                                	         0.0     + ret.y() +                        0.0,
			       (ret.x() * sin(anglePhi+pipi)) +     0.0 + ( ret.z() * cos(anglePhi+pipi))
                                );

		ret = ret + base;
		//cout << ret;
		return ret;
	}







void texReaderBeta(
		const char * file_name, const Vector3D& A, 
		const Vector3D& B, string colorS, 
		int iC, int numScenes, double SIZE, 
		double sizeGlobal, const Vector3D& move,
		double rr, double gg, double bb
		) {
                
                //cout << "\n\n<<<<<<<<<<<<<<< POVray Tex Reader >>>>>>>>>>>>>>>>>>>\n";

                double IC = (double)iC;
                double numS = (double) numScenes;
                double sizeText = IC/numS + 0.000001;
                //cout << "\n----->Relative size of text := " << sizeText << endl;
                
                std::ifstream file;
                file = std::ifstream(file_name);
                file.clear();
                file.seekg(0);
                
                int i = 1, j = 0;
                int count = 0;
                int maxI = 0;
                int maxJ = 0;
                int dimI = 0;
                int dimJ = 0;
                //cout << "\n\n  -->Scan Function begins -------------------------------\n\n";

                while( file.peek() != EOF ){
    
    
                        int count00 = 0;
                        char c0;
                        char c1;
                        char c2;
                        
                        while (count00 < 3) {
                        
                            char lex = file.get();
                        
                            if (lex != ' '  && lex != '\n') { } else {

                                if(lex == '\n') {
                                    i += 1;
                                    dimI += 1;
                                }
                                break;
                            }               
                            count00 += 1;
                        }
    
                        if (count00 > 0) {
                            j += 1;
                            if (i == 1) dimJ += 1;
                        }
                }

                //cout << "\n-->dimI := " << dimI << "       dimJ := " << dimJ << endl;

                i = 1;
                j = 0;

                file.clear();
                file.seekg(0);
                
                while( file.peek() != EOF ){
    
    
                        int count00 = 0;
                        char c0;
                        char c1;
                        char c2;
                        
                        while (count00 < 3) {
                        
                            char lex = file.get();
                        
                            if (lex != ' '  && lex != '\n') {
                                if (count00 == 0) c0 = lex;
                                else {
                                    if (count00 == 1) c1 = lex;
                                    else c2 = lex;
                                }
                            } else {

                                //if (lex == ' ') cout << " ";
    
                                if(lex == '\n') {
                                    i += 1;
                                    maxI += 1;
                                    j = 0;
                                    //cout << "\n";
                                    //cout << "  --> i:= " << i << endl;
                                }
    
                                break;
                            }
                        
                                                
                            count00 += 1;
                        }
    
                        if (count00 > 0) {
    
                            char array[count00];
                            if (count00 == 1) {
                                //cout << c0 << "\n";////////////////////////////////////////////////////////////////////////
                                array[0] = c0;
                            }
                            if (count00 == 2) {
                                //cout << c0 << c1 << "\n";
                                array[0] = c0;
                                array[1] = c1;
                            }
                            if (count00 == 3) {
                                //cout << c0 << c1 << c2 << "\n";
                                array[0] = c0;
                                array[1] = c1;
                                array[2] = c2;
                            }
                            //string s = convertToString(array, count00);
    
                            string s = ""; 
                            for (int i = 0; i < count00; i++) { 
                                s = s + array[i]; 
                            }  
    
                            stringstream geek(s); 
                            int x = 0; 
                            geek >> x;
                            j += 1;
                            //cout << x;
                            //cout << "(" << maxI << ", " << j << ") ";
                            
                            if ((double)x < 1) {
				
				Vector3D I00 = Vector3D(
						-SIZE * ((double)i - 0.5*(double)dimI), 
						(double)x/765, 
						-SIZE * ((double)j - 0.5*(double)dimJ));
				I00 = sizeText * I00;
				I00 = I00 + move;
				I00 = rotateVector3D2(I00, A, B);
				createSphere( sizeGlobal, I00, rr, gg, bb);
				//drawSphereTrans(sizeGlobal, I00, rr, gg, bb, 0.0);
			    }


                            if (i == 1) maxJ += 1;
                        }
                }

                //cout << "\n-->maxI := " << maxI << "       maxJ := " << maxJ << endl;
            }


		void texReaderGamma(
                const char * file_name, const Vector3D& A,
                const Vector3D& B, string colorS,
                int iC, int numScenes, double SIZE,
                double sizeGlobal, const Vector3D& move,
                double rr, double gg, double bb,
		double exp, double ICC, double moveY) {
		//exp explode		ICC to transform	moveY to move through the Yaxis
                //cout << "\n\n<<<<<<<<<<<<<<< POVray Tex Reader >>>>>>>>>>>>>>>>>>>\n";

                double IC = (double)iC;
                double numS = (double) numScenes;
                double sizeText = IC/numS + 0.000001;
                //cout << "\n----->Relative size of text := " << sizeText << endl;

                std::ifstream file;
                file = std::ifstream(file_name);
                file.clear();
                file.seekg(0);

                int i = 1, j = 0;
                int count = 0;
                int maxI = 0;
                int maxJ = 0;
                int dimI = 0;
                int dimJ = 0;
                //cout << "\n\n  -->Scan Function begins -------------------------------\n\n";

                while( file.peek() != EOF ){


                        int count00 = 0;
                        char c0;
                        char c1;
                        char c2;

                        while (count00 < 3) {

                            char lex = file.get();

                            if (lex != ' '  && lex != '\n') { } else {

                                if(lex == '\n') {
                                    i += 1;
                                    dimI += 1;
                                }
                                break;
                            }
                            count00 += 1;
                        }

                        if (count00 > 0) {
                            j += 1;
                            if (i == 1) dimJ += 1;
                        }
                }

                //cout << "\n-->dimI := " << dimI << "       dimJ := " << dimJ << endl;

                i = 1;
                j = 0;

                file.clear();
                file.seekg(0);

                while( file.peek() != EOF ){


                        int count00 = 0;
                        char c0;
                        char c1;
                        char c2;

                        while (count00 < 3) {

                            char lex = file.get();

                            if (lex != ' '  && lex != '\n') {
                                if (count00 == 0) c0 = lex;
                                else {
                                    if (count00 == 1) c1 = lex;
                                    else c2 = lex;
                                }
                            } else {

                                //if (lex == ' ') cout << " ";

                                if(lex == '\n') {
                                    i += 1;
                                    maxI += 1;
                                    j = 0;
                                    //cout << "\n";
                                    //cout << "  --> i:= " << i << endl;
                                }

                                break;
                            }


                            count00 += 1;
                        }

                        if (count00 > 0) {

                            char array[count00];
                            if (count00 == 1) {
                                //cout << c0 << "\n";////////////////////////////////////////////////////////////////////////


			         array[0] = c0;
                            }
                            if (count00 == 2) {
                                //cout << c0 << c1 << "\n";
                                array[0] = c0;
                                array[1] = c1;
                            }
                            if (count00 == 3) {
                                //cout << c0 << c1 << c2 << "\n";
                                array[0] = c0;
                                array[1] = c1;
                                array[2] = c2;
                            }
                            //string s = convertToString(array, count00);

                            string s = "";
                            for (int i = 0; i < count00; i++) {
                                s = s + array[i];
                            }

                            stringstream geek(s);
                            int x = 0;
                            geek >> x;
                            j += 1;
                            //cout << x;
                            //cout << "(" << maxI << ", " << j << ") ";

                            if ((double)x < 1) {

                                Vector3D I00 = Vector3D(
                                                -SIZE * ((double)i - 0.5*(double)dimI),
                                                (double)x/765,
                                                -SIZE * ((double)j - 0.5*(double)dimJ));
                                I00 = sizeText * I00;
                                I00 = I00 + move;

				double radio = 0.4;
				Vector3D invCenter = Vector3D(0.0, 0.0, 0.0);
				double medida = abs(invCenter - I00);
				Vector3D U = ((1.0/medida) * I00);
				if (medida > radio){
					Vector3D transf = Vector3D(((radio*radio)/medida) * U);
					if (ICC < 0.25 * (double) numScenes)
						I00 = piecewiseVector(transf, I00, ICC, 0.25*(double)numScenes);
					else
						I00 = piecewiseVector(transf, I00, 0.25*(double)numScenes, 0.25*(double)numScenes);
				}
				//screen adjust///////////////////////////////////////////////////
                                
				I00 = exp * I00;
				I00 = rotateVector3D2(I00, A, B);
				I00 = I00 + Vector3D(0.0, 0.0, moveY);
                                createSphere( sizeGlobal, I00, rr, gg, bb);
                            }


                            if (i == 1) maxJ += 1;
                        }
                }

                //cout << "\n-->maxI := " << maxI << "       maxJ := " << maxJ << endl;
            }






		void disk(double theta, int m, Vector3D center, double R) {
			
			double divisionTheta = theta/(double) m;
			for (int i = 0; i < m; i++) {
				
				double angle = divisionTheta * (double) i;
				double angle1 = divisionTheta * (double) (i+1);
				Vector3D a = Vector3D(0.0, R * sin(angle), R * cos(angle)); 
				Vector3D b = Vector3D(0.0, R * sin(angle1), R * cos(angle1));
				
				a = a + center;
				b = b + center;	

				TriangleColor(center, a, b, 5, 0, 5);
			}

		}

		void digitalClock(const Vector3D& A, const Vector3D& B, double size, double ballSize, 
				const Vector3D& cameraCenter, double r, double g, double b, double seconds) {
			
			int count = 0;
			int cycle = 0;
			int secondsUnidades = 0;
			int secondsDecimas = 0;
			int minutes = 0;

			//cout << "\n\n-->Clock\n\n";
			while (cycle < seconds) {
				
				secondsUnidades++;
				
				if (secondsUnidades > 9) {
					secondsUnidades = 0;
					secondsDecimas++;
				}

				if (secondsDecimas > 5) {
					secondsDecimas = 0;
					minutes++;
				}

				cycle++;
			}

			//cout << "       " << minutes << ":" << secondsDecimas << secondsUnidades << "\n";	
			string min = "0101" + to_string(minutes) + ".txt";
			string space = "0101:.txt";
			string secD = "0101" + to_string(secondsDecimas) + ".txt";
			string secU = "0101" + to_string(secondsUnidades) + ".txt";
			
			const char *M = min.c_str();
			const char *S = space.c_str();
			const char *sD = secD.c_str();
			const char *sU = secU.c_str();
			
			//texReaderBeta("0101t.txt",  A, B, "Blue",
                        //        160, 160, size, ballSize, cameraCenter + Vector3D(0.0, 0.0, 0.0335), 7, 0, 0);
			//texReaderBeta("0101=.txt",  A, B, "Blue",
                        //        160, 160, size, ballSize, cameraCenter + Vector3D(0.0, 0.0, 0.02), 7, 0, 0);
			texReaderBeta(M,  A, B, "Blue",
                                160, 160, size, ballSize, cameraCenter, 7, 0, 0);
			texReaderBeta(S,  A, B, "Blue",
                                160, 160, size, ballSize, cameraCenter + Vector3D(0.0, 0.0,-0.01), 7, 0, 0);
			texReaderBeta(sD,  A, B, "Blue",
                                160, 160, size, ballSize, cameraCenter + Vector3D(0.0, 0.0,-0.02), 7, 0, 0);
			texReaderBeta(sU,  A, B, "Blue",
                                160, 160, size, ballSize, cameraCenter + Vector3D(0.0, 0.0,-0.032), 7, 0, 0);
		}

		void Cone(const Vector3D& A, const Vector3D& B, double rU, double rD,double r, double b, double g) {


			string u = to_string(rU);
			string d = to_string(rD);
			writer << "cone {" << endl;
    			writeVector(A.x(), A.y(), A.z()); writer << "," << u  << endl;
    			writeVector(B.x(), B.y(), B.z()); writer << "," << d  << endl;
    			Paint(r, g, b);
  			writer << "}" << endl;


		}

		void flecha(const Vector3D& a, const Vector3D& b, double grosor, int R, int G, int Bb) {
			
			if (abs(a-b) > 0.01) {
				CylinderI( 0.8 * (a-b) + b, b, grosor, R, G, Bb);
				Cone(a, 0.8 * (a-b) + b, 0.0001, 2.0 * grosor, R, Bb, G);
			}
		}

		Vector3D flechaD(const Vector3D& a, const Vector3D& b, double grosor, int R, int G, int Bb) {

                        if (abs(a-b) > 1e-20) {
                                //CylinderI( 0.8 * (a-b) + b, b, grosor, R, G, Bb);

				for (int i = 0; i < 10; i++) {
					Vector3D at0 = piecewiseVector(0.8 * (a-b) + b, b, i, 10);
					drawSphereTrans(grosor, at0, R, G, Bb, 0.0);				
				}
                                Cone(a, 0.8 * (a-b) + b, 0.0001, 2.0 * grosor, R, Bb, G);
                        }

			Vector3D ret = 0.5 * ((0.8 * (a-b) + b) - b);
			return ret;
                }

		Vector3D flechaDRot(const Vector3D& a, const Vector3D& b, double grosor, 
				int R, int G, int Bb, const Vector3D& a0, const Vector3D& b0, const Vector3D& c) {
		
			if (abs(a-b) > 1e-20) {
                                //CylinderI( 0.8 * (a-b) + b, b, grosor, R, G, Bb);
				Vector3D A = rotateVector3D2(a+c, a0, b0);
                                Vector3D B = rotateVector3D2(b+c, a0, b0);
                                for (int i = 0; i < 20; i++) {
                                        Vector3D at0 = piecewiseVector(A, B, i, 10);
                                        drawSphereTrans(grosor, at0, R, G, Bb, 0.0);
                                }
                        }

                        Vector3D ret = 0.5 * ((0.8 * (a-b) + b) - b);
                        return ret;

                }

		Vector3D flechaDRot2(const Vector3D& a, const Vector3D& b, double grosor,
                                int R, int G, int Bb, const Vector3D& a0, 
				const Vector3D& b0, const Vector3D& c, int at) {
			
			Vector3D A = rotateVector3D2(a+c, a0, b0);
                        Vector3D B = rotateVector3D2(b+c, a0, b0);
			Vector3D ret;
                        if (abs(A-B) > 1e-20) {
                                //CylinderI( 0.8 * (a-b) + b, b, grosor, R, G, Bb);
                                Vector3D A = rotateVector3D2(a+c, a0, b0);
                                Vector3D B = rotateVector3D2(b+c, a0, b0);
                                for (int i = 0; i < 20; i++) {
                                        Vector3D at0 = piecewiseVector(A, B, i, 10);
					if (i == at) {
						drawSphereTrans(2.5 * grosor, at0, R, R, R, 0.0);
						ret = Vector3D(at0);
					} else drawSphereTrans(grosor, at0, R, G, Bb, 0.0);
                                }

                        }

                        return ret;

                }

		double piecewiseNumber(double a, double b, double iC, double numScene) {
			
			double time = iC/numScene;
			return (time * (a-b)) + b;
		}

		Vector3D piecewiseVector(const Vector3D& a, const Vector3D& b, double iC, double numScene) {
			return ((iC/numScene) * (a-b)) + b;
		}


		void TILEFLOOR3(int iC, int numScene, double param, double elevation, double trans) {

      			double t = param;	

        		writer << "polygon {" << endl;
              		writer << "3" << endl;
              		writer << "<"<< t <<", " << elevation <<", "<< t <<">   <-"<< t <<", "<< elevation <<", "<< t <<">   <-"<< t <<", "<<elevation <<", -"<< t <<">" << endl;
              		writer << "	texture {  " << endl;
              		writer << "     	pigment{ checker color<5, 5, 5> transmit "<<trans<<" Black transmit "<<trans<<" scale 0.5" << endl;  
			writer << "			 scale 5 " << endl;
			writer << "			}" << endl;
              		writer << "		finish {" << endl;
          		writer << "   			ambient .1" << endl;
          		writer << "   			diffuse .1" << endl;
          		writer << "   			specular 1" << endl;
          		writer << "   			roughness .001" << endl;
          		writer << "   			phong 1" << endl;
          		writer << "   			reflection {" << endl;
          		writer << "             		0.1" << endl;
          		writer << "   			}" << endl;
         	 	writer << "		}" << endl;
              		writer << "	} " << endl;

			writer << "}" << endl;

        		writer << "  polygon {" << endl;
            		writer << "  3" << endl;
            		writer << "  <-"<< t <<", "<<elevation<<", -"<< t <<">   <"<< t <<", "<<elevation<< ", -"<< t <<">   <"<< t <<", "<<elevation<<", "<< t <<">   " << endl;
            		writer << "texture {  " << endl;
              		//writer << "    pigment{ checker color <5, 5, 5> Black scale 0.5} " << endl;
			
			writer << "             pigment{ checker color<5, 5, 5> transmit "<<trans<<" Black transmit "<<trans<<" scale 0.5" << endl;
                        writer << "                      scale 5 " << endl;
                        writer << "                     }" << endl;
			
			writer << "finish {" << endl;
          		writer << "   ambient .1" << endl;
          		writer << "   diffuse .1" << endl;
          		writer << "   specular 1" << endl;
          		writer << "   roughness .001" << endl;
          		writer << "   phong 1" << endl;
          		writer << "   reflection {" << endl;
          		writer << "                 0.1" << endl;
          		writer << "   }" << endl;
          		writer << "}" << endl;
              		writer << "  } " << endl;
			

        		writer << "}" << endl;
			
    		}

	void spaceCurve(int m, double R, Vector3D center, double width, string colorS, int timeI, double up) {
  		
		double r = 1;
		double pipi = 3.14159265358979;
		double anglePhi = 0.0;
		
		double bar = (double) m / 2;
  		for (int i = (m-1) - timeI; i < m; i++) {

      			double length = 2*pipi;
      			double sublength1 = length/m;
			
			int I = i - (m/2);
      			double u0 = (I + (0.0)) * sublength1;
      			double u1 = (I + (1.0)) * sublength1;

      			Vector3D v[2] = {
        			Vector3D(u0, -R*u0*u0 + up, 0.0),
        			Vector3D(u1, -R*u1*u1 + up, 0.0)
      			};

			///On ths part of the code we can perform any action on the curve.
			//ROTATION WITH RESPECT TO THE Y AXIS
			//

			Vector3D retI = Vector3D(v[0]);
			Vector3D retJ = Vector3D(v[1]);

			retI = 0.15 * retI;
			retJ = 0.15 * retJ;


      			//Cylinder(retI, retJ, width);
			createStandardCylinder(retI.x(), retI.y(), retI.z(), retJ.x(), retJ.y(), retJ.z(), width, colorS);

  		}//end i

	}

	void drawGreatCircle(const GreatCircle& circle, double width, int R, int G, int B) {
	
		for (int i = 0; i < circle.getM(); i++) {

			if (i < circle.getM() - 1)
				CylinderI(circle.getR(i), circle.getR(i+1), width, R, G, B);
			if (i == circle.getM()-1)
				CylinderI(circle.getR(i), circle.getR(0), width, R, G, B);
		}
	}
	
	void drawCubeQ(const CubeQ& dodeca, int R, int G, int B, const Vector3D& position1) {
		
		double width = 0.02 * dodeca.getRadius();
		CylinderI(dodeca.getQ(0 ),  dodeca.getQ(1 ), width, R, G, B);
		CylinderI(dodeca.getQ(1 ),  dodeca.getQ(2 ), width, R, G, B);
		CylinderI(dodeca.getQ(2 ),  dodeca.getQ(3 ), width, R, G, B);
		CylinderI(dodeca.getQ(3 ),  dodeca.getQ(0 ), width, R, G, B);

		CylinderI(dodeca.getQ(0 ),  dodeca.getQ(4 ), width, R, G, B);
		CylinderI(dodeca.getQ(1 ),  dodeca.getQ(5 ), width, R, G, B);
		CylinderI(dodeca.getQ(2 ),  dodeca.getQ(6 ), width, R, G, B);
		CylinderI(dodeca.getQ(3 ),  dodeca.getQ(7 ), width, R, G, B);

		CylinderI(dodeca.getQ(4 ),  dodeca.getQ(5 ), width, R, G, B);
		CylinderI(dodeca.getQ(5 ),  dodeca.getQ(6 ), width, R, G, B);
		CylinderI(dodeca.getQ(6 ),  dodeca.getQ(7 ), width, R, G, B);
		CylinderI(dodeca.getQ(7 ),  dodeca.getQ(4 ), width, R, G, B);
	
	
		double rr = 0.1;
                texReaderBeta("01010.txt", position1, 1.15 * dodeca.getQ(0), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, 1.15 * dodeca.getQ(1), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01012.txt", position1, 1.15 * dodeca.getQ(2), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01013.txt", position1, 1.15 * dodeca.getQ(3), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01014.txt", position1, 1.15 * dodeca.getQ(4), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01015.txt", position1, 1.15 * dodeca.getQ(5), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01016.txt", position1, 1.15 * dodeca.getQ(6), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01017.txt", position1, 1.15 * dodeca.getQ(7), "Blue",
                                               rr*dodeca.getRadius()*1000, dodeca.getRadius()*1000, 0.00064, 0.001, Vector3D(0, 0, 0), 0, 0, 7);
	}	
	
	void drawDodecahedron(const Dodecahedron& dodeca, int R, int G, int B, const Vector3D& position1) {

		double width = 0.02 * dodeca.getRadius();
    		
		cout << "\n-->START";
		CylinderI(dodeca.getQ(9 ),  dodeca.getQ(8 ), width, R, G, B);
    		CylinderI(dodeca.getQ(8 ),  dodeca.getQ(12), width, R, G, B);
    		CylinderI(dodeca.getQ(12),  dodeca.getQ(11), width, R, G, B);
    		CylinderI(dodeca.getQ(11),  dodeca.getQ(10), width, R, G, B);
    		CylinderI(dodeca.getQ(10),  dodeca.getQ(9 ), width, R, G, B);
    		CylinderI(dodeca.getQ(14),  dodeca.getQ(13), width, R, G, B);/////a
    		CylinderI(dodeca.getQ(13),  dodeca.getQ(8 ), width, R, G, B);
    		CylinderI(dodeca.getQ(9 ),  dodeca.getQ(15), width, R, G, B);
    		CylinderI(dodeca.getQ(15),  dodeca.getQ(14), width, R, G, B);
    		CylinderI(dodeca.getQ(10),  dodeca.getQ(18), width, R, G, B);
    		CylinderI(dodeca.getQ(18),  dodeca.getQ(17), width, R, G, B);
    		CylinderI(dodeca.getQ(17),  dodeca.getQ(15), width, R, G, B);
    		CylinderI(dodeca.getQ(11),  dodeca.getQ(5 ), width, R, G, B);
    		CylinderI(dodeca.getQ(5 ),  dodeca.getQ(7 ), width, R, G, B);
    		CylinderI(dodeca.getQ(7 ),  dodeca.getQ(18), width, R, G, B);
    		CylinderI(dodeca.getQ(16),  dodeca.getQ(6 ), width, R, G, B);/////f
    		CylinderI(dodeca.getQ(6 ),  dodeca.getQ(5 ), width, R, G, B);
    		CylinderI(dodeca.getQ(5 ),  dodeca.getQ(11), width, R, G, B);
    		CylinderI(dodeca.getQ(12),  dodeca.getQ(16), width, R, G, B);
    		CylinderI(dodeca.getQ(13),  dodeca.getQ(19), width, R, G, B);/////c
    		CylinderI(dodeca.getQ(19),  dodeca.getQ(16), width, R, G, B);
    		CylinderI(dodeca.getQ(12),  dodeca.getQ(8 ), width, R, G, B);
    		CylinderI(dodeca.getQ(0 ),  dodeca.getQ(1 ), width, R, G, B);/////w3
    		CylinderI(dodeca.getQ(6 ),  dodeca.getQ(0 ), width, R, G, B);//
    		CylinderI(dodeca.getQ(7 ),  dodeca.getQ(1 ), width, R, G, B);/////w4
    		CylinderI(dodeca.getQ(17),  dodeca.getQ(2 ), width, R, G, B);
    		CylinderI(dodeca.getQ(1 ),  dodeca.getQ(2 ), width, R, G, B);
    		CylinderI(dodeca.getQ(18),  dodeca.getQ(7 ), width, R, G, B);
    		CylinderI(dodeca.getQ(19),  dodeca.getQ(4 ), width, R, G, B);
    		CylinderI(dodeca.getQ(4 ),  dodeca.getQ(0 ), width, R, G, B);//
    		CylinderI(dodeca.getQ(4 ),  dodeca.getQ(3 ), width, R, G, B);//
    		CylinderI(dodeca.getQ(3 ),  dodeca.getQ(2 ), width, R, G, B);//
    		CylinderI(dodeca.getQ(3 ),  dodeca.getQ(14), width, R, G, B);
		
		//facetGlass2(dodeca.getQ(19), dodeca.getQ(14 ), dodeca.getQ(3 ));
		//facetGlass2(dodeca.getQ(19), dodeca.getQ(13), dodeca.getQ(14));
		//facetGlass2(dodeca.getQ(19), dodeca.getQ( 4), dodeca.getQ( 3));

		//facetGlass2(dodeca.getQ(19), dodeca.getQ(13), dodeca.getQ(8 ));
		//facetGlass2(dodeca.getQ(19), dodeca.getQ(8 ), dodeca.getQ(12));
		//facetGlass2(dodeca.getQ(19), dodeca.getQ(12), dodeca.getQ(16));

		//facetGlass2(dodeca.getQ(4 ), dodeca.getQ(19 ), dodeca.getQ(16));
		//facetGlass2(dodeca.getQ(16), dodeca.getQ(0 ), dodeca.getQ(4 ));
		//facetGlass2(dodeca.getQ(0 ), dodeca.getQ(16), dodeca.getQ(6 ));

		//facetGlass2(dodeca.getQ(0 ), dodeca.getQ(2 ), dodeca.getQ(3 ));
		//facetGlass2(dodeca.getQ(0 ), dodeca.getQ(1 ), dodeca.getQ(2 ));
		//facetGlass2(dodeca.getQ(0 ), dodeca.getQ(3 ), dodeca.getQ(4 ));

		//facetGlass2(dodeca.getQ(2 ), dodeca.getQ(17 ), dodeca.getQ(15));
		//facetGlass2(dodeca.getQ(2 ), dodeca.getQ(15), dodeca.getQ(14));
		//facetGlass2(dodeca.getQ(2 ), dodeca.getQ(14 ), dodeca.getQ(3 ));
		//
		//facetGlass2(dodeca.getQ(12), dodeca.getQ(13), dodeca.getQ(14));
                //facetGlass2(dodeca.getQ(12), dodeca.getQ(14), dodeca.getQ(15));
                //facetGlass2(dodeca.getQ(12), dodeca.getQ(15), dodeca.getQ(9 ));
		//
		//facetGlass2(dodeca.getQ(5 ), dodeca.getQ(6 ), dodeca.getQ(12));
		//facetGlass2(dodeca.getQ(11), dodeca.getQ(5 ), dodeca.getQ(12));
		//facetGlass2(dodeca.getQ(6 ), dodeca.getQ(16), dodeca.getQ(12));
		//
		//facetGlass2(dodeca.getQ(8 ), dodeca.getQ(9 ), dodeca.getQ(12));
		//facetGlass2(dodeca.getQ(9 ), dodeca.getQ(10), dodeca.getQ(12));
		//facetGlass2(dodeca.getQ(10 ), dodeca.getQ(11), dodeca.getQ(12));

		//facetGlass2(dodeca.getQ(9 ), dodeca.getQ(15), dodeca.getQ(10));
                //facetGlass2(dodeca.getQ(15), dodeca.getQ(17), dodeca.getQ(10));
                //facetGlass2(dodeca.getQ(17 ), dodeca.getQ(18), dodeca.getQ(10));

		//facetGlass2(dodeca.getQ(18), dodeca.getQ( 7), dodeca.getQ(10));
                //facetGlass2(dodeca.getQ(7 ), dodeca.getQ( 5), dodeca.getQ(10));
                //facetGlass2(dodeca.getQ(5 ), dodeca.getQ(11), dodeca.getQ(10));

		//facetGlass2(dodeca.getQ(18), dodeca.getQ(17), dodeca.getQ(2 ));
                //facetGlass2(dodeca.getQ(7 ), dodeca.getQ(18), dodeca.getQ(2 ));
                //facetGlass2(dodeca.getQ(1 ), dodeca.getQ(7 ), dodeca.getQ(2 ));

		//facetGlass2(dodeca.getQ(0 ), dodeca.getQ(7 ), dodeca.getQ(1 ));
                //facetGlass2(dodeca.getQ(0 ), dodeca.getQ(5 ), dodeca.getQ(7 ));
                //facetGlass2(dodeca.getQ(0 ), dodeca.getQ(6 ), dodeca.getQ(5 ));
		
		cout << "START2";
		double rr = 1;
		double size = 0.000075;
		double globalSize = 0.0001;

		double a = 1.2;
		texReaderBeta("01010.txt", position1, (a * (dodeca.getQ(0) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);
		
		texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(1) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01012.txt", position1, (a * (dodeca.getQ(2) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01013.txt", position1, (a * (dodeca.getQ(3) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01014.txt", position1, (a * (dodeca.getQ(4) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01015.txt", position1, (a * (dodeca.getQ(5) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01016.txt", position1, (a * (dodeca.getQ(6) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01017.txt", position1, (a * (dodeca.getQ(7) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01018.txt", position1, (a * (dodeca.getQ(8) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01019.txt", position1, (a * (dodeca.getQ(9) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

		texReaderBeta("01010.txt", position1, (a * (dodeca.getQ(10) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);
		
		texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(10) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);


		texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(11) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(11) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);



		texReaderBeta("01012.txt", position1, (a * (dodeca.getQ(12) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(12) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);



		texReaderBeta("01013.txt", position1, (a * (dodeca.getQ(13) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(13) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);


		texReaderBeta("01014.txt", position1, (a * (dodeca.getQ(14) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(14) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);


		texReaderBeta("01015.txt", position1, (a * (dodeca.getQ(15) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(15) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);


		texReaderBeta("01016.txt", position1, (a * (dodeca.getQ(16) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(16) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);


		texReaderBeta("01017.txt", position1, (a * (dodeca.getQ(17) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(17) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);


		texReaderBeta("01018.txt", position1, (a * (dodeca.getQ(18) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(18) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);


		texReaderBeta("01019.txt", position1, (a * (dodeca.getQ(19) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0), 0, 0, 7);

                texReaderBeta("01011.txt", position1, (a * (dodeca.getQ(19) - dodeca.getCenter())) + dodeca.getCenter(), "Blue",
                                               1.0, 1.0, size, globalSize, Vector3D(0, 0, 0.0025), 0, 0, 7);

		cout << "\nEND\n";
	}

	void drawIntersectionC(Intersection intersection, int R, int G, int B, const Facet& facet, FacetBox * pila) {
		
                        Vector3D A0 = Vector3D(facet.getA().V());
                        Vector3D B0 = Vector3D(facet.getB().V());
                        Vector3D C0 = Vector3D(facet.getC().V());

                        Vector3D J = Vector3D(0, 1, 0);
                        Quaternion QJ = Quaternion(0.0, J);
                        int aa = intersection.checkPoint(A0, QJ);
                        int bb = intersection.checkPoint(B0, QJ);
                        int cc = intersection.checkPoint(C0, QJ);	

			if (aa == 1 && bb == 1 && cc == 1) {
				//drawFacet(A0, B0, C0, R, G, B, 0.0);
				pila->pushFacet(A0, B0, C0);
			}	
		//	pila.pushFacet(A0, B0, C0);
	}

	void drawIntersection(Intersection intersection, int R, int G, int B, const Vector3D& position1) {
		
		drawPlaneQuaternion(intersection.getSaw(), 0.1, 3, 0, 0);
		
	}

	int  linePointIntersection(const Vector3D& r, const Vector3D& a, const Vector3D& b) {
		
		Vector3D cro = (a-r) % (b-r); 
		if (cro == Vector3D(0, 0, 0)) return 1;
		else return 0;
	}

	void auxFun(const Vector3D& position1, Intersection intersection, int a, int b, int aa, int bb, int cc, int R, int G, int B, int i, const Vector3D& A0, const Vector3D& B0, const Vector3D& C0, FacetBox * pila ) {
		
				CylinderI(intersection.getM(i, a).V(), intersection.getM(i, b).V(), 0.0005, R, G, B);
				
			       	Vector3D r0 = Vector3D(intersection.getM(i, a).V());
				Vector3D r1 = Vector3D(intersection.getM(i, b).V());	
				
							if (aa == 1 && bb == 0 && cc == 0) {
								pila->pushFacet(r0, r1, A0);
							}	

							if (aa == 0 && bb == 1 && cc == 0) {
								pila->pushFacet(r0, r1, B0);
							}

							if (aa == 0 && bb == 0 && cc == 1) {
								pila->pushFacet(r0, r1, C0);
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


	void checkR (const Vector3D& r0, const Vector3D& r1, const Vector3D& A0, const Vector3D& B0, const Vector3D& C0, FacetBox * pila) {
								
								int l = linePointIntersection(r0, B0, A0);
                                                                int l0 = linePointIntersection(r0, C0, A0);

                                                                if ( l == 1) {

									pila->pushFacet(r0, B0, C0);
									pila->pushFacet(C0, r1, r0);
                                                                }

                                                                if ( l0 == 1) {
									
									pila->pushFacet(r1, B0, C0);
									pila->pushFacet(C0, r1, r0);
                                                                }
	}	

	void drawE(const Quaternion& p, const Quaternion& normal, const Quaternion& J) {
		
		Quaternion Tau = cross(normal, J);
                Vector3D tau = unit(unit(normal.V()) % unit(J.V()));
                double phi = acos(unit(normal.V()) * unit(J.V()));

                Quaternion tauQ = Qan(phi, tau);
		//flecha(2.0 * tauQ.V(), Vector3D(0, 0, 0), 0.001, 0, 0, 6);
		//flecha(0.025 * normal.V(), Vector3D(0, 0, 0), 0.0005, 0, 6, 0);
		//flecha(p.V(), Vector3D(0, 0, 0), 0.0005, 6, 0, 6);
                Quaternion p0 = tauQ * p * tauQ.conjugate();
	
		//flecha(p0.V(), Vector3D(0, 0, 0), 0.0005, 7, 7, 7);
		drawSphereTrans(0.001, p0.V(), 6, 0, 0, 0.0);
		drawSphereTrans(0.001, p.V(),  6, 0, 6, 0.0);	
	}


	void drawPlaneQuaternion(PlaneQuaternion plane, double width, int R, int G, int B) {
		
		Vector3D p = Vector3D(0.1, 0, 0);
		int i0 = 2;

			Vector3D center = Vector3D(0, 0, 0);
			//flecha(plane.getPoint(), center, 0.015, 0, 0, 6);
			double f = 0.1 * abs(plane.getNormal().V() - plane.getBase());
			flecha( plane.getNormal().V() + plane.getBase(), plane.getBase(), 0.25 * f, 7, 0, 7);
			flecha(-plane.getNormal().V() + plane.getBase(), plane.getBase(), 0.25 * f, 7, 0, 7);	
			for (int j = 1; j < 20; j++) {
			
				double jump = (2 * 3.1415)/ (20*j);
				for (int i = 0; i < j*20; i++) {
					Quaternion rotAux = Qan(i * jump, plane.getNormal().V());
					//flecha(rotAux.V(), center, 0.015, 6, 0, 6);
					
					Quaternion P = rotAux.conjugate() * Quaternion(0, 0.005 * j * unit(plane.getPoint())) * rotAux;
					P = P + Quaternion(0, plane.getBase());
					//drawSphereTrans(0.0004, P.V(), 6, 6, 6, 0.0);
				
					if (i < j*20-1 && j == 5) {
						
						Quaternion rotAux0 = Qan((i+1) * jump, plane.getNormal().V());
	                                        //flecha(rotAux.V(), center, 0.015, 6, 0, 6);

        	                                Quaternion P1 = rotAux0.conjugate() * Quaternion(0, 0.005 * j * unit(plane.getPoint())) * rotAux0;
                	                        P1 = P1 + Quaternion(0, plane.getBase());
						
						drawFacet(P1, P, plane.getBase(), 7, 0, 7, 0.5);

					}

				}
			}

        }

	void drawPlaneQuaternionTIME(PlaneQuaternion plane, const Vector3D& point, double width, int R, int G, int B, int time) {

                Vector3D p = Vector3D(0.1, 0, 0);
                int i0 = 2;

                        Vector3D center = Vector3D(0, 0, 0);
                        flecha(plane.getNormal().V(), plane.getPoint(), 0.015, 7, 0, 0);

			time = time % 96;
			double tt = 96/10;
                        for (int j = 3; j < 4; j++) {

                                double jump = (2 * 3.1415)/ (tt*j);
                                for (int i = 0; i < 96; i++) {
					if (i == time) {
                                        Quaternion rotAux = Qan(i * jump, plane.getNormal().V());
                                        //flecha(rotAux.V(), center, 0.015, 6, 0, 6);

                                        Quaternion P = rotAux.conjugate() * Quaternion(0, 0.019 * j * unit(plane.getPoint())) * rotAux;
                                        P = P + Quaternion(0, point);
                                        drawSphereTrans(0.03, P.V(), 7, 0, 0, 0.0);
					drawSphereTrans(0.03, point, 7, 0, 0, 0.0);
					flecha(P.V(), point, 0.015, 7, 0, 0);
					}
                                }
                        }



			for (int j = 1; j < 10; j++) {

                                double jump = (2 * 3.1415)/ (tt*j);
                                for (int i = 0; i < 96; i++) {
                                        Quaternion rotAux = Qan(i * jump, plane.getNormal().V());
                                        //flecha(rotAux.V(), center, 0.015, 6, 0, 6);

                                        Quaternion P = rotAux.conjugate() * Quaternion(0, 0.019 * j * unit(plane.getPoint())) * rotAux;
                                        P = P + Quaternion(0, point);
                                        drawSphereTrans(0.01, P.V(), 7, 7, 7, 0.0);
                                }
                        }

        }

	//anglesVector3D(const Vector& a, const Vector3D& b)

	void greatCircle(int m, double R, const Quaternion& center, const Quaternion& axe, double width, int RR, int B, int G) {

                double r = 1;
                double pipi = 3.14159265358979;
                double anglePhi = 0.0;

                double bar = (double) m / 2;
                for (int i = 0; i < m; i++) {

                        double length = 2*pipi;
                        double sublength1 = length/m;

                        double u0 = (i + (0.0)) * sublength1;
                        double u1 = (i + (1.0)) * sublength1;

                        Vector3D v[2] = {
                                Vector3D(R * cos(u0), 0.0, R * sin(u0)),
                                Vector3D(R * cos(u1), 0.0, R * sin(u1))
                        };

                        ///On ths part of the code we can perform any action on the curve.
                        //ROTATION WITH RESPECT TO THE Y AXIS
                        //

			Quaternion quat  = Quaternion(0.0, v[0]);
			Quaternion quat0 = Quaternion(0.0, v[1]);
			
			quat  = axe.conjugate() * quat * axe;
			quat0 = axe.conjugate() * quat0 * axe;

			CylinderI(quat0.V(), quat.V(), width, RR, G, B);
                }//end i

        }



	void spaceCurveMorf(int m, double R, Vector3D center, double width, string colorS, double iC, double numScene, int initState, int metaState) {

                double r = 1;
                double pipi = 3.14159265358979;
                double anglePhi = 0.0;
		Vector3D arrow;
                double bar = (double) m / 2;
                for (int i = 0; i < m; i++) {
                        double length = 2*pipi;
                        double sublength1 = length/m;
                        double u0 = (i + (0.0)) * sublength1;
                        double u1 = (i + (1.0)) * sublength1;
			Vector3D state[3][2];
                        state[0][0] = Vector3D(u0-3.14, 0.0, 1.0 * sin(5*u0));
                        state[0][1] = Vector3D(u1-3.14, 0.0, 1.0 * sin(5*u1));
			
			state[1][0] = Vector3D(u0-3.14, (1.0 * cos(3 * u0)) - 1.0, 1.0 * sin(5*u0));
                        state[1][1] = Vector3D(u1-3.14, (1.0 * cos(3 * u1)) - 1.0, 1.0 * sin(5*u1));
			
			state[2][0] = Vector3D(u0-3.14, 2.0 * cos(3 * u0) * sin(4*u0), 1.0 * sin(5*u0));
                        state[2][1] = Vector3D(u1-3.14, 2.0 * cos(3 * u1) * sin(4*u1), 1.0 * sin(5*u1));

                        ///On ths part of the code we can perform any action on the curve.
                        //ROTATION WITH RESPECT TO THE Y AXIS
                        //
			//
			//MORF
			//
			int ii = initState%3;
			int jj = metaState%3;
		
			Vector3D retI = piecewiseVector(state[jj][0], state[ii][0], iC, numScene);
			Vector3D retJ = piecewiseVector(state[jj][1], state[ii][1], iC, numScene);

			//ROTATE
                        retI = Vector3D(
                               (retI.x() * cos(anglePhi*pipi)) +     0.0 + (-retI.z() * sin(anglePhi*pipi)),
                                                 0.0     + retI.y() +                        0.0,
                               (retI.x() * sin(anglePhi*pipi)) +     0.0 + ( retI.z() * cos(anglePhi*pipi))
                        );
                        retJ = Vector3D(
                               (retJ.x() * cos(anglePhi*pipi)) +     0.0 + (-retJ.z() * sin(anglePhi*pipi)),
                                                 0.0     + retJ.y() +                        0.0,
                               (retJ.x() * sin(anglePhi*pipi)) +     0.0 + ( retJ.z() * cos(anglePhi*pipi))
                        );
                        retI = 0.15 * retI;
                        retJ = 0.15 * retJ;

			if (i == (int)iC)
				arrow = Vector3D(retI);
                        //Cylinder(retI, retJ, width);
                        createStandardCylinder(retI.x(), retI.y(), retI.z(), retJ.x(), retJ.y(), retJ.z(), width, colorS);
			//flecha(Vector3D(retI.x(), retI.y(), retI.z()), Vector3D(0.0, 0.0, 0.0), 0.015, 6, 0, 0);
                }//end i

		//flecha(arrow, Vector3D(0.0, 0.0, 0.0), 0.015, 6, 0, 0);
        }


	void scene8(int m, double R, Vector3D center, double width, string colorS, double iC, double numScene, int initState, int metaState) {

                double r = 1;
                double pipi = 3.14159265358979;
                double anglePhi = 0.0;
		Vector3D arrowTrack[m];

                double bar = (double) m / 2;
                for (int i = 0; i < m; i++) {
                        double length = 2*pipi;
                        double sublength1 = length/m;
                        double u0 = (i + (0.0)) * sublength1;
                        double u1 = (i + (1.0)) * sublength1;
                        Vector3D state[3][2];
                        state[0][0] = Vector3D(u0-3.14, 0.0, 1.0 * sin(5*u0));
                        state[0][1] = Vector3D(u1-3.14, 0.0, 1.0 * sin(5*u1));

                        state[1][0] = Vector3D(u0-3.14, (1.0 * cos(3 * u0)) - 1.0, 1.0 * sin(5*u0));
                        state[1][1] = Vector3D(u1-3.14, (1.0 * cos(3 * u1)) - 1.0, 1.0 * sin(5*u1));

                        state[2][0] = Vector3D(u0-3.14, 2.0 * cos(3 * u0) * sin(4*u0), 1.0 * sin(5*u0));
                        state[2][1] = Vector3D(u1-3.14, 2.0 * cos(3 * u1) * sin(4*u1), 1.0 * sin(5*u1));

                        int ii = initState%3;
                        int jj = metaState%3;
                        Vector3D retI = piecewiseVector(state[jj][0], state[ii][0], iC, numScene);
                        retI = 0.15 * retI;

			arrowTrack[i] = Vector3D(retI);
                }//end i


		flecha(arrowTrack[(int) iC], Vector3D(0.0, 0.0, 0.0), 0.015, 6, 0, 0);
        }


	void parabola(int m, Vector3D center, double width, string colorS, int timeI) {

                double r = 1;
                double pipi = 3.14159265358979;
                double anglePhi = 0.0;

                double bar = (double) m / 2;
                for (int i =-bar; i < -bar + timeI; i++) {

                        double length = 2*pipi;
                        double sublength1 = length/m;

                        double u0 = (i + (0.0)) * sublength1;
                        double u1 = (i + (1.0)) * sublength1;

                        Vector3D v[2] = {
                                Vector3D(u0, 0.0, (0.5*u0*u0) - 5.0),
                                Vector3D(u1, 0.0, (0.5*u1*u1) - 5.0)
                        };

                        ///On ths part of the code we can perform any action on the curve.
                        //ROTATION WITH RESPECT TO THE Y AXIS
                        //

                        Vector3D retI = Vector3D(
                               (v[0].x() * cos(anglePhi*pipi)) +     0.0 + (-v[0].z() * sin(anglePhi*pipi)),
                                                 0.0     + v[0].y() +                        0.0,
                               (v[0].x() * sin(anglePhi*pipi)) +     0.0 + ( v[0].z() * cos(anglePhi*pipi))
                        );

                        Vector3D retJ = Vector3D(
                               (v[1].x() * cos(anglePhi*pipi)) +     0.0 + (-v[1].z() * sin(anglePhi*pipi)),
                                                 0.0     + v[1].y() +                        0.0,
                               (v[1].x() * sin(anglePhi*pipi)) +     0.0 + ( v[1].z() * cos(anglePhi*pipi))
                        );

                        retI = 0.15 * retI;
                        retJ = 0.15 * retJ;


                        //Cylinder(retI, retJ, width);
                        createStandardCylinder(retI.x(), retI.y(), retI.z(), retJ.x(), retJ.y(), retJ.z(), width, colorS);

                }//end i

        }


	void parabola2(int m, double R, Vector3D center, double width, string colorS, double iC, double numScene, int initState, int metaState) {

                double r = 1;
                double pipi = 3.14159265358979;
                double anglePhi = 0.0;

                double bar = (double) m / 2;
                for (int i =-bar; i < bar +1; i++) {

                        double length = 2*pipi;
                        double sublength1 = length/m;

                        double u0 = (i + (0.0)) * sublength1;
                        double u1 = (i + (1.0)) * sublength1;

                        Vector3D v[2] = {
                                Vector3D(u0, 0.0, (0.5*u0*u0) - 5.0),
                                Vector3D(u1, 0.0, (0.5*u1*u1) - 5.0)
                        };

			Vector3D w[2] = {
                                Vector3D(u0, (0.5*u0*u0) - 5.0, 0.0),
                                Vector3D(u1, (0.5*u1*u1) - 5.0, 0.0)
                        };

                        ///On ths part of the code we can perform any action on the curve.
                        //ROTATION WITH RESPECT TO THE Y AXIS
                        //
			//
			Vector3D retI = piecewiseVector(w[0], v[0], iC, numScene);
                        Vector3D retJ = piecewiseVector(w[1], v[1], iC, numScene);

                        retI = Vector3D(
                               (retI.x() * cos(anglePhi*pipi)) +     0.0 + (-retI.z() * sin(anglePhi*pipi)),
                                                 0.0     + retI.y() +                        0.0,
                               (retI.x() * sin(anglePhi*pipi)) +     0.0 + ( retI.z() * cos(anglePhi*pipi))
                        );

                        retJ = Vector3D(
                               (retJ.x() * cos(anglePhi*pipi)) +     0.0 + (-retJ.z() * sin(anglePhi*pipi)),
                                                 0.0     + retJ.y() +                        0.0,
                               (retJ.x() * sin(anglePhi*pipi)) +     0.0 + ( retJ.z() * cos(anglePhi*pipi))
                        );

                        retI = 0.15 * retI;
                        retJ = 0.15 * retJ;


                        //Cylinder(retI, retJ, width);
                        createStandardCylinder(retI.x(), retI.y(), retI.z(), retJ.x(), retJ.y(), retJ.z(), width, colorS);

                }//end i

        }

	void drawFacet(const Quaternion& A, const Quaternion& B, const Quaternion& C, double RR, double GG, double BB, double trans) {

                writer << "polygon {" << endl;
		writer << 3;
                writeVector(A.V().x(), A.V().y(), A.V().z());
		writeVector(B.V().x(), B.V().y(), B.V().z());
		writeVector(C.V().x(), C.V().y(), C.V().z());

                PaintTrans(RR, GG, BB, trans);
                writer << "}" << endl << endl;

                return;
        }

	void drawFacet(const Facet& f, int RR, int GG, int BB, double trans) {
		
		cout << f.getAv() << endl;
		cout << f.getBv() << endl;
		cout << f.getCv() << endl;

		writer << "polygon {" << endl;
                writer << 3;
                writeVector(f.getAv().x(), f.getAv().y(), f.getAv().z());
                writeVector(f.getBv().x(), f.getBv().y(), f.getBv().z());
                writeVector(f.getCv().x(), f.getCv().y(), f.getCv().z());

                PaintTrans(RR, GG, BB, trans);
                writer << "}" << endl << endl;

                return;
	}
	
	void drawFacet(const Vector3D& A, const Vector3D& B, const Vector3D& C, double RR, double GG, double BB, double trans) {

                writer << "polygon {" << endl;
                writer << 3;
                writeVector(A.x(), A.y(), A.z());
                writeVector(B.x(), B.y(), B.z());
                writeVector(C.x(), C.y(), C.z());

                PaintTrans(RR, GG, BB, trans);
                writer << "}" << endl << endl;

                return;
        }

	void facetGlass2(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
    		
		writer << "polygon {" << endl;
    		writer << 3; //<< endl;
    		writeVector(a.x(), a.y(), a.z());
    		writeVector(b.x(), b.y(), b.z());
    		writeVector(c.x(), c.y(), c.z());
		//swirlTexture();
		//woodTexture();
		//mirrorTexture();
		//glassTexture3();
		//glassTexture1();
		T_Gold_1A();
		//marbleTexture1();
		photons();
		//writer << "clipped_by { box{<-12, -12, -12>, <12, 12, 12>} }" << endl;
		writer << "}" << endl << endl;
 		//   Cylinder(a, b, 0.05 * abs(a-b));
    		writer << endl;
    		return;
	}

	void drawSphere(double r, double x, double y, double z, double RR, double GG, double BB) {
    		
		addFinishToNextObject(0.5,-1,-1);
    		addPigmentToNextObject(RR, GG, BB, -1,-1);

    		createSphere(r,x,y,z);

    		return;
	}

	void drawSphereTrans(double r, const Vector3D& center, double RR, double GG, double BB, double trans) {

                writer << "sphere {" << endl;

    		writeVector(center.x(), center.y(), center.z());

    		writer << r; //<< endl;

		PaintTrans(RR, GG, BB, trans);
    		writer << "}" << endl << endl;

                return;
        }

	void drawSphereTrans(double r, const Quaternion& center, double RR, double GG, double BB, double trans) {

                writer << "sphere {" << endl;

                writeVector(center.i(), center.j(), center.k());

                writer << r; //<< endl;

                PaintTrans(RR, GG, BB, trans);
                writer << "}" << endl << endl;

                return;
        }


	void TriangleColor(const Vector3D& a, const Vector3D& b, const Vector3D& c, double r, double g, double bb) {
		
		writer << "polygon {" << endl;
		writer << 3; //<< endl;
		writeVector(a.x(), a.y(), a.z());
		writeVector(b.x(), b.y(), b.z());
		writeVector(c.x(), c.y(), c.z());

		//Paint(r, g, bb);
		PaintTrans(r, g, bb, 0.0);
		photons();

		//writer << "clipped_by { box{<-12, -12, -12>, <12, 12, 12>} }" << endl;

   		 writer << "}" << endl << endl;
    		return;
	}

	void TriangleColorTrans(const Vector3D& a, const Vector3D& b, const Vector3D& c, 
			   double r, double g, double bb, double trans) {



                writer << "polygon {" << endl;
                writer << 3; //<< endl;
                writeVector(a.x(), a.y(), a.z());
                writeVector(b.x(), b.y(), b.z());
                writeVector(c.x(), c.y(), c.z());

               // PaintTrans(r, g, bb, trans);
                //photons();
		writer << "     texture {  " << endl;
                        writer << "             pigment{ color<"<< r <<", "<< g <<", "<< bb <<">" << endl;
                        writer << "                      scale 0.5 " << endl;
                        writer << "                     }" << endl;
                        writer << "             finish {" << endl;
                        writer << "                     ambient .1" << endl;
                        writer << "                     diffuse .1" << endl;
                        writer << "                     specular 1" << endl;
                        writer << "                     roughness .001" << endl;
                        writer << "                     phong 1" << endl;
                        writer << "                     reflection {" << endl;
                        writer << "                             0.1" << endl;
                        writer << "                     }" << endl;
                        writer << "             }" << endl;
			writer << "             }" << endl;
                //writer << "clipped_by { box{<-12, -12, -12>, <12, 12, 12>} }" << endl;

                 writer << "}" << endl << endl;
                return;
        }

	void Paint(double R, double G, double B) {
		
		string r = to_string(R);
		string g = to_string(G);
		string b = to_string(B);

		//writer << "pigment { color rgb< " << r << ", " << g << ", " << b <<  "> }" << endl;
		//writer << "finish {" << endl;
  		//writer << "   ambient .1" << endl;
  		//writer << "   diffuse .1" << endl;
  		//writer << "   specular 1" << endl;
  		//writer << "   roughness .1" << endl;
  		//writer << "   reflection {" << endl;
  		//writer << "   0.0" << endl;
  		//writer << "   }" << endl;
  		//writer << "}" << endl;
		
		writer << "pigment { color rgb< " << r << ", " << g << ", " << b <<  "> }" << endl;
                writer << "finish {" << endl;
                writer << "   ambient .1" << endl;
                writer << "   diffuse .1" << endl;
                writer << "   specular 1" << endl;
                writer << "   roughness .001" << endl;
                writer << "   reflection {" << endl;
                writer << "   0.2" << endl;
                writer << "   }" << endl;
                writer << "}" << endl;

	}
	
	void PaintTrans(double R, double G, double B, double trans) {

                string r = to_string(R);
                string g = to_string(G);
                string b = to_string(B);
		
                writer << "pigment { color rgb< " << r << ", " << g << ", " << b <<  ">  transmit " << trans << "}" << endl;
                writer << "finish {" << endl;
                writer << "   ambient .1" << endl;
                writer << "   diffuse .1" << endl;
                writer << "   specular 1" << endl;
                writer << "   roughness .001" << endl;
                writer << "   reflection {" << endl;
                writer << "   0.2" << endl;
                writer << "   }" << endl;
                writer << "}" << endl;
        }

	void CylinderI(const Vector3D& a, const Vector3D& b, double width, double r, double g, double bb) {


             if (abs(a-b) > 1e-10)  {  
                writer << "cylinder {" << endl;
                writeVector(b.x(), b.y(), b.z());
                writeVector(a.x(), a.y(), a.z());
                writer << width << endl;

		Paint(r, g, bb);

                writer << "}" << endl << endl;
		}
                return;
        }

	void drawCylinderTrans(const Vector3D& a, const Vector3D& b, double width, double RR, double GG, double BB, double trans) {

                writer << "cylinder {" << endl;

		writeVector(b.x(), b.y(), b.z());
                writeVector(a.x(), a.y(), a.z());
                writer << width << endl;

                PaintTrans(RR, GG, BB, trans);
                writer << "}" << endl << endl;

                return;
        }
	
	void DrawDodeca(
                 double x1, double x2, double x3,
                 double x4, double x5, double x6,
                 double x7, double x8, double x9,
				 double x10, double x11, double x12,
				 double x13, double x14, double x15,
                 double x16, double x17, double x18,
                 double x19, double x20, double x21,
				 double x22, double x23, double x24,
				 double x25, double x26, double x27,
                 double x28, double x29, double x30,
                 double x31, double x32, double x33,
				 double x34, double x35, double x36,
				 double x37, double x38, double x39,
				 double x40, double x41, double x42,
				 double x43, double x44, double x45,
				 double x46, double x47, double x48,
				 double x49, double x50, double x51,
				 double x52, double x53, double x54,
				 double x55, double x56, double x57,
				 double x58, double x59, double x60,
				 int n, double d1,  double d2, double d3
                 )
{
      	double gold= (1 + sqrt(5))/2;
      	double g = 0.975 / (gold*gold);


         Vector3D w[20] = {
         Vector3D( x1 , x2, x3 ),//0
         Vector3D( x4 , x5, x6 ),//1
         Vector3D( x7 , x8, x9 ),//2
         Vector3D( x10 , x11, x12 ),//3
         Vector3D( x13 , x14, x15 ),//4
         Vector3D( x16 , x17, x18 ),//5
         Vector3D( x19 , x20, x21 ),//6
         Vector3D( x22 , x23, x24 ),//7
         Vector3D( x25 , x26, x27 ),//8
         Vector3D( x28 , x29, x30 ),//9
         Vector3D( x31 , x32, x33 ),//10
         Vector3D( x34 , x35, x36 ),//11
         Vector3D( x37 , x38, x39 ),//12
         Vector3D( x40 , x41, x42 ),//13
         Vector3D( x43 , x44, x45 ),//14
         Vector3D( x46 , x47, x48 ),//15
         Vector3D( x49 , x50, x51 ),//16
         Vector3D( x52 , x53, x54 ),//17
         Vector3D( x55 , x56, x57 ),//18
         Vector3D( x58 , x59, x60 ),//19

 };

	Vector3D v[20] = {
         Vector3D( x1 + d1, x2 + d2, x3 + d3 ),//0
         Vector3D( x4 + d1, x5 + d2, x6 + d3 ),//1
         Vector3D( x7 + d1, x8 + d2, x9 + d3 ),//2
         Vector3D( x10 +d1, x11 +d2, x12 +d3 ),//3
         Vector3D( x13 +d1, x14 +d2, x15 +d3 ),//4
         Vector3D( x16 +d1, x17 +d2, x18 +d3 ),//5
         Vector3D( x19 +d1, x20 +d2, x21 +d3 ),//6
         Vector3D( x22 +d1, x23 +d2, x24 +d3 ),//7
         Vector3D( x25 +d1, x26 +d2, x27 +d3 ),//8
         Vector3D( x28 +d1, x29 +d2, x30 +d3 ),//9
         Vector3D( x31 +d1, x32 +d2, x33 +d3 ),//10
         Vector3D( x34 +d1, x35 +d2, x36 +d3 ),//11
         Vector3D( x37 +d1, x38 +d2, x39 +d3 ),//12
         Vector3D( x40 +d1, x41 +d2, x42 +d3 ),//13
         Vector3D( x43 +d1, x44 +d2, x45 +d3 ),//14
         Vector3D( x46 +d1, x47 +d2, x48 +d3 ),//15
         Vector3D( x49 +d1, x50 +d2, x51 +d3 ),//16
         Vector3D( x52 +d1, x53 +d2, x54 +d3 ),//17
         Vector3D( x55 +d1, x56 +d2, x57 +d3 ),//18
         Vector3D( x58 +d1, x59 +d2, x60 +d3 ),//19

     };


	int aristas[30][2] = {
  {0, 4},//0
  {4, 3},//1
  {3, 2},//2
  {2, 1},//3
  {1, 0},//4
  {0, 6},//5
  {6, 16},//6
  {16, 19},//7
  {19, 4},//8
  {1, 7},//9
  {7, 5},//10
  {5, 6},//11
  {2, 17},//12
  {17, 18},//13
  {18, 7},//14
  {3, 14},//15
  {14,15},//16
  {15, 17},//17
  {19, 13},//18
  {13, 14},//19
  {15, 9},//21
  {9, 8},//22
  {8, 13},
  {8, 12},
  {12, 16},
  {12, 11},
  {5, 11},
  {11, 10},
  {10, 9},
  {10, 18}
};


if( n == 0 )
{

	for (int i = 0; i < 30; i++)
	 CylinderI(v[aristas[i][0]], v[aristas[i][1]], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     
     Triangle(v[9], v[15], v[14]);
     Triangle(v[8], v[9], v[14]);
     Triangle(v[13], v[8], v[14]);


     Triangle(v[1], v[7], v[5]);
     Triangle(v[0], v[1], v[5]);
     Triangle(v[6], v[0], v[5]);

     Triangle(v[12], v[8], v[13]);
     Triangle(v[16], v[12], v[13]);
     Triangle(v[19], v[16], v[13]);

     Triangle(v[17], v[18], v[7]);
     Triangle(v[2], v[17], v[7]);
     Triangle(v[1], v[2], v[7]);

	 Triangle(v[18], v[17], v[15]);
     Triangle(v[10], v[18], v[15]);
     Triangle(v[9], v[10], v[15]);

	 Triangle(v[4], v[0], v[6]);
     Triangle(v[19], v[4], v[6]);
     Triangle(v[16], v[19], v[6]);

     Triangle(v[11], v[10], v[9]);
     Triangle(v[12], v[11], v[9]);
     Triangle(v[8], v[12], v[9]);

	 Triangle(v[2], v[1], v[0]);
     Triangle(v[3], v[2], v[0]);
     Triangle(v[4], v[3], v[0]);

     Triangle(v[11], v[12], v[16]);
     Triangle(v[5], v[11], v[16]);
     Triangle(v[6], v[5], v[16]);

     Triangle(v[14], v[15], v[17]);
     Triangle(v[3], v[14], v[17]);
     Triangle(v[2], v[3], v[17]);

	 Triangle(v[7], v[18], v[10]);
     Triangle(v[5], v[7], v[10]);
     Triangle(v[11], v[5], v[10]);

     Triangle(v[14], v[3], v[4]); //w1
     Triangle(v[13], v[14], v[4]);
     Triangle(v[19], v[13], v[4]);


}
 else
 {

	 for (int i = 0; i < 30; i++)
          CylinderI(v[aristas[i][0]], v[aristas[i][1]], 0.1 * abs(v[0] - v[4]), 0, 0, 6);

    Triangle(v[11], v[10], v[9]);//s
     Triangle(v[12], v[11], v[9]);
     Triangle(v[8], v[12], v[9]);

 	 Triangle(v[9], v[15], v[14]);//a
     Triangle(v[8], v[9], v[14]);
     Triangle(v[13], v[8], v[14]);

     Triangle(v[18], v[17], v[15]);//d
     Triangle(v[10], v[18], v[15]);
     Triangle(v[9], v[10], v[15]);

    Triangle(v[7], v[18], v[10]); //e
     Triangle(v[5], v[7], v[10]);
     Triangle(v[11], v[5], v[10]);

     Triangle(v[11], v[12], v[16]);//f
     Triangle(v[5], v[11], v[16]);
     Triangle(v[6], v[5], v[16]);

     Triangle(v[12], v[8], v[13]); //c
     Triangle(v[16], v[12], v[13]);
     Triangle(v[19], v[16], v[13]);

     Triangle(v[1], v[7], v[5]);// w 3
     Triangle(v[0], v[1], v[5]);
     Triangle(v[6], v[0], v[5]);

    Triangle(v[17], v[18], v[7]);    //w 4
     Triangle(v[2], v[17], v[7]);
     Triangle(v[1], v[2], v[7]);

	 Triangle(v[4], v[0], v[6]);// w 2
     Triangle(v[19], v[4], v[6]);
     Triangle(v[16], v[19], v[6]);

	 Triangle(v[2], v[1], v[0]); ////b center
     Triangle(v[3], v[2], v[0]);
     Triangle(v[4], v[3], v[0]);

     Triangle(v[14], v[15], v[17]); //w5
     Triangle(v[3], v[14], v[17]);
     Triangle(v[2], v[3], v[17]);


     Triangle(v[14], v[3], v[4]);//w1
     Triangle(v[13], v[14], v[4]);
     Triangle(v[19], v[13], v[4]);



 	double a[ 4];
           a [ 0 ] = 0.0;


 	for(int k=0; k<=0; ++k)
 	{


 	// We calculate the vector normal to face A.
 	double a1 = ( ( (x41-x44) * (x48-x45) ) - ( (x47-x44) * (x42-x45)) );  a[ 1] = a1;
 	double a2 = ( ( (x46-x43) * (x42-x45) ) - ( (x40-x43) * (x48-x45)) );  a[ 2] = a2;
 	double a3 = ( ( (x40-x43) * (x47-x44) ) - ( (x46-x43) * (x41-x44)) );  a[ 3] = a3;

 	double l = sqrt( (a1*a1) + (a2*a2) + (a3*a3));
 	//Let  d  be any arbitrary real number.
 	double d = 1.0;
 	//We now calculate the unit vector asociated to

 	a1=pow(-1, k)*d * (a1 / l);
 	a2=pow(-1, k)*d * (a2 / l);
 	a3=pow(-1, k)*d * (a3 / l);

 	d = 0.666666 * gold + 0.0;

 	double v1 =  x52 - x4;
        double v2 =  x53 - x5;
        double v3 =  x54 - x6;

        double w1 =  x4 - x7;
        double w2 =  x5 - x8;
        double w3 =  x6 - x9;

        double u1 = ( ( (v2 * w3 ) - ( w2 * v3 )));
 	double u2 = ( ( w1 * v3 ) - ( v1 * w3 ));
 	double u3 = ( ( v1 * w2 ) - ( w1 * v2 ));

 	double x[ n + 1];
           x [ 0 ] = 0.0;

        double x01 = (x1 * g) + (a1*d);
	double x02 = (x2 * g) + (a2*d);
	double x03 = (x3 * g) + (a3*d);

	double x04 = (x4 * g) + (a1*d);
	double x05 = (x5 * g) + (a2*d);
	double x06 = (x6 * g) + (a3*d);

	double x07 = (x7 * g) + (a1*d);
	double x08 = (x8 * g) + (a2*d);
	double x09 = (x9 * g) + (a3*d);

	double x010 = (x10 * g) + (a1*d);
	double x011 = (x11 * g) + (a2*d);
	double x012 = (x12 * g) + (a3*d);

	double x013 = (x13 * g) + (a1*d);
	double x014 = (x14 * g) + (a2*d);
	double x015 = (x15 * g) + (a3*d);

	double x016 = (x16 * g) + (a1*d);
	double x017 = (x17 * g) + (a2*d);
	double x018 = (x18 * g) + (a3*d);

	double x019 = (x19 * g) + (a1*d);
	double x020 = (x20 * g) + (a2*d);
	double x021 = (x21 * g) + (a3*d);

	double x022 = (x22 * g) + (a1*d);
	double x023 = (x23 * g) + (a2*d);
	double x024 = (x24 * g) + (a3*d);

	double x025 = (x25 * g) + (a1*d);
	double x026 = (x26 * g) + (a2*d);
	double x027 = (x27 * g) + (a3*d);

	double x028 = (x28 * g) + (a1*d);
	double x029 = (x29 * g) + (a2*d);
	double x030 = (x30* g) + (a3*d);

	double x031 = (x31 * g) + (a1*d);
	double x032 = (x32 * g) + (a2*d);
	double x033 = (x33 * g) + (a3*d);


        double x034 = (x34 * g) + (a1*d);
	double x035 = (x35 * g) + (a2*d);
	double x036 = (x36 * g) + (a3*d);

	double x037 = (x37 * g) + (a1*d);
	double x038 = (x38 * g) + (a2*d);
	double x039 = (x39 * g) + (a3*d);

	double x040 = (x40 * g) + (a1*d);
	double x041 = (x41 * g) + (a2*d);
	double x042 = (x42 * g) + (a3*d);

	double x043 = (x43 * g) + (a1*d);
	double x044 = (x44 * g) + (a2*d);
	double x045 = (x45 * g) + (a3*d);

	double x046 = (x46 * g) + (a1*d);
	double x047 = (x47 * g) + (a2*d);
	double x048 = (x48 * g) + (a3*d);

	double x049 = (x49 * g) + (a1*d);
	double x050 = (x50 * g) + (a2*d);
	double x051 = (x51 * g) + (a3*d);

	double x052 = (x52 * g) + (a1*d);
	double x053 = (x53 * g) + (a2*d);
	double x054 = (x54 * g) + (a3*d);

	double x055 = (x55 * g) + (a1*d);
	double x056 = (x56 * g) + (a2*d);
	double x057 = (x57 * g) + (a3*d);

	double x058 = (x58 * g) + (a1*d);
	double x059 = (x59 * g) + (a2*d);
	double x060 = (x60 * g) + (a3*d);


	DrawDodeca(
                  x01,  x02,  x03,
                  x04,  x05, x06,
                  x07,  x08, x09,
	          x010, x011, x012,
		  x013, x014, x015,
                  x016, x017, x018,
                  x019, x020,  x021,
		  x022, x023,  x024,
		  x025, x026,  x027,
                  x028, x029,  x030,
                  x031, x032,  x033,
		  x034, x035,  x036,
		  x037, x038,  x039,
		  x040, x041,  x042,
	          x043, x044,  x045,
				  x046, x047,  x048,
				  x049, x050,  x051,
				  x052, x053,  x054,
				  x055, x056,  x057,
				  x058, x059,  x060,
				 n - 1,d1,d2,d3
                 );












































	       v1 =  x13 - x1;
		   v2 =  x14 - x2;
           v3 =  x15 - x3;

		   w1 =  x4 - x1;
		   w2 =  x5 - x2;
           w3 =  x6 - x3;

     double b[ 4];
           b [ 0 ] = 0.0;


 	for(int k=0; k<=0; ++k)
 	{
 		// We calculate the vector normal to face A.
 	 double b1 = ( ( (v2 * w3 ) - ( w2 * v3 )));  b[ 1] = a1;
 	 double b2 = ( ( w1 * v3 ) - ( v1 * w3 ));  b[ 2] = a2;
 	 double b3 = ( ( v1 * w2 ) - ( w1 * v2 ));  b[ 3] = a3;
          double D = sqrt( (b1 * b1) + (b2 * b2) + (b3 * b3));
   /* cout<<endl<<"b = (  ";
 	for( int i = 1; i <= 3; ++i)
 {

	 	if( i < 3)
	 	{
	 		cout<<b[ i]/D<<",   ";
		 }
		 else
	 	cout<<b[3]/D<<" )";

 }*/

 	 l = sqrt( (b1*b1) + (b2*b2) + (b3*b3));
 	 d = 0.666666 * gold;

 	b1=pow(-1, k)*d * (b1 / l);
 	b2=pow(-1, k)*d * (b2 / l);
 	b3=pow(-1, k)*d * (b3 / l);

     //  1.9999, -1.99999, 1.99999
	double y01 = (x1 * g) + (b1*d);
	double y02 = (x2 * g) + (b2*d);
	double y03 = (x3 * g) + (b3*d);


    	double y04 = (x4 * g) + (b1*d);
	double y05 = (x5 * g) + (b2*d);
	double y06 = (x6 * g) + (b3*d);

	double y07 = (x7 * g) + (b1*d);
	double y08 = (x8 * g) + (b2*d);
	double y09 = (x9 * g) + (b3*d);

	double y010 = (x10 * g) + (b1*d);
	double y011 = (x11 * g) + (b2*d);
	double y012 = (x12 * g) + (b3*d);

	double y013 = (x13 * g) + (b1*d);
	double y014 = (x14 * g) + (b2*d);
	double y015 = (x15 * g) + (b3*d);

	double y016 = (x16 * g) + (b1*d);
	double y017 = (x17 * g) + (b2*d);
	double y018 = (x18 * g) + (b3*d);

	double y019 = (x19 * g) + (b1*d);
	double y020 = (x20 * g) + (b2*d);
	double y021 = (x21 * g) + (b3*d);

	double y022 = (x22 * g) + (b1*d);
	double y023 = (x23 * g) + (b2*d);
	double y024 = (x24 * g) + (b3*d);

	double y025 = (x25 * g) + (b1*d);
	double y026 = (x26 * g) + (b2*d);
	double y027 = (x27 * g) + (b3*d);

	double y028 = (x28 * g) + (b1*d);
	double y029 = (x29 * g) + (b2*d);
	double y030 = (x30* g) + (b3*d);

	double y031 = (x31 * g) + (b1*d);
	double y032 = (x32 * g) + (b2*d);
	double y033 = (x33 * g) + (b3*d);


    double y034 = (x34 * g) + (b1*d);
	double y035 = (x35 * g) + (b2*d);
	double y036 = (x36 * g) + (b3*d);

	double y037 = (x37 * g) + (b1*d);
	double y038 = (x38 * g) + (b2*d);
	double y039 = (x39 * g) + (b3*d);

	double y040 = (x40 * g) + (b1*d);
	double y041 = (x41 * g) + (b2*d);
	double y042 = (x42 * g) + (b3*d);

	double y043 = (x43 * g) + (b1*d);
	double y044 = (x44 * g) + (b2*d);
	double y045 = (x45 * g) + (b3*d);

	double y046 = (x46 * g) + (b1*d);
	double y047 = (x47 * g) + (b2*d);
	double y048 = (x48 * g) + (b3*d);

	double y049 = (x49 * g) + (b1*d);
	double y050 = (x50 * g) + (b2*d);
	double y051 = (x51 * g) + (b3*d);

	double y052 = (x52 * g) + (b1*d);
	double y053 = (x53 * g) + (b2*d);
	double y054 = (x54 * g) + (b3*d);

	double y055 = (x55 * g) + (b1*d);
	double y056 = (x56 * g) + (b2*d);
	double y057 = (x57 * g) + (b3*d);

	double y058 = (x58 * g) + (b1*d);
	double y059 = (x59 * g) + (b2*d);
	double y060 = (x60 * g) + (b3*d);


	DrawDodeca(
                  y01,  y02,  y03,
                  y04,  y05,  y06,
                  y07,  y08,  y09,
				  y010, y011, y012,
				  y013, y014, y015,
                  y016, y017, y018,
                  y019, y020, y021,
				  y022, y023, y024,
				  y025, y026, y027,
                  y028, y029, y030,
                  y031, y032, y033,
				  y034, y035, y036,
				  y037, y038, y039,
				  y040, y041, y042,
				  y043, y044, y045,
				  y046, y047, y048,
				  y049, y050, y051,
				  y052, y053, y054,
				  y055, y056, y057,
				  y058, y059, y060,
				 n - 1, d1, d2, d3
                 );


          v1 =  x1 - x13;
		  v2 =  x2 - x14;
          v3 =  x3 - x15;

		  w1 =  x58 - x13;
		  w2 =  x59 - x14;
          w3 =  x60 - x15;







      double c[ 4];
           c [ 0 ] = 0.0;



 		// We calculate the vector normal to face A.
 	double c1 = ( ( (v2 * w3 ) - ( w2 * v3 )));  c[ 1] = c1;
 	double c2 = ( ( w1 * v3 ) - ( v1 * w3 ));  c[ 2] = c2;
 	double c3 = ( ( v1 * w2 ) - ( w1 * v2 ));  c[ 3] = c3;




 	 l = sqrt( (c1*c1) + (c2*c2) + (c3*c3));
 	 d = -0.666666 * gold;

 	c1=pow(-1, k)*d * (c1 / l);
 	c2=pow(-1, k)*d * (c2 / l);
 	c3=pow(-1, k)*(-1)*d * (c3 / l);

     //  1.9999, -1.99999, 1.99999
	double y101 = (x1 * g) + (c1*d);
	double y102 = (x2 * g) + (c2*d);
	double y103 = (x3 * g) + (c3*d);


    double y104 = (x4 * g) + (c1*d);
	double y105 = (x5 * g) + (c2*d);
	double y106 = (x6 * g) + (c3*d);

	double y107 = (x7 * g) + (c1*d);
	double y108 = (x8 * g) + (c2*d);
	double y109 = (x9 * g) + (c3*d);

	double y1010 = (x10 * g) + (c1*d);
	double y1011 = (x11 * g) + (c2*d);
	double y1012 = (x12 * g) + (c3*d);

	double y1013 = (x13 * g) + (c1*d);
	double y1014 = (x14 * g) + (c2*d);
	double y1015 = (x15 * g) + (c3*d);

	double y1016 = (x16 * g) + (c1*d);
	double y1017 = (x17 * g) + (c2*d);
	double y1018 = (x18 * g) + (c3*d);

	double y1019 = (x19 * g) + (c1*d);
	double y1020 = (x20 * g) + (c2*d);
	double y1021 = (x21 * g) + (c3*d);

	double y1022 = (x22 * g) + (c1*d);
	double y1023 = (x23 * g) + (c2*d);
	double y1024 = (x24 * g) + (c3*d);

	double y1025 = (x25 * g) + (c1 *d);
	double y1026 = (x26 * g) + (c2 *d);
	double y1027 = (x27 * g) + (c3*d);

	double y1028 = (x28 * g) + (c1*d);
	double y1029 = (x29 * g) + (c2*d);
	double y1030 = (x30* g) + (c3*d);

	double y1031 = (x31 * g) + (c1*d);
	double y1032 = (x32 * g) + (c2*d);
	double y1033 = (x33 * g) + (c3*d);


    double y1034 = (x34 * g) + (c1*d);
	double y1035 = (x35 * g) + (c2*d);
	double y1036 = (x36 * g) + (c3*d);

	double y1037 = (x37 * g) + (c1*d);
	double y1038 = (x38 * g) + (c2*d);
	double y1039 = (x39 * g) + (c3*d);

	double y1040 = (x40 * g) + (c1*d);
	double y1041 = (x41 * g) + (c2*d);
	double y1042 = (x42 * g) + (c3*d);

	double y1043 = (x43 * g) + (c1*d);
	double y1044 = (x44 * g) + (c2*d);
	double y1045 = (x45 * g) + (c3*d);

	double y1046 = (x46 * g) + (c1*d);
	double y1047 = (x47 * g) + (c2*d);
	double y1048 = (x48 * g) + (c3*d);

	double y1049 = (x49 * g) + (c1*d);
	double y1050 = (x50 * g) + (c2*d);
	double y1051 = (x51 * g) + (c3*d);

	double y1052 = (x52 * g) + (c1*d);
	double y1053 = (x53 * g) + (c2*d);
	double y1054 = (x54 * g) + (c3*d);

	double y1055 = (x55 * g) + (c1*d);
	double y1056 = (x56 * g) + (c2*d);
	double y1057 = (x57 * g) + (c3*d);

	double y1058 = (x58 * g) + (c1*d);
	double y1059 = (x59 * g) + (c2*d);
	double y1060 = (x60 * g) + (c3*d);


	DrawDodeca(
                  y101,  y102,  y103,
                  y104,  y105,  y106,
                  y107,  y108,  y109,
				  y1010, y1011, y1012,
				  y1013, y1014, y1015,
                  y1016, y1017, y1018,
                  y1019, y1020, y1021,
				  y1022, y1023, y1024,
				  y1025, y1026, y1027,
                  y1028, y1029, y1030,
                  y1031, y1032, y1033,
				  y1034, y1035, y1036,
				  y1037, y1038, y1039,
				  y1040, y1041, y1042,
				  y1043, y1044, y1045,
				  y1046, y1047, y1048,
				  y1049, y1050, y1051,
				  y1052, y1053, y1054,
				  y1055, y1056, y1057,
				  y1058, y1059, y1060,
				 n - 1,d1,d2,d3
                 );

				 //////////////////////////////////////////////   f
		  v1 =  x34 - x37;
		  v2 =  x35 - x38;
          v3 =  x36 - x39;

		  w1 =  x49 - x37;
		  w2 =  x50 - x38;
          w3 =  x51 - x39;

     double f1 = ( ( v2 * w3 ) - ( w2 * v3 ));
 	 double f2 = ( ( w1 * v3 ) - ( v1 * w3 ));
 	 double f3 = ( ( v1 * w2 ) - ( w1 * v2 ));

 	 l = sqrt( (f1*f1) + (f2*f2) + (f3*f3));
 	 d = 0.666666 * gold;

 	f1=-pow(-1, k)*d * (f1 / l);
 	f2=-pow(-1, k)*d * (f2 / l);
 	f3=-pow(-1, k)*d * (f3 / l);

     //  1.9999, -1.99999, 1.99999
	double y201 = (x1 * g) + (f1*d);
	double y202 = (x2 * g) + (f2*d);
	double y203 = (x3 * g) + (f3*d);


    double y204 = (x4 * g) + (f1*d);
	double y205 = (x5 * g) + (f2*d);
	double y206 = (x6 * g) + (f3*d);

	double y207 = (x7 * g) + (f1*d);
	double y208 = (x8 * g) + (f2*d);
	double y209 = (x9 * g) + (f3*d);

	double y2010 = (x10 * g) + (f1*d);
	double y2011 = (x11 * g) + (f2*d);
	double y2012 = (x12 * g) + (f3*d);

	double y2013 = (x13 * g) + (f1*d);
	double y2014 = (x14 * g) + (f2*d);
	double y2015 = (x15 * g) + (f3*d);

	double y2016 = (x16 * g) + (f1*d);
	double y2017 = (x17 * g) + (f2*d);
	double y2018 = (x18 * g) + (f3*d);

	double y2019 = (x19 * g) + (f1*d);
	double y2020 = (x20 * g) + (f2*d);
	double y2021 = (x21 * g) + (f3*d);

	double y2022 = (x22 * g) + (f1*d);
	double y2023 = (x23 * g) + (f2*d);
	double y2024 = (x24 * g) + (f3*d);

	double y2025 = (x25 * g) + (f1 *d);
	double y2026 = (x26 * g) + (f2 *d);
	double y2027 = (x27 * g) + (f3*d);

	double y2028 = (x28 * g) + (f1*d);
	double y2029 = (x29 * g) + (f2*d);
	double y2030 = (x30* g) +  (f3*d);

	double y2031 = (x31 * g) + (f1*d);
	double y2032 = (x32 * g) + (f2*d);
	double y2033 = (x33 * g) + (f3*d);


    double y2034 = (x34 * g) + (f1*d);
	double y2035 = (x35 * g) + (f2*d);
	double y2036 = (x36 * g) + (f3*d);

	double y2037 = (x37 * g) + (f1*d);
	double y2038 = (x38 * g) + (f2*d);
	double y2039 = (x39 * g) + (f3*d);

	double y2040 = (x40 * g) + (f1*d);
	double y2041 = (x41 * g) + (f2*d);
	double y2042 = (x42 * g) + (f3*d);

	double y2043 = (x43 * g) + (f1*d);
	double y2044 = (x44 * g) + (f2*d);
	double y2045 = (x45 * g) + (f3*d);

	double y2046 = (x46 * g) + (f1*d);
	double y2047 = (x47 * g) + (f2*d);
	double y2048 = (x48 * g) + (f3*d);

	double y2049 = (x49 * g) + (f1*d);
	double y2050 = (x50 * g) + (f2*d);
	double y2051 = (x51 * g) + (f3*d);

	double y2052 = (x52 * g) + (f1*d);
	double y2053 = (x53 * g) + (f2*d);
	double y2054 = (x54 * g) + (f3*d);

	double y2055 = (x55 * g) + (f1*d);
	double y2056 = (x56 * g) + (f2*d);
	double y2057 = (x57 * g) + (f3*d);

	double y2058 = (x58 * g) + (f1*d);
	double y2059 = (x59 * g) + (f2*d);
	double y2060 = (x60 * g) + (f3*d);


	DrawDodeca(
                  y201,  y202,  y203,
                  y204,  y205,  y206,
                  y207,  y208,  y209,
				  y2010, y2011, y2012,
				  y2013, y2014, y2015,
                  y2016, y2017, y2018,
                  y2019, y2020, y2021,
				  y2022, y2023, y2024,
				  y2025, y2026, y2027,
                  y2028, y2029, y2030,
                  y2031, y2032, y2033,
				  y2034, y2035, y2036,
				  y2037, y2038, y2039,
				  y2040, y2041, y2042,
				  y2043, y2044, y2045,
				  y2046, y2047, y2048,
				  y2049, y2050, y2051,
				  y2052, y2053, y2054,
				  y2055, y2056, y2057,
				  y2058, y2059, y2060,
				 n - 1,d1,d2,d3
                 );

	     //////////////////////////////////////////////   e
		  v1 =  x31 - x34;
		  v2 =  x32 - x35;
          v3 =  x33 - x36;

		  w1 =  x16 - x34;
		  w2 =  x17 - x35;
          w3 =  x18 - x36;

     double e1 = ( ( v2 * w3 ) - ( w2 * v3 ));
 	 double e2 = ( ( w1 * v3 ) - ( v1 * w3 ));
 	 double e3 = ( ( v1 * w2 ) - ( w1 * v2 ));

 	 l = sqrt( (e1*e1) + (e2*e2) + (e3*e3));
 	 d = 0.666666 * gold;

 	e1=-pow(-1, k)*d * (e1 / l);
 	e2=-pow(-1, k)*d * (e2 / l);
 	e3=-pow(-1, k)*d * (e3 / l);

     //  1.9999, -1.99999, 1.99999
	double y301 = (x1 * g) + (e1*d);
	double y302 = (x2 * g) + (e2*d);
	double y303 = (x3 * g) + (e3*d);


    double y304 = (x4 * g) + (e1*d);
	double y305 = (x5 * g) + (e2*d);
	double y306 = (x6 * g) + (e3*d);

	double y307 = (x7 * g) + (e1*d);
	double y308 = (x8 * g) + (e2*d);
	double y309 = (x9 * g) + (e3*d);

	double y3010 = (x10 * g) + (e1*d);
	double y3011 = (x11 * g) + (e2*d);
	double y3012 = (x12 * g) + (e3*d);

	double y3013 = (x13 * g) + (e1*d);
	double y3014 = (x14 * g) + (e2*d);
	double y3015 = (x15 * g) + (e3*d);

	double y3016 = (x16 * g) + (e1*d);
	double y3017 = (x17 * g) + (e2*d);
	double y3018 = (x18 * g) + (e3*d);

	double y3019 = (x19 * g) + (e1*d);
	double y3020 = (x20 * g) + (e2*d);
	double y3021 = (x21 * g) + (e3*d);

	double y3022 = (x22 * g) + (e1*d);
	double y3023 = (x23 * g) + (e2*d);
	double y3024 = (x24 * g) + (e3*d);

	double y3025 = (x25 * g) + (e1 *d);
	double y3026 = (x26 * g) + (e2 *d);
	double y3027 = (x27 * g) + (e3*d);

	double y3028 = (x28 * g) + (e1*d);
	double y3029 = (x29 * g) + (e2*d);
	double y3030 = (x30* g) +  (e3*d);

	double y3031 = (x31 * g) + (e1*d);
	double y3032 = (x32 * g) + (e2*d);
	double y3033 = (x33 * g) + (e3*d);


    double y3034 = (x34 * g) + (e1*d);
	double y3035 = (x35 * g) + (e2*d);
	double y3036 = (x36 * g) + (e3*d);

	double y3037 = (x37 * g) + (e1*d);
	double y3038 = (x38 * g) + (e2*d);
	double y3039 = (x39 * g) + (e3*d);

	double y3040 = (x40 * g) + (e1*d);
	double y3041 = (x41 * g) + (e2*d);
	double y3042 = (x42 * g) + (e3*d);

	double y3043 = (x43 * g) + (e1*d);
	double y3044 = (x44 * g) + (e2*d);
	double y3045 = (x45 * g) + (e3*d);

	double y3046 = (x46 * g) + (e1*d);
	double y3047 = (x47 * g) + (e2*d);
	double y3048 = (x48 * g) + (e3*d);

	double y3049 = (x49 * g) + (e1*d);
	double y3050 = (x50 * g) + (e2*d);
	double y3051 = (x51 * g) + (e3*d);

	double y3052 = (x52 * g) + (e1*d);
	double y3053 = (x53 * g) + (e2*d);
	double y3054 = (x54 * g) + (e3*d);

	double y3055 = (x55 * g) + (e1*d);
	double y3056 = (x56 * g) + (e2*d);
	double y3057 = (x57 * g) + (e3*d);

	double y3058 = (x58 * g) + (e1*d);
	double y3059 = (x59 * g) + (e2*d);
	double y3060 = (x60 * g) + (e3*d);


	DrawDodeca(
                  y301,  y302,  y303,
                  y304,  y305,  y306,
                  y307,  y308,  y309,
				  y3010, y3011, y3012,
				  y3013, y3014, y3015,
                  y3016, y3017, y3018,
                  y3019, y3020, y3021,
				  y3022, y3023, y3024,
				  y3025, y3026, y3027,
                  y3028, y3029, y3030,
                  y3031, y3032, y3033,
				  y3034, y3035, y3036,
				  y3037, y3038, y3039,
				  y3040, y3041, y3042,
				  y3043, y3044, y3045,
				  y3046, y3047, y3048,
				  y3049, y3050, y3051,
				  y3052, y3053, y3054,
				  y3055, y3056, y3057,
				  y3058, y3059, y3060,
				 n - 1
                 ,d1,d2,d3);

	 	//////////////////////////////////////////////   d
		  v1 =  x28 - x31;
		  v2 =  x29 - x32;
          v3 =  x30 - x33;

		  w1 =  x55 - x31;
		  w2 =  x56 - x32;
          w3 =  x57 - x33;

      e1 = ( ( v2 * w3 ) - ( w2 * v3 ));
 	  e2 = ( ( w1 * v3 ) - ( v1 * w3 ));
 	  e3 = ( ( v1 * w2 ) - ( w1 * v2 ));

 	 l = sqrt( (e1*e1) + (e2*e2) + (e3*e3));
 	 d = 0.666666 * gold;

 	e1=-pow(-1, k)*d * (e1 / l);
 	e2=-pow(-1, k)*d * (e2 / l);
 	e3=-pow(-1, k)*d * (e3 / l);

     //  1.9999, -1.99999, 1.99999
	double y401 = (x1 * g) + (e1*d);
	double y402 = (x2 * g) + (e2*d);
	double y403 = (x3 * g) + (e3*d);

    double y404 = (x4 * g) + (e1*d);
	double y405 = (x5 * g) + (e2*d);
	double y406 = (x6 * g) + (e3*d);

	double y407 = (x7 * g) + (e1*d);
	double y408 = (x8 * g) + (e2*d);
	double y409 = (x9 * g) + (e3*d);

	double y4010 = (x10 * g) + (e1*d);
	double y4011 = (x11 * g) + (e2*d);
	double y4012 = (x12 * g) + (e3*d);

	double y4013 = (x13 * g) + (e1*d);
	double y4014 = (x14 * g) + (e2*d);
	double y4015 = (x15 * g) + (e3*d);

	double y4016 = (x16 * g) + (e1*d);
	double y4017 = (x17 * g) + (e2*d);
	double y4018 = (x18 * g) + (e3*d);

	double y4019 = (x19 * g) + (e1*d);
	double y4020 = (x20 * g) + (e2*d);
	double y4021 = (x21 * g) + (e3*d);

	double y4022 = (x22 * g) + (e1*d);
	double y4023 = (x23 * g) + (e2*d);
	double y4024 = (x24 * g) + (e3*d);

	double y4025 = (x25 * g) + (e1 *d);
	double y4026 = (x26 * g) + (e2 *d);
	double y4027 = (x27 * g) + (e3*d);

	double y4028 = (x28 * g) + (e1*d);
	double y4029 = (x29 * g) + (e2*d);
	double y4030 = (x30* g) +  (e3*d);

	double y4031 = (x31 * g) + (e1*d);
	double y4032 = (x32 * g) + (e2*d);
	double y4033 = (x33 * g) + (e3*d);

    double y4034 = (x34 * g) + (e1*d);
	double y4035 = (x35 * g) + (e2*d);
	double y4036 = (x36 * g) + (e3*d);

	double y4037 = (x37 * g) + (e1*d);
	double y4038 = (x38 * g) + (e2*d);
	double y4039 = (x39 * g) + (e3*d);

	double y4040 = (x40 * g) + (e1*d);
	double y4041 = (x41 * g) + (e2*d);
	double y4042 = (x42 * g) + (e3*d);

	double y4043 = (x43 * g) + (e1*d);
	double y4044 = (x44 * g) + (e2*d);
	double y4045 = (x45 * g) + (e3*d);

	double y4046 = (x46 * g) + (e1*d);
	double y4047 = (x47 * g) + (e2*d);
	double y4048 = (x48 * g) + (e3*d);

	double y4049 = (x49 * g) + (e1*d);
	double y4050 = (x50 * g) + (e2*d);
	double y4051 = (x51 * g) + (e3*d);

	double y4052 = (x52 * g) + (e1*d);
	double y4053 = (x53 * g) + (e2*d);
	double y4054 = (x54 * g) + (e3*d);

	double y4055 = (x55 * g) + (e1*d);
	double y4056 = (x56 * g) + (e2*d);
	double y4057 = (x57 * g) + (e3*d);

	double y4058 = (x58 * g) + (e1*d);
	double y4059 = (x59 * g) + (e2*d);
	double y4060 = (x60 * g) + (e3*d);


	DrawDodeca(
                  y401,  y402,  y403,
                  y404,  y405,  y406,
                  y407,  y408,  y409,
				  y4010, y4011, y4012,
				  y4013, y4014, y4015,
                  y4016, y4017, y4018,
                  y4019, y4020, y4021,
				  y4022, y4023, y4024,
				  y4025, y4026, y4027,
                  y4028, y4029, y4030,
                  y4031, y4032, y4033,
				  y4034, y4035, y4036,
				  y4037, y4038, y4039,
				  y4040, y4041, y4042,
				  y4043, y4044, y4045,
				  y4046, y4047, y4048,
				  y4049, y4050, y4051,
				  y4052, y4053, y4054,
				  y4055, y4056, y4057,
				  y4058, y4059, y4060,
				 n - 1
                 ,d1,d2,d3);



















































		//0.975                      //0.64
	g = (1.0 / (gold * gold * gold ));

	double aj1 = (x46 - x52) / 2;
 	double aj2 = (x47 - x53) / 2;
 	double aj3 = (x48 - x54) / 2;

 	 l = sqrt( (aj1*aj1) + (aj2*aj2) + (aj3*aj3));
 	    //0.675
 	 d = 0.685 * gold;

 	aj1=pow(-1, k)*d * (aj1 / l);
 	aj2=pow(-1, k)*d * (aj2 / l);
 	aj3=pow(-1, k)*d * (aj3 / l);


	double xj01 = (x1 * g) + (aj1*d);
	double xj02 = (x2 * g) + (aj2*d);
	double xj03 = (x3 * g) + (aj3*d);


    double xj04 = (x4 * g) + (aj1*d);
	double xj05 = (x5 * g) + (aj2*d);
	double xj06 = (x6 * g) + (aj3*d);

	double xj07 = (x7 * g) + (aj1*d);
	double xj08 = (x8 * g) + (aj2*d);
	double xj09 = (x9 * g) + (aj3*d);

	double xj010 = (x10 * g) + (aj1*d);
	double xj011 = (x11 * g) + (aj2*d);
	double xj012 = (x12 * g) + (aj3*d);

	double xj013 = (x13 * g) + (aj1*d);
	double xj014 = (x14 * g) + (aj2*d);
	double xj015 = (x15 * g) + (aj3*d);

	double xj016 = (x16 * g) + (aj1*d);
	double xj017 = (x17 * g) + (aj2*d);
	double xj018 = (x18 * g) + (aj3*d);

	double xj019 = (x19 * g) + (aj1*d);
	double xj020 = (x20 * g) + (aj2*d);
	double xj021 = (x21 * g) + (aj3*d);

	double xj022 = (x22 * g) + (aj1*d);
	double xj023 = (x23 * g) + (aj2*d);
	double xj024 = (x24 * g) + (aj3*d);

	double xj025 = (x25 * g) + (aj1*d);
	double xj026 = (x26 * g) + (aj2*d);
	double xj027 = (x27 * g) + (aj3*d);

	double xj028 = (x28 * g) + (aj1*d);
	double xj029 = (x29 * g) + (aj2*d);
	double xj030 = (x30 * g) + (aj3*d);

	double xj031 = (x31 * g) + (aj1*d);
	double xj032 = (x32 * g) + (aj2*d);
	double xj033 = (x33 * g) + (aj3*d);


    double xj034 = (x34 * g) + (aj1*d);
	double xj035 = (x35 * g) + (aj2*d);
	double xj036 = (x36 * g) + (aj3*d);

	double xj037 = (x37 * g) + (aj1*d);
	double xj038 = (x38 * g) + (aj2*d);
	double xj039 = (x39 * g) + (aj3*d);

	double xj040 = (x40 * g) + (aj1*d);
	double xj041 = (x41 * g) + (aj2*d);
	double xj042 = (x42 * g) + (aj3*d);

	double xj043 = (x43 * g) + (aj1*d);
	double xj044 = (x44 * g) + (aj2*d);
	double xj045 = (x45 * g) + (aj3*d);

	double xj046 = (x46 * g) + (aj1*d);
	double xj047 = (x47 * g) + (aj2*d);
	double xj048 = (x48 * g) + (aj3*d);

	double xj049 = (x49 * g) + (aj1*d);
	double xj050 = (x50 * g) + (aj2*d);
	double xj051 = (x51 * g) + (aj3*d);

	double xj052 = (x52 * g) + (aj1*d);
	double xj053 = (x53 * g) + (aj2*d);
	double xj054 = (x54 * g) + (aj3*d);

	double xj055 = (x55 * g) + (aj1*d);
	double xj056 = (x56 * g) + (aj2*d);
	double xj057 = (x57 * g) + (aj3*d);

	double xj058 = (x58 * g) + (aj1*d);
	double xj059 = (x59 * g) + (aj2*d);
	double xj060 = (x60 * g) + (aj3*d);


	DrawDodeca(
                  xj01,  xj02,  xj03,
                  xj04,  xj05,  xj06,
                  xj07,  xj08,  xj09,
				  xj010, xj011, xj012,
				  xj013, xj014, xj015,
                  xj016, xj017, xj018,
                  xj019, xj020,  xj021,
				  xj022, xj023,  xj024,
				  xj025, xj026,  xj027,
                  xj028, xj029,  xj030,
                  xj031, xj032,  xj033,
				  xj034, xj035,  xj036,
				  xj037, xj038,  xj039,
				  xj040, xj041,  xj042,
				  xj043, xj044,  xj045,
				  xj046, xj047,  xj048,
				  xj049, xj050,  xj051,
				  xj052, xj053,  xj054,
				  xj055, xj056,  xj057,
				  xj058, xj059,  xj060,
				 n - 1
                 ,d1,d2,d3);



	 //0.975                      //0.64
	g = (1.0 / (gold * gold * gold ));

	double ai1 = (x40 - x43) / 2;
 	double ai2 = (x41 - x44) / 2;
 	double ai3 = (x42 - x45) / 2;

 	 l = sqrt( (ai1*ai1) + (ai2*ai2) + (ai3*ai3));
 	    //0.675
 	 d = 0.685 * gold;

 	ai1=pow(-1, k)*d * (ai1 / l);
 	ai2=pow(-1, k)*d * (ai2 / l);
 	ai3=pow(-1, k)*d * (ai3 / l);


	double xi01 = (x1 * g) + (ai1*d);
	double xi02 = (x2 * g) + (ai2*d);
	double xi03 = (x3 * g) + (ai3*d);


    double xi04 = (x4 * g) + (ai1*d);
	double xi05 = (x5 * g) + (ai2*d);
	double xi06 = (x6 * g) + (ai3*d);

	double xi07 = (x7 * g) + (ai1*d);
	double xi08 = (x8 * g) + (ai2*d);
	double xi09 = (x9 * g) + (ai3*d);

	double xi010 = (x10 * g) + (ai1*d);
	double xi011 = (x11 * g) + (ai2*d);
	double xi012 = (x12 * g) + (ai3*d);

	double xi013 = (x13 * g) + (ai1*d);
	double xi014 = (x14 * g) + (ai2*d);
	double xi015 = (x15 * g) + (ai3*d);

	double xi016 = (x16 * g) + (ai1*d);
	double xi017 = (x17 * g) + (ai2*d);
	double xi018 = (x18 * g) + (ai3*d);

	double xi019 = (x19 * g) + (ai1*d);
	double xi020 = (x20 * g) + (ai2*d);
	double xi021 = (x21 * g) + (ai3*d);

	double xi022 = (x22 * g) + (ai1*d);
	double xi023 = (x23 * g) + (ai2*d);
	double xi024 = (x24 * g) + (ai3*d);

	double xi025 = (x25 * g) + (ai1*d);
	double xi026 = (x26 * g) + (ai2*d);
	double xi027 = (x27 * g) + (ai3*d);

	double xi028 = (x28 * g) + (ai1*d);
	double xi029 = (x29 * g) + (ai2*d);
	double xi030 = (x30 * g) + (ai3*d);

	double xi031 = (x31 * g) + (ai1*d);
	double xi032 = (x32 * g) + (ai2*d);
	double xi033 = (x33 * g) + (ai3*d);


    double xi034 = (x34 * g) + (ai1*d);
	double xi035 = (x35 * g) + (ai2*d);
	double xi036 = (x36 * g) + (ai3*d);

	double xi037 = (x37 * g) + (ai1*d);
	double xi038 = (x38 * g) + (ai2*d);
	double xi039 = (x39 * g) + (ai3*d);

	double xi040 = (x40 * g) + (ai1*d);
	double xi041 = (x41 * g) + (ai2*d);
	double xi042 = (x42 * g) + (ai3*d);

	double xi043 = (x43 * g) + (ai1*d);
	double xi044 = (x44 * g) + (ai2*d);
	double xi045 = (x45 * g) + (ai3*d);

	double xi046 = (x46 * g) + (ai1*d);
	double xi047 = (x47 * g) + (ai2*d);
	double xi048 = (x48 * g) + (ai3*d);

	double xi049 = (x49 * g) + (ai1*d);
	double xi050 = (x50 * g) + (ai2*d);
	double xi051 = (x51 * g) + (ai3*d);

	double xi052 = (x52 * g) + (ai1*d);
	double xi053 = (x53 * g) + (ai2*d);
	double xi054 = (x54 * g) + (ai3*d);

	double xi055 = (x55 * g) + (ai1*d);
	double xi056 = (x56 * g) + (ai2*d);
	double xi057 = (x57 * g) + (ai3*d);

	double xi058 = (x58 * g) + (ai1*d);
	double xi059 = (x59 * g) + (ai2*d);
	double xi060 = (x60 * g) + (ai3*d);


	DrawDodeca(
                  xi01,  xi02,  xi03,
                  xi04,  xi05,  xi06,
                  xi07,  xi08,  xi09,
				  xi010, xi011, xi012,
				  xi013, xi014, xi015,
                  xi016, xi017, xi018,
                  xi019, xi020,  xi021,
				  xi022, xi023,  xi024,
				  xi025, xi026,  xi027,
                  xi028, xi029,  xi030,
                  xi031, xi032,  xi033,
				  xi034, xi035,  xi036,
				  xi037, xi038,  xi039,
				  xi040, xi041,  xi042,
				  xi043, xi044,  xi045,
				  xi046, xi047,  xi048,
				  xi049, xi050,  xi051,
				  xi052, xi053,  xi054,
				  xi055, xi056,  xi057,
				  xi058, xi059,  xi060,
				 n - 1
                 ,d1,d2,d3);




	 //0.975                      //0.64
	g = (1.0 / (gold * gold * gold ));

	double ak1 = (x55 - x22) / 2;
 	double ak2 = (x56 - x23) / 2;
 	double ak3 = (x57 - x24) / 2;

 	 l = sqrt( (ak1*ak1) + (ak2*ak2) + (ak3*ak3));
 	    //0.675
 	 d = 0.685 * gold;

 	ak1=pow(-1, k)*d * (ak1 / l);
 	ak2=pow(-1, k)*d * (ak2 / l);
 	ak3=pow(-1, k)*d * (ak3 / l);


	double xk01 = (x1 * g) + (ak1*d);
	double xk02 = (x2 * g) + (ak2*d);
	double xk03 = (x3 * g) + (ak3*d);

    double xk04 = (x4 * g) + (ak1*d);
	double xk05 = (x5 * g) + (ak2*d);
	double xk06 = (x6 * g) + (ak3*d);

	double xk07 = (x7 * g) + (ak1*d);
	double xk08 = (x8 * g) + (ak2*d);
	double xk09 = (x9 * g) + (ak3*d);

	double xk010 = (x10 * g) + (ak1*d);
	double xk011 = (x11 * g) + (ak2*d);
	double xk012 = (x12 * g) + (ak3*d);

	double xk013 = (x13 * g) + (ak1*d);
	double xk014 = (x14 * g) + (ak2*d);
	double xk015 = (x15 * g) + (ak3*d);

	double xk016 = (x16 * g) + (ak1*d);
	double xk017 = (x17 * g) + (ak2*d);
	double xk018 = (x18 * g) + (ak3*d);

	double xk019 = (x19 * g) + (ak1*d);
	double xk020 = (x20 * g) + (ak2*d);
	double xk021 = (x21 * g) + (ak3*d);

	double xk022 = (x22 * g) + (ak1*d);
	double xk023 = (x23 * g) + (ak2*d);
	double xk024 = (x24 * g) + (ak3*d);

	double xk025 = (x25 * g) + (ak1*d);
	double xk026 = (x26 * g) + (ak2*d);
	double xk027 = (x27 * g) + (ak3*d);

	double xk028 = (x28 * g) + (ak1*d);
	double xk029 = (x29 * g) + (ak2*d);
	double xk030 = (x30 * g) + (ak3*d);

	double xk031 = (x31 * g) + (ak1*d);
	double xk032 = (x32 * g) + (ak2*d);
	double xk033 = (x33 * g) + (ak3*d);

    double xk034 = (x34 * g) + (ak1*d);
	double xk035 = (x35 * g) + (ak2*d);
	double xk036 = (x36 * g) + (ak3*d);

	double xk037 = (x37 * g) + (ak1*d);
	double xk038 = (x38 * g) + (ak2*d);
	double xk039 = (x39 * g) + (ak3*d);

	double xk040 = (x40 * g) + (ak1*d);
	double xk041 = (x41 * g) + (ak2*d);
	double xk042 = (x42 * g) + (ak3*d);

	double xk043 = (x43 * g) + (ak1*d);
	double xk044 = (x44 * g) + (ak2*d);
	double xk045 = (x45 * g) + (ak3*d);

	double xk046 = (x46 * g) + (ak1*d);
	double xk047 = (x47 * g) + (ak2*d);
	double xk048 = (x48 * g) + (ak3*d);

	double xk049 = (x49 * g) + (ak1*d);
	double xk050 = (x50 * g) + (ak2*d);
	double xk051 = (x51 * g) + (ak3*d);

	double xk052 = (x52 * g) + (ak1*d);
	double xk053 = (x53 * g) + (ak2*d);
	double xk054 = (x54 * g) + (ak3*d);

	double xk055 = (x55 * g) + (ak1*d);
	double xk056 = (x56 * g) + (ak2*d);
	double xk057 = (x57 * g) + (ak3*d);

	double xk058 = (x58 * g) + (ak1*d);
	double xk059 = (x59 * g) + (ak2*d);
	double xk060 = (x60 * g) + (ak3*d);


	DrawDodeca(
                  xk01,  xk02,  xk03,
                  xk04,  xk05,  xk06,
                  xk07,  xk08,  xk09,
				  xk010, xk011, xk012,
				  xk013, xk014, xk015,
                  xk016, xk017, xk018,
                  xk019, xk020,  xk021,
				  xk022, xk023,  xk024,
				  xk025, xk026,  xk027,
                  xk028, xk029,  xk030,
                  xk031, xk032,  xk033,
				  xk034, xk035,  xk036,
				  xk037, xk038,  xk039,
				  xk040, xk041,  xk042,
				  xk043, xk044,  xk045,
				  xk046, xk047,  xk048,
				  xk049, xk050,  xk051,
				  xk052, xk053,  xk054,
				  xk055, xk056,  xk057,
				  xk058, xk059,  xk060,
				 n - 1
                 ,d1,d2,d3);


     //0.975                      //0.64
	g = (1.0 / (gold * gold * gold ));

	double al1 = (x16 - x19) / 2;
 	double al2 = (x17 - x20) / 2;
 	double al3 = (x18 - x21) / 2;



 	double le = sqrt( (al1*al1) + (al2*al2) + (al3*al3));
 	    //0.675
 	 d = 0.685 * gold;

 	al1=pow(-1, k)*d * (al1 / le);
 	al2=pow(-1, k)*d * (al2 / le);
 	al3=pow(-1, k)*d * (al3 / le);


	double xl01 = (x1 * g) + (al1*d);
	double xl02 = (x2 * g) + (al2*d);
	double xl03 = (x3 * g) + (al3*d);

    double xl04 = (x4 * g) + (al1*d);
	double xl05 = (x5 * g) + (al2*d);
	double xl06 = (x6 * g) + (al3*d);

	double xl07 = (x7 * g) + (al1*d);
	double xl08 = (x8 * g) + (al2*d);
	double xl09 = (x9 * g) + (al3*d);

	double xl010 = (x10 * g) + (al1*d);
	double xl011 = (x11 * g) + (al2*d);
	double xl012 = (x12 * g) + (al3*d);

	double xl013 = (x13 * g) + (al1*d);
	double xl014 = (x14 * g) + (al2*d);
	double xl015 = (x15 * g) + (al3*d);

	double xl016 = (x16 * g) + (al1*d);
	double xl017 = (x17 * g) + (al2*d);
	double xl018 = (x18 * g) + (al3*d);

	double xl019 = (x19 * g) + (al1*d);
	double xl020 = (x20 * g) + (al2*d);
	double xl021 = (x21 * g) + (al3*d);

	double xl022 = (x22 * g) + (al1*d);
	double xl023 = (x23 * g) + (al2*d);
	double xl024 = (x24 * g) + (al3*d);

	double xl025 = (x25 * g) + (al1*d);
	double xl026 = (x26 * g) + (al2*d);
	double xl027 = (x27 * g) + (al3*d);

	double xl028 = (x28 * g) + (al1*d);
	double xl029 = (x29 * g) + (al2*d);
	double xl030 = (x30 * g) + (al3*d);

	double xl031 = (x31 * g) + (al1*d);
	double xl032 = (x32 * g) + (al2*d);
	double xl033 = (x33 * g) + (al3*d);

    double xl034 = (x34 * g) + (al1*d);
	double xl035 = (x35 * g) + (al2*d);
	double xl036 = (x36 * g) + (al3*d);

	double xl037 = (x37 * g) + (al1*d);
	double xl038 = (x38 * g) + (al2*d);
	double xl039 = (x39 * g) + (al3*d);

	double xl040 = (x40 * g) + (al1*d);
	double xl041 = (x41 * g) + (al2*d);
	double xl042 = (x42 * g) + (al3*d);

	double xl043 = (x43 * g) + (al1*d);
	double xl044 = (x44 * g) + (al2*d);
	double xl045 = (x45 * g) + (al3*d);

	double xl046 = (x46 * g) + (al1*d);
	double xl047 = (x47 * g) + (al2*d);
	double xl048 = (x48 * g) + (al3*d);

	double xl049 = (x49 * g) + (al1*d);
	double xl050 = (x50 * g) + (al2*d);
	double xl051 = (x51 * g) + (al3*d);

	double xl052 = (x52 * g) + (al1*d);
	double xl053 = (x53 * g) + (al2*d);
	double xl054 = (x54 * g) + (al3*d);

	double xl055 = (x55 * g) + (al1*d);
	double xl056 = (x56 * g) + (al2*d);
	double xl057 = (x57 * g) + (al3*d);

	double xl058 = (x58 * g) + (al1*d);
	double xl059 = (x59 * g) + (al2*d);
	double xl060 = (x60 * g) + (al3*d);


	DrawDodeca(
                  xl01,  xl02,  xl03,
                  xl04,  xl05,  xl06,
                  xl07,  xl08,  xl09,
				  xl010, xl011, xl012,
				  xl013, xl014, xl015,
                  xl016, xl017, xl018,
                  xl019, xl020,  xl021,
				  xl022, xl023,  xl024,
				  xl025, xl026,  xl027,
                  xl028, xl029,  xl030,
                  xl031, xl032,  xl033,
				  xl034, xl035,  xl036,
				  xl037, xl038,  xl039,
				  xl040, xl041,  xl042,
				  xl043, xl044,  xl045,
				  xl046, xl047,  xl048,
				  xl049, xl050,  xl051,
				  xl052, xl053,  xl054,
				  xl055, xl056,  xl057,
				  xl058, xl059,  xl060,
				 n - 1
                 ,d1,d2,d3);


//0.975                      //0.64
	g = (1.0 / (gold * gold * gold ));

	double am1 = (x49 - x58) / 2;
 	double am2 = (x50 - x59) / 2;
 	double am3 = (x51 - x60) / 2;

 	 l = sqrt( (am1*am1) + (am2*am2) + (am3*am3));
 	    //0.675
 	 d = 0.685 * gold;

 	am1=pow(-1, k)*d * (am1 / l);
 	am2=pow(-1, k)*d * (am2 / l);
 	am3=pow(-1, k)*d * (am3 / l);


	double xm01 = (x1 * g) + (am1*d);
	double xm02 = (x2 * g) + (am2*d);
	double xm03 = (x3 * g) + (am3*d);

    double xm04 = (x4 * g) + (am1*d);
	double xm05 = (x5 * g) + (am2*d);
	double xm06 = (x6 * g) + (am3*d);

	double xm07 = (x7 * g) + (am1*d);
	double xm08 = (x8 * g) + (am2*d);
	double xm09 = (x9 * g)   + (am3*d);

	double xm010 = (x10 * g) + (am1*d);
	double xm011 = (x11 * g) + (am2*d);
	double xm012 = (x12 * g) + (am3*d);

	double xm013 = (x13 * g) + (am1*d);
	double xm014 = (x14 * g) + (am2*d);
	double xm015 = (x15 * g) + (am3*d);

	double xm016 = (x16 * g) + (am1*d);
	double xm017 = (x17 * g) + (am2*d);
	double xm018 = (x18 * g) + (am3*d);

	double xm019 = (x19 * g) + (am1*d);
	double xm020 = (x20 * g) + (am2*d);
	double xm021 = (x21 * g) + (am3*d);

	double xm022 = (x22 * g) + (am1*d);
	double xm023 = (x23 * g) + (am2*d);
	double xm024 = (x24 * g) + (am3*d);

	double xm025 = (x25 * g) + (am1*d);
	double xm026 = (x26 * g) + (am2*d);
	double xm027 = (x27 * g) + (am3*d);

	double xm028 = (x28 * g) + (am1*d);
	double xm029 = (x29 * g) + (am2*d);
	double xm030 = (x30 * g) + (am3*d);

	double xm031 = (x31 * g) + (am1*d);
	double xm032 = (x32 * g) + (am2*d);
	double xm033 = (x33 * g) + (am3*d);

    double xm034 = (x34 * g) + (am1*d);
	double xm035 = (x35 * g) + (am2*d);
	double xm036 = (x36 * g) + (am3*d);

	double xm037 = (x37 * g) + (am1*d);
	double xm038 = (x38 * g) + (am2*d);
	double xm039 = (x39 * g) + (am3*d);

	double xm040 = (x40 * g) + (am1*d);
	double xm041 = (x41 * g) + (am2*d);
	double xm042 = (x42 * g) + (am3*d);

	double xm043 = (x43 * g) + (am1*d);
	double xm044 = (x44 * g) + (am2*d);
	double xm045 = (x45 * g) + (am3*d);

	double xm046 = (x46 * g) + (am1*d);
	double xm047 = (x47 * g) + (am2*d);
	double xm048 = (x48 * g) + (am3*d);

	double xm049 = (x49 * g) + (am1*d);
	double xm050 = (x50 * g) + (am2*d);
	double xm051 = (x51 * g) + (am3*d);

	double xm052 = (x52 * g) + (am1*d);
	double xm053 = (x53 * g) + (am2*d);
	double xm054 = (x54 * g) + (am3*d);

	double xm055 = (x55 * g) + (am1*d);
	double xm056 = (x56 * g) + (am2*d);
	double xm057 = (x57 * g) + (am3*d);

	double xm058 = (x58 * g) + (am1*d);
	double xm059 = (x59 * g) + (am2*d);
	double xm060 = (x60 * g) + (am3*d);


	DrawDodeca(
                  xm01,  xm02,  xm03,
                  xm04,  xm05,  xm06,
                  xm07,  xm08,  xm09,
				  xm010, xm011, xm012,
				  xm013, xm014, xm015,
                  xm016, xm017, xm018,
                  xm019, xm020,  xm021,
				  xm022, xm023,  xm024,
				  xm025, xm026,  xm027,
                  xm028, xm029,  xm030,
                  xm031, xm032,  xm033,
				  xm034, xm035,  xm036,
				  xm037, xm038,  xm039,
				  xm040, xm041,  xm042,
				  xm043, xm044,  xm045,
				  xm046, xm047,  xm048,
				  xm049, xm050,  xm051,
				  xm052, xm053,  xm054,
				  xm055, xm056,  xm057,
				  xm058, xm059,  xm060,
				 n - 1
                 ,d1,d2,d3);
























	};




	  }








}

}




};

/* SIGUIENTE:

- Cuidado con la UseVector en writeVectorAtIndex.
- Añadir comentarios.

*/


// ================ CLASS CONSTRUCTOR ================== //

//Class constructor. Initializes the file writer.
POVRayWriter::POVRayWriter(string path)
{
    writer.open(path.c_str());

    if (writer.is_open())
    {
            filePath = path;
            writer << "// Visualing Topology" << endl;
            writer << "// Miguels Topology Master" << endl << endl;

            writer << "#include \"colors.inc\" " << endl;
            writer << "#include \"textures.inc\" " << endl;
            writer << "#include \"glass.inc\" " << endl;
            writer << "#include \"golds.inc\" " << endl;
            writer << "#include \"metals.inc\" " << endl<<endl;
            writer << "background { color Black} " << endl << endl;
    }

    finish = pigment = checker = defaultFinish = defaultPigment = inBlob = rotation = texture = false;
    pi = 3.14159265358;
    return;
}

//Returns the clock variable of POV-Ray
string POVRayWriter::Clock()
{
    return "clock";
}

//Creates a ini animation file with the specified number of frames, starting
//at initClock and ending at endClock. The file will be created in the path specified.
void POVRayWriter::createIniFile(string path,int frames, int initClock, int endClock)
{
    iniCreator.open(path.c_str());

    iniCreator << "; INI File Generated with Victor Buendia's POVRayWriter" << endl;
    iniCreator << "Input_File_Name = " << filePath << endl;
    iniCreator << "Initial_Frame = 0" << endl << "Final_Frame = " << frames << endl;
    iniCreator << "Initial_Clock = " << initClock << endl << "Final_Clock = " << endClock << endl;

    iniCreator.close();
    return;
}

//Create a ini animation file in the path given, with the specified frames.
//InitClock and endClock will be adjusted to make a relation 1:1 between
//frames and clocks; this is useful for arrays.
void POVRayWriter::createIniFile(string path, int frames)
{
    iniCreator.open(path.c_str());

    iniCreator << "; INI File Generated with Victor Buendia's POVRayWriter" << endl;
    iniCreator << "Input_File_Name = " << filePath << endl;
    iniCreator << "Initial_Frame = 0" << endl << "Final_Frame = " << frames << endl;
    iniCreator << "Initial_Clock = 0" << endl << "Final_Clock = " << frames << endl;

    iniCreator.close();
    return;
}

//Allows the user to write custom content.
void POVRayWriter::write(string str)
{
    writer << str;
    return;
}

//Close the final.
//IT'S VERY IMPORTANT TO INVOKE THIS FUNCTION AFTER FINISH.
void POVRayWriter::closePOVRayWriter()
{
    writer.close();
    return;
}


// ================= PRIMITIVE CREATION ============================ //

//Create a standard camera from its positions and the point that is looking at.
void POVRayWriter::createCamera(double xi, double yi, double zi, double xf, double yf, double zf)
{
    writer << "camera { " << endl;
    writer << "location ";
    writeVector(xi, yi, zi);
    writer << endl << "look_at ";
    writeVector(xf, yf, zf);
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;

    return;
}

void POVRayWriter::ultra_wide_Camera(const Vector3D& position, const Vector3D& lookAt, double angle)
{
    writer << "camera { " << endl;
    writer << "  ultra_wide_angle " << endl;
    writer << "  location ";
    writeVector(position.x(), position.y(), position.z());
    writer << endl << "  look_at ";
    writeVector(lookAt.x(), lookAt.y(), lookAt.z());
//    writer << endl << "  look_at ";
//    writeVector(sky.x(), sky.y(), sky.z());
    writer << "  right x*image_width/image_height" << endl;
    writer << "angle "; writer << angle << endl;
    writer << "} " << endl << endl;

    return;
}

//Create a light with custom position and RGB color.
void POVRayWriter::createLight(double x, double y, double z, double r, double g, double b)
{
    writer << "light_source {" << endl;
    writeVector(x,y,z);
    writer << endl << "color rgb <" << r <<", " << g << ", " << b << ">" << endl;
    writer << "} " << endl << endl;

    return;
}

//Create a light with a standard color at the specified position
void POVRayWriter::createLight(double x, double y, double z)
{
    writer << "light_source {" << endl;
    writeVector(x,y,z);
    writer << endl << "color rgb <1,1,1>" << endl;
    writer << "} " << endl << endl;

    return;
}

void POVRayWriter::createLight(const Vector3D& position)
{
  writer << "light_source {" << endl;
  writeVector(position.x(), position.y(), position.z());
  writer << endl << "color rgb <0.5, 0.5, 0.5>" << endl;
  writer << "} " << endl << endl;

  return;
}

void POVRayWriter::spotLight(const Vector3D& position, const Vector3D& lookAt)
{
    writer << "light_source {" << endl;
    writeVector(0, 0, 0);
    writer << endl << "color rgb <1,1,1>" << endl;
    writer << "spotlight" << endl;
    writer << "translate "; writeVector(position.x(), position.y(), position.z()); writer << " " << endl;
    writer << "point_at "; writeVector(lookAt.x(), lookAt.y(), lookAt.z()); writer << " " << endl;
    writer << "radius 20" << endl;
    writer << "tightness 50" << endl;
    writer << "falloff 8" << endl;
    writer << "} " << endl << endl;

    return;
}

//Create a sphere with the radious and coordinates indicated
void POVRayWriter::createSphere(double r, double x, double y, double z)
{
    writer << "sphere {" << endl;

    writeVector(x,y,z);

    writer << r; //<< endl;


	T_Gold_1A();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}//Paint(r, g, bb);

void POVRayWriter::createSphere(double r, const Vector3D& c, double rr, double gg, double bb) {
    
    writer << "sphere {" << endl;
    writeVector(c.x(), c.y(), c.z());
    writer << r << endl;
	
    Paint(rr, gg, bb);

    writer << "}" << endl << endl;

    return;
}


void POVRayWriter::createTriangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    writer << "polygon {" << endl;
    writer << 3; //<< endl;
    writeVector(x1, y1, z1);
    writeVector(x2, y2, z2);
    writeVector(x3, y3, z3);

    writeBlob();
    writeTexture();
    writeFinish();
    writePigment();

    writeRotation();
    writer << "}" << endl << endl;

    return;
}

void POVRayWriter::mirrorTexture() {
  writer << "texture{ Polished_Chrome" << endl;
  writer << "         pigment{ color rgb<1, 1, 1> }" << endl;
  //writer << "         normal { crackle 5.5 scale 0.20 }" <<endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "       }" << endl;
return;
}

void POVRayWriter::woodTexture() {
  writer << "texture{" << endl;
  writer << "pigment{ wood turbulence 0.02 octaves 4 lambda 3"<<endl;
  writer << "scale 10.75  rotate <2, 3, 0>" << endl;
  writer << "color_map {" << endl;
  writer << "[0.0 color rgb <1.00, 0.88, 0.54>]" << endl;
  writer << "[0.1 color rgb <1.00, 0.80, 0.54>]" << endl;
  writer << "[0.5 color rgb <0.70, 0.42, 0.23>]" << endl;
  writer << "[0.7 color rgb <0.70, 0.42, 0.23>]" << endl;
  writer << "[1.0 color rgb <1.00, 0.88, 0.54>]" << endl;
  writer << "}" << endl;
  writer << "}" << endl;
  writer << "finish { phong 1 }" << endl;
  writer << "rotate <0,0, 0>  scale 1  translate <0,0,0>" << endl;
  writer << "}" << endl;
}

void POVRayWriter::glassTexture1() {
  writer << " " << endl;
  writer << "material{ texture{ Glass3  }" << endl;
  writer << "          interior{I_Glass }" << endl;
  writer << "}" << endl << endl;
}

void POVRayWriter::glassTexture2() {
  writer << " " << endl;
  writer << "material{ texture{ NBglass  }" << endl;
  writer << "          interior{I_Glass }" << endl;
  writer << "}" << endl << endl;
}

void POVRayWriter::glassTexture3() {
  writer << " " << endl;
  writer << "texture{ pigment{ rgbf <0.98, 0.98, 0.98, 0.9> }" << endl;
  writer << "         finish {diffuse 0.1 reflection 0.2" << endl;
  writer << "         specular 0.8 roughness 0.0003 phong 1 phong_size 400}" << endl;
  writer << "       }" << endl << endl;
}


void POVRayWriter::marbleTexture1() {
  writer << "texture{ " << endl;
  writer << "         pigment{ White_Marble }" << endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "         scale 2.0" << endl;
  writer << "       }" << endl;
}

void POVRayWriter::T_Gold_1A() {
  writer << "texture{ T_Gold_1A" << endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "       }" << endl;
}

void POVRayWriter::T_Chrome_5A() {
  writer << "\n texture{ T_Chrome_5A" << endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "       }" << endl;
}

void POVRayWriter::swirlTexture() {
  writer << "texture{ pigment{ spiral1 5 rotate<90,0,0>"<< endl;
  writer << "color_map{"<<endl;
  writer << "[0.0 color rgb<1, 1, 1>]"<<endl;
  writer << "[0.5 color rgb<1, 1, 1>]"<<endl;
  writer << "[0.5 color rgb<1, 0, 0>]"<<endl;
  writer << "[1.0 color rgb<1, 0, 0>]"<<endl;
  writer << "}"<<endl;
  writer << "scale 0.5"<<endl;
  writer << "}"<<endl;
  writer << "finish {phong 1 reflection 0.3}"<<endl;
  writer << "}"<<endl << endl;
}

void POVRayWriter::photons() {
  writer << "photons{" << endl;
  writer << "   target 1.0" << endl;
  writer << "   refraction on" << endl;
  writer << "   reflection on" << endl;
  writer << "       }" << endl;
}


void POVRayWriter::Triangle(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    writer << "polygon {" << endl;
    writer << 3; //<< endl;
    writeVector(a.x(), a.y(), a.z());
    writeVector(b.x(), b.y(), b.z());
    writeVector(c.x(), c.y(), c.z());

//swirlTexture();
//woodTexture();
mirrorTexture();
//glassTexture1();
//glassTexture1();
//marbleTexture1();
photons();

//writer << "clipped_by { box{<-12, -12, -12>, <12, 12, 12>} }" << endl;

    writer << "}" << endl << endl;
    return;
}

void POVRayWriter::facet(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    writer << "polygon {" << endl;
    writer << 3; //<< endl;
    writeVector(a.x(), a.y(), a.z());
    writeVector(b.x(), b.y(), b.z());
    writeVector(c.x(), c.y(), c.z());

//swirlTexture();
//woodTexture();
mirrorTexture();
//glassTexture1();
//glassTexture1();
//marbleTexture1();
photons();

//writer << "clipped_by { box{<-12, -12, -12>, <12, 12, 12>} }" << endl;

    writer << "}" << endl << endl;
    return;
}

void POVRayWriter::facetGlass(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    writer << "polygon {" << endl;
    writer << 3; //<< endl;
    writeVector(a.x(), a.y(), a.z());
    writeVector(b.x(), b.y(), b.z());
    writeVector(c.x(), c.y(), c.z());
//swirlTexture();
T_Gold_1A();
//woodTexture();
//mirrorTexture();
//glassTexture3();
//glassTexture1();
//marbleTexture1();
photons();

//writer << "clipped_by { box{<-12, -12, -12>, <12, 12, 12>} }" << endl;

    writer << "}" << endl << endl;

    Cylinder(a, b, 0.05 * abs(a-b));
    writer << endl;
    return;
}

void POVRayWriter::Square(Vector3D a0, Vector3D a1, Vector3D a2, Vector3D a3, double width, bool T) {
  if (T == true) {
    facet(a0, a1, a2);
    facet(a2, a3, a0);
  }

  Cylinder(a0, a1, width);
  Cylinder(a1, a2, width);
  //Cylinder(a2, a3, width);
  //Cylinder(a3, a0, width);

  return;
}

void POVRayWriter::Triangle1(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    writer << "polygon {" << endl;
    writer << 3; //<< endl;
    writeVector(a.x(), a.y(), a.z());
    writeVector(b.x(), b.y(), b.z());
    writeVector(c.x(), c.y(), c.z());


    woodTexture();
    writer << "}" << endl << endl;
    return;
}
//Creates an sphere with radious and a vector array
//Needs to be initialized with setNextObjectPosFromVector function
void POVRayWriter::createSphere(double r)
{
    writer << "sphere {" << endl;

    writeVectorAtIndex();
    writer << r;// << endl;

    writeBlob();
    writeFinish();
    writeTexture();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Create a plane with the normal vector and distances indicated
void POVRayWriter::createPlane(double n1, double n2, double n3, double d)
{
    writer << "plane {" << endl;
    writeVector(n1, n2, n3);
    writer << ", " <<  d << endl;

    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;
    return;
}

//Create a plane perpendicular to the selected vector, at
//a d distance.
void POVRayWriter::createPlane(double d)
{
    writer << "plane {" << endl;
    writeVectorAtIndex();
    writer << d << endl;

    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;
    return;
}

//Create a plane from its formula, like "x" or "3*z" at a d distance.
void POVRayWriter::createPlane(string plane, double d)
{
    writer << "plane {" << endl;
    writer << plane << ",  " << d << endl;

    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;
    return;
}

void POVRayWriter::Plane(string plane, double d)
{
    writer << "plane {" << endl;
    writer << plane << ",  " << d << endl;

    writer << "pigment{ " << endl;
    writer << "             tiling 14" << endl;
    writer << "                color_map{" << endl;
    writer << "                  [ 0.0 color rgb<1, 1, 1>*1]" << endl;
    writer << "                  [ 0.5 color rgb<0, 0, 0>*1]" << endl;
    writer << "                  [ 1.0 color rgb<0.5, 0.5, 0.5>*0]" << endl;
    writer << "                  }" << endl;
    writer << "             scale 10.5" << endl;
    writer << "       }" << endl;

    writer << "}" << endl << endl;
    return;
}

//Creates a bnx from the upper left corner and down right corner.
void POVRayWriter::createBox(double xi, double yi, double zi, double xf, double yf, double zf)
{
    writer << "box {" << endl;
    writeVector(xi,yi,zi);
    writeVector(xf, yf, zf);

    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a box substituting the first vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
void POVRayWriter::createBoxInitFromVectorArray(double xf, double yf, double zf)
{
    writer << "box {" << endl;
    writeVectorAtIndex();
    writeVector(xf, yf, zf);

    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a box substituting the last vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
void POVRayWriter::createBoxLastFromVectorArray(double xi, double yi, double zi)
{
    writer << "box {" << endl;
    writeVector(xi, yi, zi);
    writeVectorAtIndex();


    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a box using the vectors indicated.
void POVRayWriter::createBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex)
{
    writer << "box {" << endl;

    setNextObjectPosFromVector(initVector,initIndex);
    writeVectorAtIndex();
    setNextObjectPosFromVector(lastVector,lastIndex);
    writeVectorAtIndex();


    writer << endl;
    writeTexture();
    writeFinish();
    writePigment();
    writeRotation();
    writer << "}" << endl << endl;

    return;
}

//Creates a basic cylinder from the position of its faces and a radious.
 void POVRayWriter::createCylinder(double xi, double yi, double zi, double xf, double yf, double zf, double r)
 {
     writer << "cylinder {" << endl;
     writeVector(xi, yi, zi);
     writeVector(xf, yf, zf);
     writer << r; //<< endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

 void POVRayWriter::Cylinder(const Vector3D& a, const Vector3D& b, double r)
 {

	if (abs(a-b) > 1e-5) {
     writer << "cylinder {" << endl;
     writeVector(b.x(), b.y(), b.z());
     writeVector(a.x(), a.y(), a.z());
     writer << r; //<< endl;

     T_Gold_1A();

     writer << "}" << endl << endl;
	}
     return;
 }

 void POVRayWriter::Cylinder1(const Vector3D& a, const Vector3D& b, double r)
 {
     writer << "cylinder {" << endl;
     writeVector(b.x(), b.y(), b.z());
     writeVector(a.x(), a.y(), a.z());
     writer << r; //<< endl;

     T_Chrome_5A();

     writer << "}" << endl << endl;

     return;
 }

 //Creates a cylinder substituting the first vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
  void POVRayWriter::createCylinderInitFromVectorArray(double xf, double yf, double zf, double r)
 {
     writer << "cylinder {" << endl;
     writeVectorAtIndex();
     writeVector(xf, yf, zf);
     writer << r;// << endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

  //Creates a cylinder substituting the last vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
  void POVRayWriter::createCylinderLastFromVectorArray(double xi, double yi, double zi, double r)
 {
     writer << "cylinder {" << endl;
    writeVector(xi, yi, zi);
    writeVectorAtIndex();
     writer << r; //<< endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

  //Creates a cylinder substituting the last vector by the vector array at the index selected by
//setNextObjectPosFromVector, which is mandatory to use.
  void POVRayWriter::createCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r)
 {
     writer << "cylinder {" << endl;

    setNextObjectPosFromVector(initVector,initIndex);
    writeVectorAtIndex();
    setNextObjectPosFromVector(lastVector,lastIndex);
    writeVectorAtIndex();

    writer << r;// << endl;

     writeBlob();
     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();
     writer << "}" << endl << endl;

     return;
 }

 //Creates a torus using the major radious (from center to middle line) and the
 //minor radious of the torus, in the position specified by the function
 //setNextObjectPosFromVector.
 void POVRayWriter::createTorus(double middleR, double minorR)
 {
     writer << "torus {" << endl << middleR << ", " << minorR << endl;

     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();

     writer << "translate ";
     writeVectorAtIndex();

     writer << "}" << endl << endl;

     return;
 }

 //Creates a torus using the major radious (from center to middle line) and the
 //minor radious of the torus, in the indicated position
 void POVRayWriter::createTorus(double x, double y, double z, double middleR, double minorR)
 {
     writer << "torus {" << endl << middleR << ", " << minorR << endl;

     writeTexture();
     writeFinish();
     writePigment();
     writeRotation();

     writer << "translate ";
     writeVector(x,y,z);

     writer << "}" << endl << endl;

     return;
 }




// ========================== DECORATED PRIMITIVE CREATION ==================== //

/* Creates a camera using a vector; The vector can substitute the location, the look_at or both.
Note the first two (which only substitute one parameter) needs to be initialized with
setNextObjectPosFromVector function.
The other two don't need this sentence.*/


void POVRayWriter::createCameraLocationFromVectorArray(double xf, double yf, double zf)
{
    writer << "camera { " << endl;
    writer << "location ";
    writeVectorAtIndex();
    writer << endl << "look_at ";
    writeVector(xf, yf, zf);
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;

    return;
}

void POVRayWriter::createCameraLookingAtFromVectorArray(double xi, double yi, double zi)
{
    writer << "camera { " << endl;
    writer << "location ";
    writeVector(xi, yi, zi);
    writer << endl << "look_at ";
    writeVectorAtIndex();
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;

}

void POVRayWriter::createCameraFromVectorArray(string vectorLocation, string vectorLookAt, string indexPos, string indexLookingAt)
{
    setNextObjectPosFromVector(vectorLocation, indexPos);

    writer << "camera { " << endl;
    writer << "location ";
    writeVectorAtIndex();

    setNextObjectPosFromVector(vectorLookAt, indexLookingAt);

    writer << endl << "look_at ";
    writeVectorAtIndex();
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;


    return;
}

void POVRayWriter::createCameraFromVectorArray(string vectorToUse, string indexPos, string indexLookingAt)
{
    setNextObjectPosFromVector(vectorToUse, indexPos);

    writer << "camera { " << endl;
    writer << "location ";
    writeVectorAtIndex();

    setNextObjectPosFromVector(vectorToUse, indexLookingAt);

    writer << endl << "look_at ";
    writeVectorAtIndex();
    writer << endl << "sky <0,0,1>" << endl << "} " << endl << endl;


    return;
}

/* Creates the same primitive shapes, but with a predefined color and a standard value
of phong = 0.5. NOTE: if you want to add a custom rgb color o custum finish / pigment properties
you should use the primitives instead of this functions. */

void POVRayWriter::createStandardSphere(double r, double x, double y, double z, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createSphere(r,x,y,z);

    return;
}

void POVRayWriter::createStandardTriangle(
  double x1, double y1, double z1,
  double x2, double y2, double z2,
  double x3, double y3, double z3, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);

    return;
}

void POVRayWriter::colorTriangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    Triangle(a, b, c);

    return;
}

void POVRayWriter::smallDodeca(double r, const Vector3D& center, double width) {
     double gold= (1 + sqrt(5))/2;
     double g1= 1/gold;
     double g2= 1/(gold*gold);
     double s = gold;
     Vector3D v[32] = {
       Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +         1.0*r),
       Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +         1.0*r),
       Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +          g1*r),
       Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +          g2*r),
       Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +          g1*r),
       Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +          g2*r),
       Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +          g1*r),
       Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +          g1*r),
       Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),
       Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),
       Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +         -g1*r),
       Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +         -g2*r),
       Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +         -g1*r),
       Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +         -g1*r),
       Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +         -g2*r),
       Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +         -g1*r),
       Vector3D(center.x() +         1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),
       Vector3D(center.x() +        -1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
       Vector3D(center.x() +        -1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),
       Vector3D(center.x() +         1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
       Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() +  0.917587*s*r),
       Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() +  0.917587*s*r),
       Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() + -0.917587*s*r),
       Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() + -0.917587*s*r),
       Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
       Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
       Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
       Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
       Vector3D(center.x() +    0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
       Vector3D(center.x() +   -0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
       Vector3D(center.x() +    0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r),
       Vector3D(center.x() +   -0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r)
     };

      Triangle(v[9], v[8], v[23]);/////s
      Triangle(v[8], v[12], v[23]);
      Triangle(v[12], v[11], v[23]);
      Triangle(v[11], v[10], v[23]);
      Triangle(v[10], v[9], v[23]);
/////////////////////////////////////////////
      Cylinder(v[9], v[8], width);
      Cylinder(v[8], v[12], width);
      Cylinder(v[12], v[11], width);
      Cylinder(v[11], v[10], width);
      Cylinder(v[10], v[9], width);

      //Cylinder(v[9], v[23], width);
      //Cylinder(v[8], v[23], width);
      //Cylinder(v[12], v[23], width);
      //Cylinder(v[11], v[23], width);
      //Cylinder(v[10], v[23], width);

      Triangle(v[14], v[13], v[22]);/////a
      Triangle(v[13], v[8], v[22]);
      Triangle(v[8], v[9], v[22]);
      Triangle(v[9], v[15], v[22]);
      Triangle(v[15], v[14], v[22]);
///////////////////////////////////////////
      Cylinder(v[14], v[13], width);/////a
      Cylinder(v[13], v[8], width);
      Cylinder(v[8], v[9], width);
      Cylinder(v[9], v[15], width);
      Cylinder(v[15], v[14], width);

      //Cylinder(v[14], v[22], width);
      //Cylinder(v[13], v[22], width);
      //Cylinder(v[8], v[22], width);
      //Cylinder(v[9], v[22], width);
      //Cylinder(v[15], v[22], width);

      Triangle(v[15], v[9], v[27]);/////d
      Triangle(v[9], v[10], v[27]);
      Triangle(v[10], v[18], v[27]);
      Triangle(v[18], v[17], v[27]);
      Triangle(v[17], v[15], v[27]);

//////////////////////////////////////////////
Cylinder(v[15], v[9], width);/////d
Cylinder(v[9], v[10], width);
Cylinder(v[10], v[18], width);
Cylinder(v[18], v[17], width);
Cylinder(v[17], v[15], width);

      //Cylinder(v[15], v[27], width);
      //Cylinder(v[9], v[27], width);
      //Cylinder(v[10], v[27], width);
      //Cylinder(v[18], v[27], width);
      //Cylinder(v[17], v[27], width);

      Triangle(v[10], v[11], v[31]);/////e
      Triangle(v[11], v[5], v[31]);
      Triangle(v[5], v[7], v[31]);
      Triangle(v[7], v[18], v[31]);
      Triangle(v[18], v[10], v[31]);
/////////////////////////////////////////////

Cylinder(v[10], v[11], width);/////e
Cylinder(v[11], v[5], width);
Cylinder(v[5], v[7], width);
Cylinder(v[7], v[18], width);
Cylinder(v[18], v[10], width);

      //Cylinder(v[10], v[31], width);
      //Cylinder(v[11], v[31], width);
      //Cylinder(v[5], v[31], width);
      //Cylinder(v[7], v[31], width);
      //Cylinder(v[18], v[31], width);

      Triangle(v[16], v[6], v[30]);/////f
      Triangle(v[6], v[5], v[30]);
      Triangle(v[5], v[11], v[30]);
      Triangle(v[11], v[12], v[30]);
      Triangle(v[12], v[16], v[30]);
////////////////////////////////////////////////

Cylinder(v[16], v[6], width);/////f
Cylinder(v[6], v[5], width);
Cylinder(v[5], v[11], width);
Cylinder(v[11], v[12], width);
Cylinder(v[12], v[16], width);

      //Cylinder(v[16], v[30], width);
      //Cylinder(v[6], v[30], width);
      //Cylinder(v[5], v[30], width);
      //Cylinder(v[11], v[30], width);
      //Cylinder(v[12], v[30], width);

      Triangle(v[13], v[19], v[26]);/////c
      Triangle(v[19], v[16], v[26]);
      Triangle(v[16], v[12], v[26]);
      Triangle(v[12], v[8], v[26]);
      Triangle(v[8], v[13], v[26]);
////////////////////////////////////////////

Cylinder(v[13], v[19], width);/////c
Cylinder(v[19], v[16], width);
Cylinder(v[16], v[12], width);
Cylinder(v[12], v[8], width);
Cylinder(v[8], v[13], width);

      //Cylinder(v[13], v[26], width);
      //Cylinder(v[19], v[26], width);
      //Cylinder(v[16], v[26], width);
      //Cylinder(v[12], v[26], width);
      //Cylinder(v[8], v[26], width);

      Triangle(v[0], v[1], v[21]);/////w3
      Triangle(v[1], v[7], v[21]);
      Triangle(v[7], v[5], v[21]);
      Triangle(v[5], v[6], v[21]);
      Triangle(v[6], v[0], v[21]);
/////////////////////////////////////////

Cylinder(v[0], v[1], width);/////w3
Cylinder(v[1], v[7], width);
Cylinder(v[7], v[5], width);
Cylinder(v[5], v[6], width);
Cylinder(v[6], v[0], width);

      //Cylinder(v[0], v[21], width);
      //Cylinder(v[1], v[21], width);
      //Cylinder(v[7], v[21], width);
      //Cylinder(v[5], v[21], width);
      //Cylinder(v[6], v[21], width);

      Triangle(v[7], v[1], v[25]);/////w4
      Triangle(v[1], v[2], v[25]);
      Triangle(v[2], v[17], v[25]);
      Triangle(v[17], v[18], v[25]);
      Triangle(v[18], v[7], v[25]);
//////////////////////////////////////////

Cylinder(v[7], v[1], width);/////w4
Cylinder(v[1], v[2], width);
Cylinder(v[2], v[17], width);
Cylinder(v[17], v[18], width);
Cylinder(v[18], v[7], width);

      //Cylinder(v[7], v[25], width);
      //Cylinder(v[1], v[25], width);
      //Cylinder(v[2], v[25], width);
      //Cylinder(v[17], v[25], width);
      //Cylinder(v[18], v[25], width);

	    Triangle(v[0], v[6], v[24]);/////w2
      Triangle(v[6], v[16], v[24]);
      Triangle(v[16], v[19], v[24]);
      Triangle(v[19], v[4], v[24]);
      Triangle(v[4], v[0], v[24]);
///////////////////////////////////////////////

Cylinder(v[0], v[6], width);/////w2
Cylinder(v[6], v[16], width);
Cylinder(v[16], v[19], width);
Cylinder(v[19], v[4], width);
Cylinder(v[4], v[0], width);

      //Cylinder(v[0], v[24], width);
      //Cylinder(v[6], v[24], width);
      //Cylinder(v[16], v[24], width);
      //Cylinder(v[19], v[24], width);
      //Cylinder(v[4], v[24], width);

      Triangle(v[0], v[4], v[20]);//////b
      Triangle(v[4], v[3], v[20]);
      Triangle(v[3], v[2], v[20]);
      Triangle(v[2], v[1], v[20]);
      Triangle(v[1], v[0], v[20]);
////////////////////////////////////////////////

Cylinder(v[0], v[4], width);//////b
Cylinder(v[4], v[3], width);
Cylinder(v[3], v[2], width);
Cylinder(v[2], v[1], width);
Cylinder(v[1], v[0], width);

      //Cylinder(v[0], v[20], width);
      //Cylinder(v[4], v[20], width);
      //Cylinder(v[3], v[20], width);
      //Cylinder(v[2], v[20], width);
      //Cylinder(v[1], v[20], width);

      Triangle(v[17], v[2], v[29]);/////w5
      Triangle(v[2], v[3], v[29]);
      Triangle(v[3], v[14], v[29]);
      Triangle(v[14], v[15], v[29]);
      Triangle(v[15], v[17], v[29]);
///////////////////////////////////////////////

Cylinder(v[17], v[2], width);/////w5
Cylinder(v[2], v[3], width);
Cylinder(v[3], v[14], width);
Cylinder(v[14], v[15], width);
Cylinder(v[15], v[17], width);

      //Cylinder(v[17], v[29], width);
      //Cylinder(v[2], v[29], width);
      //Cylinder(v[3], v[29], width);
      //Cylinder(v[14], v[29], width);
      //Cylinder(v[15], v[29], width);

      Triangle(v[4], v[19], v[28]);/////w1
      Triangle(v[19], v[13], v[28]);
      Triangle(v[13], v[14], v[28]);
      Triangle(v[14], v[3], v[28]);
      Triangle(v[3], v[4], v[28]);
///////////////////////////////////////////////

Cylinder(v[4], v[19], width);/////w1
Cylinder(v[19], v[13], width);
Cylinder(v[13], v[14], width);
Cylinder(v[14], v[3], width);
Cylinder(v[3], v[4], width);

      //Cylinder(v[4], v[28], width);
      //Cylinder(v[19], v[28], width);
      //Cylinder(v[13], v[28], width);
      //Cylinder(v[14], v[28], width);
      //Cylinder(v[3], v[28], width);

      return;
}

void POVRayWriter::rotTest(double r, const Vector3D& center, double width, double angle) {
  Vector3D I = Vector3D(1, 0, 0);
  createStandardSphere(0.2, 0, 0, 0, "Black");
  double gold= (1 + sqrt(5))/2;
  double g1= 1/gold;
  double g2= 1/(gold*gold);
  double s = 0.8;

  Vector3D w[32] = {
    Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +         1.0*r),
    Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +         1.0*r),//1
    Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +          g1*r),//2
    Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +          g2*r),//3
    Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +          g1*r),//4
    Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +          g2*r),//5
    Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +          g1*r),//7
    Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +          g1*r),
    Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),//9
    Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),
    Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +         -g1*r),//11
    Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +         -g2*r),
    Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +         -g1*r),//13
    Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +         -g1*r),
    Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +         -g2*r),//15
    Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +         -g1*r),
    Vector3D(center.x() +         1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),//17
    Vector3D(center.x() +        -1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
    Vector3D(center.x() +        -1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),
    Vector3D(center.x() +         1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
    Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() +  0.917587*s*r),
    Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() +  0.917587*s*r),
    Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() + -0.917587*s*r),
    Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() + -0.917587*s*r),
    Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
    Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
    Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
    Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
    Vector3D(center.x() +    0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
    Vector3D(center.x() +   -0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
    Vector3D(center.x() +    0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r),
    Vector3D(center.x() +   -0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r)
  };

  //define axe of rotation with two Vectors
  Vector3D rot = unit(w[2] - w[17]);

  //draw axe of rotation
  createStandardSphere(0.2, rot.x(), rot.y(), rot.z(), "Blue");
  Cylinder(rot, center, 0.1);

  //rotate any vector with respect to that axe
  I = cos(angle) * I + sin(angle) * (rot % I) + (1-cos(angle)) * (rot*(rot*I));

  //add vector to the base of the axe
  I += w[17];
  createStandardSphere(0.2, I.x(), I.y(), I.z(), "Red");

  //translate the axe
  createStandardSphere(0.2, w[2].x(), w[2].y(), w[2].z(), "Green");
  createStandardSphere(0.2, w[17].x(), w[17].y(), w[17].z(), "White");
  Cylinder(w[2], w[17], 0.1);

}

Vector3D POVRayWriter::axeRotation(Vector3D head, Vector3D base, Vector3D I, double width, double angle) {
  //define axe of rotation with two Vectors
  Vector3D center = Vector3D(0, 0, 0);
  Vector3D rot = unit(head - base);

  //draw axe of rotation at th origin
  //createStandardSphere(0.2, 0, 0, 0, "Black");
  //createStandardSphere(0.2, rot.x(), rot.y(), rot.z(), "Blue");
  //Cylinder(rot, center, 0.1);

  //translate to the origin
  Vector3D trans =-base;

  //add vector to the base of the axe
  I += trans;

  Matrix3D identity = Matrix3D( 1, 0, 0,
                              0, 1, 0,
                              0, 0, 1
                            );

 Matrix3D anti1 = Matrix3D(       0,-rot.z(), rot.y(),
                            rot.z(),       0,-rot.x(),
                           -rot.y(), rot.x(),       0
                                                   );

  Matrix3D anti2 = Matrix3D(                  0,-sin(angle)*rot.z(), sin(angle)*rot.y(),
                            sin(angle)*rot.z(),                  0,-sin(angle)*rot.x(),
                           -sin(angle)*rot.y(), sin(angle)*rot.x(),                  0
                         );

 Matrix3D anti3 = Matrix3D(                     0,-(1-cos(angle))*rot.z(), (1-cos(angle))*rot.y(),
                           (1-cos(angle))*rot.z(),                     0, -(1-cos(angle))*rot.x(),
                          -(1-cos(angle))*rot.y(), (1-cos(angle))*rot.x(),                  0
                         );

Matrix3D rotationMat = identity + anti2 + (anti3*anti1);

Vector3D rotated = rotationMat * I;
  //return rotated vector
  return rotated + base;
}

double g0= (1 + sqrt(5))/2;
double g01= 1/g0;
double g02= 1/(g0*g0);
double S = g0;
Vector3D W[20] = {
  Vector3D(  g02,  0.0,  1.0),
  Vector3D( -g02,  0.0,  1.0),
  Vector3D( -g01,   g01,   g01),
  Vector3D( 0.0,  1.0,   g02),
  Vector3D(  g01,   g01,   g01),
  Vector3D( 0.0, -1.0,   g02),
  Vector3D(  g01,  -g01,   g01),
  Vector3D( -g01,  -g01,   g01),
  Vector3D(  g02,  0.0, -1.0),
  Vector3D( -g02,  0.0, -1.0),
  Vector3D( -g01,  -g01,  -g01),
  Vector3D( 0.0, -1.0,  -g02),
  Vector3D(  g01,  -g01,  -g01),
  Vector3D(  g01,   g01,  -g01),
  Vector3D( 0.0,  1.0,  -g02),
  Vector3D( -g01,   g01,  -g01),
  Vector3D( 1.0,  -g02,  0.0),
  Vector3D(-1.0,   g02,  0.0),
  Vector3D(-1.0,  -g02,  0.0),
  Vector3D( 1.0,   g02,  0.0)
};

Vector3D net[12] = { //points of the icosahedron
  Vector3D(0.0, 0.5617*S ,0.917587*S),
  Vector3D(0.0, -0.5617*S ,0.917587*S),
  Vector3D(0.0, -0.5617*S ,-0.917587*S),
  Vector3D(0.0, 0.5617 *S,-0.917587*S),
  Vector3D(-0.917587*S, 0.0,  -0.5671*S),
  Vector3D(-0.5671*S , -0.917587*S, 0.0),
  Vector3D(0.5671*S , -0.917587*S, 0.0),
  Vector3D(0.917587*S, 0.0,  -0.5671*S),
  Vector3D(-0.917587*S, 0.0,  0.5671*S),
  Vector3D(0.917587*S, 0.0,  0.5671*S),//
  Vector3D(-0.5671*S , 0.917587*S, 0.0),//
  Vector3D(0.5671*S , 0.917587*S, 0.0)
};

int aristas[30][2] = {
  {0, 4},//0
  {4, 3},//1
  {3, 2},//2
  {2, 1},//3
  {1, 0},//4
  {0, 6},//5
  {6, 16},//6
  {16, 19},//7
  {19, 4},//8
  {1, 7},//9
  {7, 5},//10
  {5, 6},//11
  {2, 17},//12
  {17, 18},//13
  {18, 7},//14
  {3, 14},//15
  {14,15},//16
  {15, 17},//17
  {19, 13},//18
  {13, 14},//19
  {15, 9},//21
  {9, 8},//22
  {8, 13},
  {8, 12},
  {12, 16},
  {12, 11},
  {5, 11},
  {11, 10},
  {10, 9},
  {10, 18}
};
void POVRayWriter::dodecaClass(Vector3D v[], Vector3D M) {
  /*Vector3D a = unit(M);
  double distances[10];
  bool T = false;
  while (T == false) {
    int checklist[10];
    for (int j = 0; j < 10; j++) {
        if (abs(abs(M) - v[j]) < 0.1) {checklist[j] = 1}
        else {checklist[j] = 0;}
    }

  }*/
}


void POVRayWriter::DrawH(
                    double x1, double x2, double x3,
                    double x4, double x5, double x6,
                    double x7, double x8, double x9,
                    double x10, double x11, double x12,
                    double x13, double x14, double x15,
                    double x16, double x17, double x18,
                    double x19, double x20, double x21,
                    double x22, double x23, double x24,
                    double x25, double x26, double x27,
                    double x28, double x29, double x30,
                    double x31, double x32, double x33,
                    double x34, double x35, double x36,
                    double x37, double x38, double x39,
                    double x40, double x41, double x42,
                    double x43, double x44, double x45,
                    double x46, double x47, double x48,
                    double x49, double x50, double x51,
                    double x52, double x53, double x54,
                    double x55, double x56, double x57,
                    double x58, double x59, double x60,
                    double x61, double x62, double x63,
                    double x64, double x65, double x66,
                    double x67, double x68, double x69,
                    double x70, double x71, double x72,
                    double x73, double x74, double x75,
                    double x76, double x77, double x78,
                    double x79, double x80, double x81,
                    double x82, double x83, double x84,
                    double x85, double x86, double x87,
                    double x88, double x89, double x90,
                    double x91, double x92, double x93,
                    double x94, double x95, double x96,
                    int n, double width, double inv,
                    double dist, int g
                    ) {

  Vector3D w[32] = {
         Vector3D( x1, x2, x3 ),///0
         Vector3D( x4, x5, x6 ),///1
         Vector3D( x7, x8, x9 ),///2
         Vector3D( x10, x11, x12 ),//3
         Vector3D( x13, x14, x15 ),//4
         Vector3D( x16, x17, x18 ),//5
         Vector3D( x19, x20, x21 ),//6
         Vector3D( x22, x23, x24 ),//7
         Vector3D( x25, x26, x27 ),//8
         Vector3D( x28, x29, x30 ),//9
         Vector3D( x31, x32, x33 ),//10
         Vector3D( x34, x35, x36 ), //11

         Vector3D(x37, x38 , x39),//12
         Vector3D(x40, x41 , x42),//13
         Vector3D(x43, x44 , x45),//14
         Vector3D(x46, x47 , x48),//15
         Vector3D(x49, x50 , x51),//16
         Vector3D(x52, x53 , x54),//17
         Vector3D(x55, x56 , x57),//18
         Vector3D(x58, x59 , x60),//19
         Vector3D(x61, x62 , x63),//20
         Vector3D(x64, x65 , x66),//21
         Vector3D(x67, x68 , x69),//22
         Vector3D(x70, x71 , x72),//23
         Vector3D(x73, x74 , x75),//24
         Vector3D(x76, x77 , x78),//25
         Vector3D(x79, x80 , x81),//26
         Vector3D(x82, x83 , x84),//27
         Vector3D(x85, x86 , x87),//28
         Vector3D(x88, x89 , x90),//29
         Vector3D(x91, x92 , x93),//30
         Vector3D(x94, x95 , x96)//31
       };

       double CONTROL = 0.82;
       double CONTROL1 = 0.82;

        if (n == 0) {

          if (g < 42)
          for (int i1 = 0; i1 < 30; i1++) {
            Cylinder1(w[aristas[i1][0]], w[aristas[i1][1]], width);
          }
          else{
            Vector3D auxW[20];
            for (int i1 = 0; i1 < 20; i1++)
              auxW[i1] = Vector3D(w[i1]);

            for (int i1 = 0; i1 < 20; i1++)
            auxW[i1] = axeRotation(W[g - 42], Vector3D(0, 0, 0), auxW[i1], 1.0, 0.333*pi);

            for (int i1 = 0; i1 < 30; i1++) {
             // Cylinder1(auxW[aristas[i1][0]], auxW[aristas[i1][1]], width);
            }

          }
          double s = CONTROL;
          Vector3D d[62];
          d[0] = Vector3D(0.0, 0.5617*s ,0.917587*s);
          d[1] = Vector3D(0.0, -0.5617*s ,0.917587*s);
          d[2] = Vector3D(0.0, -0.5617*s ,-0.917587*s);
          d[3] = Vector3D(0.0, 0.5617 *s,-0.917587*s);
          d[4] = Vector3D(-0.917587*s, 0.0,  -0.5671*s);
          d[5] = Vector3D(-0.5671*s , -0.917587*s, 0.0);
          d[6] = Vector3D(0.5671*s , -0.917587*s, 0.0);
          d[7] = Vector3D(0.917587*s, 0.0,  -0.5671*s);
          d[8] = Vector3D(-0.917587*s, 0.0,  0.5671*s);
          d[9] = Vector3D(0.917587*s, 0.0,  0.5671*s);//
          d[10] = Vector3D(-0.5671*s , 0.917587*s, 0.0);//
          d[11] = Vector3D(0.5671*s , 0.917587*s, 0.0);

          d[12] = 0.5*(W[aristas[0][0]] - W[aristas[0][1]]) + W[aristas[0][1]];
          d[13] = 0.5*(W[aristas[1][0]] - W[aristas[1][1]]) + W[aristas[1][1]];
          d[14] = 0.5*(W[aristas[2][0]] - W[aristas[2][1]]) + W[aristas[2][1]];
          d[15] = 0.5*(W[aristas[3][0]] - W[aristas[3][1]]) + W[aristas[3][1]];
          d[16] = 0.5*(W[aristas[4][0]] - W[aristas[4][1]]) + W[aristas[4][1]];
          d[17] = 0.5*(W[aristas[5][0]] - W[aristas[5][1]]) + W[aristas[5][1]];
          d[18] = 0.5*(W[aristas[6][0]] - W[aristas[6][1]]) + W[aristas[6][1]];
          d[19] = 0.5*(W[aristas[7][0]] - W[aristas[7][1]]) + W[aristas[7][1]];
          d[20] = 0.5*(W[aristas[8][0]] - W[aristas[8][1]]) + W[aristas[8][1]];
          d[21] = 0.5*(W[aristas[9 ][0]] - W[aristas[9][1]]) + W[aristas[9][1]];
          d[22] = 0.5*(W[aristas[10][0]] - W[aristas[10][1]]) + W[aristas[10][1]];
          d[23] = 0.5*(W[aristas[11][0]] - W[aristas[11][1]]) + W[aristas[11][1]];
          d[24] = 0.5*(W[aristas[12][0]] - W[aristas[12][1]]) + W[aristas[12][1]];
          d[25] = 0.5*(W[aristas[13][0]] - W[aristas[13][1]]) + W[aristas[13][1]];
          d[26] = 0.5*(W[aristas[14][0]] - W[aristas[14][1]]) + W[aristas[14][1]];
          d[27] = 0.5*(W[aristas[15][0]] - W[aristas[15][1]]) + W[aristas[15][1]];
          d[28] = 0.5*(W[aristas[16][0]] - W[aristas[16][1]]) + W[aristas[16][1]];
          d[29] = 0.5*(W[aristas[17][0]] - W[aristas[17][1]]) + W[aristas[17][1]];
          d[30] = 0.5*(W[aristas[18][0]] - W[aristas[18][1]]) + W[aristas[18][1]];
          d[31] = 0.5*(W[aristas[19][0]] - W[aristas[19][1]]) + W[aristas[19][1]];
          d[32] = 0.5*(W[aristas[20][0]] - W[aristas[20][1]]) + W[aristas[20][1]];
          d[33] = 0.5*(W[aristas[21][0]] - W[aristas[21][1]]) + W[aristas[21][1]];
          d[34] = 0.5*(W[aristas[22][0]] - W[aristas[22][1]]) + W[aristas[22][1]];
          d[35] = 0.5*(W[aristas[23][0]] - W[aristas[23][1]]) + W[aristas[23][1]];
          d[36] = 0.5*(W[aristas[24][0]] - W[aristas[24][1]]) + W[aristas[24][1]];
          d[37] = 0.5*(W[aristas[25][0]] - W[aristas[25][1]]) + W[aristas[25][1]];
          d[38] = 0.5*(W[aristas[26][0]] - W[aristas[26][1]]) + W[aristas[26][1]];
          d[39] = 0.5*(W[aristas[27][0]] - W[aristas[27][1]]) + W[aristas[27][1]];
          d[40] = 0.5*(W[aristas[28][0]] - W[aristas[28][1]]) + W[aristas[28][1]];
          d[41] = 0.5*(W[aristas[29][0]] - W[aristas[29][1]]) + W[aristas[29][1]];


          for (int i2 = 42; i2 < 62; i2++) {
            d[i2] = Vector3D(W[i2 - 42]);
          }

/*

    for (int i3 = 0; i3 < 43; i3 += 2) {
      Vector3D auxW[20];
      for (int i1 = 0; i1 < 20; i1++)
        auxW[i1] = Vector3D(w[i1]);

      if (i3 < 12)
      for (int i2 = 0; i2 < 20; i2++) {
        auxW[i2] = inversionNew(auxW[i2], abs(d[i3]) + ((1-CONTROL)*abs(d[i3])), 2.0 * d[i3]);
      }
      else{
        if (i3 < 42)
          for (int i2 = 0; i2 < 20; i2++) {
            auxW[i2] = inversionNew(auxW[i2], abs(d[i3]), CONTROL1 * d[i3]);
          }
        else{
          for (int i2 = 0; i2 < 20; i2++) {
            auxW[i2] = inversionNew(auxW[i2], abs((1.3 * 1.618 * d[i3]) - d[i3]), 1.3 * 1.618 * d[i3]);
          }
        }
      }

      if (g < 42)
      for (int i1 = 0; i1 < 30; i1++) {
        if (i3 < 12)
          Cylinder1(auxW[aristas[i1][0]], auxW[aristas[i1][1]], width);
        else
          Cylinder(auxW[aristas[i1][0]], auxW[aristas[i1][1]], width);
      }

    }*/
  } else { /* ---------------------------------------------------------------------------*/

          for (int i1 = 0; i1 < 30; i1++) {
            Cylinder(w[aristas[i1][0]], w[aristas[i1][1]], width);
          }

          int index[12][5] = {
            {4, 3, 2, 1, 0},
            {0, 1, 7, 5, 6},
            {9, 8, 12, 11, 10},
            {14, 13, 8, 9, 15},
            {15, 9, 10, 18, 17},
            {10, 11, 5, 7, 18},
            {16, 6, 5, 11, 12},
            {13, 19, 16, 12, 8},
            {7, 1, 2, 17, 18},
            {0, 6, 16, 19, 4},
            {17, 2, 3, 14, 15},
            {4, 19, 13, 14, 3}
          };

          double gold= (1 + sqrt(5))/2;
          double s = CONTROL;
          double g1= 1/gold;
          double g2= 1/(gold*gold);

          Vector3D d[62];
          d[0] = Vector3D(0.0, 0.5617*s ,0.917587*s);
          d[1] = Vector3D(0.0, -0.5617*s ,0.917587*s);
          d[2] = Vector3D(0.0, -0.5617*s ,-0.917587*s);
          d[3] = Vector3D(0.0, 0.5617 *s,-0.917587*s);
          d[4] = Vector3D(-0.917587*s, 0.0,  -0.5671*s);
          d[5] = Vector3D(-0.5671*s , -0.917587*s, 0.0);
          d[6] = Vector3D(0.5671*s , -0.917587*s, 0.0);
          d[7] = Vector3D(0.917587*s, 0.0,  -0.5671*s);
          d[8] = Vector3D(-0.917587*s, 0.0,  0.5671*s);
          d[9] = Vector3D(0.917587*s, 0.0,  0.5671*s);//
          d[10] = Vector3D(-0.5671*s , 0.917587*s, 0.0);//
          d[11] = Vector3D(0.5671*s , 0.917587*s, 0.0);

          for (int q1 = 12; q1  < 42; q1++) {
            d[q1] = 0.5*(W[aristas[q1-12][0]] - W[aristas[q1-12][1]]) + W[aristas[q1-12][1]];
            createStandardSphere(0.05, d[q1].x(), d[q1].y(), d[q1].z(), "Red");
          }

          for (int i2 = 42; i2 < 62; i2++) {
            d[i2] = Vector3D(W[i2 - 42]);
          }

          for (int i  = 0; i < 42; i += 1) {

           if (isnan(w[i].x()) == false && isnan(w[i].y()) == false && isnan(w[i].z()) == false)
            {
              //createStandardSphere(0.05, d[i].x(), d[i].y(), d[i].z(), "Red");

            Vector3D w1[20];
            for (int i11 = 0; i11 < 20; i11++) {
              w1[i11] = Vector3D(w[i11]);
            }

          Vector3D inversionCenter;
          if (i < 12)
            inversionCenter = 3.0 * d[i];
          else
            if (i < 42)
              inversionCenter = 2.38 * d[i];
            else{
              inversionCenter = 1.05 * 1.618 * d[i];
              //createStandardSphere(0.1, inversionCenter.x(),  inversionCenter.y(),  inversionCenter.z(), "White");
              //createStandardSphere(0.1, d[i].x(),  d[i].y(),  d[i].z(), "Red");
            }


            //createStandardSphere(0.1, inversionCenter.x(),  inversionCenter.y(),  inversionCenter.z(), "White");
           // Cylinder(d[i], inversionCenter, 0.05);

            double inversionRadius;
            if (i < 12)
              inversionRadius = 2*abs(d[i]) + ((1-CONTROL)*abs(d[i]));
            else
              if (i < 42)
                inversionRadius = abs(inversionCenter - 0.95*d[i]);
              else
                inversionRadius = (abs(inversionCenter - d[i]));


  double a1 = inversionNew(w[0], inversionRadius, inversionCenter).x();
	double a2 = inversionNew(w[0], inversionRadius, inversionCenter).y();
	double a3 = inversionNew(w[0], inversionRadius, inversionCenter).z();
	double a4 = inversionNew(w[1], inversionRadius, inversionCenter).x();
	double a5 = inversionNew(w[1], inversionRadius, inversionCenter).y();
	double a6 = inversionNew(w[1], inversionRadius, inversionCenter).z();
	double a7 = inversionNew(w[2], inversionRadius, inversionCenter).x();
	double a8 = inversionNew(w[2], inversionRadius, inversionCenter).y();
	double a9 = inversionNew(w[2], inversionRadius, inversionCenter).z();
	double a10 = inversionNew(w[3], inversionRadius, inversionCenter).x();
	double a11 = inversionNew(w[3], inversionRadius, inversionCenter).y();
	double a12 = inversionNew(w[3], inversionRadius, inversionCenter).z();
	double a13 = inversionNew(w[4], inversionRadius, inversionCenter).x();
	double a14 = inversionNew(w[4], inversionRadius, inversionCenter).y();
	double a15 = inversionNew(w[4], inversionRadius, inversionCenter).z();
	double a16 = inversionNew(w[5], inversionRadius, inversionCenter).x();
	double a17 = inversionNew(w[5], inversionRadius, inversionCenter).y();
	double a18 = inversionNew(w[5], inversionRadius, inversionCenter).z();
	double a19 = inversionNew(w[6], inversionRadius, inversionCenter).x();
	double a20 = inversionNew(w[6], inversionRadius, inversionCenter).y();
	double a21 = inversionNew(w[6], inversionRadius, inversionCenter).z();
	double a22 = inversionNew(w[7], inversionRadius, inversionCenter).x();
	double a23 = inversionNew(w[7], inversionRadius, inversionCenter).y();
	double a24 = inversionNew(w[7], inversionRadius, inversionCenter).z();
	double a25 = inversionNew(w[8], inversionRadius, inversionCenter).x();
	double a26 = inversionNew(w[8], inversionRadius, inversionCenter).y();
	double a27 = inversionNew(w[8], inversionRadius, inversionCenter).z();
	double a28 = inversionNew(w[9], inversionRadius, inversionCenter).x();
	double a29 = inversionNew(w[9], inversionRadius, inversionCenter).y();
	double a30 = inversionNew(w[9], inversionRadius, inversionCenter).z();
	double a31 = inversionNew(w[10], inversionRadius, inversionCenter).x();
	double a32 = inversionNew(w[10], inversionRadius, inversionCenter).y();
	double a33 = inversionNew(w[10], inversionRadius, inversionCenter).z();
	double a34 = inversionNew(w[11], inversionRadius, inversionCenter).x();
	double a35 = inversionNew(w[11], inversionRadius, inversionCenter).y();
	double a36 = inversionNew(w[11], inversionRadius, inversionCenter).z();

	double a37 = inversionNew(w[12], inversionRadius, inversionCenter).x();
	double a38 = inversionNew(w[12], inversionRadius, inversionCenter).y();
	double a39 = inversionNew(w[12], inversionRadius, inversionCenter).z();
	double a40 = inversionNew(w[13], inversionRadius, inversionCenter).x();
	double a41 = inversionNew(w[13], inversionRadius, inversionCenter).y();
	double a42 = inversionNew(w[13], inversionRadius, inversionCenter).z();
	double a43 = inversionNew(w[14], inversionRadius, inversionCenter).x();
	double a44 = inversionNew(w[14], inversionRadius, inversionCenter).y();
	double a45 = inversionNew(w[14], inversionRadius, inversionCenter).z();
	double a46 = inversionNew(w[15], inversionRadius, inversionCenter).x();
	double a47 = inversionNew(w[15], inversionRadius, inversionCenter).y();
	double a48 = inversionNew(w[15], inversionRadius, inversionCenter).z();
	double a49 = inversionNew(w[16], inversionRadius, inversionCenter).x();
	double a50 = inversionNew(w[16], inversionRadius, inversionCenter).y();
	double a51 = inversionNew(w[16], inversionRadius, inversionCenter).z();
	double a52 = inversionNew(w[17], inversionRadius, inversionCenter).x();
	double a53 = inversionNew(w[17], inversionRadius, inversionCenter).y();
	double a54 = inversionNew(w[17], inversionRadius, inversionCenter).z();
	double a55 = inversionNew(w[18], inversionRadius, inversionCenter).x();
	double a56 = inversionNew(w[18], inversionRadius, inversionCenter).y();
	double a57 = inversionNew(w[18], inversionRadius, inversionCenter).z();
	double a58 = inversionNew(w[19], inversionRadius, inversionCenter).x();
	double a59 = inversionNew(w[19], inversionRadius, inversionCenter).y();
	double a60 = inversionNew(w[19], inversionRadius, inversionCenter).z();
	double a61 = inversionNew(w[20], inversionRadius, inversionCenter).x();
	double a62 = inversionNew(w[20], inversionRadius, inversionCenter).y();
	double a63 = inversionNew(w[20], inversionRadius, inversionCenter).z();
	double a64 = inversionNew(w[21], inversionRadius, inversionCenter).x();
	double a65 = inversionNew(w[21], inversionRadius, inversionCenter).y();
	double a66 = inversionNew(w[21], inversionRadius, inversionCenter).z();
	double a67 = inversionNew(w[22], inversionRadius, inversionCenter).x();
	double a68 = inversionNew(w[22], inversionRadius, inversionCenter).y();
	double a69 = inversionNew(w[22], inversionRadius, inversionCenter).z();
	double a70 = inversionNew(w[23], inversionRadius, inversionCenter).x();
	double a71 = inversionNew(w[23], inversionRadius, inversionCenter).y();
	double a72 = inversionNew(w[23], inversionRadius, inversionCenter).z();
	double a73 = inversionNew(w[24], inversionRadius, inversionCenter).x();
	double a74 = inversionNew(w[24], inversionRadius, inversionCenter).y();
	double a75 = inversionNew(w[24], inversionRadius, inversionCenter).z();
	double a76 = inversionNew(w[25], inversionRadius, inversionCenter).x();
	double a77 = inversionNew(w[25], inversionRadius, inversionCenter).y();
	double a78 = inversionNew(w[25], inversionRadius, inversionCenter).z();
	double a79 = inversionNew(w[26], inversionRadius, inversionCenter).x();
	double a80 = inversionNew(w[26], inversionRadius, inversionCenter).y();
	double a81 = inversionNew(w[26], inversionRadius, inversionCenter).z();
	double a82 = inversionNew(w[27], inversionRadius, inversionCenter).x();
	double a83 = inversionNew(w[27], inversionRadius, inversionCenter).y();
	double a84 = inversionNew(w[27], inversionRadius, inversionCenter).z();
	double a85 = inversionNew(w[28], inversionRadius, inversionCenter).x();
	double a86 = inversionNew(w[28], inversionRadius, inversionCenter).y();
	double a87 = inversionNew(w[28], inversionRadius, inversionCenter).z();
	double a88 = inversionNew(w[29], inversionRadius, inversionCenter).x();
	double a89 = inversionNew(w[29], inversionRadius, inversionCenter).y();
	double a90 = inversionNew(w[29], inversionRadius, inversionCenter).z();
	double a91 = inversionNew(w[30], inversionRadius, inversionCenter).x();
	double a92 = inversionNew(w[30], inversionRadius, inversionCenter).y();
	double a93 = inversionNew(w[30], inversionRadius, inversionCenter).z();
	double a94 = inversionNew(w[31], inversionRadius, inversionCenter).x();
	double a95 = inversionNew(w[31], inversionRadius, inversionCenter).y();
	double a96 = inversionNew(w[31], inversionRadius, inversionCenter).z();

	DrawH(//////////////////////////////////face 1
         a1,  a2,  a3,
         a4,  a5,  a6,
         a7,  a8,  a9,
				 a10, a11, a12,
				 a13, a14, a15,
         a16, a17, a18,
         a19, a20, a21,
				 a22, a23, a24,
				 a25, a26, a27,
         a28, a29, a30,
         a31, a32, a33,
				 a34, a35, a36,
				 a37, a38, a39,
				 a40, a41, a42,
				 a43, a44, a45,
				 a46, a47, a48,
				 a49, a50, a51,
				 a52, a53, a54,
				 a55, a56, a57,
				 a58, a59, a60,
				 a61, a62, a63,
				 a64, a65, a66,
				 a67, a68, a69,
				 a70, a71, a72,
				 a73, a74, a75,
				 a76, a77, a78,
				 a79, a80, a81,
				 a82, a83, a84,
				 a85, a86, a87,
				 a88, a89, a90,
				 a91, a92, a93,
				 a94, a95, a96,
				 n - 1, 0.5*width, inv, dist, i
       );
               }//en if
         /*   for (int i = 0; i < 32; i++) {
              w[i] = inversionNew(w[i], rad, CENTER);
            }

            DrawH(//////////////////////////////////face 1
                   w[0].x(), w[0].y(), w[0].z(),
                   w[1].x(), w[1].y(), w[1].z(),
                   w[2].x(), w[2].y(), w[2].z(),
                   w[3].x(), w[3].y(), w[3].z(),
                   w[4].x(), w[4].y(), w[4].z(),
                   w[5].x(), w[5].y(), w[5].z(),
                   w[6].x(), w[6].y(), w[6].z(),
                   w[7].x(), w[7].y(), w[7].z(),
                   w[8].x(), w[8].y(), w[8].z(),
                   w[9].x(), w[9].y(), w[9].z(),
                   w[10].x(), w[10].y(), w[10].z(),
                   w[11].x(), w[11].y(), w[11].z(),
                   w[12].x(), w[12].y(), w[12].z(),
                   w[13].x(), w[13].y(), w[13].z(),
                   w[14].x(), w[14].y(), w[14].z(),
                   w[15].x(), w[15].y(), w[15].z(),
                   w[16].x(), w[16].y(), w[16].z(),
                   w[17].x(), w[17].y(), w[17].z(),
                   w[18].x(), w[18].y(), w[18].z(),
                   w[19].x(), w[19].y(), w[19].z(),
                   w[20].x(), w[20].y(), w[20].z(),
                   w[21].x(), w[21].y(), w[21].z(),
                   w[22].x(), w[22].y(), w[22].z(),
                   w[23].x(), w[23].y(), w[23].z(),
                   w[24].x(), w[24].y(), w[24].z(),
                   w[25].x(), w[25].y(), w[25].z(),
                   w[26].x(), w[26].y(), w[26].z(),
                   w[27].x(), w[27].y(), w[27].z(),
                   w[28].x(), w[28].y(), w[28].z(),
                   w[29].x(), w[29].y(), w[29].z(),
                   w[30].x(), w[30].y(), w[30].z(),
                   w[31].x(), w[31].y(), w[31].z(),
                   n - 1, 0.5*width
                 );*/
          }// end for i

        }//end else

return;
}

  void POVRayWriter::cube(double r, Vector3D center, double width, double angle, 
		  int n, Vector3D gamma, double radi, double rr, double gg, double bb, double trans) {
  double PI = 3.14159265358;
  double gold= (1 + sqrt(5))/2;
  double g1= 1/gold;
  double g2= 1/(gold*gold);
  double s = 0.8;
	//TriangleColorTrans(const Vector3D& a, const Vector3D& b, const Vector3D& c,
                           //double r, double g, double bb, double trans)
  Vector3D w[32] = {
    Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +         1.0*r),
    Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +         1.0*r),//1
    Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +          g1*r),//2
    Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +          g2*r),//3
    Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +          g1*r),//4
    Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +          g2*r),//5
    Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +          g1*r),//7
    Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +          g1*r),
    Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),//9
    Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),
    Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +         -g1*r),//11
    Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +         -g2*r),
    Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +         -g1*r),//13
    Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +         -g1*r),
    Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +         -g2*r),//15
    Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +         -g1*r),
    Vector3D(center.x() +         1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),//17
    Vector3D(center.x() +        -1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
    Vector3D(center.x() +        -1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),
    Vector3D(center.x() +         1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
    Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() +  0.917587*s*r),
    Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() +  0.917587*s*r),
    Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() + -0.917587*s*r),
    Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() + -0.917587*s*r),
    Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
    Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
    Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
    Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
    Vector3D(center.x() +    0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
    Vector3D(center.x() +   -0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
    Vector3D(center.x() +    0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r),
    Vector3D(center.x() +   -0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r)
  };

  Vector3D v[32];


  Vector3D base = w[6];
  Vector3D head = w[0];

  if (n == 0) {
    Cylinder(w[9], w[8], width);
    Cylinder(w[8], w[12], width);
    Cylinder(w[12], w[11], width);
    Cylinder(w[11], w[10], width);
    Cylinder(w[10], w[9], width);
    Cylinder(w[14], w[13], width);/////a
    Cylinder(w[13], w[8], width);
    Cylinder(w[9], w[15], width);
    Cylinder(w[15], w[14], width);
    Cylinder(w[10], w[18], width);
    Cylinder(w[18], w[17], width);
    Cylinder(w[17], w[15], width);
    Cylinder(w[11], w[5], width);
    Cylinder(w[5], w[7], width);
    Cylinder(w[7], w[18], width);
    Cylinder(w[16], w[6], width);/////f
    Cylinder(w[6], w[5], width);
    Cylinder(w[5], w[11], width);
    Cylinder(w[12], w[16], width);
    Cylinder(w[13], w[19], width);/////c
    Cylinder(w[19], w[16], width);
    Cylinder(w[12], w[8], width);
    Cylinder(w[0], w[1], width);/////w3
    //Cylinder(w[1], w[7], width);
    Cylinder(w[6], w[0], width);//
    Cylinder(w[7], w[1], width);/////w4
    Cylinder(w[17], w[2], width);
    Cylinder(w[1], w[2], width);
    Cylinder(w[18], w[7], width);
    Cylinder(w[19], w[4], width);
    Cylinder(w[4], w[0], width);//
    Cylinder(w[4], w[3], width);//
    Cylinder(w[3], w[2], width);//
    Cylinder(w[3], w[14], width);//
	
	  //TriangleColorTrans(const Vector3D& a, const Vector3D& b, const Vector3D& c,
                           //double r, double g, double bb, double trans)
    //TriangleColorTrans(w[9],  w[8],  w[23], rr, gg, bb, trans);/////s
    //TriangleColorTrans(w[8],  w[12], w[23], rr, gg, bb, trans);
    //TriangleColorTrans(w[12], w[11], w[23], rr, gg, bb, trans);
    //TriangleColorTrans(w[11], w[10], w[23], rr, gg, bb, trans);
    //TriangleColorTrans(w[10], w[9],  w[23], rr, gg, bb, trans);
    //TriangleColorTrans(w[13], w[8],  w[22], rr, gg, bb, trans);
    //TriangleColorTrans(w[8],  w[9],  w[22], rr, gg, bb, trans);
    //TriangleColorTrans(w[9],  w[15], w[22], rr, gg, bb, trans);
    //TriangleColorTrans(w[15], w[14], w[22], rr, gg, bb, trans);
    //TriangleColorTrans(w[14], w[13], w[22], rr, gg, bb, trans);
    //TriangleColorTrans(w[9],  w[10], w[27], rr, gg, bb, trans);
    //TriangleColorTrans(w[10], w[18], w[27], rr, gg, bb, trans);
    //TriangleColorTrans(w[18], w[17], w[27], rr, gg, bb, trans);
    //TriangleColorTrans(w[17], w[15], w[27], rr, gg, bb, trans);
    //TriangleColorTrans(w[15], w[9],  w[27], rr, gg, bb, trans);
    //TriangleColorTrans(w[10], w[11], w[31], rr, gg, bb, trans);/////e
    //TriangleColorTrans(w[11], w[5],  w[31], rr, gg, bb, trans);
    //TriangleColorTrans(w[5],  w[7],  w[31], rr, gg, bb, trans);
    //TriangleColorTrans(w[7],  w[18], w[31], rr, gg, bb, trans);
    //TriangleColorTrans(w[18], w[10], w[31], rr, gg, bb, trans);
    //TriangleColorTrans(w[16], w[6],  w[30], rr, gg, bb, trans);
    //TriangleColorTrans(w[6],  w[5],  w[30], rr, gg, bb, trans);
    //TriangleColorTrans(w[5],  w[11], w[30], rr, gg, bb, trans);
    //TriangleColorTrans(w[11], w[12], w[30], rr, gg, bb, trans);
    //TriangleColorTrans(w[12], w[16], w[30], rr, gg, bb, trans);
    //TriangleColorTrans(w[13], w[19], w[26], rr, gg, bb, trans);
    //TriangleColorTrans(w[19], w[16], w[26], rr, gg, bb, trans);
    //TriangleColorTrans(w[16], w[12], w[26], rr, gg, bb, trans);
    //TriangleColorTrans(w[12], w[8],  w[26], rr, gg, bb, trans);
    //TriangleColorTrans(w[8],  w[13], w[26], rr, gg, bb, trans);
    //TriangleColorTrans(w[0],  w[1],  w[21], rr, gg, bb, trans);
    //TriangleColorTrans(w[1],  w[7],  w[21], rr, gg, bb, trans);
    //TriangleColorTrans(w[7],  w[5],  w[21], rr, gg, bb, trans);
    //TriangleColorTrans(w[5],  w[6],  w[21], rr, gg, bb, trans);
    //TriangleColorTrans(w[6],  w[0],  w[21], rr, gg, bb, trans);
    //TriangleColorTrans(w[7],  w[1],  w[25], rr, gg, bb, trans);
    //TriangleColorTrans(w[1],  w[2],  w[25], rr, gg, bb, trans);
    //TriangleColorTrans(w[2],  w[17], w[25], rr, gg, bb, trans);
    //TriangleColorTrans(w[17], w[18], w[25], rr, gg, bb, trans);
    //TriangleColorTrans(w[18], w[7],  w[25], rr, gg, bb, trans);
    //TriangleColorTrans(w[0],  w[6],  w[24], rr, gg, bb, trans);/////w2
    //TriangleColorTrans(w[6],  w[16], w[24], rr, gg, bb, trans);
    //TriangleColorTrans(w[16], w[19], w[24], rr, gg, bb, trans);
    //TriangleColorTrans(w[19], w[4],  w[24], rr, gg, bb, trans);
    //TriangleColorTrans(w[4],  w[0],  w[24], rr, gg, bb, trans);
    //TriangleColorTrans(w[0],  w[4],  w[20], rr, gg, bb, trans);//////b
    //TriangleColorTrans(w[4],  w[3],  w[20], rr, gg, bb, trans);
    //TriangleColorTrans(w[3],  w[2],  w[20], rr, gg, bb, trans);
    //TriangleColorTrans(w[2],  w[1],  w[20], rr, gg, bb, trans);
    //TriangleColorTrans(w[1],  w[0],  w[20], rr, gg, bb, trans);
    //TriangleColorTrans(w[17], w[2],  w[29], rr, gg, bb, trans);/////w5
    //TriangleColorTrans(w[2],  w[3],  w[29], rr, gg, bb, trans);
    //TriangleColorTrans(w[3],  w[14], w[29], rr, gg, bb, trans);
    //TriangleColorTrans(w[14], w[15], w[29], rr, gg, bb, trans);
    //TriangleColorTrans(w[15], w[17], w[29], rr, gg, bb, trans);
    //TriangleColorTrans(w[4],  w[19], w[28], rr, gg, bb, trans);/////w1
    //TriangleColorTrans(w[19], w[13], w[28], rr, gg, bb, trans);
    //TriangleColorTrans(w[13], w[14], w[28], rr, gg, bb, trans);
    //TriangleColorTrans(w[14], w[3],  w[28], rr, gg, bb, trans);
    //TriangleColorTrans(w[3],  w[4],  w[28], rr, gg, bb, trans);

  }
  else
  {
    //for (int i = 0; i < 32; i++) {
    //  w[i] = inversionNew(w[i], radi, gamma);
    //}

    //for (int i = 0; i < 32; i++) {
    //  v[i] = axeRotation(head, base, w[i], 0.1, angle);
    //}

    for (int i = 0; i < 20; i++) {
      createStandardSphere(2.0*width, v[i].x(), v[i].y(), v[i].z(), "White");
    }


    //Cylinder1(v[9], v[8], width);
    //Cylinder1(v[17], v[2], width);
    //Cylinder1(v[8], v[12], width);
    //Cylinder1(v[12], v[11], width);
    //Cylinder1(v[11], v[10], width);

    //Cylinder1(v[10], v[9], width);
    //Cylinder1(v[14], v[13], width);/////a
    //Cylinder1(v[13], v[8], width);
    //Cylinder1(v[9], v[15], width);
    //Cylinder1(v[15], v[14], width);
    //Cylinder1(v[10], v[18], width);
    //Cylinder1(v[18], v[17], width);
    //Cylinder1(v[17], v[15], width);
    //Cylinder1(v[11], v[5], width);
    //Cylinder1(v[5], v[7], width);
    //Cylinder1(v[7], v[18], width);
    //Cylinder1(v[16], v[6], width);/////f
    //Cylinder1(v[6], v[5], width);
    //Cylinder1(v[5], v[11], width);
    //Cylinder1(v[12], v[16], width);
    //Cylinder1(v[13], v[19], width);/////c
    //Cylinder1(v[19], v[16], width);
    //Cylinder1(v[12], v[8], width);
    //Cylinder1(v[0], v[1], width);/////w3
    //Cylinder1(v[1], v[7], width);
    //Cylinder1(v[6], v[0], width);
    //Cylinder1(v[7], v[1], width);/////w4
    //Cylinder1(v[1], v[2], width);
    //Cylinder1(v[18], v[7], width);
    //Cylinder1(v[19], v[4], width);
    //Cylinder1(v[4], v[0], width);
    //Cylinder1(v[4], v[3], width);
    //Cylinder1(v[3], v[2], width);
    //Cylinder1(v[3], v[14], width);
  }


/*
  Triangle(v[9], v[8], v[23]);/////s
  Triangle(v[8], v[12], v[23]);
  Triangle(v[12], v[11], v[23]);
  Triangle(v[11], v[10], v[23]);
  Triangle(v[10], v[9], v[23]);
  Triangle(v[13], v[8], v[22]);
  Triangle(v[8], v[9], v[22]);
  Triangle(v[9], v[15], v[22]);
  Triangle(v[15], v[14], v[22]);
  Triangle(v[9], v[10], v[27]);
  Triangle(v[10], v[18], v[27]);
  Triangle(v[18], v[17], v[27]);
  Triangle(v[17], v[15], v[27]);
  Triangle(v[10], v[11], v[31]);/////e
  Triangle(v[11], v[5], v[31]);
  Triangle(v[5], v[7], v[31]);
  Triangle(v[7], v[18], v[31]);
  Triangle(v[18], v[10], v[31]);
  Triangle(v[16], v[6], v[30]);
  Triangle(v[6], v[5], v[30]);
  Triangle(v[5], v[11], v[30]);
  Triangle(v[11], v[12], v[30]);
  Triangle(v[12], v[16], v[30]);
  Triangle(v[13], v[19], v[26]);
  Triangle(v[19], v[16], v[26]);
  Triangle(v[16], v[12], v[26]);
  Triangle(v[12], v[8], v[26]);
  Triangle(v[8], v[13], v[26]);
  Triangle(v[0], v[1], v[21]);
  Triangle(v[1], v[7], v[21]);
  Triangle(v[7], v[5], v[21]);
  Triangle(v[5], v[6], v[21]);
  Triangle(v[6], v[0], v[21]);
  Triangle(v[7], v[1], v[25]);
  Triangle(v[1], v[2], v[25]);
  Triangle(v[2], v[17], v[25]);
  Triangle(v[17], v[18], v[25]);
  Triangle(v[18], v[7], v[25]);
  Triangle(v[0], v[6], v[24]);/////w2
  Triangle(v[6], v[16], v[24]);
  Triangle(v[16], v[19], v[24]);
  Triangle(v[19], v[4], v[24]);
  Triangle(v[4], v[0], v[24]);
  Triangle(v[0], v[4], v[20]);//////b
  Triangle(v[4], v[3], v[20]);
  Triangle(v[3], v[2], v[20]);
  Triangle(v[2], v[1], v[20]);
  Triangle(v[1], v[0], v[20]);
  Triangle(v[17], v[2], v[29]);/////w5
  Triangle(v[2], v[3], v[29]);
  Triangle(v[3], v[14], v[29]);
  Triangle(v[14], v[15], v[29]);
  Triangle(v[15], v[17], v[29]);
  Triangle(v[4], v[19], v[28]);/////w1
  Triangle(v[19], v[13], v[28]);
  Triangle(v[13], v[14], v[28]);
  Triangle(v[14], v[3], v[28]);
  Triangle(v[3], v[4], v[28]);
*/
}

void POVRayWriter::dodecahedron(double r, const Vector3D& center, double width, double angle) {
     double gold= (1 + sqrt(5))/2;
     double g1= 1/gold;
     double g2= 1/(gold*gold);
     double s = 0.8;
     Vector3D I = Vector3D(1, 0, 0);
     Vector3D J = Vector3D(0, 1, 0);
     Vector3D K = Vector3D(0, 0, 1);

     Vector3D w[32] = {
       Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +         1.0*r),
       Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +         1.0*r),//1
       Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +          g1*r),//2
       Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +          g2*r),//3
       Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +          g1*r),//4
       Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +          g2*r),//5
       Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +          g1*r),//7
       Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +          g1*r),
       Vector3D(center.x() +          g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),//9
       Vector3D(center.x() +         -g2*r, center.y() +         0.0*r,center.z() +        -1.0*r),
       Vector3D(center.x() +         -g1*r, center.y() +         -g1*r,center.z() +         -g1*r),//11
       Vector3D(center.x() +         0.0*r, center.y() +        -1.0*r,center.z() +         -g2*r),
       Vector3D(center.x() +          g1*r, center.y() +         -g1*r,center.z() +         -g1*r),//13
       Vector3D(center.x() +          g1*r, center.y() +          g1*r,center.z() +         -g1*r),
       Vector3D(center.x() +         0.0*r, center.y() +         1.0*r,center.z() +         -g2*r),//15
       Vector3D(center.x() +         -g1*r, center.y() +          g1*r,center.z() +         -g1*r),
       Vector3D(center.x() +         1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),//17
       Vector3D(center.x() +        -1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
       Vector3D(center.x() +        -1.0*r, center.y() +         -g2*r,center.z() +         0.0*r),
       Vector3D(center.x() +         1.0*r, center.y() +          g2*r,center.z() +         0.0*r),
       Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() +  0.917587*s*r),
       Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() +  0.917587*s*r),
       Vector3D(center.x() +         0.0*r, center.y() +    0.5617*s*r,center.z() + -0.917587*s*r),
       Vector3D(center.x() +         0.0*r, center.y() +   -0.5617*s*r,center.z() + -0.917587*s*r),
       Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
       Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +    0.5671*s*r),
       Vector3D(center.x() +  0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
       Vector3D(center.x() + -0.917587*s*r, center.y() +         0.0*r,center.z() +   -0.5671*s*r),
       Vector3D(center.x() +    0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
       Vector3D(center.x() +   -0.5671*s*r, center.y() +  0.917587*s*r,center.z() +         0.0*r),
       Vector3D(center.x() +    0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r),
       Vector3D(center.x() +   -0.5671*s*r, center.y() + -0.917587*s*r,center.z() +         0.0*r)
     };

     Vector3D v[32];

     for (int i = 0; i < 32; i++) {
       v[i] = inversion(w[i], 4);
     }

     Vector3D R = v[2] - v[17];


     createStandardSphere(0.2, 0, 0, 0, "Black");
     createStandardSphere(0.2, R.x(), R.y(), R.z(), "Red");
     Cylinder(v[2]-v[17], Vector3D(0, 0, 0), 0.1);
     Vector3D rotAxe = unit(v[2]-v[17]);
/*
     for (int i = 0; i < 32; i++) {
       v[i] += -1*Vector3D(center.x() + -g1*r, center.y() + g1*r, center.z() + g1*r);
     }
*/
     if (angle>0.0) {
             for (int i = 0; i < 32; i++) {
                v[i] += -1*center;
             }

            for (int i = 0; i < 32; i++) {
              v[i] = cos(angle) * v[i] + sin(angle) * (rotAxe % v[i]) + (1-cos(angle)) * (rotAxe*(rotAxe*v[i]));
            }

            for (int i = 0; i < 32; i++) {
              v[i] = v[i] + inversion(Vector3D(center.x() + -1.0*r, center.y() + g2*r,center.z() + 0.0*r), 4.0)+center;
            }
     }

/*
     for (int i = 0; i < 32; i++) {
       quaternion q1 = (0, v[i].x(), v[i].y(), v[i].z());
       quaternion q2 = (cos(0.5 * angle), rotAxe.x() * sin(0.5 * angle),  rotAxe.y() * sin(0.5 * angle),  rotAxe.z() * sin(0.5 * angle));
       quaternion q3 = (q2 * q1) * star(q2);
       v[i] = Vector3D(q3.Qy(), q3.Qz(), q3.Qt());
     }*/

     //Triangle(v[9], v[8], v[23]);/////s
     //Triangle(v[8], v[12], v[23]);
     //Triangle(v[12], v[11], v[23]);
     //Triangle(v[11], v[10], v[23]);
     //Triangle(v[10], v[9], v[23]);

/////////////////////////////////////////////
      Cylinder(v[9], v[8], width);
      Cylinder(v[8], v[12], width);
      Cylinder(v[12], v[11], width);
      Cylinder(v[11], v[10], width);
      Cylinder(v[10], v[9], width);

      //Cylinder(v[9], v[23], width);
      //Cylinder(v[8], v[23], width);
      //Cylinder(v[12], v[23], width);
      //Cylinder(v[11], v[23], width);
      //Cylinder(v[10], v[23], width);
      //Triangle(v[14], v[13], v[22]);/////a
      //Triangle(v[13], v[8], v[22]);
      //Triangle(v[8], v[9], v[22]);
      //Triangle(v[9], v[15], v[22]);
      //Triangle(v[15], v[14], v[22]);

///////////////////////////////////////////
      Cylinder(v[14], v[13], width);/////a
      Cylinder(v[13], v[8], width);
      //Cylinder(v[8], v[9], width);
      Cylinder(v[9], v[15], width);
      Cylinder(v[15], v[14], width);

      //Cylinder(v[14], v[22], width);
      //Cylinder(v[13], v[22], width);
      //Cylinder(v[8], v[22], width);
      //Cylinder(v[9], v[22], width);
      //Cylinder(v[15], v[22], width);
      //Triangle(v[15], v[9], v[27]);/////d
      //Triangle(v[9], v[10], v[27]);
      //Triangle(v[10], v[18], v[27]);
      //Triangle(v[18], v[17], v[27]);
      //Triangle(v[17], v[15], v[27]);


//////////////////////////////////////////////
//Cylinder(v[15], v[9], width);/////d
//Cylinder(v[9], v[10], width);
Cylinder(v[10], v[18], width);
Cylinder(v[18], v[17], width);
Cylinder(v[17], v[15], width);

      //Cylinder(v[15], v[27], width);
      //Cylinder(v[9], v[27], width);
      //Cylinder(v[10], v[27], width);
      //Cylinder(v[18], v[27], width);
      //Cylinder(v[17], v[27], width);
      //Triangle(v[10], v[11], v[31]);/////e
      //Triangle(v[11], v[5], v[31]);
      //Triangle(v[5], v[7], v[31]);
      //Triangle(v[7], v[18], v[31]);
      //Triangle(v[18], v[10], v[31]);

/////////////////////////////////////////////

//Cylinder(v[10], v[11], width);/////e
Cylinder(v[11], v[5], width);
Cylinder(v[5], v[7], width);
Cylinder(v[7], v[18], width);
//Cylinder(v[18], v[10], width);

      //Cylinder(v[10], v[31], width);
      //Cylinder(v[11], v[31], width);
      //Cylinder(v[5], v[31], width);
      //Cylinder(v[7], v[31], width);
      //Cylinder(v[18], v[31], width);
      //Triangle(v[16], v[6], v[30]);/////f
      //Triangle(v[6], v[5], v[30]);
      //Triangle(v[5], v[11], v[30]);
      //Triangle(v[11], v[12], v[30]);
      //Triangle(v[12], v[16], v[30]);

////////////////////////////////////////////////

Cylinder(v[16], v[6], width);/////f
Cylinder(v[6], v[5], width);
Cylinder(v[5], v[11], width);
//Cylinder(v[11], v[12], width);
Cylinder(v[12], v[16], width);

      //Cylinder(v[16], v[30], width);
      //Cylinder(v[6], v[30], width);
      //Cylinder(v[5], v[30], width);
      //Cylinder(v[11], v[30], width);
      //Cylinder(v[12], v[30], width);
      //Triangle(v[13], v[19], v[26]);/////c
      //Triangle(v[19], v[16], v[26]);
      //Triangle(v[16], v[12], v[26]);
      //Triangle(v[12], v[8], v[26]);
      //Triangle(v[8], v[13], v[26]);

////////////////////////////////////////////

Cylinder(v[13], v[19], width);/////c
Cylinder(v[19], v[16], width);
//Cylinder(v[16], v[12], width);
Cylinder(v[12], v[8], width);
//Cylinder(v[8], v[13], width);

      //Cylinder(v[13], v[26], width);
      //Cylinder(v[19], v[26], width);
      //Cylinder(v[16], v[26], width);
      //Cylinder(v[12], v[26], width);
      //Cylinder(v[8], v[26], width);
      //Triangle(v[0], v[1], v[21]);/////w3
      //Triangle(v[1], v[7], v[21]);
      //Triangle(v[7], v[5], v[21]);
      //Triangle(v[5], v[6], v[21]);
      //Triangle(v[6], v[0], v[21]);

/////////////////////////////////////////

Cylinder(v[0], v[1], width);/////w3
Cylinder(v[1], v[7], width);
//Cylinder(v[7], v[5], width);
//Cylinder(v[5], v[6], width);
Cylinder(v[6], v[0], width);

      //Cylinder(v[0], v[21], width);
      //Cylinder(v[1], v[21], width);
      //Cylinder(v[7], v[21], width);
      //Cylinder(v[5], v[21], width);
      //Cylinder(v[6], v[21], width);
      //Triangle(v[7], v[1], v[25]);/////w4
      //Triangle(v[1], v[2], v[25]);
      //Triangle(v[2], v[17], v[25]);
      //Triangle(v[17], v[18], v[25]);
      //Triangle(v[18], v[7], v[25]);

//////////////////////////////////////////

Cylinder(v[7], v[1], width);/////w4
Cylinder(v[1], v[2], width);
//Cylinder(v[2], v[17], width);//**********************************************************************
//Cylinder(v[17], v[18], width);
Cylinder(v[18], v[7], width);

      //Cylinder(v[7], v[25], width);
      //Cylinder(v[1], v[25], width);
      //Cylinder(v[2], v[25], width);
      //Cylinder(v[17], v[25], width);
      //Cylinder(v[18], v[25], width);
      //Triangle(v[0], v[6], v[24]);/////w2
      //Triangle(v[6], v[16], v[24]);
      //Triangle(v[16], v[19], v[24]);
      //Triangle(v[19], v[4], v[24]);
      //Triangle(v[4], v[0], v[24]);

///////////////////////////////////////////////

//Cylinder(v[0], v[6], width);/////w2
//Cylinder(v[6], v[16], width);
//Cylinder(v[16], v[19], width);
Cylinder(v[19], v[4], width);
Cylinder(v[4], v[0], width);

      //Cylinder(v[0], v[24], width);
      //Cylinder(v[6], v[24], width);
      //Cylinder(v[16], v[24], width);
      //Cylinder(v[19], v[24], width);
      //Cylinder(v[4], v[24], width);
      //Triangle(v[0], v[4], v[20]);//////b
      //Triangle(v[4], v[3], v[20]);
      //Triangle(v[3], v[2], v[20]);
      //Triangle(v[2], v[1], v[20]);
      //Triangle(v[1], v[0], v[20]);

////////////////////////////////////////////////

//Cylinder(v[0], v[4], width);//////b
Cylinder(v[4], v[3], width);
Cylinder(v[3], v[2], width);
//Cylinder(v[2], v[1], width);
//Cylinder(v[1], v[0], width);

      //Cylinder(v[0], v[20], width);
      //Cylinder(v[4], v[20], width);
      //Cylinder(v[3], v[20], width);
      //Cylinder(v[2], v[20], width);
      //Cylinder(v[1], v[20], width);

      //Triangle(v[17], v[2], v[29]);/////w5
      //Triangle(v[2], v[3], v[29]);
      //Triangle(v[3], v[14], v[29]);
      //Triangle(v[14], v[15], v[29]);
      //Triangle(v[15], v[17], v[29]);

///////////////////////////////////////////////

//Cylinder(v[17], v[2], width);/////w5
//Cylinder(v[2], v[3], width);
Cylinder(v[3], v[14], width);
//Cylinder(v[14], v[15], width);
//Cylinder(v[15], v[17], width);

      //Cylinder(v[17], v[29], width);
      //Cylinder(v[2], v[29], width);
      //Cylinder(v[3], v[29], width);
      //Cylinder(v[14], v[29], width);
      //Cylinder(v[15], v[29], width);
      //Triangle(v[4], v[19], v[28]);/////w1
      //Triangle(v[19], v[13], v[28]);
      //Triangle(v[13], v[14], v[28]);
      //Triangle(v[14], v[3], v[28]);
      //Triangle(v[3], v[4], v[28]);

///////////////////////////////////////////////

//Cylinder(v[4], v[19], width);/////w1
//Cylinder(v[19], v[13], width);
//Cylinder(v[13], v[14], width);
//Cylinder(v[14], v[3], width);
//Cylinder(v[3], v[4], width);

      //Cylinder(v[4], v[28], width);
      //Cylinder(v[19], v[28], width);
      //Cylinder(v[13], v[28], width);
      //Cylinder(v[14], v[28], width);
      //Cylinder(v[3], v[28], width);

      return;
}

void POVRayWriter::colorIco(double r, const Vector3D& center, string color)
{
    double gold = (1 + sqrt(5))/2;
    Vector3D v[12] = {
      Vector3D(center.x() +  gold*r, center.y(), center.z() +  r),
      Vector3D(center.x() +  gold*r, center.y(), center.z() + -r),
      Vector3D(center.x() + -gold*r, center.y(), center.z() +  r),
      Vector3D(center.x() + -gold*r, center.y(), center.z() + -r),

      Vector3D(center.x() +  r,center.y() + -gold*r, center.z() ),
      Vector3D(center.x() + -r,center.y() + -gold*r, center.z() ),
      Vector3D(center.x() + -r,center.y() +  gold*r, center.z() ),
      Vector3D(center.x() +  r,center.y() +  gold*r, center.z() ),

      Vector3D( center.x(), center.y() + -r,center.z() +  gold*r),
      Vector3D( center.x(), center.y() +  r,center.z() +  gold*r),
      Vector3D( center.x(), center.y() +  r,center.z() + -gold*r),
      Vector3D( center.x(), center.y() + -r,center.z() + -gold*r)
    };
     Triangle(v[0], v[4], v[1]);
     	CylinderI(v[0 ], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[4 ], v[1], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[0 ], v[1], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[8], v[4], v[0]);
     	CylinderI(v[8 ], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[0 ], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[8 ], v[0], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[8], v[5], v[4]);
     	CylinderI(v[8 ], v[5], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[5 ], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[4 ], v[8], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[2], v[5], v[8]);
     	CylinderI(v[2 ], v[5], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[5 ], v[8], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[8 ], v[2], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[11], v[4], v[5]);
     	CylinderI(v[11], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[ 5], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[11], v[5], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[4], v[11], v[1]);
     	CylinderI(v[11], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[ 1], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[11], v[1], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[7], v[0], v[1]);
     	 CylinderI(v[7], v[0], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[0], v[1], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[1], v[7], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[7], v[1], v[10]);
       CylinderI(v[ 7], v[ 1], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
       CylinderI(v[ 1], v[10], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
       CylinderI(v[10], v[ 7], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[9], v[0], v[7]);
     	 CylinderI(v[9], v[0], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[7], v[0], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[7], v[9], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[9], v[7], v[6]);
     	 CylinderI(v[9], v[7], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[7], v[6], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[6], v[9], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[6], v[2], v[9]);
     	 CylinderI(v[6], v[2], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[2], v[9], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[9], v[6], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[9], v[8], v[0]);
     	 CylinderI(v[9], v[8], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[8], v[0], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[0], v[9], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[8], v[9], v[2]);
     	 CylinderI(v[8], v[9], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[9], v[2], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[2], v[8], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[2], v[3], v[5]);
     	 CylinderI(v[0], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[0], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[0], v[4], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[5], v[3], v[11]);
     	CylinderI(v[ 5], v[3], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[3], v[11], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[11], v[5], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[2], v[6], v[3]);
     	 CylinderI(v[2], v[6], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[6], v[3], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	 CylinderI(v[3], v[2], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[6], v[7], v[10]);
     	CylinderI(v[ 6], v[7], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[7], v[10], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[10], v[6], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[11], v[10], v[1]);
     	CylinderI(v[11], v[10],0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[10], v[1], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[1], v[11], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[3], v[10], v[11]);
     	CylinderI(v[3], v[10], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[10],v[11], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[11], v[3], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
     Triangle(v[3], v[6], v[10]);
     	CylinderI(v[3], v[ 6], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[6], v[10], 0.1 * abs(v[0] - v[4]), 0, 0, 6);
	CylinderI(v[10], v[3], 0.1 * abs(v[0] - v[4]), 0, 0, 6);


    return;
}

void POVRayWriter::colorCube(double r, const Vector3D& center, string color)
{
    double gold = (1 + sqrt(5))/2;
    Vector3D v[8] = {
      Vector3D( r + center.x(), r + center.y(), r + center.z()),
      Vector3D(-r + center.x(), r + center.y(), r + center.z()),
      Vector3D(-r + center.x(),-r + center.y(), r + center.z()),
      Vector3D( r + center.x(),-r + center.y(), r + center.z()),

      Vector3D( r + center.x(), r + center.y(),-r + center.z()),
      Vector3D(-r + center.x(), r + center.y(),-r + center.z()),
      Vector3D(-r + center.x(),-r + center.y(),-r + center.z()),
      Vector3D( r + center.x(),-r + center.y(),-r + center.z())
    };
	
    Vector3D mmm = Vector3D(0, 0, 0);
    for (int i = 0; i < 8; i++) {
      v[i] = inversionM(v[i], 0.2, mmm);
    }

    Triangle(v[0], v[1], v[2]);
    Triangle(v[2], v[3], v[0]);
    Triangle(v[6], v[5], v[4]);
    Triangle(v[4], v[7], v[6]);
    Triangle(v[0], v[3], v[7]);
    Triangle(v[7], v[4], v[0]);
    Triangle(v[1], v[2], v[6]);
    Triangle(v[6], v[5], v[1]);
    Triangle(v[2], v[3], v[7]);
    Triangle(v[7], v[6], v[2]);
    Triangle(v[0], v[1], v[5]);
    Triangle(v[5], v[4], v[0]);

    return;
}

void POVRayWriter::colorCubeI(double r, const Vector3D& center, string color, const Vector3D& gamma)
{
    double gold = (1 + sqrt(5))/2;
    Vector3D v[8] = {
      Vector3D( r + center.x(), r + center.y(), r + center.z()),
      Vector3D(-r + center.x(), r + center.y(), r + center.z()),
      Vector3D(-r + center.x(),-r + center.y(), r + center.z()),
      Vector3D( r + center.x(),-r + center.y(), r + center.z()),

      Vector3D( r + center.x(), r + center.y(),-r + center.z()),
      Vector3D(-r + center.x(), r + center.y(),-r + center.z()),
      Vector3D(-r + center.x(),-r + center.y(),-r + center.z()),
      Vector3D( r + center.x(),-r + center.y(),-r + center.z())
    };
        
    for (int i = 0; i < 8; i++) {
      v[i] = inversionM(v[i], 0.2, gamma);
    }
    //colorTriangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, string color)
    colorTriangle(v[0], v[1], v[2], color);
    colorTriangle(v[2], v[3], v[0], color);
    colorTriangle(v[6], v[5], v[4], color);
    colorTriangle(v[4], v[7], v[6], color);
    colorTriangle(v[0], v[3], v[7], color);
    colorTriangle(v[7], v[4], v[0], color);
    colorTriangle(v[1], v[2], v[6], color);
    colorTriangle(v[6], v[5], v[1], color);
    colorTriangle(v[2], v[3], v[7], color);
    colorTriangle(v[7], v[6], v[2], color);
    colorTriangle(v[0], v[1], v[5], color);
    colorTriangle(v[5], v[4], v[0], color);

    return;
}


void POVRayWriter::createStandardSphere(double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createSphere(r);

    return;
}

void POVRayWriter::createStandardPlane(double n1, double n2, double n3, double d, string c1, string c2)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject("", -1,-1);
    setObjectColorChecker(c1, c2);

    createPlane(n1, n2, n3, d);

    return;
}

void POVRayWriter::createStandardPlane(double d, string c1, string c2)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject("", -1,-1);
    setObjectColorChecker(c1, c2);

    createPlane(d);

    return;
}

void POVRayWriter::createStandardPlane(string plane, double d, string c1, string c2)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject("", -1,-1);
    setObjectColorChecker(c1, c2);

    createPlane(plane, d);

    return;
}

void POVRayWriter::createStandardBox(double xi, double yi, double zi, double xf, double yf, double zf, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBox(xi, yi, zi, xf, yf, zf);

    return;
}

void POVRayWriter::createStandardBoxInitFromVectorArray(double xf, double yf, double zf, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBoxInitFromVectorArray(xf, yf, zf);

    return;
}

void POVRayWriter::createStandardBoxLastFromVectorArray(double xi, double yi, double zi, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBoxLastFromVectorArray(xi, yi, zi);

    return;
}

void POVRayWriter::createStandardBoxFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createBoxFromVectorArray(initVector,lastVector,initIndex,lastIndex);

    return;
}

void POVRayWriter::createStandardCylinder(double xi, double yi, double zi, double xf, double yf, double zf,double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinder(xi, yi, zi, xf, yf, zf,r);

    return;
}

void POVRayWriter::createStandardCylinderInitFromVectorArray(double xf, double yf, double zf, double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinderInitFromVectorArray(xf, yf, zf,r);

    return;
}

void POVRayWriter::createStandardCylinderLastFromVectorArray(double xi, double yi, double zi, double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinderLastFromVectorArray(xi, yi, zi,r);

    return;
}

void POVRayWriter::createStandardCylinderFromVectorArray(string initVector, string lastVector, string initIndex, string lastIndex, double r, string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createCylinderFromVectorArray(initVector,lastVector,initIndex,lastIndex,r);

    return;
}


void POVRayWriter::createStandardTorus(double middleR,double minorR,string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createTorus(middleR, minorR);

    return;
}

void POVRayWriter::createStandardTorus(double x, double y, double z, double middleR,double minorR,string color)
{
    addFinishToNextObject(0.5,-1,-1);
    addPigmentToNextObject(color, -1,-1);

    createTorus(x,y,z,middleR, minorR);

    return;
}


// ============================= DECORATORS =========================== //


//This will make FINISH true so next instantiated object will have
//a particular value of phong, ambient, etc. If any of this values is < 0
//then is NOT added to the finish.
void POVRayWriter::addFinishToNextObject(double phong, double ambient, double diffuse)
{
    finish = true;
    phongToAdd = phong;
    diffuseToAdd=diffuse;
    ambientToAdd=ambient;
    return;
}

//Write the finish part of a primite object
void POVRayWriter::writeFinish()
{
    if (finish || defaultFinish)
    {
        finish = false;
        writer << "finish { ";
        if (phongToAdd > 0)
        {
            writer << "phong " << phongToAdd << " ";
        }
        if (diffuseToAdd > 0)
        {
            writer << "diffuse " << diffuseToAdd << " ";
        }
        if (ambientToAdd > 0)
        {
            writer << "ambient " << ambientToAdd << " ";
        }

        writer << " } " << endl;

    }
    return;
}

//Makes true the PIGMENT property so next instantiated object will have
//the particular selected values. It's obligatory to choose a color.
//The other properties can be ignored, only setting them to -1.
void POVRayWriter::addPigmentToNextObject(int r, int g, int b, double transmit, double filter)
{
    pigment = true;
    colorToAdd = rgbToString(r,g,b);
    transmitToAdd = transmit;
    filterToAdd = filter;
    return;
}

//Makes true the PIGMENT property so next instantiated object will have
//the particular selected values. It's obligatory to choose a color.
//The other properties can be ignored, only setting them to -1.
void POVRayWriter::addPigmentToNextObject(string color, double transmit, double filter)
{
    pigment = true;
    colorToAdd = color;
    transmitToAdd = transmit;
    filterToAdd = filter;
    return;
}

//Add a pigment to the next object, with color white and custom transmit/filter
void POVRayWriter::addPigmentToNextObject(double transmit, double filter)
{
    pigment = true;
    colorToAdd = "White";
    transmitToAdd = transmit;
    filterToAdd = filter;
    return;
}

//This can set the color of an object to a checkr mode
void POVRayWriter::setObjectColorChecker(string c1, string c2)
{
    checker = true;
    checkerColorToAdd[0] = c1;
    checkerColorToAdd[1] = c2;
    return;
}

//This can set the color of an object to a checkr mode
void POVRayWriter::setObjectColorChecker(int r1, int g1, int b1, int r2, int g2, int b2)
{
    checker = true;
    checkerColorToAdd[0] = rgbToString(r1,g1,b1);
    checkerColorToAdd[1] = rgbToString(r2,g2,b2);
    return;
}

//Write the pigment property of an object.
void POVRayWriter::writePigment()
{
    if (pigment || defaultPigment)
    {
        pigment = false;
        if (checker)
        {
            checker = false;
            writer << "pigment { checker color " << checkerColorToAdd[0] << " color " << checkerColorToAdd[1] << " ";
        }
        else
        {
            writer << "pigment { color " << colorToAdd << " ";
        }

        if (transmitToAdd > 0)
        {
            writer << "transmit " << transmitToAdd << " ";
        }
        if (filterToAdd > 0)
        {
             writer << "filter " << filterToAdd << " ";
        }

        writer << " }" << endl;
    }
}

//inclusion for textures in POV-Ray. Mandatory to include it at
//the beginning of the file if we want to include textures.
void POVRayWriter::useTextures()
{
    writer << "#include \"textures.inc\"" << endl << endl;
    return;
}

//Include the specified texture to next object. It's necesary
//to invoke useTextures at the beginning of the file to do this.
void POVRayWriter::addTextureToNextObject(string text)
{
    textureToAdd = text;
    texture = true;
    return;
}

//Write the texture into the material
void POVRayWriter::writeTexture()
{
    if (texture)
    {
        writer << "texture { " << textureToAdd << " }" << endl;
    }
    texture = false;
    return;
}

//Set the default finish true, so all objects will have
//same finish configuration after invoke this.
//That configuration is stablished with addFinishToNextObject.
void POVRayWriter::setDefaultFinish()
{
    defaultFinish = true;
    return;
}

//Set the default pigment true, so all objects will have
//same pigment configuration after invoke this.
//That configuration is stablished with addPigmentToNextObject.
void POVRayWriter::setDefaultPigment()
{
    defaultPigment = true;
    return;
}

//Delete all defualt configurations
void POVRayWriter::unsetDefaults()
{
    defaultFinish = defaultPigment = false;
    return;
}


// ============================ BLOBS AND CSG GEOMETRIES =========================== //

//Inits a blob object. It must be followed of the creation of primitives. After that,
//it must be closed using finishBlob function.
void POVRayWriter::startBlob(double threshold)
{
    writer << "blob {" << endl << "threshold " << threshold << endl;
    inBlob = true;
    return;
}

//Set the power for the next objects inside a blob.
//It's mandatory to include at least one of this inside a blob
//Power can be negative.
void POVRayWriter::addPowerToNextObjects(double power)
{
    powerToAdd = power;
}

//Closes the blob.It is not affected by the defaults.
void POVRayWriter::finishBlob()
{
    if (!defaultFinish)
    {
        writeFinish();
    }
    if (!defaultPigment)
    {
        writePigment();
    }


    writeTexture();
    writeRotation();

    writer << endl << "}" << endl << endl;
    inBlob = false;
    return;
}

//Write blob configuration inside an object
void POVRayWriter::writeBlob()
{
    if (inBlob)
    {
        writer << "," << endl << powerToAdd << endl;
    }
    else
    {
        writer << endl;
    }
    return;
}

//Start a new CSG object
//The string CSG can be union, difference,
//etc. depeding on what we want to do.
void POVRayWriter::startCSG(string CSG)
{
    writer << CSG << " {" << endl;
    return;
}

//Finish a CSG object and apply it's configuration
void POVRayWriter::finishCSG()
{
    if (!defaultFinish)
    {
        writeFinish();
    }
    if (!defaultPigment)
    {
        writePigment();
    }

    writeTexture();
    writeRotation();

    writer << endl << "}" << endl << endl;

    return;
}

/* This functions return the value of the constant
strings that can be used in startCSG argument */
 string POVRayWriter::CSGUnion()
 {
     return "union";
 }
string POVRayWriter::CSGIntersection()
{
    return "intersection";
}
string POVRayWriter::CSGDifference()
{
    return "difference";
}
string POVRayWriter::CSGMerge()
{
    return "merge";
}



// ===================== ARRAYS AND ROTATIONS=========================== //

//Declare a vector with a specific size and name
//IT'S NECESSARY TO CLOSE THIS WITH closeVectorArray.
 void POVRayWriter::declareVectorArray(int n, string name)
 {
     writer << "#declare " << name << " = array[" << n << "] {" << endl;

     return;
 }
 //This will add a element to the current opened/declared vector
void POVRayWriter::addElementToVectorArray(double x, double y, double z)
{
    writer << "<" << x << ", " << y << ", " << z << ">,";
}
//Closes the current vector. It's necessary to close a vector
//after the data input
void POVRayWriter::closeVectorArray()
{
    writer << endl << "} " << endl << endl;
}

//Declares a vector, introduces the data stored in x[], y[] and z[] and closes the vector
//This is a faster way to create a vector. If you need a flexible way or you like to control
//the details of the data input, you can use the primitives above.
void POVRayWriter::createFullVectorArray(int n, string name, double x[], double y[], double z[])
{
    int i;
    declareVectorArray(n, name);
    for (i=0; i < n; i++)
    {
        addElementToVectorArray(x[i], y[i], z[i]);
    }
    closeVectorArray();
}

//Allows the user to set the position of an object from the value of
//a vector array. It will affect only the next object.
void POVRayWriter::setNextObjectPosFromVector(string name, string index)
{
    nameToUse=name;
    indexToUse=index;
    useVector=true;

    return;
}

//Tell the system to use radians
//It will only affect the first overload of
//addRotationToNextObject
void POVRayWriter::useRadians()
{
    rad = true;
    return;
}

//Tell the system to use degrees (default configuration)
//It will only affect the first overload of
//addRotationToNextObject
void POVRayWriter::useDegrees()
{
    rad = false;
    return;
}

//Rotates the object x degrees around X axis, y  degrees
//around Y axis and z degrees around Z axis.
//The units by default are degrees, but it can be set to radians.
void POVRayWriter::addRotationToNextObject(double x, double y, double z)
{
    if (rad)
    {
        x = (180 * x) / pi;
        y = (180 * y) / pi;
        z = (180 * z) / pi;
    }
    stringstream s1, s2, s3;
    s1 << x;
    s2 << y;
    s3 << z;
    rotationToAdd = "<" + s1.str() + ", " + s2.str() + ", " + s3.str() + ">";
    rotation = true;
    return;
}

//It uses the vector name[index] to rotate the object. This will be
//ALWAYS in degrees, so if you use radians, make sure to transform them
//when you write your vector
void POVRayWriter::addRotationToNextObject(string name, string index)
{
    rotationToAdd.append(name);
    rotationToAdd.append("[");
    rotationToAdd.append(index);
    rotationToAdd.append("]");
    rotation = true;
    return;
}

//Write the rotation into an object
void POVRayWriter::writeRotation()
{
    if (rotation)
    {
        writer << "rotate " << rotationToAdd << endl;
    }

    return;
}



// ============================== AUXILIAR FUNCTIONS ===================================== //

//Write the (r,g,b) values into a correctly formated rgb color
string POVRayWriter::rgbToString(int r, int g, int b)
{
     stringstream s1, s2, s3;
    s1 << r;
    s2 << g;
    s3 << b;
    return "rgb <" + s1.str() + ", " + s2.str() + ", " + s3.str() + ">";
}

//Write the vector value at the index selected.
void POVRayWriter::writeVectorAtIndex()
{
    writer << nameToUse << "[" << indexToUse << "] ";
    useVector = false; //AÑADIDO DESPUES. CUIDADO. PUEDE QUE HAYA QUE QUITAR
    return;
}

//Writes the vector indicated in the file
void POVRayWriter::writeVector(double x, double y, double z)
{
    writer << "<" << x << ", " << y << ", " << z << "> ";
    return;
}

//Fractals
double gold = (1 + sqrt(5))/2;
Vector3D v[12] = {
  Vector3D( gold, 0, 1),
  Vector3D( gold, 0,-1),
  Vector3D(-gold, 0, 1),
  Vector3D(-gold, 0,-1),

  Vector3D( 1,-gold, 0),
  Vector3D(-1,-gold, 0),
  Vector3D(-1, gold, 0),
  Vector3D( 1, gold, 0),

  Vector3D( 0,-1, gold),
  Vector3D( 0, 1, gold),
  Vector3D( 0, 1,-gold),
  Vector3D( 0,-1,-gold)
};

Vector3D POVRayWriter::inversion(Vector3D p, double r) {
  Vector3D gamma = Vector3D(0, 0, 0);
  if (abs(p) < r) {
    return ((r*r)/abs(p)) * unit(p);
  } else{
    if ((abs(p) - r) < 0.000000000001) return p;
    else{
      return ((r*r)/abs(p)) * unit(p);
    }
  }
}

Vector3D POVRayWriter::inversionM(Vector3D p, double r, const Vector3D& gamma) {
  
	double d = abs(p-gamma);
	double check = sqrt((d-r)*(d-r));

        if (check < 1e-20) {return p;} else{
		
		double dd = (r*r)/d;
		Vector3D rest = p - gamma;
		rest = unit(rest);
		rest = (dd*rest) + gamma;
		return rest;
    	}
}


Vector3D POVRayWriter::inversionNew(Vector3D p, double r, Vector3D gamma) {
  if (abs(abs(p-gamma) - r) < 0.000000000001) return p;
  else {
    double d = (r*r)/abs(p-gamma);
    Vector3D u = unit(p-gamma);
    return (d*u) + gamma;
  }
}

void POVRayWriter::fractal1(const Vector3D& center, double r, int n) {
  
  double g = 0.33;
  Vector3D v[12] = {
      Vector3D(center.x() +  gold*r, center.y(), center.z() +  r),
      Vector3D(center.x() +  gold*r, center.y(), center.z() + -r),
      Vector3D(center.x() + -gold*r, center.y(), center.z() +  r),
      Vector3D(center.x() + -gold*r, center.y(), center.z() + -r),

      Vector3D(center.x() +  r,center.y() + -gold*r, center.z() ),
      Vector3D(center.x() + -r,center.y() + -gold*r, center.z() ),
      Vector3D(center.x() + -r,center.y() +  gold*r, center.z() ),
      Vector3D(center.x() +  r,center.y() +  gold*r, center.z() ),

      Vector3D( center.x(), center.y() + -r,center.z() +  gold*r),
      Vector3D( center.x(), center.y() +  r,center.z() +  gold*r),
      Vector3D( center.x(), center.y() +  r,center.z() + -gold*r),
      Vector3D( center.x(), center.y() + -r,center.z() + -gold*r)
 };

  for (int i = 0; i < 12; i++)
	  v[i] = g * v[i];


  if (n == 0)
  colorIco(r, center, "Red");
  else{

    //colorIco(r, center, "White");
    double r1 = r*g;
    Vector3D c1 = Vector3D(center);
    c1 += v[0];

    fractal1(c1, r1, n - 1);

    double r2 = r*g;
    Vector3D c2 = Vector3D(center);
    c2 += v[1];

    fractal1(c2, r2, n - 1);

    double r3 = r*g;
    Vector3D c3 = Vector3D(center);
    c3 += v[2];
    fractal1(c3, r3, n - 1);

    double r4 = r*g;
    Vector3D c4 = Vector3D(center);
    c4 += v[3];
    fractal1(c4, r4, n - 1);

    double r5 = r*g;
    Vector3D c5 = Vector3D(center);
    c5 += v[4];
    fractal1(c5, r5, n - 1);

    double r6 = r*g;
    Vector3D c6 = Vector3D(center);
    c6 += v[5];
    fractal1(c6, r6, n - 1);

    double r7 = r*g;
    Vector3D c7 = Vector3D(center);
    c7 += v[6];
    fractal1(c7, r7, n - 1);

    double r8 = r*g;
    Vector3D c8 = Vector3D(center);
    c8 += v[7];
    fractal1(c8, r8, n - 1);

    double r9 = r*g;
    Vector3D c9 = Vector3D(center);
    c9 += v[8];
    fractal1(c9, r9, n - 1);

    double r10 = r*g;
    Vector3D c10 = Vector3D(center);
    c10 += v[9];
    fractal1(c10, r10, n - 1);

    double r11 = r*g;
    Vector3D c11 = Vector3D(center);
    c11 += v[10];
    fractal1(c11, r11, n - 1);

    double r12 = r*g;
    Vector3D c12 = Vector3D(center);
    c12 += v[11];
    fractal1(c12, r12, n - 1);
  }

}

void POVRayWriter::polyTrace(Vector3D center[], double width) {
  bool simetria[12][12];
  for(int i = 0; i < 12; i++){
   for(int j = 0; j < 12; j++){
     simetria[i][j] = false;
    }
  }

double longitud = abs(center[0] - center[4]);

 int counting = 0;
 for(int i = 0; i < 12; i++){
   for(int j = 0; j < 12; j++){

     if((simetria[i][j] ==false) && ((abs(center[i] - center[j]) - longitud) <0.001) &&(abs(center[i] - center[j])>0.0)){
       Cylinder(center[i], center[j], width);
       simetria[j][i] = true;
     }
  }
}

}

void POVRayWriter::fractal2(Vector3D center[], int n, double width) {
  double gold= (1 + sqrt(5))/2;
  double g = 1/gold;
  double d = 1.61*gold;

  if (n == 0) {

    polyTrace(center, width);

     facet( center[0],  center[4],  center[1]);
     facet( center[8],  center[4],  center[0]);
     facet( center[8],  center[5],  center[4]);
     facet( center[2],  center[5],  center[8]);
     facet( center[11], center[4],  center[5]);
     facet( center[4],  center[11], center[1]);
     facet( center[7],  center[0],  center[1]);
     facet( center[7],  center[1],  center[10]);
     facet( center[9],  center[0],  center[7]);
     facet( center[9],  center[7],  center[6]);
     facet( center[6],  center[2],  center[9]);
     facet( center[9],  center[8],  center[0]);
     facet( center[8],  center[9],  center[2]);
     facet( center[2],  center[3],  center[5]);
     facet( center[5],  center[3],  center[11]);
     facet( center[2],  center[6],  center[3]);
     facet( center[6],  center[7],  center[10]);
     facet( center[11], center[10], center[1]);
     facet( center[3],  center[10], center[11]);
     facet( center[3],  center[6],  center[10]);
  } else {

    polyTrace(center, width);
    facet( center[0],  center[4],  center[1]);
    facet( center[8],  center[4],  center[0]);
    facet( center[8],  center[5],  center[4]);
    facet( center[2],  center[5],  center[8]);
    facet( center[11], center[4],  center[5]);
    facet( center[4],  center[11], center[1]);
    facet( center[7],  center[0],  center[1]);
    facet( center[7],  center[1],  center[10]);
    facet( center[9],  center[0],  center[7]);
    facet( center[9],  center[7],  center[6]);
    facet( center[6],  center[2],  center[9]);
    facet( center[9],  center[8],  center[0]);
    facet( center[8],  center[9],  center[2]);
    facet( center[2],  center[3],  center[5]);
    facet( center[5],  center[3],  center[11]);
    facet( center[2],  center[6],  center[3]);
    facet( center[6],  center[7],  center[10]);
    facet( center[11], center[10], center[1]);
    facet( center[3],  center[10], center[11]);
    facet( center[3],  center[6],  center[10]);

for (int j = 0; j < 12; j++) {
  Vector3D newCenter[12];
  Vector3D D = d * center[j];

  for (int i = 0; i < 12; i++) {
    newCenter[i] = (g * center[i]) + D;
  }

  fractal2(newCenter, n - 1, 0.5*width);

}

  }//end of else

}

void POVRayWriter::truncatedCubicHoneyComb(const Vector3D& center, double r, double thickness, double iC, double S) {
  Vector3D branch[6] = {
    Vector3D( r + center.x(), 0 + center.y(), 0 + center.z()),
    Vector3D( 0 + center.x(), r + center.y(), 0 + center.z()),
    Vector3D( 0 + center.x(), 0 + center.y(), r + center.z()),
    Vector3D(-r + center.x(), 0 + center.y(), 0 + center.z()),
    Vector3D( 0 + center.x(),-r + center.y(), 0 + center.z()),
    Vector3D( 0 + center.x(), 0 + center.y(),-r + center.z())
  };

  double r1 = abs(branch[0] - branch[1]) + r;

  Vector3D branch1[6] = {
    Vector3D( r1 + center.x(),  0 + center.y(),  0 + center.z()),
    Vector3D(  0 + center.x(), r1 + center.y(),  0 + center.z()),
    Vector3D(  0 + center.x(),  0 + center.y(), r1 + center.z()),
    Vector3D(-r1 + center.x(),  0 + center.y(),  0 + center.z()),
    Vector3D(  0 + center.x(),-r1 + center.y(),  0 + center.z()),
    Vector3D(  0 + center.x(),  0 + center.y(),-r1 + center.z())
  };


  for (int i = 0; i < 6; i++) {
    	
	  Vector3D end = inversion(branch[i], 5);
	  branch[i] = piecewiseVector(end, branch[i], iC, S);
  }

  for (int i = 0; i < 6; i++) {
  	
	Vector3D end = inversion(branch1[i], 5);
      	branch1[i] = piecewiseVector(end, branch1[i], iC, S);  
  }

  Cylinder(branch[0], branch[1], thickness);
  Cylinder(branch[1], branch[3], thickness);
  Cylinder(branch[3], branch[4], thickness);
  Cylinder(branch[4], branch[0], thickness);

  Cylinder(branch[0], branch[2], thickness);
  Cylinder(branch[1], branch[2], thickness);
  Cylinder(branch[3], branch[2], thickness);
  Cylinder(branch[4], branch[2], thickness);

  Cylinder(branch[0], branch[5], thickness);
  Cylinder(branch[1], branch[5], thickness);
  Cylinder(branch[3], branch[5], thickness);
  Cylinder(branch[4], branch[5], thickness);

  Cylinder(branch[0], branch1[0], thickness);
  Cylinder(branch[1], branch1[1], thickness);
  Cylinder(branch[2], branch1[2], thickness);
  Cylinder(branch[3], branch1[3], thickness);
  Cylinder(branch[4], branch1[4], thickness);
  Cylinder(branch[5], branch1[5], thickness);

  //Triangle(branch[0], branch[1], branch[2]);
  //Triangle(branch[1], branch[3], branch[2]);
  //Triangle(branch[3], branch[4], branch[2]);
  //Triangle(branch[4], branch[0], branch[2]);

  //Triangle(branch[0], branch[1], branch[5]);
  //Triangle(branch[1], branch[3], branch[5]);
  //Triangle(branch[3], branch[4], branch[5]);
  //Triangle(branch[4], branch[0], branch[5]);

}

void POVRayWriter::rhombicuboctahedronHoneyComb(const Vector3D& center, double r, double thickness) {
  Vector3D rhombi[24] = {
      Vector3D(center.x() + ( 1.0*r), center.y() + ( 1.0*r), center.z() + ( 2.4*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + ( 1.0*r), center.z() + ( 2.4*r)),
      Vector3D(center.x() + ( 1.0*r), center.y() + (-1.0*r), center.z() + ( 2.4*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + (-1.0*r), center.z() + ( 2.4*r)),
      Vector3D(center.x() + ( 1.0*r), center.y() + ( 1.0*r), center.z() + (-2.4*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + ( 1.0*r), center.z() + (-2.4*r)),
      Vector3D(center.x() + ( 1.0*r), center.y() + (-1.0*r), center.z() + (-2.4*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + (-1.0*r), center.z() + (-2.4*r)),

      Vector3D(center.x() + ( 1.0*r), center.y() + ( 2.4*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + ( 2.4*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + ( 1.0*r), center.y() + ( 2.4*r), center.z() + (-1.0*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + ( 2.4*r), center.z() + (-1.0*r)),
      Vector3D(center.x() + ( 1.0*r), center.y() + (-2.4*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + (-2.4*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + ( 1.0*r), center.y() + (-2.4*r), center.z() + (-1.0*r)),
      Vector3D(center.x() + (-1.0*r), center.y() + (-2.4*r), center.z() + (-1.0*r)),

      Vector3D(center.x() + ( 2.4*r), center.y() + ( 1.0*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + ( 2.4*r), center.y() + (-1.0*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + ( 2.4*r), center.y() + ( 1.0*r), center.z() + (-1.0*r)),
      Vector3D(center.x() + ( 2.4*r), center.y() + (-1.0*r), center.z() + (-1.0*r)),
      Vector3D(center.x() + (-2.4*r), center.y() + ( 1.0*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + (-2.4*r), center.y() + (-1.0*r), center.z() + ( 1.0*r)),
      Vector3D(center.x() + (-2.4*r), center.y() + ( 1.0*r), center.z() + (-1.0*r)),
      Vector3D(center.x() + (-2.4*r), center.y() + (-1.0*r), center.z() + (-1.0*r))
  };

  for (int i = 0; i < 24; i++) {
    rhombi[i] = inversion(rhombi[i], 5);
  }

  Cylinder(rhombi[0], rhombi[1], thickness);
  Cylinder(rhombi[4], rhombi[5], thickness);
  Cylinder(rhombi[1], rhombi[3], thickness);
  Cylinder(rhombi[5], rhombi[7], thickness);

  Cylinder(rhombi[3], rhombi[2], thickness);
  Cylinder(rhombi[7], rhombi[6], thickness);
  Cylinder(rhombi[2], rhombi[0], thickness);
  Cylinder(rhombi[6], rhombi[4], thickness);

  Cylinder(rhombi[8], rhombi[9],   thickness);
  Cylinder(rhombi[12], rhombi[13], thickness);
  Cylinder(rhombi[9], rhombi[11],  thickness);
  Cylinder(rhombi[13], rhombi[15], thickness);

  Cylinder(rhombi[11], rhombi[10], thickness);
  Cylinder(rhombi[15], rhombi[14], thickness);
  Cylinder(rhombi[10], rhombi[8],  thickness);
  Cylinder(rhombi[14], rhombi[12], thickness);

  Cylinder(rhombi[16], rhombi[17], thickness);
  Cylinder(rhombi[20], rhombi[21], thickness);
  Cylinder(rhombi[17], rhombi[19], thickness);
  Cylinder(rhombi[21], rhombi[23], thickness);

  Cylinder(rhombi[19], rhombi[18], thickness);
  Cylinder(rhombi[23], rhombi[22], thickness);
  Cylinder(rhombi[18], rhombi[16], thickness);
  Cylinder(rhombi[22], rhombi[20], thickness);


  Triangle(rhombi[3], rhombi[2], rhombi[0]);
  Triangle(rhombi[0], rhombi[1], rhombi[3]);

  Triangle(rhombi[4], rhombi[6], rhombi[7]);
  Triangle(rhombi[7], rhombi[5], rhombi[4]);

  Triangle(rhombi[9], rhombi[8], rhombi[10]);
  Triangle(rhombi[10], rhombi[11], rhombi[9]);

  Triangle(rhombi[12], rhombi[13], rhombi[15]);
  Triangle(rhombi[15], rhombi[14], rhombi[12]);

  Triangle(rhombi[2], rhombi[3], rhombi[13]);
  Triangle(rhombi[13], rhombi[12], rhombi[2]);

  Triangle(rhombi[14], rhombi[15], rhombi[7]);
  Triangle(rhombi[7], rhombi[6], rhombi[14]);

  Triangle(rhombi[1], rhombi[0], rhombi[8]);
  Triangle(rhombi[8], rhombi[9], rhombi[1]);

  Triangle(rhombi[11], rhombi[10], rhombi[4]);
  Triangle(rhombi[4], rhombi[5], rhombi[11]);

  Triangle(rhombi[16], rhombi[17], rhombi[19]);
  Triangle(rhombi[19], rhombi[18], rhombi[16]);

  Triangle(rhombi[0], rhombi[2], rhombi[17]);
  Triangle(rhombi[17], rhombi[16], rhombi[0]);

  Triangle(rhombi[17], rhombi[12], rhombi[14]);
  Triangle(rhombi[14], rhombi[19], rhombi[17]);

  Triangle(rhombi[18], rhombi[19], rhombi[6]);
  Triangle(rhombi[6], rhombi[4], rhombi[18]);

  Triangle(rhombi[8], rhombi[16], rhombi[18]);
  Triangle(rhombi[18], rhombi[10], rhombi[8]);

  Triangle(rhombi[3], rhombi[1], rhombi[20]);
  Triangle(rhombi[20], rhombi[21], rhombi[3]);

  Triangle(rhombi[21], rhombi[20], rhombi[22]);
  Triangle(rhombi[22], rhombi[23], rhombi[21]);

  Triangle(rhombi[23], rhombi[22], rhombi[5]);
  Triangle(rhombi[5], rhombi[7], rhombi[23]);

  Triangle(rhombi[20], rhombi[9], rhombi[11]);
  Triangle(rhombi[11], rhombi[22], rhombi[20]);

  Triangle(rhombi[13], rhombi[21], rhombi[23]);
  Triangle(rhombi[23], rhombi[15], rhombi[13]);

  Cylinder(rhombi[0], rhombi[8],   thickness);
  Cylinder(rhombi[0], rhombi[16],  thickness);
  Cylinder(rhombi[8], rhombi[16],  thickness);
  Triangle(rhombi[0], rhombi[16], rhombi[8]);

  Cylinder(rhombi[1], rhombi[9],   thickness);
  Cylinder(rhombi[1], rhombi[20],  thickness);
  Cylinder(rhombi[20], rhombi[9],  thickness);
  Triangle(rhombi[1], rhombi[9], rhombi[20]);

  Cylinder(rhombi[2], rhombi[12],  thickness);
  Cylinder(rhombi[2], rhombi[17],  thickness);
  Cylinder(rhombi[12], rhombi[17], thickness);
  Triangle(rhombi[2], rhombi[17], rhombi[12]);

  Cylinder(rhombi[3], rhombi[13],  thickness);
  Cylinder(rhombi[3], rhombi[21],  thickness);
  Cylinder(rhombi[13], rhombi[21], thickness);
  Triangle(rhombi[3], rhombi[13], rhombi[21]);

  Cylinder(rhombi[4], rhombi[10],  thickness);
  Cylinder(rhombi[4], rhombi[18],  thickness);
  Cylinder(rhombi[10], rhombi[18], thickness);
  Triangle(rhombi[4], rhombi[10], rhombi[18]);

  Cylinder(rhombi[6], rhombi[14],  thickness);
  Cylinder(rhombi[6], rhombi[19],  thickness);
  Cylinder(rhombi[14], rhombi[19], thickness);
  Triangle(rhombi[6], rhombi[14], rhombi[19]);

  Cylinder(rhombi[7], rhombi[15],  thickness);
  Cylinder(rhombi[7], rhombi[23],  thickness);
  Cylinder(rhombi[15], rhombi[23], thickness);
  Triangle(rhombi[7], rhombi[15], rhombi[23]);

  Cylinder(rhombi[5], rhombi[11],  thickness);
  Cylinder(rhombi[5], rhombi[22],  thickness);
  Cylinder(rhombi[11], rhombi[22], thickness);
  Triangle(rhombi[5], rhombi[11], rhombi[22]);


  return;
}

void POVRayWriter::rhombiHoneyComb(const Vector3D& center, double r, double thickness, int n) {
  for (int i =-n; i < n+1; i++) {
    for (int j =-0; j < 1; j++) {
      for (int k =-n; k < n+1; k++) {
        rhombicuboctahedronHoneyComb(Vector3D(center.x() + 7*r*i, center.y() + 7*r*j, center.z() + 7*r*k), r, thickness);
      }
    }
  }
}

double POVRayWriter::X(double u, double v, double R, double r) {
  return R*sin(u)*cos(v);//( R + (r*cos(v*0.5)) ) * cos(u*0.5);
}

double POVRayWriter::Y(double u, double v, double R, double r) {
  return R*sin(u)*sin(v);;//( R + (r*cos(v*0.5)) ) * sin(u*0.5);
}

double POVRayWriter::Z(double u, double v, double R, double r) {
  return R*cos(u);//r * sin(v*0.5);
}

double POVRayWriter::Cx(double x, double rad) {
  return cos(x)*rad;
}

double POVRayWriter::Cy(double x, double rad) {
  return sin(x)*rad;
}

double POVRayWriter::Cz(double x, double rad) {
  return 0*rad;
}

void POVRayWriter::functionDeclaration(string S) {
  int n = S.length();
  char functionInfo[n];
  strcpy(functionInfo, S.c_str());

  for (int i = 0; i < n; i++)
    if (isalpha(functionInfo[i]) == true)
      cout << functionInfo[i];
    else
      cout << "#";
}

void POVRayWriter::torusHoneyComb(double R, double r, int n, int m)
{
    Vector3D cuad[n+1][m+1];
    Vector3D cuad1[n+1][m+1];
    Vector3D cuad2[n+1][m+1];
    Vector3D cuad3[n+1][m+1];
    Vector3D cuad4[n+1][m+1];
    Vector3D cuad5[n+1][m+1];
    Vector3D cuad6[n+1][m+1];
    Vector3D cuad7[n+1][m+1];

    Vector3D cuad0[n+1][m+1];
    Vector3D cuad01[n+1][m+1];
    Vector3D cuad02[n+1][m+1];
    Vector3D cuad03[n+1][m+1];
    Vector3D cuad04[n+1][m+1];
    Vector3D cuad05[n+1][m+1];
    Vector3D cuad06[n+1][m+1];
    Vector3D cuad07[n+1][m+1];

    Vector3D Nexus0[n+1][m+1];
    Vector3D Nexus1[n+1][m+1];
    Vector3D Nexus2[n+1][m+1];
    Vector3D Nexus02[n+1][m+1];
    Vector3D Nexus3[n+1][m+1];
    Vector3D Nexus4[n+1][m+1];
    Vector3D Nexus5[n+1][m+1];
    Vector3D Nexus6[n+1][m+1];


    double ha= 2.0 * M_PI / n;
    double hb= 2.0 * M_PI / m;

    double R1 = R;
    double r1 = 1.12*r;
    double R2 = R1;
    double r2 = 1.12*r1;
    double R3 = R2;
    double r3 = 1.12*r2;

    for (int i=0; i<=n; ++i)
      {
       double a= (i * ha) + (ha * 0.33);
       double a1= (i * ha) + (ha * 0.66);
       double a2= (i * ha) + (ha);
       double a3= (i * ha) + (ha);
       double a4= (i * ha) + (ha*0.66);
       double a5= (i * ha) + (ha*0.33);
       double a6= (i * ha);
       double a7= (i * ha);



       for (int j=0; j<=m; ++j)
	   {
            double b= j * hb;
            double b1= (j * hb);
            double b2= (j * hb) + (0.33*hb);
            double b3= (j * hb) + (0.66*hb);
            double b4= (j * hb) + (hb);
            double b5= (j * hb) + (hb);
            double b6= (j * hb) + (0.66*hb);
            double b7= (j * hb) + (0.33*hb);

            double u= R + r*cos(b);
            double u1= R + r*cos(b1);
            double u2= R + r*cos(b2);
            double u3= R + r*cos(b3);
            double u4= R + r*cos(b4);
            double u5= R + r*cos(b5);
            double u6= R + r*cos(b6);
            double u7= R + r*cos(b7);

            double u0= R3 + r3*cos(b);
            double u01= R3 + r3*cos(b1);
            double u02= R3 + r3*cos(b2);
            double u03= R3 + r3*cos(b3);
            double u04= R3 + r3*cos(b4);
            double u05= R3 + r3*cos(b5);
            double u06= R3 + r3*cos(b6);
            double u07= R3 + r3*cos(b7);

            cuad[i][j]= Vector3D(u*cos(a), u*sin(a), r*sin(b));
            cuad1[i][j]= Vector3D(u1*cos(a1), u1*sin(a1), r*sin(b1));
            cuad2[i][j]= Vector3D(u2*cos(a2), u2*sin(a2), r*sin(b2));
            cuad3[i][j]= Vector3D(u3*cos(a3), u3*sin(a3), r*sin(b3));
            cuad4[i][j]= Vector3D(u4*cos(a4), u4*sin(a4), r*sin(b4));
            cuad5[i][j]= Vector3D(u5*cos(a5), u5*sin(a5), r*sin(b5));
            cuad6[i][j]= Vector3D(u6*cos(a6), u6*sin(a6), r*sin(b6));
            cuad7[i][j]= Vector3D(u7*cos(a7), u7*sin(a7), r*sin(b7));

            cuad0[i][j]= Vector3D(u0*cos(a), u0*sin(a), r3*sin(b));
            cuad01[i][j]= Vector3D(u01*cos(a1), u01*sin(a1), r3*sin(b1));
            cuad02[i][j]= Vector3D(u02*cos(a2), u02*sin(a2), r3*sin(b2));
            cuad03[i][j]= Vector3D(u03*cos(a3), u03*sin(a3), r3*sin(b3));
            cuad04[i][j]= Vector3D(u04*cos(a4), u04*sin(a4), r3*sin(b4));
            cuad05[i][j]= Vector3D(u05*cos(a5), u05*sin(a5), r3*sin(b5));
            cuad06[i][j]= Vector3D(u06*cos(a6), u06*sin(a6), r3*sin(b6));
            cuad07[i][j]= Vector3D(u07*cos(a7), u07*sin(a7), r3*sin(b7));
            /////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////// Octahedron Conection
            ///////////////////////////////////////////////////////////////////////////////////

            Nexus0[i][j]= Vector3D((R1 + r1*cos(b))*cos(a6), (R1 + r1*cos(b))*sin(a6), r1*sin(b));
            Nexus1[i][j]= Vector3D((R1 + r1*cos(b4))*cos(a2), (R1 + r1*cos(b4))*sin(a2), r1*sin(b4));


            Nexus2[i][j]= Vector3D((R2 + r2*cos(b))*cos(a6), (R2 + r2*cos(b))*sin(a6), r2*sin(b));
             Nexus02[i][j]= Vector3D((R2 + r2*cos(b5))*cos(a2), (R2 + r2*cos(b5))*sin(a2), r2*sin(b5));

		   /////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////// OctahedronConection2
            ///////////////////////////////////////////////////////////////////////////////////


            Nexus3[i][j]= Vector3D((R3 + r3*cos(b7))*cos(a7), (R3 + r3*cos(b7))*sin(a7), r3*sin(b7));
            Nexus4[i][j]= Vector3D((R3 + r3*cos(b))*cos(a), (R3 + r3*cos(b))*sin(a), r3*sin(b));
            Nexus5[i][j]= Vector3D((R3 + r3*cos(b4))*cos(a4), (R3 + r3*cos(b4))*sin(a4), r3*sin(b4));
            Nexus6[i][j]= Vector3D((R3 + r3*cos(b3))*cos(a3), (R3 + r3*cos(b3))*sin(a3), r3*sin(b3));

           }
      }

    for (int i=0; i<n; ++i)
       for (int j=0; j<m; ++j)
          {
          	double width = 0.5*0.25*0.5*0.25;
          	Cylinder(cuad[i][j], cuad1[i][j], width);
          	Cylinder(cuad1[i][j], cuad2[i][j], width);
          	Cylinder(cuad2[i][j], cuad3[i][j], width);
          	Cylinder(cuad3[i][j], cuad4[i][j], width);
          	Cylinder(cuad4[i][j], cuad5[i][j], width);
          	Cylinder(cuad5[i][j], cuad6[i][j], width);
          	Cylinder(cuad7[i][j], cuad[i][j], width);

          	Cylinder(cuad0[i][j], cuad01[i][j], width);
          	Cylinder(cuad01[i][j], cuad02[i][j], width);
          	Cylinder(cuad02[i][j], cuad03[i][j], width);
          	Cylinder(cuad03[i][j], cuad04[i][j], width);
          	Cylinder(cuad04[i][j], cuad05[i][j], width);
          	Cylinder(cuad05[i][j], cuad06[i][j], width);
          	Cylinder(cuad07[i][j], cuad0[i][j], width);

          	Cylinder(cuad7[i][j], Nexus0[i][j], width * 0.5);
          	Cylinder(cuad[i][j], Nexus0[i][j], width * 0.5);
          	Cylinder(cuad4[i][j], Nexus1[i][j], width * 0.5);
          	Cylinder(cuad3[i][j], Nexus1[i][j], width * 0.5);

            Cylinder(Nexus2[i][j], Nexus0[i][j], width * 0.5);

			Cylinder(Nexus2[i][j], Nexus3[i][j], width * 0.5);
			Cylinder(Nexus2[i][j], Nexus4[i][j], width * 0.5);
			Cylinder(Nexus5[i][j], Nexus02[i][j], width * 0.5);
			Cylinder(Nexus6[i][j], Nexus02[i][j], width * 0.5);

		   Triangle(cuad[i+1][j+1], cuad[i+1][j], cuad[i][j]);
           Triangle(cuad[i][j+1], cuad[i+1][j+1], cuad[i][j]);
          }
}

void POVRayWriter::torusHoneyComb1(double R, double r, int n, int m)
{
    Vector3D cuad[n+1][m+1];
    Vector3D cuad1[n+1][m+1];
    Vector3D cuad2[n+1][m+1];
    Vector3D cuad3[n+1][m+1];

    Vector3D cuad0[n+1][m+1];
    Vector3D cuad01[n+1][m+1];
    Vector3D cuad02[n+1][m+1];
    Vector3D cuad03[n+1][m+1];
    Vector3D cuad04[n+1][m+1];
    Vector3D cuad05[n+1][m+1];
    Vector3D cuad06[n+1][m+1];
    Vector3D cuad07[n+1][m+1];

    Vector3D cuada [n+1][m+1];
    Vector3D cuada1[n+1][m+1];
    Vector3D cuada2[n+1][m+1];
    Vector3D cuada3[n+1][m+1];
    Vector3D cuada4[n+1][m+1];
    Vector3D cuada5[n+1][m+1];
    Vector3D cuada6[n+1][m+1];
    Vector3D cuada7[n+1][m+1];

    Vector3D cuadb[n+1][m+1];
    Vector3D cuadb1[n+1][m+1];
    Vector3D cuadb2[n+1][m+1];
    Vector3D cuadb3[n+1][m+1];


    double ha= 2.0 * M_PI / n;
    double hb= 2.0 * M_PI / m;

    double R1 = R;
    double r1 = 1.12*r;
    double R2 = R1;
    double r2 = 1.12*r1;
    double R3 = R2;
    double r3 = 1.12*r2;

    for (int i=0; i<=n; ++i)
      {
       double a = (i * ha) + (ha * 0.25);
       double a1= (i * ha) + (ha * 0.75);
       double a2= (i * ha) + (ha * 0.75);
       double a3= (i * ha) + (ha * 0.25);

       double q0 = (i * ha) + (ha * 0.33);
       double q1 = (i * ha) + (ha * 0.66);
       double q2 = (i * ha) + (ha * 0.90);
       double q3 = (i * ha) + (ha * 0.90);
       double q4 = (i * ha) + (ha * 0.66);
       double q5 = (i * ha) + (ha * 0.33);
       double q6 = (i * ha) + (ha * 0.10);
       double q7 = (i * ha) + (ha * 0.10);

       for (int j=0; j<=m; ++j)
	   {
            double b = (j * hb) + (0.25*hb);
            double b1= (j * hb) + (0.25*hb);
            double b2= (j * hb) + (0.75*hb);
            double b3= (j * hb) + (0.75*hb);

            double p0 = (j * ha) + (ha * 0.10);
            double p1 = (j * ha) + (ha * 0.10);
            double p2 = (j * ha) + (ha * 0.33);
            double p3 = (j * ha) + (ha * 0.66);
            double p4 = (j * ha) + (ha * 0.90);
            double p5 = (j * ha) + (ha * 0.90);
            double p6 = (j * ha) + (ha * 0.66);
            double p7 = (j * ha) + (ha * 0.33);
            /*double u0= R3 + r3*cos(b);
            double u01= R3 + r3*cos(b1);
            double u02= R3 + r3*cos(b2);
            double u03= R3 + r3*cos(b3);
            double u04= R3 + r3*cos(b4);
            double u05= R3 + r3*cos(b5);
            double u06= R3 + r3*cos(b6);
            double u07= R3 + r3*cos(b7);*/

            cuad[i][j] = Vector3D((R + r*cos(b ))*cos(a),  (R + r*cos(b ))*sin(a),  r*sin(b));
            cuad1[i][j]= Vector3D((R + r*cos(b1))*cos(a1), (R + r*cos(b1))*sin(a1), r*sin(b1));
            cuad2[i][j]= Vector3D((R + r*cos(b2))*cos(a2), (R + r*cos(b2))*sin(a2), r*sin(b2));
            cuad3[i][j]= Vector3D((R + r*cos(b3))*cos(a3), (R + r*cos(b3))*sin(a3), r*sin(b3));

            cuad0[i][j] = Vector3D((R + r1*cos(p0))*cos(q0), (R + r1*cos(p0))*sin(q0), r1*sin(p0));
            cuad01[i][j]= Vector3D((R + r1*cos(p1))*cos(q1), (R + r1*cos(p1))*sin(q1), r1*sin(p1));
            cuad02[i][j]= Vector3D((R + r1*cos(p2))*cos(q2), (R + r1*cos(p2))*sin(q2), r1*sin(p2));
            cuad03[i][j]= Vector3D((R + r1*cos(p3))*cos(q3), (R + r1*cos(p3))*sin(q3), r1*sin(p3));
            cuad04[i][j]= Vector3D((R + r1*cos(p4))*cos(q4), (R + r1*cos(p4))*sin(q4), r1*sin(p4));
            cuad05[i][j]= Vector3D((R + r1*cos(p5))*cos(q5), (R + r1*cos(p5))*sin(q5), r1*sin(p5));
            cuad06[i][j]= Vector3D((R + r1*cos(p6))*cos(q6), (R + r1*cos(p6))*sin(q6), r1*sin(p6));
            cuad07[i][j]= Vector3D((R + r1*cos(p7))*cos(q7), (R + r1*cos(p7))*sin(q7), r1*sin(p7));

            cuada[i][j] = Vector3D((R + r2*cos(p0))*cos(q0), (R + r2*cos(p0))*sin(q0), r2*sin(p0));
            cuada1[i][j]= Vector3D((R + r2*cos(p1))*cos(q1), (R + r2*cos(p1))*sin(q1), r2*sin(p1));
            cuada2[i][j]= Vector3D((R + r2*cos(p2))*cos(q2), (R + r2*cos(p2))*sin(q2), r2*sin(p2));
            cuada3[i][j]= Vector3D((R + r2*cos(p3))*cos(q3), (R + r2*cos(p3))*sin(q3), r2*sin(p3));
            cuada4[i][j]= Vector3D((R + r2*cos(p4))*cos(q4), (R + r2*cos(p4))*sin(q4), r2*sin(p4));
            cuada5[i][j]= Vector3D((R + r2*cos(p5))*cos(q5), (R + r2*cos(p5))*sin(q5), r2*sin(p5));
            cuada6[i][j]= Vector3D((R + r2*cos(p6))*cos(q6), (R + r2*cos(p6))*sin(q6), r2*sin(p6));
            cuada7[i][j]= Vector3D((R + r2*cos(p7))*cos(q7), (R + r2*cos(p7))*sin(q7), r2*sin(p7));

            cuadb[i][j] = Vector3D((R + r3*cos(b ))*cos(a),  (R + r3*cos(b ))*sin(a),  r3*sin(b));
            cuadb1[i][j]= Vector3D((R + r3*cos(b1))*cos(a1), (R + r3*cos(b1))*sin(a1), r3*sin(b1));
            cuadb2[i][j]= Vector3D((R + r3*cos(b2))*cos(a2), (R + r3*cos(b2))*sin(a2), r3*sin(b2));
            cuadb3[i][j]= Vector3D((R + r3*cos(b3))*cos(a3), (R + r3*cos(b3))*sin(a3), r3*sin(b3));

            /////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////// Octahedron Conection
            ///////////////////////////////////////////////////////////////////////////////////
/*
            Nexus0[i][j]= Vector3D((R1 + r1*cos(b))*cos(a6), (R1 + r1*cos(b))*sin(a6), r1*sin(b));
            Nexus1[i][j]= Vector3D((R1 + r1*cos(b4))*cos(a2), (R1 + r1*cos(b4))*sin(a2), r1*sin(b4));


            Nexus2[i][j]= Vector3D((R2 + r2*cos(b))*cos(a6), (R2 + r2*cos(b))*sin(a6), r2*sin(b));
            Nexus02[i][j]= Vector3D((R2 + r2*cos(b5))*cos(a2), (R2 + r2*cos(b5))*sin(a2), r2*sin(b5));

		   /////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////// OctahedronConection2
            ///////////////////////////////////////////////////////////////////////////////////


            Nexus3[i][j]= Vector3D((R3 + r3*cos(b7))*cos(a7), (R3 + r3*cos(b7))*sin(a7), r3*sin(b7));
            Nexus4[i][j]= Vector3D((R3 + r3*cos(b))*cos(a), (R3 + r3*cos(b))*sin(a), r3*sin(b));
            Nexus5[i][j]= Vector3D((R3 + r3*cos(b4))*cos(a4), (R3 + r3*cos(b4))*sin(a4), r3*sin(b4));
            Nexus6[i][j]= Vector3D((R3 + r3*cos(b3))*cos(a3), (R3 + r3*cos(b3))*sin(a3), r3*sin(b3));
*/
           }
      }

    for (int i=0; i<n; ++i)
       for (int j=0; j<m; ++j)
          {
          	double width = 0.1;
          	Cylinder(cuad[i][j], cuad1[i][j], width);
          	Cylinder(cuad1[i][j], cuad2[i][j], width);
          	Cylinder(cuad2[i][j], cuad3[i][j], width);
          	Cylinder(cuad3[i][j], cuad[i][j], width);

          	Cylinder(cuad0[i][j], cuad01[i][j], width);
          	Cylinder(cuad01[i][j], cuad02[i][j], width);
          	Cylinder(cuad02[i][j], cuad03[i][j], width);
          	Cylinder(cuad03[i][j], cuad04[i][j], width);
          	Cylinder(cuad04[i][j], cuad05[i][j], width);
          	Cylinder(cuad05[i][j], cuad06[i][j], width);
            Cylinder(cuad06[i][j], cuad07[i][j], width);
          	Cylinder(cuad07[i][j], cuad0[i][j], width);

            Cylinder( cuad[i][j], cuad0[i][j], width);
            Cylinder(cuad1[i][j], cuad01[i][j], width);
            Cylinder(cuad1[i][j], cuad02[i][j], width);
            Cylinder(cuad2[i][j], cuad03[i][j], width);
            Cylinder(cuad2[i][j], cuad04[i][j], width);
            Cylinder(cuad3[i][j], cuad05[i][j], width);
            Cylinder(cuad3[i][j], cuad06[i][j], width);
            Cylinder( cuad[i][j], cuad07[i][j], width);

            Cylinder(cuada[i][j],  cuada1[i][j], width);
          	Cylinder(cuada1[i][j], cuada2[i][j], width);
          	Cylinder(cuada2[i][j], cuada3[i][j], width);
          	Cylinder(cuada3[i][j], cuada4[i][j], width);
          	Cylinder(cuada4[i][j], cuada5[i][j], width);
          	Cylinder(cuada5[i][j], cuada6[i][j], width);
            Cylinder(cuada6[i][j], cuada7[i][j], width);
          	Cylinder(cuada7[i][j], cuada[i][j], width);

            Cylinder( cuad0[i][j], cuada[i][j], width);
            Cylinder(cuad01[i][j], cuada1[i][j], width);
            Cylinder(cuad02[i][j], cuada2[i][j], width);
            Cylinder(cuad03[i][j], cuada3[i][j], width);
            Cylinder(cuad04[i][j], cuada4[i][j], width);
            Cylinder(cuad05[i][j], cuada5[i][j], width);
            Cylinder(cuad06[i][j], cuada6[i][j], width);
            Cylinder(cuad07[i][j], cuada7[i][j], width);

            Cylinder(cuadb[i][j],  cuadb1[i][j], width);
          	Cylinder(cuadb1[i][j], cuadb2[i][j], width);
          	Cylinder(cuadb2[i][j], cuadb3[i][j], width);
          	Cylinder(cuadb3[i][j], cuadb[i][j], width);

            Cylinder(cuadb[i][j],  cuada[i][j], width);
            Cylinder(cuadb1[i][j], cuada1[i][j], width);
            Cylinder(cuadb1[i][j], cuada2[i][j], width);
            Cylinder(cuadb2[i][j], cuada3[i][j], width);
            Cylinder(cuadb2[i][j], cuada4[i][j], width);
            Cylinder(cuadb3[i][j], cuada5[i][j], width);
            Cylinder(cuadb3[i][j], cuada6[i][j], width);
            Cylinder(cuadb[i][j],  cuada7[i][j], width);

            facet(cuadb[i][j], cuada7[i][j], cuada[i][j]);
            facet(cuadb1[i][j], cuada1[i][j], cuada2[i][j]);
            facet(cuadb2[i][j], cuada3[i][j], cuada4[i][j]);
            facet(cuadb3[i][j], cuada5[i][j], cuada6[i][j]);

            facet(cuadb[i][j], cuadb1[i][j], cuada1[i][j]);
            facet(cuada1[i][j], cuada[i][j], cuadb[i][j]);

            facet(cuadb3[i][j], cuadb[i][j], cuada7[i][j]);
            facet(cuada7[i][j], cuada6[i][j], cuadb3[i][j]);

            facet(cuadb2[i][j], cuadb3[i][j], cuada5[i][j]);
            facet(cuada5[i][j], cuada4[i][j], cuadb2[i][j]);

            facet(cuadb2[i][j], cuadb1[i][j], cuada2[i][j]);
            facet(cuada2[i][j], cuada3[i][j], cuadb2[i][j]);

            facet(cuadb[i][j], cuadb1[i][j], cuada1[i][j]);
            facet(cuada1[i][j], cuada[i][j], cuadb[i][j]);


		       Triangle(cuad[i+1][j+1], cuad[i+1][j], cuad[i][j]);
           Triangle(cuad[i][j+1], cuad[i+1][j+1], cuad[i][j]);
          }
}

