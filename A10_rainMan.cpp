// Write C++ program to draw man walking in the rain with an umbrella. Apply the concept of polymorphism.

#include <GL/glut.h>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

// Base class representing a drawable object
class Drawable {
public:
    virtual void draw() = 0; // Pure virtual function
    virtual ~Drawable() = default;
};

// Class representing the man
class Man : public Drawable {
    float x;
public:
    Man(float startX) : x(startX) {}

    float getX() const {
        return x;
    }

    void updatePosition() {
        x += 0.01f;
        if (x > 1.0f) x = -1.0f; // Loop position
    }

    void draw() override {
        // Draw head
        glColor3f(1.0f, 0.8f, 0.6f);
        glPushMatrix();
        glTranslatef(x, -0.2f, 0.0f);
        glutSolidSphere(0.05, 20, 20);

        // Draw body
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glEnd();

        // Draw legs
        glBegin(GL_LINES);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.05f, -0.3f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(0.05f, -0.3f);
        glEnd();

        // Draw arms
        glBegin(GL_LINES);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(-0.05f, -0.15f);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(0.05f, -0.15f);
        glEnd();
        glPopMatrix();
    }
};

// Class representing the umbrella
class Umbrella : public Drawable {
    const Man& man; // Reference to the man
public:
    Umbrella(const Man& associatedMan) : man(associatedMan) {}

    void draw() override {
        glColor3f(1.0f, 0.0f, 0.0f);
        glPushMatrix();
        glTranslatef(man.getX(), -0.1f, 0.0f);

        // Draw umbrella top (semi-circle)
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= 180; ++i) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(0.1f * cos(angle), 0.1f * sin(angle));
        }
        glEnd();

        // Draw umbrella handle
        glColor3f(0.5f, 0.2f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glEnd();
        glPopMatrix();
    }
};

// Class representing raindrops
class Raindrop : public Drawable {
    float x, y;
public:
    Raindrop(float startX, float startY) : x(startX), y(startY) {}

    void updatePosition() {
        y -= 0.02f;
        if (y < -1.0f) y = 1.0f; // Reset position
    }

    void draw() override {
        glColor3f(0.5f, 0.5f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y - 0.05f);
        glEnd();
    }
};

// List of drawable objects
vector<shared_ptr<Drawable>> objects;

// Man and raindrop specific logic
shared_ptr<Man> man;
vector<shared_ptr<Raindrop>> raindrops;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& obj : objects) {
        obj->draw();
    }

    glutSwapBuffers();
}

void timer(int) {
    man->updatePosition();
    for (auto& drop : raindrops) {
        drop->updatePosition();
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void initialize() {
    // Initialize man
    man = make_shared<Man>(-0.5f);
    objects.push_back(man);

    // Initialize umbrella
    auto umbrella = make_shared<Umbrella>(*man);
    objects.push_back(umbrella);

    // Initialize raindrops
    for (int i = 0; i < 100; ++i) {
        float x = (rand() % 200 - 100) / 100.0f;
        float y = (rand() % 200) / 100.0f;
        auto drop = make_shared<Raindrop>(x, y);
        raindrops.push_back(drop);
        objects.push_back(drop);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Man Walking in Rain with Umbrella");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    initialize();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
