/*Model.h
    Abstract base class for a model. The specific extended calss will render the given model.
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
    //Mesh 网格
    struct Mesh
    {
        int m_materialIndex;//材质索引，-1为没有材质
        int m_numTriangles;//网格中的三角形数目  
        int *m_pTriangleIndices;//三角形索引
    };

    //材质与贴图
    struct Material
    {
        //分别为环境光，漫射光，反射光，自发光
        float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
        float m_shininess;//发光值，冯模型中的N值
        GLuint m_texture;
        char *m_pTextureFilename;//贴图文件名
    };

    //三角形
    struct Triangle
    {
        float m_vertexNormals[3][3];//三个顶点的法线
        float m_s[3], m_t[3];//存储三个点的纹理坐标
        int m_vertexIndices[3];//顶点索引
    };

    //点
    struct Vertex
    {
        char m_boneID;//该顶点所绑定的骨骼的ID号，如果该值为-1，则代表没有绑定任何骨骼
        float m_location[3];//顶点的坐标
    };

    //关键帧，表示某一帧时某个骨骼的旋转帧数据或平移帧数据
    struct Keyframe
    {
        int m_jointIndex;
        float m_time;   //毫秒级，表示这一帧所处的时间
        float m_parameter[3];//用一个三维向量来表示旋转或平移。如果表示平移，那么三个值分别是X,Y,Z轴上的平移值；如果表示旋转，那么三个值表示旋转的欧拉角
    };

    //关节
    struct Joint
    {
        float m_localRotation[3];//初始旋转
        float m_localTranslation[3];//初始平移
        Matrix m_absolute, m_relative;//绝对矩阵与相对矩阵

        //本骨骼的旋转帧数量和平移帧数量
        int m_numRotationKeyframes,m_numTranslationKeyframes;
        Keyframe *m_pTranslationKeyframes;//本骨骼的所有旋转帧数据
        Keyframe *m_pRotationKeyframes;//本骨骼的所有平移帧数据
        
        //可以看做临时变量
        int m_currentTranslationKeyframe, m_currentRotationKeyframe;
        Matrix m_final;

        int m_parent;//本骨骼的父骨骼
    };

public :
    Model();

    virtual ~Model();

    virtual bool loadModelData(const char *filename) = 0;

    void draw();

    /*Called if OpenGL context was lost and we need to reload textures, display lists
    将纹路载入内存*/
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
    /*
    Set the values of a particular keyframe for a particular joint.
    jointIndex		The joint to setup the keyframe for
    keyframeIndex	The maximum number of keyframes
    time			The time in milliseconds of the keyframe
    parameter		The rotation/translation values for the keyframe
    isRotation		Whether it is a rotation or a translation keyframe
    */
    void setJointKeyframe(int jointIndex, int keyframeIndex, float time, float *parameter, bool isRotation);

    /*Setup joint matrices. 初始化骨骼与绑定节点*/
    void setupJoints();

    /*Setup looping factor for animation*/
    void setLooping(bool looping){
        m_looping = looping;
    }

    /*Advance animation by a frame.根据动画的关键帧，以正确的顺序遍历所有节点，并且根据前一个节点变换后的矩阵乘以此节点对前一个节点的相对变化，那么可以刷新所有骨骼的位置*/
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

