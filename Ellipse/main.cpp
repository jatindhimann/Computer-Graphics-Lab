#include <GL/glut.h>
#include <iostream>
using namespace std;

int rx, ry;
int xCenter, yCenter;

void myinit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ellipseMidPoint() {
    float x = 0;
    float y = ry;
    float p1 = ry * ry - (rx * rx) * ry + (rx * rx) * 0.25;
    float dx = 2 * (ry * ry) * x;
    float dy = 2 * (rx * rx) * y;

    while (dx < dy) {
        setPixel(xCenter + x, yCenter + y);
        setPixel(xCenter - x, yCenter + y);
        setPixel(xCenter + x, yCenter - y);
        setPixel(xCenter - x, yCenter - y);
        if (p1 < 0) {
            x++;
            dx = 2 * (ry * ry) * x;
            p1 = p1 + dx + (ry * ry);
        } else {
            x++;
            y--;
            dx = 2 * (ry * ry) * x;
            dy = 2 * (rx * rx) * y;
            p1 = p1 + dx - dy + (ry * ry);
        }
    }

    float p2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y - 1) * (y - 1) - (rx * rx) * (ry * ry);

    while (y > 0) {
        setPixel(xCenter + x, yCenter + y);
        setPixel(xCenter - x, yCenter + y);
        setPixel(xCenter + x, yCenter - y);
        setPixel(xCenter - x, yCenter - y);
        if (p2 > 0) {
            y--;
            dy = 2 * (rx * rx) * y;
            p2 = p2 - dy + (rx * rx);
        } else {
            x++;
            y--;
            dx = dx + 2 * (ry * ry);
            dy = dy - 2 * (rx * rx);
            p2 = p2 + dx - dy + (rx * rx);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    ellipseMidPoint();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter Center Of Ellipse\n";
    cout << "x = ";
    cin >> xCenter;
    cout << "y = ";
    cin >> yCenter;
    cout << "Enter Semi Major Axis: ";
    cin >> rx;
    cout << "Enter Semi Minor Axis: ";
    cin >> ry;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Midpoint Ellipse Drawing Algorithm");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}
