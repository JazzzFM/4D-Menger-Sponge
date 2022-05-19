#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Vector3D.cpp"
#include "Matrix3D.cpp"
#include "Vector4D.cpp"
#include "Matrix4D.cpp"
#include "Quaternion.cpp"
#include "Facet.cpp"
#include "Octahedron.cpp"
#include "PlaneQuaternion.cpp"
#include "FacetBox.cpp"
#include "FacetGash.cpp"
#include "Vector3DBox.cpp"
#include "QuaternionBox.cpp"
#include "QuaternionBoxBox.cpp"
#include "Dodecahedron.cpp"
#include "STL.cpp"
#include "Hypercube.cpp"

//////////////////////////////////////
//                                  
//                                  
//        VARIABLES GLOBALES PARA EL TECLADO        
//                                  
//                                  
//////////////////////////////////////

/*variables*/ 
int ciclo = 0;
int cicloSegund = 0;
int color = 0;
double count = 0.25 * M_PI;
double angle = 0.0;
double count2 = 0.25 * 3.14159265358979;
double count3 = 0.25 * M_PI;
double rotSpeed = 0.0;
double rotAxe = 0.0;
double rad = 20.0;
double rot = 0.0;
int iter0 = 0;
int iter = 9;
int iter1 = 0;
int iter2 = 0;
int pass00 = 0;
int pass0 = 0;
int pass = 0;
int pass1 = 0;
int pass2 = 0;
int ITT = 35;
int stlP = 8;


//////////////////////////////////////
//                                  
//                                  
//        BASE EUCLIDEANA Y CENTRO        
//                                  
//                                  
//////////////////////////////////////



Vector3D origen = Vector3D(0.0, 0.0, 0.0);
Vector3D I = Vector3D(1.0, 0.0, 0.0);
Vector3D J = Vector3D(0.0, 1.0, 0.0);
Vector3D K = Vector3D(0.0, 0.0, 1.0);
int faces[1440][5];


//////////////////////////////////////
//                                  
//                                  
//        FUNCIONES PARA DIBUJAR OBJETOS EN OPENGL        
//                                  
//                                  
//////////////////////////////////////



Vector3D piecewise(double t, const Vector3D& a, const Vector3D& b);
void drawLine(const Vector3D& a, const Vector3D& b);
void drawFacet(const Facet& f, int R, int G, int B);
void drawFacet2(const Vector3D& a, const Vector3D& b, const Vector3D& c, int R, int G, int B);
void drawOctahedron(const Octahedron& octa, int R, int G, int B);
void drawPlaneQuaternion(const PlaneQuaternion& plane, int R, int G, int B);
void drawFacetBox(const FacetBox& box, int R, int G, int B);
void drawFacetBoxSTL(const FacetBox& box, string fname);
void drawFacetGash(FacetGash gash, int R, int G, int B);



