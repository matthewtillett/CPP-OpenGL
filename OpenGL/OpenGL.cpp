// OpenGL.cpp : Defines the entry point for the console application.
// http://makeagame.info/c-plus-plus-2d-pong-game

#include "stdafx.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream> 
#include <math.h> 
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#pragma comment(lib, "Opengl32.lib")


// window size and update rate (60 fps)
int width = 800;
int height = 600;
int interval = 1000 / 60;

// keycodes
#define VK_ESCAPE 0x1b


// prototype functions
void draw();
void update(int value);
void enable2D(int width, int height);
void drawText(float x, float y, std::string text);
std::string int2str(int x);
std::string float2str(float x);
void keyboard();
void vec2_norm(float& x, float& y);


int _tmain(int argc, char** argv)
{
  // initialize opengl (via glut)
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("OpenGL Example");

  // Open Fullscreen
  glutFullScreen();

  // Register callback functions   
  glutDisplayFunc(draw);
  glutTimerFunc(interval, update, 0);

  // setup scene to 2d mode and set draw color to white
  enable2D(width, height);
  glColor3f(1.0f, 1.0f, 1.0f);

  // start the whole thing
  glutMainLoop();

	return 0;
}


void draw()
{
  // clear (has to be done at the beginning)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  // TODO draw our scene

  // draw message
  glColor3ub(255, 255, 255);
  drawText(width / 2 - 10, height - 25, "- Running OpenGL -");
  glColor3ub(255,255,0);
  drawText(width / 2 - 10, height - 35, "Press ESC to exit.");


  // swap buffers (has to be done at the end)
  glutSwapBuffers();
}


void update(int value)
{
  // input handling
  keyboard();

  // Call update() again in 'interval' milliseconds
  glutTimerFunc(interval, update, 0);
 
  // Redisplay frame
  glutPostRedisplay();
}


void enable2D(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
}


void drawText(float x, float y, std::string text)
{
  glRasterPos2f(x, y);
  glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}


std::string int2str(int x)
{
    // converts int to string
    std::stringstream ss;
    ss << x;
    return ss.str();
}

std::string float2str(float x)
{
    // converts float to string
    std::ostringstream ss;
    ss << x;
    return ss.str();
}


void keyboard()
{
  // Quit application
  if (GetAsyncKeyState(VK_ESCAPE)) exit(0);
}


void vec2_norm(float& x, float& y)
{
  // sets a vectors length to 1 (which means that x + y == 1)
  float length = sqrt((x * x) + (y * y));
  if (length != 0.0f)
  {
    length = 1.0f / length;
    x *= length;
    y *= length;
  }
}
