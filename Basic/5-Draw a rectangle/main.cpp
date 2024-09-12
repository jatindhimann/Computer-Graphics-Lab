#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

void MyInit()
{
    glClearColor(0, 0, 0, 1);

    glColor3f(1, 0, 0);

    gluOrtho2D(0.0, 200.0, 0.0, 200.0); // Projection - IMP
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
        glVertex2f(50, 50);
        glVertex2f(100, 50);
        glVertex2f(100, 150);
        glVertex2f(50, 150);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    // Initialize Glut
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Set Window Position and Size
    glutInitWindowSize(800, 550);
    glutInitWindowPosition(300, 60);

    glutCreateWindow("Rectangle");

    MyInit();

    glutDisplayFunc(Draw);

    glutMainLoop();

    return 0;
}
