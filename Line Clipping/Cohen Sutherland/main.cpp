#include <iostream>
#include <GL/glut.h>

const int RIGHT = 8;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 1;

double xmin = 50, ymin = 50, xmax = 100, ymax = 100; // Window boundaries
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300; // Viewport boundaries

// Function to compute the outcode for a point (x, y)
int ComputeOutCode(double x, double y) {
    int code = 0;
    if (y > ymax) code |= TOP;       // above the clip window
    else if (y < ymin) code |= BOTTOM; // below the clip window
    if (x > xmax) code |= RIGHT;     // to the right of clip window
    else if (x < xmin) code |= LEFT; // to the left of clip window
    return code;
}

// Cohen-Sutherland clipping algorithm clips a line from P0=(x0, y0) to P1=(x1, y1)
void CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1) {
    int outcode0 = ComputeOutCode(x0, y0);
    int outcode1 = ComputeOutCode(x1, y1);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) {
            // accept
            accept = true;
            break;
        } else if (outcode0 & outcode1) {
            // reject
            break;
        } else {
            // Line needs to be clipped
            double x, y;
            int outcodeOut = outcode0 ? outcode0 : outcode1;

            // Find the intersection point
            if (outcodeOut & TOP) {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            } else if (outcodeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            } else if (outcodeOut & RIGHT) {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            } else {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            // Replace outside point with the intersection point
            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    }

    if (accept) {
        // Window to viewport mapping
        double sx = (xvmax - xvmin) / (xmax - xmin);
        double sy = (yvmax - yvmin) / (ymax - ymin);
        double vx0 = xvmin + (x0 - xmin) * sx;
        double vy0 = yvmin + (y0 - ymin) * sy;
        double vx1 = xvmin + (x1 - xmin) * sx;
        double vy1 = yvmin + (y1 - ymin) * sy;

        // Draw the viewport
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin, yvmin);
        glVertex2f(xvmax, yvmin);
        glVertex2f(xvmax, yvmax);
        glVertex2f(xvmin, yvmax);
        glEnd();

        // Draw the clipped line
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2d(vx0, vy0);
        glVertex2d(vx1, vy1);
        glEnd();
    }
}

void display() {
    double x0 = 60, y0 = 20, x1 = 80, y1 = 120;

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the original line in red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);
    glEnd();

    // Draw the clipping window in blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Clip and draw the line
    CohenSutherlandLineClipAndDraw(x0, y0, x1, y1);

    glFlush();
}

void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen-Sutherland Line Clipping Algorithm");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
