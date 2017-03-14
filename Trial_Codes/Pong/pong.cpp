//Tutorial : https://noobtuts.com/cpp/2d-pong-game

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <bits/stdc++.h>

int width = 750;
int height = 500;
int interval = 1000/60;

int score_player1 = 0;
int score_player2 = 0;

using namespace std;

void drawText(float x, float y, string text) {
	glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

string int2str(int x) {
	stringstream ss;
	ss << x;
	return ss.str();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
    drawText(width / 2 - 10, height - 15, int2str(score_player1) + ":" + int2str(score_player2)); 
	
	glutSwapBuffers();
}

void update(int value) {
	glutTimerFunc(interval, update, 0);

	glutPostRedisplay();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pong Game");

	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	enable2D(width, height);
	glColor3f(1.0f, 1.0f, 1.0f);

	glutMainLoop();
	return 0;
} 