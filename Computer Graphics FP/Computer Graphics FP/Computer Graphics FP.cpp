#include <windows.h>	// Header file for the Windows Library
#include <MMSystem.h>
#include <gl/gl.h>	// Header file for the OpenGL32 Library
#include <gl/glu.h>	// Header file for the GlU32 Library
#include <gl/glut.h>	// Header file for the Glut32 Library
#include <math.h>	// Header file for the Math Library
#include <iostream>
#include <vector>
#include<cstdlib>
#include <stdio.h>
#include<string>
using namespace std;

//These lines above link the code to the openGL libraries.
#pragma comment(lib, "opengl32.lib")	// import gl library
#pragma comment(lib, "glu32.lib")	// import glu library
#pragma comment(lib, "glut32.lib")	// import glut library

void Dinosaur_body();
void Dinosaur_feet(int);
void Dinosaur_hand();
void drawCloud(int x, int y, int size);
void obstacle(int);

float fXPos_dinosaur, fYPos_dinosaur, fYPos_feet1, fYPos_feet2,  fXPos_desert, fXPos_sky;
int feet_state, jump_state, live_state, dead_state, color_state;
float game_speed, jump_speed, feet_up_speed, feet_down_speed, sky_speed;
float main_color[3];//main_color;background_color
float background_color[3];
float game_time;
vector <int>obs(3);
void Timer(int);
void OnKeyPress(unsigned char key, int x, int y);
void mouseButton(int, int, int, int);
void print(int x, int y, char const* string);
void print_score();
void print_HI_score();
int check_score, hi_score;
string s;
char const* pchar;  //use char const* as target type
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
	glColor3fv(main_color);
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
	
	glColor3fv(main_color);
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
int skyY1, skyY2, skyY3;
void background()
{
	glBegin(GL_QUADS);
	glColor3fv(background_color);
	glVertex2f(-100, 100);
	glVertex2f(100, 100);
	glVertex2f(100, -100);
	glVertex2f(-100, -100);
	glEnd();
	glPushMatrix();
	glColor3fv(main_color);
	glTranslatef(fXPos_sky, 0, 0);
	// draw 3 skys with defrent places
	drawCloud(150, skyY1, 2);
	drawCloud(210, skyY2, 2);
	drawCloud(270, skyY3, 2);
	glPopMatrix();
}
void drawCloud(int x, int y, int size)
{
	
	glColor3fv(main_color);
	glLineWidth(size);

	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x - 32, y);

	glVertex2f(x - 32, y + 1);
	glVertex2f(x - 33, y + 1);

	glVertex2f(x, y);
	glVertex2f(x, y + 2);

	glVertex2f(x, y + 2);
	glVertex2f(x - 1, y + 4);

	glVertex2f(x - 1, y + 4);
	glVertex2f(x - 3, y + 4);

	glVertex2f(x - 3, y + 4);
	glVertex2f(x - 3, y + 6);

	glVertex2f(x - 7, y + 6);
	glVertex2f(x - 3, y + 6);

	glVertex2f(x - 7, y + 6);
	glVertex2f(x - 7, y + 8);

	glVertex2f(x - 12, y + 8);
	glVertex2f(x - 7, y + 8);

	glVertex2f(x - 10, y + 8);
	glVertex2f(x - 10, y + 11);

	glVertex2f(x - 11, y + 11);
	glVertex2f(x - 10, y + 11);

	glVertex2f(x - 11, y + 12);
	glVertex2f(x - 11, y + 11);

	glVertex2f(x - 11, y + 12);
	glVertex2f(x - 13, y + 12);

	glVertex2f(x - 13, y + 12);
	glVertex2f(x - 13, y + 14);

	glVertex2f(x - 13, y + 14);
	glVertex2f(x - 17, y + 14);

	glVertex2f(x - 17, y + 14);
	glVertex2f(x - 17, y + 12);

	glVertex2f(x - 17, y + 12);
	glVertex2f(x - 22, y + 12);


	glVertex2f(x - 22, y + 12);
	glVertex2f(x - 22, y + 11);

	glVertex2f(x - 22, y + 11);
	glVertex2f(x - 23, y + 11);

	glVertex2f(x - 23, y + 11);
	glVertex2f(x - 23, y + 10);

	glVertex2f(x - 23, y + 10);
	glVertex2f(x - 26, y + 10);

	glVertex2f(x - 26, y + 10);
	glVertex2f(x - 26, y + 6);

	glVertex2f(x - 26, y + 6);
	glVertex2f(x - 30, y + 6);


	glVertex2f(x - 30, y + 6);
	glVertex2f(x - 30, y + 5);

	glVertex2f(x - 30, y + 5);
	glVertex2f(x - 35, y + 5);

	glVertex2f(x - 35, y + 5);
	glVertex2f(x - 35, y + 4);

	glVertex2f(x - 35, y + 4);
	glVertex2f(x - 36, y + 4);

	glVertex2f(x - 36, y + 4);
	glVertex2f(x - 36, y + 1);

	glVertex2f(x - 36, y + 1);
	glVertex2f(x - 37, y + 1);

	glVertex2f(x - 38, y + 1);
	glVertex2f(x - 40, y + 1);

	glVertex2f(x - 40, y + 1);
	glVertex2f(x - 40, y);

	glVertex2f(x - 40, y);
	glVertex2f(x - 41, y);
	glEnd();
}
// Help Functions
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
	if (live_state)
	{
		glBegin(GL_QUADS);
		glVertex2f(5.6, 7.7);
		glVertex2f(6.7, 7.7);
		glVertex2f(6.7, 7.4);
		glVertex2f(5.5, 7.4);
		glEnd();
		
		glColor3fv(background_color);
		glBegin(GL_QUADS);
		glVertex2f(5.45, 9.5);
		glVertex2f(5.85, 9.5);
		glVertex2f(5.85, 8.8);
		glVertex2f(5.45, 8.8);
		glEnd();
		
	}
	else {
		glColor3fv(background_color);
		//  Display geometric primitives
		glBegin(GL_QUADS);
		glVertex2f(5.4, 9.5);
		glVertex2f(5.9, 9.5);
		glVertex2f(5.9, 8.8);
		glVertex2f(5.4, 8.8);
		glEnd();
		glColor3fv(main_color);
		glBegin(GL_QUADS);
		glVertex2f(5.5, 9.4);
		glVertex2f(5.8, 9.4);
		glVertex2f(5.8, 8.9);
		glVertex2f(5.5, 8.9);
		glEnd();
	}
	glColor3fv(main_color);
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
void try_again()
{
	glColor3fv(main_color);

	glBegin(GL_QUADS);
	glVertex2f(5, 0);
	glVertex2f(-5, 0);
	glVertex2f(-5, -10);
	glVertex2f(5, -10);
	glEnd();

	glLineWidth(4);

	glColor3fv(background_color);
	glBegin(GL_LINES);
	glVertex2f(2, -3);
	glVertex2f(3, -3);

	glVertex2f(3, -3);
	glVertex2f(3, -8);

	glVertex2f(3, -8);
	glVertex2f(-3, -8);

	glVertex2f(-3, -8);
	glVertex2f(-3, -3);

	glVertex2f(-3, -3);
	glVertex2f(-1, -3);


	glEnd();
	//glVertex2f(-1, -3);

	glBegin(GL_TRIANGLES);
	glVertex2f(1, -3);
	glVertex2f(-1, -1);
	glVertex2f(-1, -5);
	glEnd();
}
/**
Handles the key press. This event is whenever
a normal ASCII character is being pressed.
*/

