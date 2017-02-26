#include "globalgl.h"
#include "Utils.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;

const int HEIGHT = 600;
const int WIDTH = 600;

const double PI = 3.14;

enum STATES { CLEAR, ANIMATE, DRAW, TIMER };
STATES task;

int legs = 0;

class point {
public:
    point(double a, double b) : x(a), y(b) {}
    double x;
    double y;
};

void drawHexagon(point center, double radius, double angle, int legs) {
	const double ANGLE_INC = 2 * PI / 6;
	double theta = angle;
	glBegin(GL_LINE_STRIP);
	for (int vert = 0; vert <= legs; vert++) {
		glVertex2d(center.x + radius*cos(theta), center.y + radius*sin(theta));
		theta += ANGLE_INC;
	}
	glEnd();
}


void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);  // bg color bright white
	glColor3f(1.0f, 0.0f, 1.0f);
	setWorldWin(-60, 60, -60, 60);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
    switch (task) {
        case TIMER:
        case ANIMATE:
        case DRAW:
            drawHexagon(point(0,0), 50, 0, legs);
            break;
        case CLEAR:
            legs = 0;
            break;
    }
	glFlush();
}

void myIdle() {
    if (task == ANIMATE) {
        delay(100);
        legs = (legs) % 6 + 1;
        glutPostRedisplay();
    }
}

void myTimer(int timernum) {
    cout << "Timer Fired" << endl;
    if (task == TIMER) {
        legs = (legs) % 6 + 1;
        glutPostRedisplay();
    }
	glutTimerFunc(1000,myTimer,0);
}


void myKeyboard(unsigned char key, int mouseX, int mouseY) {
	switch (key) {
	case 't':
        task = TIMER;
		glutPostRedisplay();
        break;
	case 'n':
        task = DRAW;
        legs = (legs) % 6 + 1;
		glutPostRedisplay();
		break;

    case 'a':
        task = ANIMATE;
        break;

    case 'c':
        task = CLEAR;
		glutPostRedisplay();
        break;

	case 27: exit(-1);	      //terminate the program
	default: break;	      // do nothing
	}

}

int main(int argc, char **argv) {
    /* here is the comment */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Hexagon Animation ");
	myInit();
	glutTimerFunc(1000,myTimer,0);		// register the timer function
	glutIdleFunc(myIdle);		// register the redraw function
	glutDisplayFunc(myDisplay);		// register the redraw function
	glutKeyboardFunc(myKeyboard); // register the keyboard action function
	glutMainLoop();			// go into a perpetual loop
}