void drawHypercube(int p, const Hypercube& cube) {
	
		p = p%9;
	        if (p == 0) drawFacetBox(cube[0], 255,   0,   0);
                if (p == 1) drawFacetBox(cube[1],   0, 255,   0);
                if (p == 2) drawFacetBox(cube[2],   0,   0, 255);
                if (p == 3) drawFacetBox(cube[3], 255, 255,   0);
                if (p == 4) drawFacetBox(cube[4], 255,   0, 255);
                if (p == 5) drawFacetBox(cube[5],   0, 255, 255);
                if (p == 6) drawFacetBox(cube[6], 255,   0, 255);
                if (p == 7) drawFacetBox(cube[7], 255,   0,   0);
		if (p == 8) {
			drawFacetBox(cube[0], 255,   0,   0);
                	drawFacetBox(cube[1],   0, 255,   0);
                	drawFacetBox(cube[2],   0,   0, 255);
                	drawFacetBox(cube[3], 255, 255,   0);
                	drawFacetBox(cube[4], 255,   0, 255);
                	drawFacetBox(cube[5],   0, 255, 255);
                	drawFacetBox(cube[6], 255,   0, 255);
                	//drawFacetBox(cube[7], 255,   0,   0);
		}
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


void drawLattice(int p, int n, int ternary, double Rs, const Matrix4D& M) {
	
	p %= n;	
	double ds = Rs/(double) n;
	double rs = 0.5 * ds;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				for (int l = p; l < p+1; l++) {
				
					int ttt = ternaryCat(i, j, k, l);
					if (ttt == ternary) {			
						Vector4D a0 = Vector4D(i * ds, j * ds, k * ds, l * ds);
						a0 = a0 - 0.5*(n-1) * Vector4D(ds, ds, ds, ds);
						Hypercube cube = Hypercube(rs, a0, M, 1.75 * Rs);
						drawHypercube(8, cube);
						//cube.empty();
					}
				}
}


//////////////////////////////////////
//
//
//        PIPELINE RENDERIZAR
//
//	  *Setup() := lo puedes ocupar como una función que ejecuta una sola vez (en el primer frame) dentro del render
//	  *Update() := Se puede utilizar para actualizar algún objeto
//	  *Draw() := lo puedes ocupar para todo y también dibujar solo que con cuidado por que se ejecuta en cada frame
//
//
//////////////////////////////////////



/*Funciones para dibujar sin pensar en OpenGL*/
void Setup();
void Draw();
void updateProcessingProto();
void ProcessingProto();
void interface();

//////////////////////////////////////
//                                  
//                                  
//        La variable ciclo es el número de FRAMES que lleva el sistema
//        Inicia con 0        
//                                  
//                                  
//////////////////////////////////////


void Setup() {

	if (ciclo == 0) {
	
	}

}


void updateProcessingProto() {

	if (ciclo > 0) {

	}
}

///////////////////     DRAW       ///////////////////////
void Draw() {

	if (ciclo > 0) {
	
		Matrix4D M = Matrix4D(
        	                                1, 0, 0, 0,
        	                                0, 1, 0, 0,
        	                                0, 0, cos(angle),-sin(angle),
        	                                0, 0, sin(angle), cos(angle)
        	                                );
		double radioDeLatice = 10;
		double layers = iter;
		double compliment = 0;
		drawLattice(stlP, layers, compliment, radioDeLatice, M);
	
	}
}


void ProcessingProto() {

	Setup();
	updateProcessingProto();
	Draw();
}









Vector3D piecewise(double t, const Vector3D& a, const Vector3D& b) {

        return (t*(a-b)) + b;
}

void drawLine(const Vector3D& a, const Vector3D& b) {

        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
        glEnd();
}

void drawFacet(const Facet& f, int R, int G, int B) {

        Vector3D n = f[3];
        Vector3D a = f[0];
        Vector3D b = f[1];
        Vector3D c = f[2];
	
	glColor4f(R, G, B, 0.75 );
	glBegin(GL_TRIANGLES);
        glNormal3f( n.x(), n.y(), n.z());
        glVertex3f( a.x(), a.y(), a.z());
        glVertex3f( b.x(), b.y(), b.z());
        glVertex3f( c.x(), c.y(), c.z());
        glEnd();

	drawLine(a, b);
	drawLine(b, c);
}

void drawFacet2(const Vector3D& a, const Vector3D& b, const Vector3D& c, int R, int G, int B) {

        Vector3D n = unit( (b-a) % (c-a));
        glColor3ub(R, G, B);
        glBegin(GL_TRIANGLES);
        glNormal3f( n.x(), n.y(), n.z());
        glVertex3f( a.x(), a.y(), a.z());
        glVertex3f( b.x(), b.y(), b.z());
        glVertex3f( c.x(), c.y(), c.z());
        glEnd();
}

void drawOctahedron(const Octahedron& octa, int R, int G, int B) {

        for (int i = 0; i < 8; i++)
                drawFacet(octa[i], R, G, B);
}

void drawPlaneQuaternion(const PlaneQuaternion& plane, int R, int G, int B) {

        double l = abs(plane[2]-plane[3]);
        drawOctahedron(Octahedron(0.05 * l, plane[0]), R, G, B);
        drawLine(plane[0], plane[1]);
        drawFacet2(piecewise(2.0, plane[2], plane[1]), piecewise(2.0, plane[3], plane[1]), piecewise(2.0, plane[4], plane[1]), R, G, B);
        drawFacet2(piecewise(2.0, plane[4], plane[1]), piecewise(2.0, plane[5], plane[1]), piecewise(2.0, plane[2], plane[1]), R, G, B);
}

void drawFacetBox(const FacetBox& box, int R, int G, int B) {


        if (box.getN() != 0)
                for (int i = 0; i < box.getN(); i++) {
                        drawFacet(box[i], R, G, B);
                }
}

void drawFacetBoxSTL(const FacetBox& box, string fname) {

        STL stl = STL(fname);

        if (box.getN() != 0)
                for (int i = 0; i < box.getN(); i++) {
                        stl.facet(box[i][0], box[i][1], box[i][2]);
                }
        stl.closeSTL();
}

void drawFacetGash(FacetGash gash, int R, int G, int B) {

        drawPlaneQuaternion(gash.getBlade(), 50, 100, 255);
        //drawFacetBox(gash.getFacets(), R, G, B);

        for (int i = 0; i < gash.getMM().getM(); i++)
                for (int j = 0; j < gash.getMM()[i].getN(); j++)
                        drawOctahedron(Octahedron(0.1, gash.getMM()[i][j]), 255, 0, 0);


}






/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/

//////////////////////////////////////
//                                  //
//                                  //
//       OPENGL AS BACKGROUND       //
//                                  //
//                                  //
//////////////////////////////////////

/*Posición y color de luz*/
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {20.0, 20.0, 20.25, 0.0};

/*Funciones de OpenGL*/
void display(void);
void init(double theta);
void TimerFunction(int value);
void keyboard(unsigned char key, int x, int y);
void ProcessMenu(int value);

int main(int argc, char **argv)
{
  
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(720, 720);
	glutCreateWindow(" JAZ 4D	U.U ");
	ProcessMenu(1);
	init(count);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(20, TimerFunction, 1);

	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}

void display(void) {
  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	ProcessingProto();
	glutSwapBuffers();
}

void init(double theta)
{
  /* Setup data. */
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 0.25f };

  /* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
  	//glEnable(GL_CULL_FACE);

  /*Enable color tracking*/
	glEnable(GL_COLOR_MATERIAL);

  /* Set material properties to follow glColor values*/
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  /*All materials have high shine*/
	glMaterialfv(GL_FRONT, GL_AMBIENT, specref);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, specref);
	
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	

  /* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 50.0,
			/* aspect ratio */ 1.0,
			/* Z near */ 0.5, 
			/* Z far */ 10000.0);
	glMatrixMode(GL_MODELVIEW);
  /* Adjust Board position to be asthetic angle. */
  //glTranslatef(0.0, 0.15, -0.0);
	glRotatef(90, 0.0, 0.0, 1.0);

	glEnable(GL_NORMALIZE);
}

