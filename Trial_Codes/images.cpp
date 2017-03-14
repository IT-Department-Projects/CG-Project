#include "GL/freeglut.h"
#include "GL/gl.h"
#include "SOIL.h"

using namespace std;

int main(int argc, char **argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SOIL Library");
}