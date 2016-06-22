#pragma  once
#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\freeglut.h>
#include <gl\GLAUX.H>
#include "glext.h"
#include <math.h>
#include <iostream>
#include "SOIL.h"
#include "Defines.h"

using namespace std;

class CAltitude
{
public:
	CAltitude(void);
	~CAltitude(void);

    //Heightmap rendering functions
    void  RenderHeightMap(PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB, PFNGLACTIVETEXTUREARBPROC glActiveTextureARB, GLuint* heightMapTexture);
	int Altitude(int X, int Y);
    void SetVertexColor(int x, int y);
    void SetupTexture(bool draw_TexturedTerrain, bool splash_screen, int x, int y, int i);

private:
    //Heightmap storage
    unsigned char* g_HeightMap;

};
