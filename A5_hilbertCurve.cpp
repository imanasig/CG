#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    float x, y;
};

vector<Point> hilbertCurve;

// Helper function to generate the Hilbert Curve
void generateHilbertCurve(int level, float x0, float y0, float xi, float xj, float yi, float yj) {
    if (level <= 0) {
        Point p = {x0 + (xi + yi) / 2, y0 + (xj + yj) / 2};
        hilbertCurve.push_back(p);
        return;
    }

    generateHilbertCurve(level - 1, x0, y0, yi / 2, yj / 2, xi / 2, xj / 2);
    generateHilbertCurve(level - 1, x0 + xi / 2, y0 + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2);
    generateHilbertCurve(level - 1, x0 + xi / 2 + yi / 2, y0 + xj / 2 + yj / 2, xi / 2, xj / 2, yi / 2, yj / 2);
    generateHilbertCurve(level - 1, x0 + xi / 2 + yi, y0 + xj / 2 + yj, -yi / 2, -yj / 2, -xi / 2, -xj / 2);
}

// OpenGL Display Function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for (const auto& point : hilbertCurve) {
        glVertex2f(point.x, point.y);
    }

    glEnd();
    glFlush();
}

// Initialization of OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    int level;
    cout << "Enter the recursion level for the Hilbert Curve (e.g., 1-6): ";
    cin >> level;

    hilbertCurve.clear();
    generateHilbertCurve(level, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Hilbert Curve");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
