#ifndef STL_H
#define STL_H

using namespace std;

#include <iostream>
#include "Vector3D.hpp"
#include <math.h>
#include <string>
#include <fstream>

class STL {
       	private:
		
		string filePath;
		ofstream pencil;
	public:
	
		STL() {};
		STL(string path);
		void write(string str);
		void facet(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
		void closeSTL();
			
};		


#endif
