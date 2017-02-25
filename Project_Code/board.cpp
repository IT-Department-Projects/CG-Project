#include "GL/freeglut.h"
#include "GL/gl.h"

void drawSquare(float x, float y, int color) {

	glBegin(GL_QUADS);
	
	glColor3f(color*1.0, color*1.0, color*1.0);			//Grey Colour
	glVertex3f(x+0.0, 0.0+y, 0.0); 		//Bottom-Left vertex
	glVertex3f(x+0.20, 0.0+y, 0.0);		//Bottom-Right vertex
	glVertex3f(x+0.20, 0.20+y, 0.0);	//Top-Right vertex
	glVertex3f(x+0.0, 0.20+y, 0.0);		//Top-Left vertex

	glEnd();

}

void renderFunction(void) {

	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0,0.0,1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	for(int i=-4; i<4; i++){
		for(int j=-4; j<4; j++){
			drawSquare(0.20*i, 0.20*j, (i+j+8)%2);
		}
	}

	glFlush();
}

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	glutInitWindowSize(600,600);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Chess Game");

	glutDisplayFunc(renderFunction);
	glutMainLoop();



	return 0;
}