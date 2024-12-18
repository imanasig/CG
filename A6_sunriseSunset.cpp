#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

float sunY = -0.8; // Initial Y position of the sun
bool isRising = true; // Control for sunrise and sunset

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the sky background
    if (isRising) {
        glClearColor(0.0, 0.5, 1.0, 1.0); // Morning sky
    } else {
        glClearColor(0.1, 0.1, 0.2, 1.0); // Evening sky
    }
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the sun
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(0.1 * cos(theta), sunY + 0.1 * sin(theta));
    }
    glEnd();

    // Draw the ground
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, -0.5);
    glVertex2f(-1.0, -0.5);
    glEnd();

    // Draw mountains
    glColor3f(0.5, 0.35, 0.05);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8, -0.5);
    glVertex2f(-0.4, 0.2);
    glVertex2f(0.0, -0.5);

    glVertex2f(-0.2, -0.5);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.6, -0.5);

    glVertex2f(0.4, -0.5);
    glVertex2f(0.8, 0.3);
    glVertex2f(1.2, -0.5);
    glEnd();

    glFlush();
}

void update(int value) {
    if (isRising) {
        sunY += 0.01;
        if (sunY >= 0.8) {
            isRising = false; // Switch to sunset
        }
    } else {
        sunY -= 0.01;
        if (sunY <= -0.8) {
            isRising = true; // Switch to sunrise
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sunrise and Sunset Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(50, update, 0);
    glutMainLoop();

    return 0;
}
