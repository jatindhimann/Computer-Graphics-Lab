#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

double PI = 3.14;
double r = 100;    // Default radius
int sides = 10;    // Default number of sides

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    glColor3f(0.0, 0.0, 1.0); // Set color to blue
    glBegin(GL_LINE_LOOP);    // Begin drawing the polygon
    for (int i = 0; i < sides; i++) {
        double angle = i * 2 * PI / sides;
        glVertex2d(400 + r * cos(angle), 300 + r * sin(angle));
    }
    glEnd();

    glFlush(); // Render the drawing
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Set the coordinate system (800x600)
}

int main(int argc, char** argv) {
    // Input for sides and radius
    cout << "Enter the number of sides (use a large number for a circle): ";
    cin >> sides;
    cout << "Enter the radius: ";
    cin >> r;

    if (sides < 3) {
        cout << "Number of sides must be at least 3. Exiting...\n";
        return 1;
    }

    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Single buffer, RGB mode
    glutInitWindowSize(800, 600);          // Window size
    glutCreateWindow("Polygon or Circle"); // Window title

    init();                                // Initialize settings
    glutDisplayFunc(display);              // Register display callback

    glutMainLoop();                        // Enter the GLUT event loop
    return 0;
}
