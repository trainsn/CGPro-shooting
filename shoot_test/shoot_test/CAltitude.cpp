#include "CAltitude.h"

CAltitude::CAltitude(void)
{
    int width = MAP_SIZE;
    int height = MAP_SIZE;
    int channals = 1;
    g_HeightMap = SOIL_load_image("../images/terrain/heightmap.png",&width, &height, &channals, SOIL_LOAD_L);
    if (0 == g_HeightMap)
    {
        printf("SOIL loading error:'%s'\n", SOIL_last_result());
        exit(0);
    }
}

CAltitude::~CAltitude(void)
{
}

void CAltitude::RenderHeightMap(PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB, PFNGLACTIVETEXTUREARBPROC glActiveTextureARB, GLuint* heightMapTexture)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glTranslatef(0, 0, -3.0f);

    for (int x = 0; x < (MAP_SIZE - STEP_SIZE); x += STEP_SIZE)
        for (int y = 0; y < (MAP_SIZE - STEP_SIZE); y += STEP_SIZE)
        {
        float x_0 = float(x) / MAP_SIZE;
        float x_1 = float(x + STEP_SIZE) / MAP_SIZE;
        float y_0 = float(y) / MAP_SIZE;
        float y_1 = float(y + STEP_SIZE) / MAP_SIZE;

        glActiveTextureARB(GL_TEXTURE0_ARB);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, heightMapTexture[0]);//terrain.png

        glActiveTextureARB(GL_TEXTURE1_ARB);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, heightMapTexture[1]);//detail.bmp

        glBegin(GL_QUADS);
            //左上点
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x_0, y_0);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 0.0f);
		glVertex3i(x, Altitude(x, y), y);
            //左下点
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x_0, y_1);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 1.0f);
		glVertex3i(x, Altitude(x, y + STEP_SIZE), y + STEP_SIZE);
            //右下点
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x_1, y_1);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f, 1.0f);
		glVertex3i(x + STEP_SIZE, Altitude(x + STEP_SIZE, y + STEP_SIZE), y + STEP_SIZE);
            //右上点
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x_1, y_0);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f, 0.0f);
		glVertex3i(x + STEP_SIZE, Altitude(x + STEP_SIZE, y), y);
        glEnd();            
        }
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glDisable(GL_TEXTURE_2D);
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glPopMatrix();
}

int CAltitude::Altitude(int X, int Y)
{
    int x = X%MAP_SIZE;//error check our x value
    int y = Y%MAP_SIZE;//error check our y value

    x = x > 0?x : 0;
    y = y > 0 ? y : 0;

    return g_HeightMap[x + (y*MAP_SIZE)] / 2;//转换到一维数组返回高程
}

void CAltitude::SetVertexColor(int x, int y)
{
	glColor3f(0, 0, -0.15f + (Altitude(x, y) / 256.0f));
}