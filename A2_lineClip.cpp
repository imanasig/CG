// Sample Points:
// Entirely visible within the clipping rectangle: Point 1: (50, 50) Point 2: (80, 80)

// Partially visible (crosses boundary): Point 1: (-150, 50) Point 2: (50, 150)

// Completely outside the clipping rectangle: Point 1: (-150, -150) Point 2: (-200, -200)

#include <GL/glut.h>
#include <iostream>

using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Define the clipping region
float xmin = -100, ymin = -100, xmax = 100, ymax = 100;

float x_start, y_start, x_end, y_end; // Line endpoints provided by the user

int computeCode(float x, float y) {
    int code = INSIDE;

    if (x < xmin)       // to the left of rectangle
        code |= LEFT;
    else if (x > xmax)  // to the right of rectangle
        code |= RIGHT;
    if (y < ymin)       // below the rectangle
        code |= BOTTOM;
    else if (y > ymax)  // above the rectangle
        code |= TOP;

    return code;
}

void cohenSutherlandClip(float x1, float y1, float x2, float y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int codeOut;
            float x, y;

            if (code1 != 0)
                codeOut = code1;
            else
                codeOut = code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(0.0, 1.0, 0.0); // Green color for clipped line
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping rectangle
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Original line in blue
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glBegin(GL_LINES);
    glVertex2f(x_start, y_start);
    glVertex2f(x_end, y_end);
    glEnd();

    // Perform line clipping
    cohenSutherlandClip(x_start, y_start, x_end, y_end);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv) {
    cout << "Enter the coordinates of the first point (x1, y1): ";
    cin >> x_start >> y_start;
    cout << "Enter the coordinates of the second point (x2, y2): ";
    cin >> x_end >> y_end;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
