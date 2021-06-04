#include <windows.h>	// Header file for the Windows Library
#include <gl/gl.h>	// Header file for the OpenGL32 Library
#include <gl/glu.h>	// Header file for the GlU32 Library
#include <gl/glut.h>	// Header file for the Glut32 Library
#include <math.h>	// Header file for the Math Library
#include <iostream>
#include <vector>
#include<cstdlib>
using namespace std;

//These lines above link the code to the openGL libraries.
#pragma comment(lib, "opengl32.lib")	// import gl library
#pragma comment(lib, "glu32.lib")	// import glu library
#pragma comment(lib, "glut32.lib")	// import glut library

void Dinosaur_body();
void Dinosaur_feet(int);
void Dinosaur_hand();

void obstacle(int);

float fXPos_dinosaur, fYPos_dinosaur, fYPos_feet1, fYPos_feet2,  fXPos_desert;
int state, jump_state, live_state;
float game_speed, jump_speed, feet_up_speed, feet_down_speed;
float score;
vector <int>obs(3);

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char* argv[]);

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations();

/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay();

// Main Functions
void Dinosaur()
{
	// Dinosaur body
	glColor3f(0.25, 0.25, 0.25);
	glPushMatrix();
	glTranslatef(fXPos_dinosaur, fYPos_dinosaur, 0);
	
	glPushMatrix();
	glScalef(2, 2, 2);
	Dinosaur_body();
	// pops the current matrix stack, replacing the
	// current matrix with the one below it on the stack.
	glPopMatrix();
	// Dinosaur left feet
	glPushMatrix();
	glTranslatef(3, fYPos_feet1, 0);
	glScalef(1, 2, 0);
	Dinosaur_feet(1);
	glPopMatrix();
	// Dinosaur rigth feet
	glPushMatrix();
	glTranslatef(6, fYPos_feet2, 0);
	glScalef(1, 2, 0);
	Dinosaur_feet(2);
	glPopMatrix();
	// Dinosaur arm
	glPushMatrix();
	glScalef(2, 2, 2);
	Dinosaur_hand();
	glPopMatrix();
	glPopMatrix();
}
void Desert()
{
	
	glPushMatrix();
	glTranslatef(fXPos_desert, 0, 0);
	//glScalef(4, 4, 4);
	glColor3f(0.25, 0.25, 0.25);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2f(480, -73);
	glVertex2f(-270, -73);
	glVertex2f(-370, -71);
	glVertex2f(480, -71);
	glEnd();
	glPopMatrix();

	glPushMatrix();

	glTranslatef(110, -85, 0);
	glScalef(4, 4, 4);
	obstacle(obs[0]);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(150, -85, 0);
	glScalef(4, 4, 4);
	obstacle(obs[1]);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(210, -85, 0);
	glScalef(4, 4, 4);
	obstacle(obs[2]);
	glPopMatrix();
	glPopMatrix();
}
// Help Functions
void DrawCircle(GLenum type, GLfloat xc, GLfloat yc, GLfloat radius, GLfloat half_circle = 2)
{
	// create circle
	glBegin(type);
	int points = 36;
	float const PI = 3.141592654;
	for (int i = 0; i < points; i++) {
		float angle = half_circle * PI * i / points;
		glVertex2f(xc + (radius * cos(angle))
			, yc + (radius * sin(angle)));
	}
	glEnd();
}
void DrawCircleColored(GLenum type, float xc, float yc, int radius, float half_circle = 2)
{
	// create circle
	glBegin(type);
	float colors[2][3] = { {0,0,0},{1,1,1} };
	int points = 50;
	float const PI = 3.141592654;
	glVertex2f(xc, yc);
	for (int i = 0; i <= points; i++) {
		glColor3fv(colors[i % 2]);
		float angle = (half_circle * PI * i / points);
		float x = xc + (radius * cos(angle)),
			y = yc + (radius * sin(angle));
		glVertex2f(x, y);
	}
	glEnd();
}
void DrawEllipse(GLenum type, GLfloat xc, GLfloat yc, GLfloat radius, GLfloat half_circle = 2)
{
	// create circle
	glBegin(type);
	int points = 360;
	float const PI = 3.141592654;
	for (float i = 0; i < points; i += 0.1) {
		glVertex2f(xc + (radius * cos(i))
			, yc + (radius / 2 * sin(i)));
	}
	glEnd();
}
void Dinosaur_body()
{
	//  Set shading model
	glShadeModel(GL_FLAT);
	//  Set the primitive color
	

	//  Display geometric primitives
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(7.00, 8.03);
	glVertex2f(7.00, 10.03);
	glVertex2f(5.20, 10.00);
	glVertex2f(5.20, 9.76);
	glVertex2f(6.99, 8.03);
	glVertex2f(5.01, 9.76);
	glVertex2f(5.99, 8.01);
	glVertex2f(5.01, 7.83);
	glVertex2f(5.99, 6.04);
	glVertex2f(5.80, 6.03);
	glVertex2f(4.98, 9.47);
	glVertex2f(4.99, 6.03);
	glVertex2f(5.80, 5.79);
	glVertex2f(5.01, 5.74);
	glVertex2f(5.62, 5.78);
	glVertex2f(5.62, 5.53);
	glVertex2f(4.98, 9.03);
	glVertex2f(4.99, 5.51);
	glVertex2f(5.53, 5.31);
	glVertex2f(4.99, 5.01);
	glVertex2f(4.52, 5.29);
	glVertex2f(4.52, 5.04);
	glVertex2f(4.97, 5.29);
	glVertex2f(4.51, 5.99);
	glVertex2f(4.96, 6.00);
	glVertex2f(4.51, 5.42);
	glVertex2f(4.25, 5.42);
	glVertex2f(4.51, 6.00);
	glVertex2f(4.01, 6.00);
	glVertex2f(4.24, 5.42);
	glVertex2f(4.24, 5.03);
	glVertex2f(4.03, 5.03);
	glVertex2f(3.99, 6.00);
	glVertex2f(3.76, 5.01);
	glVertex2f(3.76, 4.74);
	glVertex2f(3.60, 4.74);
	glVertex2f(3.38, 5.14);
	glVertex2f(4.10, 5.71);
	glVertex2f(3.98, 6.03);
	glVertex2f(3.00, 6.01);
	glVertex2f(3.38, 5.19);
	glVertex2f(3.01, 5.19);
	glVertex2f(3.00, 5.72);
	glVertex2f(2.98, 5.50);
	glVertex2f(2.71, 5.50);
	glVertex2f(2.97, 6.01);
	glVertex2f(2.68, 6.01);
	glVertex2f(2.69, 5.76);
	glVertex2f(2.46, 5.78);
	glVertex2f(2.71, 6.57);
	glVertex2f(2.48, 6.57);
	glVertex2f(2.46, 6.07);
	glVertex2f(2.23, 6.07);
	glVertex2f(2.22, 7.00);
	glVertex2f(2.22, 6.43);
	glVertex2f(2.01, 6.43);
	glVertex2f(2.00, 7.00);
	glVertex2f(2.02, 6.74);
	glVertex2f(1.76, 6.72);
	glVertex2f(1.76, 7.97);
	glVertex2f(1.97, 7.97);
	glVertex2f(2.01, 7.33);
	glVertex2f(2.01, 7.69);
	glVertex2f(2.22, 7.67);
	glVertex2f(2.21, 6.93);
	glVertex2f(2.22, 7.38);
	glVertex2f(2.49, 7.39);
	glVertex2f(2.47, 7.04);
	glVertex2f(2.48, 6.33);
	glVertex2f(2.75, 7.00);
	glVertex2f(2.71, 6.06);
	glVertex2f(2.76, 6.67);
	glVertex2f(3.00, 6.63);
	glVertex2f(3.01, 6.07);
	glVertex2f(3.00, 6.39);
	glVertex2f(3.38, 6.40);
	glVertex2f(3.37, 5.82);
	glVertex2f(3.38, 6.67);
	glVertex2f(3.57, 6.67);
	glVertex2f(3.57, 5.75);
	glVertex2f(3.57, 6.96);
	glVertex2f(3.78, 6.94);
	glVertex2f(3.80, 5.69);
	glVertex2f(3.80, 7.29);
	glVertex2f(3.97, 7.29);
	glVertex2f(3.98, 5.89);
	glVertex2f(4.01, 7.63);
	glVertex2f(4.19, 7.63);
	glVertex2f(4.11, 5.88);
	glVertex2f(4.21, 7.86);
	glVertex2f(4.36, 7.86);
	glVertex2f(4.30, 5.76);
	glVertex2f(4.37, 8.01);
	glVertex2f(4.57, 8.00);
	glVertex2f(4.46, 5.90);
	glVertex2f(4.57, 8.26);
	glVertex2f(4.76, 8.28);
	glVertex2f(4.69, 5.93);
	glVertex2f(4.73, 8.46);
	glVertex2f(4.98, 8.44);
	glVertex2f(5.09, 5.89);
	glVertex2f(3.18, 5.92);
	glVertex2f(3.42, 6.14);
	glVertex2f(2.67, 6.29);
	glVertex2f(2.84, 6.56);
	glVertex2f(2.89, 5.74);
	glVertex2f(3.23, 6.07);
	glVertex2f(2.15, 6.81);
	glVertex2f(2.63, 6.85);
	glVertex2f(1.86, 7.08);
	glVertex2f(2.22, 6.67);
	glVertex2f(2.39, 7.29);
	glVertex2f(2.42, 6.69);
	glVertex2f(2.55, 6.90);
	glVertex2f(1.81, 7.47);
	glVertex2f(1.88, 7.69);
	glVertex2f(2.15, 6.65);
	glEnd();
	if (!live_state)
	{
		glBegin(GL_QUADS);
		glVertex2f(5.6, 7.7);
		glVertex2f(6.7, 7.7);
		glVertex2f(6.7, 7.4);
		glVertex2f(5.5, 7.4);
		glEnd();
		glColor3f(1.00, 1.00, 1.00);
		glBegin(GL_QUADS);
		glVertex2f(5.45, 9.5);
		glVertex2f(5.85, 9.5);
		glVertex2f(5.85, 8.8);
		glVertex2f(5.45, 8.8);
		glEnd();
		
	}
	else {
		glColor3f(1.00, 1.00, 1.00);

		//  Display geometric primitives
		glBegin(GL_QUADS);
		glVertex2f(5.4, 9.5);
		glVertex2f(5.9, 9.5);
		glVertex2f(5.9, 8.8);
		glVertex2f(5.4, 8.8);
		glEnd();
		glColor3f(0.25, 0.25, 0.25);
		glBegin(GL_QUADS);
		glVertex2f(5.5, 9.4);
		glVertex2f(5.8, 9.4);
		glVertex2f(5.8, 8.9);
		glVertex2f(5.5, 8.9);
		glEnd();
	}
	glColor3f(0.25, 0.25, 0.25);
}
void Dinosaur_feet(int state)
{
	//  Display geometric primitives
	if (state == 1)
	{
		glBegin(GL_QUADS);
		glVertex2f(5, 5.32);
		glVertex2f(5, 5.71);
		glVertex2f(3.9, 5.71);
		glVertex2f(3.9, 5.32);
		glVertex2f(3.9, 5.74);
		glVertex2f(4.1, 5.74);
		glVertex2f(4.1, 6.80);
		glVertex2f(3.8, 6.80);
		glVertex2f(4.1, 6.2);
		glVertex2f(4.3, 6.69);
		glVertex2f(4.3, 7.33);
		glVertex2f(3.8, 6.85);
		glEnd();
	}
	else if (state == 2) 
	{
		glBegin(GL_QUADS);
		glVertex2f(5.4, 5.38);
		glVertex2f(5.4, 5.03);
		glVertex2f(4.3, 5.02);
		glVertex2f(4.2, 5.36);
		glVertex2f(4.3, 5.34);
		glVertex2f(4.5, 5.38);
		glVertex2f(4.5, 6.75);
		glVertex2f(4.2, 6.73);
		glVertex2f(4.3, 5.81);
		glVertex2f(4, 6.39);
		glVertex2f(4, 7.14);
		glVertex2f(4.5, 6.78);
		glEnd();
	}
	

	
	/*
	glVertex2f(4.43, 3.02);
	glVertex2f(3.75, 3.02);
	glVertex2f(4.42, 3.26);
	glVertex2f(3.76, 3.25);
	glVertex2f(3.99, 3.25);
	glVertex2f(4.01, 4.01);
	glVertex2f(3.77, 3.24);
	glVertex2f(3.77, 4.01);
	*/
}
void Dinosaur_hand()
{
	//  Display geometric primitives
	glTranslatef(2.2, 2.2, 0);

	glBegin(GL_QUADS);
	glVertex2f(3.01, 5.02);
	glVertex2f(4.18, 5.03);
	glVertex2f(4.18, 4.77);
	glVertex2f(2.99, 4.75);
	glVertex2f(3.90, 4.75);
	glVertex2f(3.91, 4.36);
	glVertex2f(4.20, 4.36);
	glVertex2f(4.18, 4.77);
	glEnd();
}
void obstacle(int state)
{
	glShadeModel(GL_FLAT);

	//  Set the primitive color
	//  Display geometric primitives
	if (state == 1)
	{
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(2.99, 6.03);
		glVertex2f(3.55, 6.00);
		glVertex2f(3.49, 3.03);
		glVertex2f(2.99, 6.00);
		glVertex2f(2.98, 3.02);
		glVertex2f(3.53, 4.39);
		glVertex2f(3.54, 4.02);
		glVertex2f(3.86, 4.03);
		glVertex2f(4.17, 4.39);
		glVertex2f(4.20, 5.17);
		glVertex2f(3.96, 5.17);
		glVertex2f(3.96, 4.19);
		glVertex2f(3.96, 4.41);
		glVertex2f(2.97, 4.03);
		glVertex2f(2.98, 4.41);
		glVertex2f(2.65, 4.03);
		glVertex2f(2.35, 4.41);
		glVertex2f(2.63, 4.39);
		glVertex2f(2.58, 5.02);
		glVertex2f(2.30, 5.03);
		glVertex2f(2.34, 4.44);
		glEnd();
	}
	else {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(2.97, 5.53);
		glVertex2f(3.28, 5.55);
		glVertex2f(3.23, 3.00);
		glVertex2f(2.97, 3.00);
		glVertex2f(2.98, 5.52);
		glVertex2f(2.98, 3.77);
		glVertex2f(2.95, 4.05);
		glVertex2f(2.68, 3.78);
		glVertex2f(2.45, 4.02);
		glVertex2f(2.64, 4.05);
		glVertex2f(2.64, 5.00);
		glVertex2f(2.41, 5.00);
		glVertex2f(2.43, 4.06);
		glVertex2f(2.69, 3.81);
		glVertex2f(3.25, 4.03);
		glVertex2f(3.27, 4.70);
		glVertex2f(3.27, 4.42);
		glVertex2f(3.65, 4.42);
		glVertex2f(3.43, 4.59);
		glVertex2f(3.65, 5.30);
		glVertex2f(3.46, 5.28);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(3.99, 5.53);
		glVertex2f(4.25, 5.55);
		glVertex2f(4.01, 4.48);
		glVertex2f(4.24, 4.50);
		glVertex2f(4.24, 4.81);
		glVertex2f(4.55, 4.91);
		glVertex2f(4.24, 4.52);
		glVertex2f(4.58, 4.55);
		glVertex2f(4.98, 4.56);
		glVertex2f(4.99, 6.02);
		glVertex2f(4.51, 6.00);
		glVertex2f(4.53, 3.05);
		glVertex2f(4.98, 4.56);
		glVertex2f(4.98, 3.03);
		glVertex2f(4.99, 4.23);
		glVertex2f(4.96, 3.92);
		glVertex2f(5.21, 4.25);
		glVertex2f(5.47, 3.91);
		glVertex2f(5.48, 5.22);
		glVertex2f(5.26, 5.22);
		glVertex2f(5.21, 4.23);
		glEnd();
	}
	

	
}
// Coordinates Graph
void CoordinatesGraph(int xCG, int yCG)
{
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	double yWidth = (yCG / 10) / 5;
	for (int y = -yCG; y <= yCG; y += yWidth)
	{
		glVertex2f(xCG, y);
		glVertex2f(-xCG, y);

	}
	glEnd();
	glBegin(GL_LINES);
	double xWidth = (xCG / 10) / 5;
	for (int x = -xCG; x <= xCG; x += xWidth)
	{
		glVertex2f(x, yCG);
		glVertex2f(x, -yCG);

	}
	glEnd();
	glLineWidth(2);
	glBegin(GL_LINES);
	yWidth = yCG / 10;
	for (int y = -yCG; y <= yCG; y += yWidth)
	{
		glVertex2f(xCG, y);
		glVertex2f(-xCG, y);

	}
	glEnd();
	glBegin(GL_LINES);
	xWidth = xCG / 10;
	for (int x = -xCG; x <= xCG; x += xWidth)
	{
		glVertex2f(x, yCG);
		glVertex2f(x, -yCG);

	}
	glEnd();
	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	// Y Coordinates
	glVertex2f(0, yCG);
	glVertex2f(0, -yCG);
	// X Coordinates

	glVertex2f(xCG, 0);
	glVertex2f(-xCG, 0);
	glEnd();
}
/**
Handles the key press. This event is whenever
a normal ASCII character is being pressed.
*/
void screanSaver(int);
void OnKeyPress(unsigned char key, int x, int y);

