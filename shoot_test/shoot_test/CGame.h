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
	
	// Game handle input
		void handleInput(bool fullscreen);
		void keyboardInput();

	// Game heightmap - get translation
		int getHMTrans(float x, float y);

	// Game state machine functions
		void setState(int newState);	
		void setGameOver();

	//in game text
		void setText(int time, GLuint mask, GLuint text);
		bool displayText();

	// Game variables
		int				currentState;		// Game state machine variable
		bool			CharacterWinLose;	// keep track of whether we've won yet.
		int				CharacterHealth;	// keep track of player health.
		bool			CharacterType;		// keep track of whether we're a pirate or ninja.
		int				numEnemiesKilled;	// keep track of how many enemies we've killed to decide if we've met the win condition.
		bool			gameOver;			// keep track of whether the game is over.
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
