#include<windows.h>
#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<bits/stdc++.h>

using namespace std ;

int vertices[20][3], vertexCount = 0 ;

void setPixel(GLint x, GLint y)
{
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();
}

void setPolygonColor(double red, double green, double blue)
{
    glColor3f(red, green, blue);
}

void drawLine(int x1, int y1, int x2, int y2)
{
    glPointSize(2);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void translate(int translateX, int translateY)
{
    int translationMatrix[3][3] = {{1, 0, translateX}, {0, 1, translateY}, {0, 0, 1}};
    int newCoords[3] = {};
    for(int i = 0; i < vertexCount; i++)
    {
        newCoords[0] = translationMatrix[0][0] * vertices[i][0] + translationMatrix[0][1] * vertices[i][1] + translationMatrix[0][2] * vertices[i][2];
        newCoords[1] = translationMatrix[1][0] * vertices[i][0] + translationMatrix[1][1] * vertices[i][1] + translationMatrix[1][2] * vertices[i][2];
        newCoords[2] = translationMatrix[2][0] * vertices[i][0] + translationMatrix[2][1] * vertices[i][1] + translationMatrix[2][2] * vertices[i][2];
        vertices[i][0] = newCoords[0];
        vertices[i][1] = newCoords[1];
        vertices[i][2] = newCoords[2];
    }
    for(int i = 0; i < vertexCount; i++)
    {
        int nextVertex = (i + 1) % vertexCount;
        setPolygonColor(1, 1, 0);
        drawLine(vertices[i][0], vertices[i][1], vertices[nextVertex][0], vertices[nextVertex][1]);
    }
}

void rotate(double angle, int pivotX, int pivotY)
{
    double pi = 3.14159265;
    double radians = (pi / 180.0) * angle;
    double rotationMatrix[3][3] = {{cos(radians), sin(radians), 0}, {-sin(radians), cos(radians), 0},
                                   {-pivotX * cos(radians) + pivotY * sin(radians) + pivotX,
                                   -pivotX * sin(radians) - pivotY * cos(radians) + pivotY, 1}};
    int newCoords[3] = {};
    for(int i = 0; i < vertexCount; i++)
    {
        newCoords[0] = rotationMatrix[0][0] * vertices[i][0] + rotationMatrix[0][1] * vertices[i][1] + rotationMatrix[0][2] * vertices[i][2];
        newCoords[1] = rotationMatrix[1][0] * vertices[i][0] + rotationMatrix[1][1] * vertices[i][1] + rotationMatrix[1][2] * vertices[i][2];
        newCoords[2] = rotationMatrix[2][0] * vertices[i][0] + rotationMatrix[2][1] * vertices[i][1] + rotationMatrix[2][2] * vertices[i][2];
        vertices[i][0] = newCoords[0];
        vertices[i][1] = newCoords[1];
        vertices[i][2] = newCoords[2];
    }
    for(int i = 0; i < vertexCount; i++)
    {
        int nextVertex = (i + 1) % vertexCount;
        setPolygonColor(1, 1, 0);
        drawLine(vertices[i][0], vertices[i][1], vertices[nextVertex][0], vertices[nextVertex][1]);
    }
}

void scale(int scaleX, int scaleY)
{
    int scalingMatrix[3][3] = {{scaleX, 0, 0}, {0, scaleY, 0}, {0, 0, 1}};
    int newCoords[3] = {};
    for(int i = 0; i < vertexCount; i++)
    {
        newCoords[0] = scalingMatrix[0][0] * vertices[i][0] + scalingMatrix[0][1] * vertices[i][1] + scalingMatrix[0][2] * vertices[i][2];
        newCoords[1] = scalingMatrix[1][0] * vertices[i][0] + scalingMatrix[1][1] * vertices[i][1] + scalingMatrix[1][2] * vertices[i][2];
        newCoords[2] = scalingMatrix[2][0] * vertices[i][0] + scalingMatrix[2][1] * vertices[i][1] + scalingMatrix[2][2] * vertices[i][2];
        vertices[i][0] = newCoords[0];
        vertices[i][1] = newCoords[1];
        vertices[i][2] = newCoords[2];
    }
    for(int i = 0; i < vertexCount; i++)
    {
        int nextVertex = (i + 1) % vertexCount;
        setPolygonColor(1, 1, 0);
        drawLine(vertices[i][0], vertices[i][1], vertices[nextVertex][0], vertices[nextVertex][1]);
    }
}

void reflect(char axis)
{
    int reflectionMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    if(axis == 'x' || axis == 'X')
    {
        reflectionMatrix[1][1] = -1;
    }
    else
    {
        reflectionMatrix[0][0] = -1;
    }
    int newCoords[3] = {};
    for(int i = 0; i < vertexCount; i++)
    {
        newCoords[0] = reflectionMatrix[0][0] * vertices[i][0] + reflectionMatrix[0][1] * vertices[i][1] + reflectionMatrix[0][2] * vertices[i][2];
        newCoords[1] = reflectionMatrix[1][0] * vertices[i][0] + reflectionMatrix[1][1] * vertices[i][1] + reflectionMatrix[1][2] * vertices[i][2];
        newCoords[2] = reflectionMatrix[2][0] * vertices[i][0] + reflectionMatrix[2][1] * vertices[i][1] + reflectionMatrix[2][2] * vertices[i][2];
        vertices[i][0] = newCoords[0];
        vertices[i][1] = newCoords[1];
        vertices[i][2] = newCoords[2];
    }
    for(int i = 0; i < vertexCount; i++)
    {
        int nextVertex = (i + 1) % vertexCount;
        setPolygonColor(1, 1, 0);
        drawLine(vertices[i][0], vertices[i][1], vertices[nextVertex][0], vertices[nextVertex][1]);
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350, 350, -350, 350);
}

void menu(int option)
{
    for(int i = 0; i < vertexCount; i++)
    {
        int nextVertex = (i + 1) % vertexCount;
        setPolygonColor(1, 1, 1);
        drawLine(vertices[i][0], vertices[i][1], vertices[nextVertex][0], vertices[nextVertex][1]);
    }
    glFlush();

    switch(option)
    {
        case 1:
            for(int i = 0; i < vertexCount; i++)
            {
                cout << vertices[i][0] << "  " << vertices[i][1] << endl;
            }
            break;
        case 2:
        {
            int translateX = 0, translateY = 0;
            cout << "Enter x-translation factor: ";
            cin >> translateX;
            cout << "Enter y-translation factor: ";
            cin >> translateY;
            translate(translateX, translateY);
            break;
        }
        case 3:
        {
            double rotationAngle;
            int isClockwise = 1, pivotX, pivotY;
            cout << "Enter the arbitrary point x: ";
            cin >> pivotX;
            cout << "Enter the arbitrary point y: ";
            cin >> pivotY;
            cout << "Enter the rotation angle: ";
            cin >> rotationAngle;
            cout << "Rotate clockwise (1 for yes, 0 for no): ";
            cin >> isClockwise;
            if(isClockwise == 1)
            {
                rotate(-rotationAngle, pivotX, pivotY);
            }
            else
            {
                rotate(rotationAngle, pivotX, pivotY);
            }
            break;
        }
        case 4:
        {
            int scaleX, scaleY;
            cout << "Enter the x scaling factor: ";
            cin >> scaleX;
            cout << "Enter the y scaling factor: ";
            cin >> scaleY;
            scale(scaleX, scaleY);
            break;
        }
        case 5:
        {
            char reflectionAxis;
            cout << "Reflect along which axis (x or y)? ";
            cin >> reflectionAxis;
            reflect(reflectionAxis);
            break;
        }
        default:
            break;
    }
}

void display()
{
    glPointSize(2);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < vertexCount; i++)
    {
        glVertex2i(vertices[i][0], vertices[i][1]);
    }
    glVertex2i(vertices[0][0], vertices[0][1]);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    int option = 1;
    cout << "Enter the number of vertices of the polygon: ";
    cin >> vertexCount;
    for(int i = 0; i < vertexCount; i++)
    {
        cout << "Enter vertex x-coordinate: ";
        cin >> vertices[i][0];
        cout << "Enter vertex y-coordinate: ";
        cin >> vertices[i][1];
        vertices[i][2] = 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Coordinates of the polygon", 1);
    glutAddMenuEntry("Translation", 2);
    glutAddMenuEntry("Rotation", 3);
    glutAddMenuEntry("Scaling", 4);
    glutAddMenuEntry("Reflection", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}

/*
Enter the number of vertices of the polygon: 4
Enter vertex x-coordinate: 50
Enter vertex y-coordinate: 100
Enter vertex x-coordinate: 150
Enter vertex y-coordinate: 100
Enter vertex x-coordinate: 150
Enter vertex y-coordinate: 200
Enter vertex x-coordinate: 50
Enter vertex y-coordinate: 200
Enter x-translation factor: 30
Enter y-translation factor: 30
Enter the arbitrary point x: 0
Enter the arbitrary point y: 0
Enter the rotation angle: 50
Rotate clockwise (1 for yes, 0 for no): 1
Enter the x scaling factor: 2
Enter the y scaling factor: 1
Reflect along which axis (x or y)? x
*/
