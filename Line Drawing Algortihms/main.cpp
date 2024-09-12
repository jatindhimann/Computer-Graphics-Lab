#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class Point {
public:
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

int windowHeight = 480;
int selectedAlgorithm = 1;

vector<Point> clickedPoints;

void DisplayText(string text, int x, int y, int fontSize) {
    glRasterPos2i(x, y);
    for (char &c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawSimpleDDA(Point startPoint, Point endPoint) {
    int deltaX = endPoint.x - startPoint.x;
    int deltaY = endPoint.y - startPoint.y;

    float steps = max(abs(deltaX), abs(deltaY));
    float xIncrement = deltaX / steps;
    float yIncrement = deltaY / steps;

    float x = startPoint.x;
    float y = startPoint.y;

    drawPixel(round(x), round(y));

    for (int i = 1; i <= steps; i++) {
        x += xIncrement;
        y += yIncrement;
        drawPixel(round(x), round(y));
    }
}

void drawDottedDDA(Point startPoint, Point endPoint) {
    int deltaX = endPoint.x - startPoint.x;
    int deltaY = endPoint.y - startPoint.y;

    float steps = max(abs(deltaX), abs(deltaY));
    float xIncrement = deltaX / steps;
    float yIncrement = deltaY / steps;

    float x = startPoint.x;
    float y = startPoint.y;

    drawPixel(round(x), round(y));

    for (int i = 1; i <= steps; i++) {
        x += xIncrement;
        y += yIncrement;
        if (i % 10 == 0) {
            drawPixel(round(x), round(y));
        }
    }
}

void dashedDDA(Point startPoint, Point endPoint) {
    int deltaX = endPoint.x - startPoint.x;
    int deltaY = endPoint.y - startPoint.y;

    float steps = max(abs(deltaX), abs(deltaY));
    float xIncrement = deltaX / steps;
    float yIncrement = deltaY / steps;

    float x = startPoint.x;
    float y = startPoint.y;
    int count = 0;

    for (int i = 1; i <= steps; i++) {
        x += xIncrement;
        y += yIncrement;

        if (count < 5) {
            drawPixel(round(x), round(y));
        }

        count++;
        if (count == 10) {
            count = 0;
        }
    }
}

void drawBresenham(Point startPoint, Point endPoint) {
    int dx = endPoint.x - startPoint.x;
    int dy = endPoint.y - startPoint.y;
    int pk = 2 * dy - dx;
    int pi = pk;
    int xi = startPoint.x, yi = startPoint.y;

    while (xi <= endPoint.x && yi <= endPoint.y) {
        drawPixel(xi, yi);
        if (pi < 0) {
            pi = pk + 2 * dy;
            xi = xi + 1;
            yi = yi;
        } else {
            pi = pk + 2 * (dy - dx);
            xi = xi + 1;
            yi = yi + 1;
        }
    }
}

void HandleMouseClick(int button, int state, int x, int y) {
    y = -y + windowHeight;

    if (state == GLUT_UP) return;

    if (clickedPoints.size() % 2 == 0)
        clickedPoints.push_back(Point(x, y));
    else {
        clickedPoints.push_back(Point(x, y));

        stringstream ss;
        ss << "(" << clickedPoints[0].x << "," << clickedPoints[0].y << ")";
        string text = ss.str();
        DisplayText(text, clickedPoints[0].x - 10, clickedPoints[0].y - 10, 2);

        ss.str("");
        ss << "(" << clickedPoints[1].x << "," << clickedPoints[1].y << ")";
        text = ss.str();
        DisplayText(text, clickedPoints[1].x + 10, clickedPoints[1].y + 10, 2);

        Point startPoint = clickedPoints[0];
        Point endPoint = clickedPoints[1];

        if (button == GLUT_LEFT_BUTTON) {
            switch (selectedAlgorithm) {
                case 1:
                    drawSimpleDDA(startPoint, endPoint);
                    DisplayText("SIMPLE_DDA_LINE", 50, windowHeight - 50, 3);
                    break;
                case 2:
                    drawBresenham(startPoint, endPoint);
                    DisplayText("BRESENHAM_LINE", 50, windowHeight - 50, 3);
                    break;
                case 3:
                    drawDottedDDA(startPoint, endPoint);
                    DisplayText("Dotted", 50, windowHeight - 50, 3);
                    break;
                case 4:
                    dashedDDA(startPoint, endPoint);
                    DisplayText("Dashed", 50, windowHeight - 50, 3);
                    break;
            }
        }

        glFlush();
        clickedPoints.clear();
    }
}

void menu(int option) {
    selectedAlgorithm = option;
    glutPostRedisplay();
}

void createMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("DDA", 1);
    glutAddMenuEntry("Bresenham", 2);
    glutAddMenuEntry("Dotted", 3);
    glutAddMenuEntry("Dashed", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Line and Circle Drawing Algorithms");

    init();
    createMenu();
    glutDisplayFunc(display);
    glutMouseFunc(HandleMouseClick);

    glutMainLoop();
    return 0;
}
