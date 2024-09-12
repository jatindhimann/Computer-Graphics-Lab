// Creating a Window - Basic Setup of an OpenGL Program
#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

void MyInit()
{
    glClearColor(0, 0, 0, 1); // Background Color

    glColor3f(1, 0, 0); // Drawing Color
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT); // glClearColor

    // Increase Point Size Default its 1 for visibility
    glPointSize(10); // width - 10 pixel

    glBegin(GL_POINTS); // Grouping Point as a Single Object Entity
        glVertex2i(0,0); // Drawing a Point at Coordinate(0,0)
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

    // Create Window with a Title
    glutCreateWindow("My Window");

    MyInit();

    glutDisplayFunc(Draw);

    glutMainLoop();

    return 0;
}
