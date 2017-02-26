#include "globalgl.h"
#include "Utils.h"
#include <fstream>
#include <ctime>

using namespace std;

void setWorldWin(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setViewPort(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom, right - left, top - bottom);
}

// this is a wrapper to nanosleep which sleeps for a certain
// number of milliseconds
#if defined(WIN32)
void delay(int ms) {
    Sleep(ms);
}
#else
void delay(int ms) {
    struct timespec ts;
    ts.tv_sec = ms/1000;
    ts.tv_nsec = 1000000 * (ms%1000);
    nanosleep(&ts,NULL);
}
#endif
