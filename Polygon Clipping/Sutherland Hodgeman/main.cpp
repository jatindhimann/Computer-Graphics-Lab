#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;
struct PT {
    float x, y;
};

// Global variables
int n; // Number of vertices
PT p1, p2, p[20], pp[20]; // p1 and p2 represent clipping window corners, p[] stores polygon vertices, pp[] is for intermediate results

// Left clipper
void left() {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].x < p1.x && p[i + 1].x >= p1.x) {
            // Case-1: Outside to inside
            pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p1.x - p[i].x) + p[i].y;
            pp[j].x = p1.x;
            j++;
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].x >= p1.x && p[i + 1].x >= p1.x) {
            // Case-2: Inside to inside
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].x >= p1.x && p[i + 1].x < p1.x) {
            // Case-3: Inside to outside
            pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p1.x - p[i].x) + p[i].y;
            pp[j].x = p1.x;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) {
        p[i] = pp[i];
    }
    p[n] = pp[0];
}

// Right clipper
void right() {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].x > p2.x && p[i + 1].x <= p2.x) {
            pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p2.x - p[i].x) + p[i].y;
            pp[j].x = p2.x;
            j++;
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].x <= p2.x && p[i + 1].x <= p2.x) {
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].x <= p2.x && p[i + 1].x > p2.x) {
            pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p2.x - p[i].x) + p[i].y;
            pp[j].x = p2.x;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) {
        p[i] = pp[i];
    }
    p[n] = pp[0];
}

// Top clipper
void top() {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].y > p2.y && p[i + 1].y <= p2.y) {
            pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p2.y - p[i].y) + p[i].x;
            pp[j].y = p2.y;
            j++;
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].y <= p2.y && p[i + 1].y <= p2.y) {
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].y <= p2.y && p[i + 1].y > p2.y) {
            pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p2.y - p[i].y) + p[i].x;
            pp[j].y = p2.y;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) {
        p[i] = pp[i];
    }
    p[n] = pp[0];
}

// Bottom clipper
void bottom() {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].y < p1.y && p[i + 1].y >= p1.y) {
            pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p1.y - p[i].y) + p[i].x;
            pp[j].y = p1.y;
            j++;
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].y >= p1.y && p[i + 1].y >= p1.y) {
            pp[j] = p[i + 1];
            j++;
        }
        if (p[i].y >= p1.y && p[i + 1].y < p1.y) {
            pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p1.y - p[i].y) + p[i].x;
            pp[j].y = p1.y;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) {
        p[i] = pp[i];
    }
    p[n] = pp[0];
}

// Draw polygon function
void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < n; i++) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(p[i].x, p[i].y);
        glVertex2f(p[(i + 1) % n].x, p[(i + 1) % n].y);
        glEnd();
    }
    glFlush();
}

// Mouse function for clipping
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINE_LOOP);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p1.x, p2.y);
        glEnd();

        left();
        right();
        top();
        bottom();
        drawPolygon();
    }
    glFlush();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();
    drawPolygon();
    glFlush();
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
}

// Main function
int main(int argc, char** argv) {
    cout << "Enter Window Coordinates (two points):\n";
    cout << "Enter P1(x,y):\n";
    cin >> p1.x >> p1.y;
    cout << "Enter P2(x,y):\n";
    cin >> p2.x >> p2.y;

    cout << "Enter the number of vertices: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter V" << i + 1 << "(x,y): ";
        cin >> p[i].x >> p[i].y;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sutherland-Hodgeman Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutMainLoop();

    return 0;
}

/*
Input
Enter Window Coordinates:
Please Enter two Points:
Enter P1(x,y):
200 200
Enter P2(x,y):
400 400
Enter the no. of vertices:3
Enter V1(x1,y1):
100 150
Enter V2(x2,y2):
340 210
Enter V3(x3,y3):
300 380
*/
