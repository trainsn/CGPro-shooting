/*
	Model.cpp

		Abstract base class for a model. The specific extended class will render the given model. 

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://rsn.gamedev.net
	Copyright (C)2001, Brett Porter. All Rights Reserved.

	This file may be used only as long as this copyright notice remains intact.
*/

//#include <windows.h>

#include "Model.h"

Model::Model()
{
	m_numMeshes = 0;
	m_pMeshes = NULL;
	m_numMaterials = 0;
	m_pMaterials = NULL;
	m_numTriangles = 0;
	m_pTriangles = NULL;
	m_numVertices = 0;
	m_pVertices = NULL;
	// { NEW } 
	m_numJoints = 0;
	m_pJoints = NULL;

	m_pTimer = Timer::getNewTimer();
	m_looping = true;

	state = 0;
	num_states = 0;
	suit = 0;

	visible = 0;

	restart();
	// { end NEW } 
}

Model::~Model()
{
	int i;
	for ( i = 0; i < m_numMeshes; i++ )
		delete[] m_pMeshes[i].m_pTriangleIndices;
	for ( i = 0; i < m_numMaterials; i++ )
		delete[] m_pMaterials[i].m_pTextureFilename;

	m_numMeshes = 0;
	if ( m_pMeshes != NULL )
	{
		delete[] m_pMeshes;
		m_pMeshes = NULL;
	}

	m_numMaterials = 0;
	if ( m_pMaterials != NULL )
	{
		delete[] m_pMaterials;
		m_pMaterials = NULL;
	}

	m_numTriangles = 0;
	if ( m_pTriangles != NULL )
	{
		delete[] m_pTriangles;
		m_pTriangles = NULL;
	}

	m_numVertices = 0;
	if ( m_pVertices != NULL )
	{
		delete[] m_pVertices;
		m_pVertices = NULL;
	}

	// { NEW }
	for ( i = 0; i < m_numJoints; i++ )
	{
		delete[] m_pJoints[i].m_pRotationKeyframes;
		delete[] m_pJoints[i].m_pTranslationKeyframes;
	}

	m_numJoints = 0;
	if ( m_pJoints != NULL )
	{
		delete[] m_pJoints;
		m_pJoints = NULL;
	}

	delete[] m_pTimer;
	// { end NEW }
}

void Model::draw() 
{
	if ( !noAnimation() )
		advanceAnimation();
	GLboolean texEnabled = glIsEnabled( GL_TEXTURE_2D );

	// Draw by group 遍历所有组
	for ( int i = 0; i < m_numMeshes; i++ )
	{
		int materialIndex = m_pMeshes[i].m_materialIndex+suit;
		if ( materialIndex >= 0 )
		{
			glMaterialfv( GL_FRONT, GL_AMBIENT, m_pMaterials[materialIndex].m_ambient );
			glMaterialfv( GL_FRONT, GL_DIFFUSE, m_pMaterials[materialIndex].m_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, m_pMaterials[materialIndex].m_specular );
			glMaterialfv( GL_FRONT, GL_EMISSION, m_pMaterials[materialIndex].m_emissive );
			glMaterialf( GL_FRONT, GL_SHININESS, m_pMaterials[materialIndex].m_shininess );

			if ( m_pMaterials[materialIndex].m_texture > 0 )
			{
				glBindTexture( GL_TEXTURE_2D, m_pMaterials[materialIndex].m_texture );
				glEnable( GL_TEXTURE_2D );
			}
			else
				glDisable( GL_TEXTURE_2D );
		}
		else
		{
			// Material properties?
			glDisable( GL_TEXTURE_2D );
		}

        glBegin( GL_TRIANGLES );
		{
            //遍历所有的三角形
   			for ( int j = 0; j < m_pMeshes[i].m_numTriangles; j++ )
			{
				int triangleIndex = m_pMeshes[i].m_pTriangleIndices[j];
				const Triangle* pTri = &m_pTriangles[triangleIndex];

				for ( int k = 0; k < 3; k++ )
				{
					int index = pTri->m_vertexIndices[k];

					// { NEW }
					if ( m_pVertices[index].m_boneID == -1 )
					{
						// same as before
						glTexCoord2f( pTri->m_s[k], pTri->m_t[k] );
						glNormal3fv( pTri->m_vertexNormals[k] );
						glVertex3fv( m_pVertices[index].m_location );
					}
					else
					{
						// rotate according to transformation matrix
						const Matrix& final = m_pJoints[m_pVertices[index].m_boneID].m_final;

						glTexCoord2f( pTri->m_s[k], pTri->m_t[k] );

						Vector newNormal( pTri->m_vertexNormals[k] );
						newNormal.transform3( final );
						newNormal.normalize();
						glNormal3fv( newNormal.getVector());

						Vector newVertex( m_pVertices[index].m_location );
						newVertex.transform( final );
						glVertex3fv( newVertex.getVector());
					}
					// { end NEW }
				}
			}
		}
		glEnd();
	}

	if ( texEnabled )
		glEnable( GL_TEXTURE_2D );
	else
		glDisable( GL_TEXTURE_2D );
}