void TimerFunction(int value) {

	count += 0.0;
	rotSpeed += 0.00;
	ciclo += 1;
	angle += 0.1;

	if (count > 2 * M_PI) count = 0;
	if (ciclo > 100) ciclo = 1; //CICLO NUNCA ES CERO JAJAJA
	if (angle > 2 * M_PI) angle = 0;
	
	glLoadIdentity();



	///////////////////////////////
	//
	//
	//	CAMERA CONTROL
	//
	//
	//////////////////////////////


	gluLookAt( 
		rad * cos(count)*sin(count2), rad * sin(count) * sin(count2), rad * cos(count2),      	/* eye is at (0,0,5) */
              	0.0, 0.0, 1.0,      									/* center is at (0,0,0) */
              	0.0, 0.0, 1.0);      									/* up is in positive Y direction */

	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);
}

void keyboard(unsigned char key, int x, int y) {
	GLint params[2];

	switch (key) {

		case 'b': 
			rotSpeed += 0.05;
      		break;

    		
		case 'B':
      			rotSpeed -= 0.05;
      		break;

    
		case 'C':
      			count3 += 0.05;
      		break;

    		
		case 'c':
      			count3 -= 0.05;
      		break;

    		
		case 'E':
      			count2 += 0.05;
      		break;

    
		case 'e':
      			count2 -= 0.05;
      		break;

    
		case 'r':
      			count += 0.05;
      		break;

    		
		case 'R':
      			count -= 0.05;
      		break;


    		case 'm':
			rotAxe += 0.05;
      		break;

    		
		case 'M':
      			rotAxe -= 0.05;
      		break;

    		
		case 'f':
      			rad += 0.2;
      		break;

    
		case 'F':
      			rad -= 0.2;
      		break;

    
		case 'v':
      			rot += 0.02;
      		break;

    
		case 'V':
      			rot -= 0.02;
      		break;

     
		case 'p':
      			stlP += 1;
		break;

		case 'P':
                        stlP -= 1;
                break;

		case 'i':
                        iter = 9;
                break;

                case 'I':
                        iter = 27;
                break;

	}

	glutPostRedisplay();
}

void ProcessMenu(int value) {
	switch(value) {
    		case 1:
      			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      			glEnable(GL_BLEND);
      			glEnable(GL_POINT_SMOOTH);
      			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
      			glEnable(GL_LINE_SMOOTH);
      			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
      			glEnable(GL_POLYGON_SMOOTH);
      			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
      		break;

    		case 2:
      			glDisable(GL_BLEND);
      			glDisable(GL_LINE_SMOOTH);
      			glDisable(GL_POINT_SMOOTH);
      			glDisable(GL_POLYGON_SMOOTH);
      		break;
    
    		default:
      		break;
  	}

	glutPostRedisplay();
}
