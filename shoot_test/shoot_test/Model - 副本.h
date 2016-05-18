/*Model.h
    class for a model.
*/
#ifndef MODEL_H
#define MODEL_H


#include "matrix.h"
#include "CTimer.h"
#include "Defines.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <gl/GL.h>
#include <GL/GLU.h>

#include<assert.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Vector.h"
#include "SOIL.h"

#pragma comment(lib,"opengl32.lib");
#pragma  comment(lib,"glu32.lib");
#pragma  comment(lib,"glaux.lib");

#define  MAX_STATES 20

class Model
{
public :
    struct Mesh
    {
        int m_materialIndex;
        int m_numTriangles;
        int *m_pTriangleIndices;
    };

    struct Material
    {
        float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
        float m_shininess;
        GLuint m_texture;
        char *m_pTextureFilename;
    };

    struct Triangle
    {
        float m_vertexNormals[3][3];
        float m_s[3], m_t[3];
        int m_vertexIndices[3];
    };

    struct Vertex
    {
        char m_boneID;
        float m_location[3];
    };

    struct Keyframe
    {
        int m_jointIndex;
        float m_time;
        float m_parameter[3];
    };

    struct Joint
    {
        float m_localRotation[3];
        float m_localTranslation[3];
        Matrix m_absolute, m_relative;

        int m_numRotationKeyframes,m_numTranslationKeyframes;
        Keyframe *m_pTranslationKeyframes;
        Keyframe *m_pRotationKeyframes;
        
        int m_currentTranslationKeyframe, m_currentRotationKeyframe;
        Matrix m_final;

        int m_parent;
    };

public :
    Model();

    virtual ~Model();

    virtual bool loadModelData(const char *filename) = 0;

    void draw();

    void reloadTextures();

    void setState(int newState);

    void addState(int start, int length, int loop)
    {
        states[num_states][0] = start;
        states[num_states][1] = length;
        states[num_states][2] = loop;
        num_states++;
    };
    void setSuite(int newSuit)
    {
        suit = newSuit;
    };

    int getSuite()
    {
        return suit;
    };
    
    bool noAnimation()
    {
        return state == NO_ANIMATION;
    };
    void setVisible(bool visibility)
    {
        visible = visibility;
    };
    bool getVisible()
    {
        return visible;
    }

protected:
    void setJointKeyframe(int jointIndex, int keyframeIndex, float time, float *parameter, bool isRotation);

    void setupJoints();

    void setLooping(bool looping){
        m_looping = looping;
    }

    void advanceAnimation();

    void restart();

protected:
    //Meshes used
    int m_numMeshes;
    Mesh *m_pMeshes;
    
    //Materials used
    int m_numMaterials;
    Material *m_pMaterials;

    //Triangles used
    int m_numTriangles;
    Triangle *m_pTriangles;

    //Vertices used
    int m_numVertices;
    Vertex *m_pVertices;

    //Joints used
    int m_numJoints;
    Joint *m_pJoints;

    Timer *m_pTimer;

    double m_totalTime;

    bool m_looping;

    //current state of model
    int state;

    //number of states
    int num_states;

    //state description
    int states[MAX_STATES][3];//start of animation and length of animation

    //suit :)
    int suit;

    float FPS;

    bool visible;
       
};

#endif // ndef MODEL_H

