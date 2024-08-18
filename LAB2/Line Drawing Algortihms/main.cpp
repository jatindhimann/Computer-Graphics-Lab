#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

class Point {
    int x, y;
};

vector<Point> points; // Stores the clicked points
int lineAlgorithm = 0; // 0 for Simple DDA, 1 for Symmetric DDA, 2 for Bresenham, 3 for Midpoint

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Simple DDA Algorithm
void simpleDDA(Point p1, Point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = max(abs(dx), abs(dy));
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = p1.x;
    float y = p1.y;

    for (int i = 0; i <= steps; i++) {
        drawPixel(x, y);
        x += xInc;
        y += yInc;
    }
}

// Symmetric DDA Algorithm
void symmetricDDA(Point p1, Point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int L = max(abs(dx), abs(dy));

    // Step increments
    float xInc = (float)dx / L;
    float yInc = (float)dy / L;

    // Start point
    float x = p1.x + 0.5 * ((dx > 0) ? 1 : -1);
    float y = p1.y + 0.5 * ((dy > 0) ? 1 : -1);

    for (int i = 0; i <= L; i++) {
        drawPixel(x, y);
        x += xInc;
        y += yInc;
    }
}

// Bresenham's Algorithm
void Bresenham(Point p1, Point p2) {
    int x = p1.x;
    int y = p1.y;
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(x, y);
        if (x == p2.x && y == p2.y) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

// Midpoint Line Algorithm
void Midpoint(Point p1, Point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int d = dy - (dx / 2);
    int x = p1.x, y = p1.y;

    drawPixel(x, y);
    while (x < p2.x) {
        x++;
        if (d < 0) {
            d = d + dy;
        } else {
            d += (dy - dx);
            y++;
        }
        drawPixel(x, y);
    }
}

// Display function to draw the line based on selected algorithm
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (points.size() == 2) {
        if (lineAlgorithm == 0) {
            simpleDDA(points[0], points[1]);
        } else if (lineAlgorithm == 1) {
            symmetricDDA(points[0], points[1]);
        } else if (lineAlgorithm == 2) {
            Bresenham(points[0], points[1]);
        } else if (lineAlgorithm == 3) {
            Midpoint(points[0], points[1]);
        }
        points.clear(); // Clear points after drawing the line
    }

    glFlush();
}

// Mouse function to capture the points on screen
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Point p = {x, 500 - y}; // Adjust y-coordinate for OpenGL
        points.push_back(p);

        if (points.size() == 2) {
            glutPostRedisplay(); // Trigger the display function to draw the line
        }
    }
}

// OpenGL Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// Print Menu for selecting algorithm
void printMenu() {
    cout << "Select Line Drawing Algorithm:\n";
    cout << "1. Simple DDA\n";
    cout << "2. Symmetric DDA\n";
    cout << "3. Bresenham\n";
    cout << "4. Midpoint\n";
    cout << "Enter your choice: ";
}

// Function to capture user's choice of algorithm
void selectAlgorithm() {
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            lineAlgorithm = 0;
            cout << "Simple DDA Algorithm selected.\n";
            break;
        case 2:
            lineAlgorithm = 1;
            cout << "Symmetric DDA Algorithm selected.\n";
            break;
        case 3:
            lineAlgorithm = 2;
            cout << "Bresenham Algorithm selected.\n";
            break;
        case 4:
            lineAlgorithm = 3;
            cout << "Midpoint Algorithm selected.\n";
            break;
        default:
            cout << "Invalid choice! Defaulting to Simple DDA.\n";
            lineAlgorithm = 0;
    }
}

// Main function to set up OpenGL and GLUT
int main(int argc, char** argv) {
    printMenu();
    selectAlgorithm();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Drawing Algorithms");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