int main(int argc, char* argv[])
{
	game_time = 1000 / 60;
	check_score = hi_score = fXPos_sky = 0;
	fXPos_dinosaur = -90;
	fYPos_dinosaur = -78;
	fXPos_desert  =  0;
	fYPos_feet1 = -4;
	fYPos_feet2 = -2.5;
	feet_state = dead_state = 0;
	live_state = 1;
	jump_state = 2;
	game_speed = 0.8;
	sky_speed = 0.6;
	jump_speed = 1;
	feet_up_speed = 0.15;
	feet_down_speed = 0.2;
	skyY1 = 20;
	skyY2 = 40;
	skyY3 = 70;
	obs = { 1,2,1 };
	// color
	background_color[0] = 1;
	background_color[1] = 1;
	background_color[2] = 1;
	main_color[0] = 0.25;
	main_color[1] = 0.25;
	main_color[2] = 0.25;
	
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
	glutCreateWindow("T-Rex");

	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);
	// here is the setting of the idle function
	glutIdleFunc(OnDisplay);
	//OnDisplay will handle the paint event
	// here is the setting of the key function
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(mouseButton);
	// the timer function
	glutTimerFunc(1000, Timer, 0);
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

	// draw the skys
	background();

	// print the new score
	print_score();

	// if the Dinosaur dead the game will stop
	if (live_state == 0)
	{
		dead_state = 1;
		sky_speed = 0;
		game_speed = 0;
		jump_speed = 0;
		feet_up_speed = 0;
		feet_down_speed = 0;
		// resite the color
		background_color[0] = 1;
		background_color[1] = 1;
		background_color[2] = 1;
		main_color[0] = 0.25;
		main_color[1] = 0.25;
		main_color[2] = 0.25;
		print(-16, 5, "Game  Over");
		try_again();
	}
	if (hi_score < check_score && dead_state == 1)
		hi_score = check_score;
	if (hi_score)
		print_HI_score();

	// draw the Desert
	Desert();
	// draw the Dinosaur
	Dinosaur();


	glutSwapBuffers();

}



