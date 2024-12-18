#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159265359

// Define a Point class for 2D points
class Point {
public:
    float x, y;

    Point(float x = 0, float y = 0) : x(x), y(y) {}

    // Operator overloading for translation
    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    // Operator overloading for translation in the opposite direction
    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    // Operator overloading for scaling
    Point operator*(float scale) const {
        return Point(x * scale, y * scale);
    }
};

// Define a Shape class to hold vertices and apply transformations
class Shape {
public:
    Point vertices[4];
    Point center;

    Shape() {
        // Define a square as the initial shape
        vertices[0] = Point(-0.5, -0.5);
        vertices[1] = Point(0.5, -0.5);
        vertices[2] = Point(0.5, 0.5);
        vertices[3] = Point(-0.5, 0.5);
        calculateCenter();
    }

    // Calculate the center of the shape
    void calculateCenter() {
        center.x = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4.0;
        center.y = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4.0;
    }

    // Apply translation using operator overloading
    void translate(const Point& translation) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = vertices[i] + translation;
        }
        calculateCenter(); // Update center after translation
    }

    // Apply scaling using operator overloading
    void scale(float scale) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = (vertices[i] - center) * scale + center;
        }
    }

    // Apply rotation around the center of the shape
    // void rotate(float angle) {
    //     float rad = angle * PI / 180.0;  // Convert angle to radians
    //     float cosA = cos(rad);
    //     float sinA = sin(rad);

    //     for (int i = 0; i < 4; i++) {
    //         // Translate point to origin (relative to center), rotate, then translate back
    //         float x = vertices[i].x - center.x;
    //         float y = vertices[i].y - center.y;

    //         vertices[i].x = x * cosA - y * sinA + center.x;
    //         vertices[i].y = x * sinA + y * cosA + center.y;
    //     }
    // }

    // Function to draw the shape
    void draw() const {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 4; i++) {
            glVertex2f(vertices[i].x, vertices[i].y);
        }
        glEnd();
    }
};

// Initialize the shape
Shape square;

// OpenGL Initialization
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glColor3f(1.0, 1.0, 1.0);         // White shape
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

// Display function to render the shape
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    square.draw();
    glFlush();
}

// Keyboard control for transformations
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 't':  // Translate right
            square.translate(Point(0.1, 0.0));
            break;
        case 'T':  // Translate left
            square.translate(Point(-0.1, 0.0));
            break;
        case 's':  // Scale up
            square.scale(1.1);
            break;
        case 'S':  // Scale down
            square.scale(0.9);
            break;
        // case 'r':  // Rotate clockwise
        //     square.rotate(-10);
        //     break;
        // case 'R':  // Rotate counter-clockwise
        //     square.rotate(10);
        //     break;
    }
    glutPostRedisplay();  // Redraw the screen
}

// Main function to set up OpenGL and run the program
int main(int argc, char** argv) {
    cout << "Use the keys to transform the shape:" << endl;
    cout << "t for translating right, T for left." << endl;
    cout << "s to scale up, S to scale down." << endl;
   // cout << "r to rotate clockwise, R to rotate counter-clockwise." << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Transformations with Operator Overloading");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
