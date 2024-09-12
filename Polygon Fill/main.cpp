#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    glLineWidth(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500, 0, 500);
}

struct COLOR
{
    float r, g, b;
};

bool sameColor(COLOR a, COLOR b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

void drawPixel(int x, int y, COLOR c)
{
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

COLOR readColor(int x, int y)
{
    COLOR color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void bound_fill(int x, int y, COLOR fill, COLOR border_col)
{
    COLOR color = readColor(x, y);
    if (!sameColor(color, border_col) && !sameColor(color, fill))
    {
        drawPixel(x, y, fill);
        bound_fill(x + 1, y, fill, border_col);
        bound_fill(x, y + 1, fill, border_col);
        bound_fill(x - 1, y, fill, border_col);
        bound_fill(x, y - 1, fill, border_col);
    }
}

void flood_fill(int x, int y, COLOR fill, COLOR bg_color)
{
    COLOR color = readColor(x, y);
    if (sameColor(color, bg_color))
    {
        drawPixel(x, y, fill);
        flood_fill(x + 1, y, fill, bg_color);
        flood_fill(x, y + 1, fill, bg_color);
        flood_fill(x - 1, y, fill, bg_color);
        flood_fill(x, y - 1, fill, bg_color);
    }
}

int xc = 0, yc = 0;
void menu(int value)
{
    COLOR fill = {0.0, 0.0, 1.0}; // Blue
    COLOR bcol = {1.0, 0.0, 0.0}; // Red
    COLOR back_col = {0.0, 0.0, 0.0}; // Black

    switch(value)
    {
        case 1:
            flood_fill(xc, 500 - yc, fill, back_col);
            break;
        case 2:
            bound_fill(xc, 500 - yc, fill, bcol);
            break;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            static int prevX = -1, prevY = -1;

            if (prevX != -1 && prevY != -1)
            {
                glColor3f(1.0, 0.0, 0.0);
                glBegin(GL_LINES);
                    glVertex2i(prevX, 500 - prevY);
                    glVertex2i(x, 500 - y);
                glEnd();
                glFlush();
            }
            prevX = x;
            prevY = y;
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            xc = x;
            yc = y;
        }
    }
}

void display()
{

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("POLYGON FILL");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("FLOOD FILL", 1);
    glutAddMenuEntry("BOUNDARY FILL", 2);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    myInit();
    glutMainLoop();
    return 0;
}