/**
Handles the key press. This event is whenever
a normal ASCII character is being pressed.
*/
float score = 0;
void Timer(int)
{
	// call the ondisplay function
	glutPostRedisplay();
	// call 60 times Timer
	glutTimerFunc(game_time, Timer, 0);

	// the dinosaur is dead
	if (fXPos_desert > -204 && fXPos_desert < -198 && fYPos_dinosaur < -72 && obs[0] == 1)
		live_state = 0;
	else if (fXPos_desert > -215 && fXPos_desert < -197.5 && fYPos_dinosaur < -73 && obs[0] == 2)
		live_state = 0;
	if (fXPos_desert > -245 && fXPos_desert < -239 && fYPos_dinosaur < -73 && obs[1] == 1)
		live_state = 0;
	else if (fXPos_desert > -255 && fXPos_desert < -237.5 && fYPos_dinosaur < -73 && obs[1] == 2)
		live_state = 0;
	if (fXPos_desert > -304 && fXPos_desert < -298 && fYPos_dinosaur < -72 && obs[2] == 1)
		live_state = 0;
	else if (fXPos_desert > -315 && fXPos_desert < -297.5 && fYPos_dinosaur < -73 && obs[2] == 2)
		live_state = 0;


	// the score
	score += game_speed;
	check_score = score / 10;
	// increase the speed
	if (check_score % 10 == 0 && check_score != 0) {
		game_speed += 0.001;
		sky_speed += 0.0011;
	}
	if (check_score > 200)
	{
		background_color[0] = 0.25;
		background_color[1] = 0.25;
		background_color[2] = 0.25;
		main_color[0] = 1;
		main_color[1] = 1;
		main_color[2] = 1;
	}
	// 	change the gamecolor for hardmode
	switch (feet_state)
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
			feet_state = 1;
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
			feet_state = 0;
		}	
		break;
	}
	// dinosaur Jumb
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

	// game speed
	if (fXPos_desert > -370) {
		
		fXPos_desert -= game_speed;
	}
		
	else
	{
		fXPos_desert = 0;
		srand(time(0));
		obs = { rand() % 2 + 1,rand() % 2 + 1,rand() % 2 + 1 };
	}
	// sky speed
	if (fXPos_sky > -450)
	{
		fXPos_sky -= sky_speed;
	}
	else
	{
		fXPos_sky = 0;
		skyY1 = rand() % 75 + 10, skyY2 = rand() % 75 + 10, skyY3 = rand() % 75 + 10;
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

void mouseButton(int button, int state, int x, int y) {


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && fYPos_dinosaur == -78)
	{
		//Jump from the left cleck
		PlaySoundA((LPCSTR)"C:\\Users\\ahmed\\source\\repos\\Computer Graphics FP\\Computer Graphics FP\\jump.wav", NULL, SND_FILENAME | SND_ASYNC);
		jump_state = 1;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && dead_state == 1)
	{
		//Reset the game if he/she click the right button
		PlaySoundA((LPCSTR)"C:\\Users\\ahmed\\source\\repos\\Computer Graphics FP\\Computer Graphics FP\\death.wav", NULL, SND_FILENAME | SND_ASYNC);
		game_time = 1000 / 60;
		dead_state = fXPos_desert = fXPos_sky = score = feet_state = 0;
		live_state = jump_speed = 1;
		fXPos_dinosaur = -90;
		fYPos_dinosaur = -78;
		fYPos_feet1 = -4;
		fYPos_feet2 = -2.5;
		jump_state = 2;
		game_speed = 0.8;
		sky_speed = 0.6;
		feet_up_speed = 0.15;
		feet_down_speed = 0.2;
		skyY1 = 20;
		skyY2 = 40;
		skyY3 = 70;
		obs = { 1,2,1 };
	}
}
void print_score()    // -- print the score --
{
	char text[32];
	sprintf_s(text, "Score:%.0f", (float)check_score);  // print text in opengl window 
	glColor3fv(main_color);
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(-90, 80);
	for (int i = 0; text[i] != NULL; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]); //ex GLUT_BITMAP_TIMES_ROMAN_24
}
void print_HI_score()    // -- print high score --
{
	char text[32];
	sprintf_s(text, "HI:%.0f", (float)hi_score);  // print text in opengl window 

	glColor3fv(main_color);
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(-90, 90);
	for (int i = 0; text[i] != NULL; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]); //ex GLUT_BITMAP_TIMES_ROMAN_24
}
void print(int x, int y, char const* string)
{
	glColor3fv(main_color);
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int)strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
