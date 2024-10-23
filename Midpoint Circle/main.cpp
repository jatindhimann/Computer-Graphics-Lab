#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int pntX1, pntY1, r1;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x + pntX1, y + pntY1);
    glEnd();
}

void midPointCircleAlgo(int r) {
    int x = 0;
    int y = r;
    float p = 1 - r;

    while (x <= y) {
        plot(x, y);
        plot(y, x);
        plot(-x, y);
        plot(-y, x);
        plot(-x, -y);
        plot(-y, -x);
        plot(x, -y);
        plot(y, -x);

        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    midPointCircleAlgo(r1);
    glFlush();
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char** argv) {
    cout << "Enter the coordinates of the center:\n" << endl;
    cout<<"Enter Center of Circle"<<endl;
    cout << " X-coordinate: "; cin >> pntX1;
    cout << " Y-coordinate: "; cin >> pntY1;
    cout << "Enter radius: "; cin >> r1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Circle Drawing with Fill");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
