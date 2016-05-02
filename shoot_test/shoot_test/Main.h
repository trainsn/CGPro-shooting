#include "Glext.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <string.h>

#include "Defines.h"
#include "Model.h"
#include "vec.h"

#include "CGame.h"
#include "CCharacter.h"
#include "CStaticImages.h"
#include "MilkshapeModel.h"

//openGl Multitexturing support 
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;

//Window stuff
HDC hDC = NULL; //private GDI Device Context
HGLRC hRC = NULL; //permanent Rendering Context
HWND hWn = NULL;    //holds our window handle 
HINSTANCE hInstance;    //holds the instance of the application 

static int w = (long)GetSystemMetrics(SM_CXSCREEN);//Screen width 
static int h = (long)GetSystemMetrics(SM_CYSCREEN);//screen height

bool keys[256]; //array used for the keybord routine 
bool active = true; //window active flag set to true by default 
bool fullscreen = true;//fullscreent flag set to fulscreen mode by default

//lighting 
static GLfloat lightPosition0[] = { 0, 0, 0, 0 };
static GLfloat lightDiffuse0[] = { 1, 1, 1, 1 };
static GLfloat lightPosition1[] = { -2, 10, 5, 0 };