int main(int argc, char* argv[])
{
	fXPos_dinosaur = -90;
	fYPos_dinosaur = -78;
	fXPos_desert = score =  0;
	fYPos_feet1 = -4;
	fYPos_feet2 = -2.5;
	state = live_state = 0;
	jump_state = 2;
	game_speed = 0.8;
	jump_speed = 1;
	feet_up_speed = 0.15;
	feet_down_speed = 0.2;
	obs = { 1,2,1 };
	InitGraphics(argc, argv);
	return 0;
}


/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
Initialization is done once at the start of the program.
Rendering is done each time the window needs redrawing
*/

void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(100, 100); //pass (-1, -1) for Window-Manager defaults  glutInitWindowPosition(X, Y);
	glutInitWindowSize(800, 600);  //glutInitWindowSize(width, hight);
	glutCreateWindow("Test");

	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);
	// here is the setting of the idle function
	glutIdleFunc(OnDisplay);
	//OnDisplay will handle the paint event
	// here is the setting of the key function
	glutKeyboardFunc(OnKeyPress);
	//glutKeyboardFunc();
	glutTimerFunc(1000, screanSaver, 0);
	// Enable alpha transparency in OpenGL
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	SetTransformations();
	glutMainLoop(); //Well glutMainLoop is the main function the keeps calling and calling the displaying functions and which also keeps your window actually opened
}
/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations() {
	//set up the logical coordinate system of the window: [-100, 100] x [-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//define a 2-D orthographic projection matrix
	//parameters: left, right, bottom, top
	gluOrtho2D(-100, 100, -100, 100); //gluOrtho2D(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top)

	glMatrixMode(GL_MODELVIEW);
}
/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay() {
	// clear the transformation matrix
	glLoadIdentity();
	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);

	//ALL drawing code goes here

	// pushes the current matrix stack down by one,
	// duplicating the current matrix.
	// glPushMatrix and glPopMatrix are used here instead of glLoadIdentity.
	
	
	Desert();
	Dinosaur();
	///////////////////////////////////////////////////////////////////////////////

	// swapping the buffers causes the rendering above to be 
	// shown
	glutSwapBuffers();

}