void Model::reloadTextures()
{
	for ( int i = 0; i < m_numMaterials; i++ )
		if ( strlen( m_pMaterials[i].m_pTextureFilename ) > 0 )
			m_pMaterials[i].m_texture = SOIL_load_OGL_texture
	(
		m_pMaterials[i].m_pTextureFilename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
	);
		else
			m_pMaterials[i].m_texture = 0;
}

// { NEW }
void Model::setJointKeyframe( int jointIndex, int keyframeIndex, float time, float *parameter, bool isRotation )
{
	assert( m_numJoints > jointIndex );

	Keyframe& keyframe = isRotation ? m_pJoints[jointIndex].m_pRotationKeyframes[keyframeIndex] :
		m_pJoints[jointIndex].m_pTranslationKeyframes[keyframeIndex];

	keyframe.m_jointIndex = jointIndex;
	keyframe.m_time = time;
	memcpy( keyframe.m_parameter, parameter, sizeof( float )*3 );
}

void Model::setupJoints()
{
	int i;
	//设置新的关节的绝对矩阵
	for ( i = 0; i < m_numJoints; i++ )
	{
		Joint& joint = m_pJoints[i];

		joint.m_relative.setRotationRadians( joint.m_localRotation );
		joint.m_relative.setTranslation( joint.m_localTranslation );
		if ( joint.m_parent != -1 )//判断是不是根节点
		{
			//如果不是根节点，那么将上个点的绝对矩阵乘这个点的变换矩阵
            joint.m_absolute.set( m_pJoints[joint.m_parent].m_absolute.getMatrix());
			joint.m_absolute.postMultiply( joint.m_relative );//用relative右乘原来的矩阵得到最终的矩阵
		}
		else
            //否则根关节的绝对矩阵就是它的相对变换矩阵
			joint.m_absolute.set( joint.m_relative.getMatrix());
	}

    for ( i = 0; i < m_numVertices; i++ )
	{
		Vertex& vertex = m_pVertices[i];

		if ( vertex.m_boneID != -1 )
		{
			//获得某一个骨骼的绝对矩阵
            const Matrix& matrix = m_pJoints[vertex.m_boneID].m_absolute;

			//获得一个点相对于其对应骨骼的坐标
			matrix.inverseTranslateVect( vertex.m_location );
			matrix.inverseRotateVect( vertex.m_location );
		}
	}

    //法线的变换是通过法线所在的三角形找到对应的顶点索引，再通过顶点里的骨骼信息找到那根跟随的骨骼；由于法线是单位向量，所以只需要进行旋转变换即可
    for (i = 0; i < m_numTriangles; i++) {
        Triangle& triangle = m_pTriangles[i];
        for (int j = 0; j < 3; j++) {
			const Vertex& vertex = m_pVertices[triangle.m_vertexIndices[j]];
			if ( vertex.m_boneID != -1 ) {
				const Matrix& matrix = m_pJoints[vertex.m_boneID].m_absolute;
				matrix.inverseRotateVect( triangle.m_vertexNormals[j] );
			}
		}
	}
}

void Model::restart()
{
	for ( int i = 0; i < m_numJoints; i++ )
	{
		m_pJoints[i].m_currentRotationKeyframe = m_pJoints[i].m_currentTranslationKeyframe = 0;
		m_pJoints[i].m_final.set( m_pJoints[i].m_absolute.getMatrix());
	}

	m_pTimer->reset();
}

