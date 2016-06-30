#pragma once 

#define		CAMERASPEED			0.025f			// 相机速度
#define		MAP_SIZE			1024
#define		STEP_SIZE			16				// 控制高程图的分辨率 
#define		HM_DISPLACEMENT		10				// 人物必须要放置在高于高程图一个值才能比较好的显示
#define		NUM_TREES			10
#define		TREE_DRAW_DIST		100000

#define		SHOT_STEP			0.4
#define		SHOOT_TIME			150
#define		CROSS_RADIUS		15

#define		TEXT_TIME			40

#define		MAX_ENEMIES			5				
#define		CH					3				// 包围盒在z方向缩放的倍数

#define		NO_ANIMATION		-1
#define		NO_LOOP				0
#define		LOOP				1

#define		STAR_DRAW_AFTER		2*SHOT_STEP

#define		DEST_RADIUS			20				// 用于判断NPC是否到达了他的目标点，然后我们就要换目标了
#define		ATTACK_RADIUS		40				// 用于判断NPC是否到达了攻击区域
#define		ATTACK_TIME			1000			// 攻击时间间隔，砍两刀之间总有个时间差

// 状态（用于读取骨骼动画数据）
enum {NINJA_WALKING, NINJA_ATTACK, NINJA_DEAD, NINJA_IDLE};

// For some reason this isn't defined anywhere else, needed to make texture borders disappear.
#ifndef		GL_CLAMP_TO_EDGE
#define		GL_CLAMP_TO_EDGE        0x812F
#endif

//游戏状态机
enum {GAMESTATE_LOADING, GAMESTATE_SPLASH_START, GAMESTATE_SPLASH_ABOUT, GAMESTATE_SPLASH_EXIT, GAMESTATE_ABOUT, GAMESTATE_SELECT_NINJA, 
	  GAMESTATE_SELECT_PIRATE, GAMESTATE_PLAY, GAMESTATE_DEBUG, GAMESTATE_END}; 
enum {YOU_LOSE, YOU_WIN};

// 人物状态（用于游戏中判断人怎么走）
enum {PIRATE, NINJA};
enum {WANDER, DEFENSIVE, AGGRESSIVE, DEAD}; 
