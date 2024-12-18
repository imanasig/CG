#include<GL/glut.h>
#include<iostream>
#include<cmath>

using namespace std;

unsigned char bgColor[]={0, 0, 0};

void drawShape()
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(150,150);
	glVertex2i(150,300);
	glVertex2i(300,300);
	glVertex2i(300,150);
	
	glEnd();
	glFlush();	
}

void getPixel_RGB(int x, int y, unsigned char* RGB)
{
	glReadPixels(x,y,1,1,GL_RGB, GL_UNSIGNED_BYTE, RGB);
}

int compareRGB(unsigned char* RGB)
{
	for (int i=0; i<3; i++){
		if (bgColor[i]!=RGB[i]){
			return 0;
		}
	}
	return 1;
}

void BoundryFill(int x, int y)
{
	unsigned char currentRGB[3]={};
	getPixel_RGB(x,y, currentRGB);
	if (compareRGB(currentRGB)){
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		
		glEnd();
		glFlush();

		BoundryFill(x+1,y);
		BoundryFill(x,y+1);
		BoundryFill(x-1,y);
		BoundryFill(x,y-1);
	}
}

void Mouse(int btn, int state, int x, int y)
{	y= 480-y;
cout<<x<<" "<<y;
	if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		BoundryFill(x,y);
	}
}

void Init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640, 0,480);
}

int main(int argc,  char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Scan Fill Algorithm!");
	glutDisplayFunc(drawShape);
	Init();
	glutMouseFunc(Mouse);
	glutMainLoop();
}


