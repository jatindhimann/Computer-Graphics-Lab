#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

class Point {
public:
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class Line {
public:
    void drawSimpleDDA(Point startPoint, Point endPoint);
    void drawBresenham(Point startPoint, Point endPoint);
    void drawMidpoint(Point startPoint, Point endPoint);
    void drawDottedDDA(Point startPoint, Point endPoint);
    void dashedDDA(Point startPoint, Point endPoint);

private:
    void drawPixel(int x, int y);
};

// Global variables
int windowWidth = 800;
int windowHeight = 600;
int selectedAlgorithm = 1;
Line lineDrawer;

void ClearScreen();
void DisplayText(string text, int x, int y, int font);

vector<Point> clickedPoints;

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
                    lineDrawer.drawSimpleDDA(startPoint, endPoint);
                    DisplayText("SIMPLE_DDA_LINE", 50, windowHeight - 50, 3);
                    break;
                case 2:
                    lineDrawer.drawBresenham(startPoint, endPoint);
                    DisplayText("BRESENHAM_LINE", 50, windowHeight - 50, 3);
                    break;
                case 3:
                    break;
                case 4:
                    lineDrawer.drawDottedDDA(startPoint, endPoint);
                    DisplayText("Dotted DDA", 50, windowHeight - 50, 3);
                    break;
                case 5:
                    lineDrawer.dashedDDA(startPoint, endPoint);
                    DisplayText("Dashed DDA", 50, windowHeight - 50, 3);
                    break;
            }
        }

        glFlush();
        clickedPoints.clear();
    }
}


void ClearScreen() {
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.5, 0);
    clickedPoints.clear();
    glFlush();
}

void Initialize() {
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("LINE DRAWING ALGORITHMS");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    ClearScreen();
    glFlush();
}

void Display(){}

// Display text on the screen
void DisplayText(string text, int x, int y, int font) {
    glColor3f(0, 1, 0); // Green color for text
    glRasterPos2f(x, y);
    size_t len = text.length();
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)text[i]);

    glColor3f(1, 0.5, 0); // Orange color for future drawing
}

// Implement the drawPixel function
void Line::drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Implement the Simple DDA line drawing algorithm
void Line::drawSimpleDDA(Point startPoint, Point endPoint) {
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

void Line::drawDottedDDA(Point startPoint, Point endPoint) {
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
        if(i % 10 == 0)
        {
            drawPixel(round(x), round(y));
        }
    }
}

void Line::dashedDDA(Point startPoint, Point endPoint) {
    int deltaX = endPoint.x - startPoint.x;
    int deltaY = endPoint.y - startPoint.y;

    float steps = max(abs(deltaX), abs(deltaY));
    float xIncrement = deltaX / steps;
    float yIncrement = deltaY / steps;

    float x = startPoint.x;
    float y = startPoint.y;
    int count = 0;
    drawPixel(round(x), round(y));

    for (int i = 1; i <= steps; i++) {
        x += xIncrement;
        y += yIncrement;

        if(count < 5){
            drawPixel(round(x), round(y));
        }

        if(count == 10){
            count = 0;
        }
        count++;
    }
}

void Line::drawBresenham(Point startPoint, Point endPoint) {
	int dx = endPoint.x-startPoint.x;
	int dy = endPoint.y-startPoint.y;
	int pk = 2*dy-dx;
	int pi = pk;
	int xi = startPoint.x,yi=startPoint.y;

	while(xi<=endPoint.x&&yi<=endPoint.y) {
			drawPixel(xi,yi);
    		if(pi<0) {
    			pi = pk + 2*dy;
    			xi = xi+1;
    			yi = yi;
    		}
    		else {
    			pi = pk + 2*(dy-dx);
    			xi = xi+1;
    			yi = yi+1;
    		}
	}
}

// Main function with a menu
int main(int argc, char **argv) {
    cout << "****************[MENU]***************\n" << endl;
    cout << "1. DDA Line Algorithm\n";
    cout << "2. Bresenham Line Algorithm\n";
    cout << "3. Midpoint Line Algorithm\n";
    cout<< "4. Dotted DDA Algorithm\n";
    cout<< "5. Dashed DDA Algorithm\n";
    cout << "6. Exit\n";

    int userChoice;
    do {
        cout << "\nEnter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                selectedAlgorithm = userChoice;
                glutInit(&argc, argv);
                Initialize();
                glutDisplayFunc(Display);
                glutMouseFunc(HandleMouseClick);
                glutMainLoop();
                break;
            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please choose again." << endl;
                break;
        }
    } while (userChoice != 4);

    return 0;
}
