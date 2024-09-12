#include <GL/glut.h>
#include <iostream>
#include <cmath>


int xCenter, yCenter, radius;
bool clicked = false;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void circlePlotPoints(int xCenter, int yCenter, int x, int y) {
    setPixel(xCenter + x, yCenter + y);
    setPixel(xCenter - x, yCenter + y);
    setPixel(xCenter + x, yCenter - y);
    setPixel(xCenter - x, yCenter - y);
    setPixel(xCenter + y, yCenter + x);
    setPixel(xCenter - y, yCenter + x);
    setPixel(xCenter + y, yCenter - x);
    setPixel(xCenter - y, yCenter - x);
}

void circleMidpoint(int xCenter, int yCenter, int radius) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    circlePlotPoints(xCenter, yCenter, x, y);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        circlePlotPoints(xCenter, yCenter, x, y);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !clicked) {
        xCenter = x - 250; // Adjusting to window center
        yCenter = 250 - y; // Adjusting to window center
        clicked = true;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clicked) {
        radius = sqrt((x - (xCenter + 250)) * (x - (xCenter + 250)) +
                      (y - (250 - yCenter)) * (y - (250 - yCenter)));
        glutPostRedisplay();
        clicked = false;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (radius > 0) {
        circleMidpoint(xCenter, yCenter, radius);
    }
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
