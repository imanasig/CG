#include <GL/glut.h>
#include <iostream>
#include<cmath>

using namespace std;

// Base class Shape with virtual functions for drawing and moving
class Shape {
public:
    virtual void draw() = 0;
    virtual void move(float dx, float dy) = 0;
};

// Derived class Ball implementing specific movement and draw functionality
class Ball : public Shape {
private:
    float x, y;      // Ball's position
    float radius;    // Ball's radius
public:
    Ball(float x = 0.0, float y = 0.0, float radius = 0.1) : x(x), y(y), radius(radius) {}

// Override draw function to draw a ball
void draw() override {
    glColor3f(0.2, 0.6, 0.8); // Set color for the ball
    glBegin(GL_POLYGON);      // Use a polygon to approximate the circle
    for (int i = 0; i < 100; i++) { 
        float angle = 2.0f * 3.14159f * i / 20; // Divide the circle into 100 parts
        float dx = cos(angle) * radius;        // Calculate x offset
        float dy = sin(angle) * radius;        // Calculate y offset
        glVertex2f(x + dx, y + dy);            // Add each vertex to the polygon
    }
    glEnd();
}

    // Override move function to move the ball by dx and dy
    void move(float dx, float dy) override {
        x += dx;
        y += dy;

        // Boundary checking
        if (x + radius > 1.0) x = 1.0 - radius;
        if (x - radius < -1.0) x = -1.0 + radius;
        if (y + radius > 1.0) y = 1.0 - radius;
        if (y - radius < -1.0) y = -1.0 + radius;
    }
};

Ball ball(0.0, 0.0, 0.1); // Initialize the ball in the center

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    ball.draw(); // Draw the ball

    glutSwapBuffers();
}

// Function to handle arrow key presses to move the ball
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            ball.move(0.0, 0.05);
            break;
        case GLUT_KEY_DOWN:
            ball.move(0.0, -0.05);
            break;
        case GLUT_KEY_LEFT:
            ball.move(-0.05, 0.0);
            break;
        case GLUT_KEY_RIGHT:
            ball.move(0.05, 0.0);
            break;
    }
    glutPostRedisplay(); // Re-render the display after movement
}
void printInstructions() {
    cout << "Use the arrow keys to move the ball:\n";
    cout << "  UP ARROW    : Move up\n";
    cout << "  DOWN ARROW  : Move down\n";
    cout << "  LEFT ARROW  : Move left\n";
    cout << "  RIGHT ARROW : Move right\n";
    cout << "Press 'ESC' to exit.\n";
}

void initOpenGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	 printInstructions(); // Display movement instructions in the console
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ball Control with Arrow Keys");

    initOpenGL();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys); // Register arrow key handler
    glutMainLoop();
    return 0;
}
