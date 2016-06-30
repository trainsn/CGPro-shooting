#pragma once

#include "Defines.h"
#include "CAltitude.h"
#include "CTimer.h"
#include "CCamera.h"


class CTimer;
class CCamera;	
class CAltitude;

class CGame
{
public:
	CGame(void);
	~CGame(void);
	
	// 游戏控制输入
		void handleInput();
		void keyboardInput();

	// 高程图-移动值
		int getHMTrans(float x, float y);

	// 游戏状态机函数
		void setState(int newState);	
		void setGameOver();

	// 游戏图
		void setText(int time, GLuint mask, GLuint text);
		bool displayText();

	// 游戏变量
		int				currentState;		// 游戏状态机函数
		bool			CharacterWinLose;	// 判断是否已经赢了
		int				CharacterHealth;	// 玩家的生命值
		bool			CharacterType;		// 玩家人物
		int				numEnemiesKilled;	// 已经打死了多少敌人
		bool			gameOver;			// 游戏是否已经结束
		bool			rickroll_Mode;		// this should be self-explanatory.
		volatile int	shoot_time;			// how many Gldraws a shot lasts

	// Text showing
		volatile int	text_time; //same thing for test
		GLuint			t_mask;
		GLuint			t_text;
	
	// Global game classes
		CTimer*			timer;	// Timer class
		CCamera*		camera;	// Camera	
		CAltitude*		theMap;	// Height map
};
