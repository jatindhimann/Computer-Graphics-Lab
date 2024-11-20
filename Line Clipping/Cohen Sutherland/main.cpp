#include <iostream>
#include <vector>
#include <GL/glut.h>

const int RIGHT = 8;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 1;

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

struct Line {
    double x0, y0, x1, y1;
};
std::vector<Line> originalLines;
std::vector<Line> clippedLines;

int clickCount = 0;
double tempX0, tempY0;

// Compute region code for a point
int ComputeOutCode(double x, double y) {
    int code = 0;
    if (y > ymax) code |= TOP;
    else if (y < ymin) code |= BOTTOM;
    if (x > xmax) code |= RIGHT;
    else if (x < xmin) code |= LEFT;
    return code;
}

void CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1) {
    int outcode0 = ComputeOutCode(x0, y0);
    int outcode1 = ComputeOutCode(x1, y1);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) {
            // Line is completely inside
            accept = true;
            break;
        } else if (outcode0 & outcode1) {
            // Line is completely outside
            break;
        } else {
            double x, y;
            int outcodeOut = outcode0 ? outcode0 : outcode1;

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
        double sx = (xvmax - xvmin) / (xmax - xmin);
        double sy = (yvmax - yvmin) / (ymax - ymin);
        double vx0 = xvmin + (x0 - xmin) * sx;
        double vy0 = yvmin + (y0 - ymin) * sy;
        double vx1 = xvmin + (x1 - xmin) * sx;
        double vy1 = yvmin + (y1 - ymin) * sy;

        // Store the clipped line
        clippedLines.push_back({vx0, vy0, vx1, vy1});
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping rectangle
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Draw the viewport rectangle
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xvmin, yvmin);
    glVertex2f(xvmax, yvmin);
    glVertex2f(xvmax, yvmax);
    glVertex2f(xvmin, yvmax);
    glEnd();

    // Draw all original lines
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (const auto& line : originalLines) {
        glVertex2d(line.x0, line.y0);
        glVertex2d(line.x1, line.y1);
    }
    glEnd();

    // Draw all clipped lines
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    for (const auto& line : clippedLines) {
        glVertex2d(line.x0, line.y0);
        glVertex2d(line.x1, line.y1);
    }
    glEnd();

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clickCount == 0) {
            tempX0 = x;
            tempY0 = 500 - y;
            clickCount = 1;
        } else if (clickCount == 1) {
            double x1 = x;
            double y1 = 500 - y;
            originalLines.push_back({tempX0, tempY0, x1, y1});

            // Immediately clip and add to clippedLines
            CohenSutherlandLineClipAndDraw(tempX0, tempY0, x1, y1);

            clickCount = 0;
            glutPostRedisplay();
        }
    }
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
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    myinit();
    glutMainLoop();
    return 0;
}
