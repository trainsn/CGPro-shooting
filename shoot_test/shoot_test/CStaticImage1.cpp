#include "CStaticImage.h"

CStaticImages::CStaticImages(CGame* game, int width, int height)
{
    cGame = game;
    w = width;
    h = height;
}
CStaticImages::~CStaticImages(void)
{

}

void CStaticImages::loadSkyBoxTexture()
{
    skybox[0] = SOIL_load_OGL_texture
        (
        "../images/texture/reef_west.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
        );

    skybox[1] = SOIL_load_OGL_texture
        (
        "../images/texture/reef_east.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
        );

    skybox[2] = SOIL_load_OGL_texture
        (
        "../images/texture/reef_north.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
        );

    skybox[3] = SOIL_load_OGL_texture
        (
        "../images/texture/reef_south.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
        );

    skybox[4] = SOIL_load_OGL_texture
        (
        "../images/texture/reef_up.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
        );

    skybox[5] = SOIL_load_OGL_texture
        (
        "../images/texture/reef_down.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
        );
}

void CStaticImages::loadStaticTexture()
{
    statics[2] = SOIL_load_OGL_texture
        (
        "../images/static/hand1_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    statics[3] = SOIL_load_OGL_texture
        (
        "../images/static/hand1_image.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    statics[4] = SOIL_load_OGL_texture
        (
        "../images/static/hand2_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    statics[5] = SOIL_load_OGL_texture
        (
        "../images/static/hand2_image.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    statics[6] = SOIL_load_OGL_texture
        (
        "../images/static/stereo_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    statics[7] = SOIL_load_OGL_texture
        (
        "../images/static/stereo_img.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    statics[8] = SOIL_load_OGL_texture
        (
        "../images/static/headshot_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    statics[9] = SOIL_load_OGL_texture
        (
        "../images/static/headshot.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );



    splash[0] = SOIL_load_OGL_texture
        (
        "../images/static/splash_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    splash[1] = SOIL_load_OGL_texture
        (
        "../images/static/splash_start.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    splash[2] = SOIL_load_OGL_texture
        (
        "../images/static/splash_about.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    splash[3] = SOIL_load_OGL_texture
        (
        "../images/static/splash_exit.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );


    selectClass[0] = SOIL_load_OGL_texture
        (
        "../images/static/select_pirate.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    selectClass[1] = SOIL_load_OGL_texture
        (
        "../images/static/select_ninja.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    about[0] = SOIL_load_OGL_texture
        (
        "../images/static/aboutscreen_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );
    about[1] = SOIL_load_OGL_texture
        (
        "../images/static/aboutscreen.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    health[0] = SOIL_load_OGL_texture
        (
        "../images/static/health_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    health[1] = SOIL_load_OGL_texture
        (
        "../images/static/health_low.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    health[2] = SOIL_load_OGL_texture
        (
        "../images/static/health_high.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );
    health[3] = SOIL_load_OGL_texture
        (
        "../images/static/health_man_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );
    health[4] = SOIL_load_OGL_texture
        (
        "../images/static/health_man.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    gun[0] = SOIL_load_OGL_texture
        (
        "../images/static/gun_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    gun[1] = SOIL_load_OGL_texture
        (
        "../images/static/gun.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );
    gun[2] = SOIL_load_OGL_texture
        (
        "../images/static/gunfiring_mask.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );
    gun[3] = SOIL_load_OGL_texture
        (
        "../images/static/gunfiring.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

    endGame[0] = SOIL_load_OGL_texture
        (
        "../images/static/youwin.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );
    endGame[1] = SOIL_load_OGL_texture
        (
        "../images/static/youlose.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );
}

void CStaticImages::drawStatic(GLuint mask, GLuint image)
{
    glMatrixMode()
}