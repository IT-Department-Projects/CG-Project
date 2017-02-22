#include "GL/freeglut.h"
#include "GL/gl.h"

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Translation");

	glClearColor(0,0,0,0);	

	glutDisplayFunc(Translate);

	glutMainLoop();

	return 0;
}