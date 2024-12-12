#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
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
    vector<Point> vertices;
    Point center;

    // Constructor to initialize a regular polygon with a specified number of sides
    Shape(int sides) {
        if (sides < 3) sides = 3; // Minimum of 3 sides for a polygon
        vertices.resize(sides);
        float angleIncrement = 2 * PI / sides;
        
        // Calculate the vertices for a regular polygon
        for (int i = 0; i < sides; i++) {
            float angle = i * angleIncrement;
            vertices[i] = Point(0.5 * cos(angle), 0.5 * sin(angle));
        }
        calculateCenter();
    }

    // Calculate the center of the shape
    void calculateCenter() {
        center.x = 0;
        center.y = 0;
        for (const auto& vertex : vertices) {
            center.x += vertex.x;
            center.y += vertex.y;
        }
        center.x /= vertices.size();
        center.y /= vertices.size();
    }

    // Apply translation using operator overloading
    void translate(const Point& translation) {
        for (auto& vertex : vertices) {
            vertex = vertex + translation;
        }
        calculateCenter(); // Update center after translation
    }

    // Apply scaling using operator overloading
    void scale(float scale) {
        for (auto& vertex : vertices) {
            vertex = (vertex - center) * scale + center;
        }
    }

    // Apply rotation around the center of the shape
    void rotate(float angle) {
        float rad = angle * PI / 180.0;  // Convert angle to radians
        float cosA = cos(rad);
        float sinA = sin(rad);

        for (auto& vertex : vertices) {
            // Translate point to origin (relative to center), rotate, then translate back
            float x = vertex.x - center.x;
            float y = vertex.y - center.y;

            vertex.x = x * cosA - y * sinA + center.x;
            vertex.y = x * sinA + y * cosA + center.y;
        }
    }

    // Function to draw the shape
    void draw() const {
        glBegin(GL_POLYGON);
        for (const auto& vertex : vertices) {
            glVertex2f(vertex.x, vertex.y);
        }
        glEnd();
    }
};

// Initialize the shape
Shape* polygon;

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
    polygon->draw();
    glFlush();
}

// Keyboard control for transformations
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 't':  // Translate right
            polygon->translate(Point(0.1, 0.0));
            break;
        case 'T':  // Translate left
            polygon->translate(Point(-0.1, 0.0));
            break;
        case 's':  // Scale up
            polygon->scale(1.1);
            break;
        case 'S':  // Scale down
            polygon->scale(0.9);
            break;
        case 'r':  // Rotate clockwise
            polygon->rotate(-10);
            break;
        case 'R':  // Rotate counter-clockwise
            polygon->rotate(10);
            break;
    }
    glutPostRedisplay();  // Redraw the screen
}

// Main function to set up OpenGL and run the program
int main(int argc, char** argv) {
    int sides;
    cout << "Enter the number of sides for the polygon (minimum 3): ";
    cin >> sides;

    cout << "Use the keys to transform the shape:" <<endl;
    cout << "t for translating right, T for left." << endl;
    cout << "s to scale up, S to scale down." << endl;
    cout << "r to rotate clockwise, R to rotate counter-clockwise." << endl;

    polygon = new Shape(sides);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Transformations with Operator Overloading");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    delete polygon;
    return 0;
}
