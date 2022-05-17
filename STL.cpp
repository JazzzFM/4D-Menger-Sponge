using namespace std;

#include "STL.hpp"
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

STL::STL(string path) {
	
	pencil.open(path.c_str());

        if (pencil.is_open()) {

            filePath = path;
            pencil << "solid MIKE666" << endl;

        }
};

void STL::write(string str) {
	pencil << str;
}

void STL::facet(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) {
	
	Vector3D n= unit( (v2-v1) % (v3-v1) );	

	pencil << "facet normal ";
        pencil << std::scientific;
        pencil << n.x() << " " << n.y() << " " << n.z() << endl;
        pencil << "\touter loop\n";
        pencil << "\t\tvertex " << v1.x() << " " << v1.y() << " " << v1.z() << endl;
        pencil << "\t\tvertex " << v2.x() << " " << v2.y() << " " << v2.z() << endl;
        pencil << "\t\tvertex " << v3.x() << " " << v3.y() << " " << v3.z() << endl;
        pencil << "\tendloop\n";
        pencil << "endfacet\n";
}
void STL::closeSTL() {
	
	pencil << "endsolid MIKE666\n";
        pencil.close();
}

