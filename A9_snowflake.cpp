//Write C++ program to generate snowflake using concept of fractals by using Korch Curves.

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

using namespace std;

#define RADIAN (3.14 / 180)
#define XMAX 720
#define YMAX 540

int n = 4; // Depth of recursion

void Initialize();
void draw();
void draw_koch(float, float, float, float, int);

void Initialize()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glColor3f(1.0, 1.0, 1.0);         // Set drawing color to white
    gluOrtho2D(0.0, XMAX, 0.0, YMAX); // Set the coordinate system
}

void draw()
{
    glBegin(GL_LINES);
    // Centered coordinates for the Koch snowflake
    draw_koch(200, 170, 520, 170, n);  // Base line of the triangle
    draw_koch(520, 170, 360, 490, n);  // Right side
    draw_koch(360, 490, 200, 170, n);   // Left side
    glEnd();
    glFlush();
}

void draw_koch(float xa, float ya, float xb, float yb, int n)
{
    float xc, xd, yc, yd, midx, midy;
    xc = (2 * xa + xb) / 3;
    yc = (2 * ya + yb) / 3;
    xd = (2 * xb + xa) / 3;
    yd = (2 * yb + ya) / 3;
    midx = xc + ((xd - xc) * cos(60 * RADIAN)) + ((yd - yc) * sin(60 * RADIAN));
    midy = yc - ((xd - xc) * sin(60 * RADIAN)) + ((yd - yc) * cos(60 * RADIAN));
    
    if (n > 0)
    {
        draw_koch(xa, ya, xc, yc, n - 1);
        draw_koch(xc, yc, midx, midy, n - 1);
        draw_koch(midx, midy, xd, yd, n - 1);
        draw_koch(xd, yd, xb, yb, n - 1);
    }
    else
    {
        glVertex2f(xa, ya);
        glVertex2f(xc, yc);
        glVertex2f(xc, yc);
        glVertex2f(midx, midy);
        glVertex2f(midx, midy);
        glVertex2f(xd, yd);
        glVertex2f(xd, yd);
        glVertex2f(xb, yb);
    }
}

int main(int argc, char **argv)
{   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(XMAX, YMAX);
    glutInitWindowPosition(450, 150);
    glutCreateWindow("KOCH SNOWFLAKE");
    Initialize();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
