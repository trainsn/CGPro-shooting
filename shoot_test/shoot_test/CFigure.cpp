#include "CFigure.h"

#include <fstream>

using namespace std;

CFigure::CFigure(const char* filename, CGame* game, int suit, float x_i, float y_i)
{
	cGame = game;

	x = x_i;
	y = y_i;

	cModel = new Milkshape();
	if ( cModel->loadModelData( filename ) == false )
	{
		MessageBox( NULL, "Couldn't load the model", "Error", MB_OK | MB_ICONERROR );
		exit(0);
	}

	if (cGame->CharacterType == PIRATE) {

		cModel->setSuite(suit);
		cModel->addState(1, 14, LOOP);			// NINJA_WALKING
		cModel->addState(45,59,LOOP);			// NINJA_ATTACK
		cModel->addState(166, 173, NO_LOOP);	// NINJA_DEAD
		cModel->addState(184,205, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true); // 如果visible为true，那么我们将会进行碰撞检测

		cBehavior	= AGGRESSIVE;
		cType		= NINJA;

	}
	else {

		cModel->setSuite(0);
		cModel->addState(2, 14, LOOP);			// NINJA_WALKING
		cModel->addState(112, 126,LOOP);		// NINJA_ATTACK
		cModel->addState(230, 251, NO_LOOP);	// NINJA_DEAD
		cModel->addState(292, 325, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true);  // 如果visible为true，那么我们将会进行碰撞检测

		cBehavior	= AGGRESSIVE;
		cType		= PIRATE;

	}

	currentPosition[0] = x;
	currentPosition[2] = y;
	currentPosition[1] = cGame->getHMTrans(x,y)+10;
	setNewEndPosition();

	attackTime = (float)cGame->timer->getTicks_mS();
}

CFigure::~CFigure(void)
{
	delete cModel;
}

void CFigure::Draw()
{
	// 根据人物在干什么，选择正确的绘制方式
	switch(cBehavior)
	{
		case WANDER:
			wander();
			break;
		case AGGRESSIVE:
			attack();
			break;
		case DEFENSIVE:
			defend();
			break;
		case DEAD:
			//do nothing
			break;
		default:
			break;
	}

	// 正式绘制
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(currentPosition[0], currentPosition[1], currentPosition[2]);
	glRotatef(rotation, 0,1,0);

	//矮人模型比忍者模型要大，这很奇怪，所以要通过缩放变小
	if (cGame->CharacterType == NINJA)
		glScalef(0.18, 0.2, 0.18);

	//碰撞检测之前必须要做这部分的工作，把包围盒矩阵从模型坐标系转换到视图坐标系
	//当然需要在之前所有转换都完成之后才能够拿出矩阵来
	cModel->updateTransfMatrix();

	//debugging purposes
	/*cModel->drawBoundingBox();*/
	cModel->draw();

	glPopMatrix();
}

void CFigure::die()
{
	cModel->setState(NINJA_DEAD);
	cModel->setVisible(false);
	cBehavior = DEAD;
	cGame->numEnemiesKilled++;
}


void CFigure::wander()
{
	cModel->setState(NINJA_WALKING);

	lastPosition = currentPosition;		// 保存需要到达的位置
	
	// 判断是否已经到达目标点
	Vec3d check = endPosition - currentPosition;
	if ( check.length() < DEST_RADIUS )
		setNewEndPosition();	// 更新目标点
	
	Vec3d delta = endPosition - startPosition;
	delta.normalize();
	float t = ((float)cGame->timer->getTicks_mS() - startTime)/80.0;
	
	currentPosition = startPosition + delta * t;
	currentPosition[1] = cGame->getHMTrans((float)currentPosition[0],(float)currentPosition[2])+9;
	
	Vec3d newDirection = (currentPosition - lastPosition);
	newDirection.normalize();

	if ( newDirection[2] >= 0 )
		rotation = -90 - 180 / PI * acosf( (float)newDirection[0] );
	else
		rotation = -90 + 180 / PI * acosf( (float)newDirection[0] );
}

void CFigure::attack()
{
	Vec3d cameraPosition = Vec3d(cGame->camera->mPos.x, cGame->getHMTrans(cGame->camera->mPos.x,cGame->camera->mPos.z) + 10, cGame->camera->mPos.z);
	Vec3d check = currentPosition - cameraPosition;
	double checkLength = check.length();
	if ( checkLength < ATTACK_RADIUS )
	{	
		defend();
	}
	else
		wander();
}

void CFigure::defend()
{
	Vec3d cameraPosition = Vec3d(cGame->camera->mPos.x, cGame->getHMTrans(cGame->camera->mPos.x,cGame->camera->mPos.z) + 10, cGame->camera->mPos.z);

	// 判断是否已经到达攻击范围
	Vec3d check = currentPosition - cameraPosition;
	double checkLength = check.length();
	if ( checkLength < ATTACK_RADIUS )
	{	
		cModel->setState(NINJA_ATTACK);
		if ( cGame->timer->getTicks_mS() - attackTime > ATTACK_TIME )
		{			
			cGame->CharacterHealth -= 10;	//攻击成功，健康值减10
			attackTime = (float)cGame->timer->getTicks_mS();
		}
	}
	else
		cModel->setState(NINJA_IDLE);
	
	// 要让忍者面对任务视角
	Vec3d newDirection = (currentPosition - cameraPosition);
	newDirection.normalize();

	if ( newDirection[2] >= 0 )
		rotation = 90 - 180 / PI * acosf( (float)newDirection[0] );
	else
		rotation = 90 + 180 / PI * acosf( (float)newDirection[0] );

}

void CFigure::setNewEndPosition()
{
	if ( cGame->CharacterType == PIRATE )
	{
		endPosition[0] = 200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[2] = 200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[1] = cGame->getHMTrans((float)endPosition[0],(float)endPosition[2]) + 10;
	}
	else
	{
		endPosition[0] = -200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[2] = -200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[1] = cGame->getHMTrans((float)endPosition[0],(float)endPosition[2]) + 10;
	}
	startPosition = currentPosition;
	startTime = (float)cGame->timer->getTicks_mS();
}