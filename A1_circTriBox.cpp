// This is a battern of the Cricle-Equilateral Triangle-Circle all of which is inscribed in an outer Square Box

#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Variables for the outer circle
int centerX, centerY, outerRadius;

// Function to draw a circle using Bresenham's Circle Drawing Algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r; // Decision parameter
    while (x <= y) {
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
        glEnd();

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Function to draw a line using the DDA Algorithm
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

// Function to draw the rectangle
void drawRectangle() {
    int halfWidth = outerRadius;  // Rectangle's width
    int halfHeight = outerRadius; // Rectangle's height

    int left = centerX - halfWidth;
    int right = centerX + halfWidth;
    int top = centerY + halfHeight;
    int bottom = centerY - halfHeight;

    // Draw rectangle
    drawLine(left, top, right, top);
    drawLine(right, top, right, bottom);
    drawLine(right, bottom, left, bottom);
    drawLine(left, bottom, left, top);
}

// Function to draw the equilateral triangle
void drawEquilateralTriangle() {
    // Bottom vertices
    float angle = M_PI / 6; // 30 degrees in radians
    int x1 = centerX - outerRadius * cos(angle);
    int y1 = centerY - outerRadius * sin(angle);

    int x2 = centerX + outerRadius * cos(angle);
    int y2 = centerY - outerRadius * sin(angle);

    // Top vertex
    int x3 = centerX;
    int y3 = centerY + outerRadius;

    // Draw triangle
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the outer circle
    drawCircle(centerX, centerY, outerRadius);

    // Draw the rectangle
    drawRectangle();

    // Draw the equilateral triangle with vertices on the circle
    drawEquilateralTriangle();

    // Draw the smaller circle inside the triangle
    int innerRadius = outerRadius / 2;
    drawCircle(centerX, centerY, innerRadius);

    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0, 0, 0, 1); // Background color: black
    glColor3f(1, 1, 1);       // Drawing color: white
    gluOrtho2D(0, 800, 0, 600);
}

int main(int argc, char** argv) {
    // User input
    cout << "Enter the center coordinates of the circle (x, y): ";
    cin >> centerX >> centerY;

    cout << "Enter the radius of the outer circle: ";
    cin >> outerRadius;

    // Initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Straight-Aligned Triangle and Circles");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