/**
Handles the key press. This event is whenever
a normal ASCII character is being pressed.
*/
int check;
void screanSaver(int)
{
	// call the ondisplay function
	glutPostRedisplay();
	// call 60 times screanSaver
	glutTimerFunc(1000 / 60, screanSaver, 0);
	// the score
	score += game_speed;
	check = (score / 10);
	cout << check <<endl;
	
	if (check % 10 == 0 && check > 9)
		game_speed += 0.001;

	// the dinosaur is dead
	if (fXPos_desert < -199 && fXPos_desert > -205 && fYPos_dinosaur < -72 && obs[0] == 1)
	{
		game_speed = 0;
		jump_speed = 0;
		feet_up_speed = 0;
		feet_down_speed = 0;
		live_state = 1;
	}
	else if (fXPos_desert < -199 && fXPos_desert > -206 && fYPos_dinosaur < -73 && obs[0] == 2)
	{
		game_speed = 0;
		jump_speed = 0;
		feet_up_speed = 0;
		feet_down_speed = 0;
		live_state = 1;
	}
	if (fXPos_desert < -239 && fXPos_desert > -255 && fYPos_dinosaur < -73 && obs[1] == 1)
	{
		game_speed = 0;
		jump_speed = 0;
		feet_up_speed = 0;
		feet_down_speed = 0;
		live_state = 1;
	}
	else if (fXPos_desert < -239 && fXPos_desert > -256 && fYPos_dinosaur < -73 && obs[1] == 2)
	{
		game_speed = 0;
		jump_speed = 0;
		feet_up_speed = 0;
		feet_down_speed = 0;
		live_state = 1;
	}
	if (fXPos_desert < -299 && fXPos_desert > -310 && fYPos_dinosaur < -72 && obs[2] == 1)
	{
		game_speed = 0;
		jump_speed = 0;
		feet_up_speed = 0;
		feet_down_speed = 0;
		live_state = 1;
	}
	else if (fXPos_desert < -299 && fXPos_desert > -311 && fYPos_dinosaur < -73 && obs[2] == 2)
	{
		game_speed = 0;
		jump_speed = 0;
		feet_up_speed = 0;
		feet_down_speed = 0;
		live_state = 1;

	}
	// game speed
	if (fXPos_desert > -330)
		fXPos_desert -= game_speed;
	else
	{
		fXPos_desert = 0;
		srand(time(0));
		obs = { rand()%2 +1,rand() % 2 + 1,rand() % 2 + 1 };
	}
	switch (state)
	{
	case 0:
		if (fYPos_feet1 < -2.5) {
			fYPos_feet1 += feet_down_speed;
			fYPos_feet2 -= feet_up_speed;
		}
		else
		{
			fYPos_feet1 = -2.5;
			fYPos_feet2 = -4;
			state = 1;
		}

		break;
	case 1:
		if (fYPos_feet1 >= -4)
		{
			fYPos_feet1 -= feet_up_speed;
			fYPos_feet2 += feet_down_speed;
		}
		else {
			fYPos_feet1 = -4;
			fYPos_feet2 = -2.5;
			state = 0;
		}
			
		break;
	default:
		break;
	}
	if (jump_state == 1 && fYPos_dinosaur < -60)
	{
		fYPos_dinosaur += jump_speed;
		if (fYPos_dinosaur == -60)
			jump_state = 0;
	}
	else if(jump_state == 0 && fYPos_dinosaur > -78)
	{
		fYPos_dinosaur -= jump_speed;
	}
}

/**
Handles the key press. This event is whenever
a normal ASCII character is being pressed.
*/
void OnKeyPress(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == 32 && fYPos_dinosaur == -78)
		jump_state = 1;


}