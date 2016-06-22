
#ifndef _MAIN_H
#define _MAIN_H

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "libSOIL.a")

#include <windows.h>					// Header File For Windows
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library
#include <gl\glaux.h>					// Header File For The Glaux Library
#include <gl\glut.h>

#include "Glext.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <string.h>

#include "Defines.h"
#include "Model.h"
#include "vec.h"

#include "CGame.h"
#include "CFigure.h"
#include "CStaticImages.h"
#include "Milkshape.h"

//openGl Multitexturing support 
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;

//Window stuff
HDC hDC = NULL; //private GDI Device Context
HGLRC hRC = NULL; //permanent Rendering Context
HWND hWnd = NULL;    //holds our window handle 
HINSTANCE hInstance;    //holds the instance of the application 

static int w = (long)GetSystemMetrics(SM_CXSCREEN);//Screen width 
static int h = (long)GetSystemMetrics(SM_CYSCREEN);//screen height

bool keys[256]; //array used for the keyboard routine 
bool active = true; //window active flag set to true by default 
bool fullscreen = true;//fullscreent flag set to fulscreen mode by default

//lighting 
static GLfloat lightPosition0[] = { 0, 0, 0, 0 };
static GLfloat lightDiffuse0[] = { 1, 1, 1, 1 };
static GLfloat lightPosition1[] = { -2, 10, 5, 0 };
static GLfloat lightDiffuse1[] = { 1, 1, 1, 1 };
static GLfloat lightSpecular1[] = { 0.6, 0.6, 0.6, 1 };
static GLfloat model_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };

//keep track of game varibales all in one spot 
static CGame game;

//we handle textures in this class
CStaticImages staticImages(&game, w, h);

//Models 
Milkshape *shot_pirate = NULL;
Milkshape *shot_ninja = NULL;
Milkshape *shot = NULL;
Milkshape *cannon = NULL;
Milkshape *japaneseTower = NULL;
Milkshape *pirateBoat = NULL;
Milkshape *tree = NULL;

//storage of random tree locations
float TreeTranslationi[NUM_TREES*NUM_TREES];
float TreeTranslationj[NUM_TREES*NUM_TREES];

//Animated charactres
CFigure* enemies[MAX_ENEMIES];

//Shooting object variables
tVector3 p, v, e;//store pos and view
float t;//t in ray

//Function Prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawSkybox(float x, float y, float z, float width, float height, float length);
void drawStaticModels();
int loadModels();
bool showLoadingScreen();

bool stuff_loaded = false;

#endif