void Model::advanceAnimation()
{

	int s = states[state][0];
	int e = states[state][1];
	int loop = states[state][2];

	double time = m_pTimer->getTime() + ((double)s*1000.0/FPS);

	if ( time > (double)e*1000.0/FPS) 
	{
		if (loop == LOOP) {
			restart();
			time = (double)s*1000.0/FPS;
		}
		else
			return;
	} 

	for ( int i = 0; i < m_numJoints; i++ )//遍历所有节点
	{
		float transVec[3];
		Matrix transform;//建立一个缓存用的相对变换矩阵
		int frame;
		Joint *pJoint = &m_pJoints[i];

		if ( pJoint->m_numRotationKeyframes == 0 && pJoint->m_numTranslationKeyframes == 0 )
		{
			//如果这个模型的转动帧和移动帧为0，那么直接把骨骼的绝对矩阵复制到最终变换矩阵里。continue调过后面的骨骼刷新
            pJoint->m_final.set( pJoint->m_absolute.getMatrix());
			continue;
		}

		//识取关键帧，计算中间差值。通过计算两个关键帧直接的时间差和变化差之间的干系，求出该时刻的转动和移动程度是多少
        frame = pJoint->m_currentTranslationKeyframe;
		while ( frame < pJoint->m_numTranslationKeyframes && pJoint->m_pTranslationKeyframes[frame].m_time < time )
		{
			frame++;//不断循环找到现在所在关键帧的位置
		}
		pJoint->m_currentTranslationKeyframe = frame;

		if ( frame == 0 )//如果是第一帧那么保持标准姿势不变
			memcpy( transVec, pJoint->m_pTranslationKeyframes[0].m_parameter, sizeof ( float )*3 );
		else if ( frame == pJoint->m_numTranslationKeyframes )//如果是最后一帧，减一，此步骤防止程序指针越界
			memcpy( transVec, pJoint->m_pTranslationKeyframes[frame-1].m_parameter, sizeof ( float )*3 );
		else
		{
			//如果现在帧在两个关键帧之间开始刷新骨骼动画
            assert( frame > 0 && frame < pJoint->m_numTranslationKeyframes );

			const Model::Keyframe& curFrame = pJoint->m_pTranslationKeyframes[frame];
			const Model::Keyframe& prevFrame = pJoint->m_pTranslationKeyframes[frame-1];

			float timeDelta = curFrame.m_time-prevFrame.m_time;
			float interpValue = ( float )(( time-prevFrame.m_time )/timeDelta );

			//保存三个方向的变化值
            transVec[0] = prevFrame.m_parameter[0]+( curFrame.m_parameter[0]-prevFrame.m_parameter[0] )*interpValue;
			transVec[1] = prevFrame.m_parameter[1]+( curFrame.m_parameter[1]-prevFrame.m_parameter[1] )*interpValue;
			transVec[2] = prevFrame.m_parameter[2]+( curFrame.m_parameter[2]-prevFrame.m_parameter[2] )*interpValue; 
		}

		//以下步骤同上是求旋转的变换
        frame = pJoint->m_currentRotationKeyframe;
		while ( frame < pJoint->m_numRotationKeyframes && pJoint->m_pRotationKeyframes[frame].m_time < time )
		{
			frame++;
		}
		pJoint->m_currentRotationKeyframe = frame;

		if ( frame == 0 )
			transform.setRotationRadians( pJoint->m_pRotationKeyframes[0].m_parameter );
		else if ( frame == pJoint->m_numRotationKeyframes )
			transform.setRotationRadians( pJoint->m_pRotationKeyframes[frame-1].m_parameter );
		else
		{
			assert( frame > 0 && frame < pJoint->m_numRotationKeyframes );

			const Model::Keyframe& curFrame = pJoint->m_pRotationKeyframes[frame];
			const Model::Keyframe& prevFrame = pJoint->m_pRotationKeyframes[frame-1];
			
			float timeDelta = curFrame.m_time-prevFrame.m_time;
			float interpValue = ( float )(( time-prevFrame.m_time )/timeDelta );

			assert( interpValue >= 0 && interpValue <= 1 );

#if 0
			Quaternion qPrev( prevFrame.m_parameter );
			Quaternion qCur( curFrame.m_parameter );
			Quaternion qFinal( qPrev, qCur, interpValue );
			transform.setRotationQuaternion( qFinal );
#else
			float rotVec[3];

			rotVec[0] = prevFrame.m_parameter[0]+( curFrame.m_parameter[0]-prevFrame.m_parameter[0] )*interpValue;
			rotVec[1] = prevFrame.m_parameter[1]+( curFrame.m_parameter[1]-prevFrame.m_parameter[1] )*interpValue;
			rotVec[2] = prevFrame.m_parameter[2]+( curFrame.m_parameter[2]-prevFrame.m_parameter[2] )*interpValue;
            //保存三个旋转变换

			transform.setRotationRadians( rotVec );
#endif
		}

		transform.setTranslation( transVec );
        //以上两个步骤是将旋转变换和平移变换放置到keyFrameMatrix

        //设置一个缓存用的最终变换矩阵
		Matrix relativeFinal( pJoint->m_relative );
        //通过矩阵乘法将前面求的相对变换矩阵和此时动画的变化矩阵累积，成为最终的相对变换矩阵
		relativeFinal.postMultiply( transform );

		//这时要判断如果是第一个节点那么最终变换矩阵就是他的最终的相对变换矩阵        
        if ( pJoint->m_parent == -1 )
			pJoint->m_final.set( relativeFinal.getMatrix());
		else
		{
			//如果不是根节点那么他的最终的相对变换矩阵乘以父节点的最终变换矩阵就可以得到此节点的最终变换矩阵，原理和前面设置节点的步骤一样
            pJoint->m_final.set( m_pJoints[pJoint->m_parent].m_final.getMatrix());
			pJoint->m_final.postMultiply( relativeFinal );
		}
	}
}


void Model::setState(int newState)
{
	if ( newState != state ) 
	{
		state = newState; 
		restart(); 
	}
};
