#include "CGame.h"

CGame::CGame(void)
{
	timer				= new CTimer();
	camera				= new CCamera();
	theMap				= new CAltitude();
	
	
	// 初始化游戏状态，任务状态和照相机
	currentState		= GAMESTATE_LOADING; //游戏状态见Defines.h 
	gameOver			= false;
	rickroll_Mode		= false;
	
	shoot_time			= 0;
	CharacterHealth		= 100;
	CharacterType		= PIRATE;
	numEnemiesKilled	= 0;
	CharacterWinLose	= YOU_LOSE;

	camera->Position_Camera(0.0f, getHMTrans(0, 0) + 70.0f, 0.0f,	
						    0.0f, getHMTrans(0, 0) + 70.0f, -1.0f,
							0.0f, 1.0f, 0.0f);
}

CGame::~CGame(void)
{
	delete timer;
	delete camera;
	delete theMap;
}

void CGame::setState(int newState)
{
	currentState = newState;
}

void CGame::setGameOver()
{

	if ( CharacterHealth <= 0 )
	{
		gameOver = true;
		CharacterWinLose = YOU_LOSE;
		setState(GAMESTATE_END);
	}
	else if (numEnemiesKilled >= MAX_ENEMIES)
	{
		gameOver = true;
		CharacterWinLose = YOU_WIN;
		setState(GAMESTATE_END);
	}
}

int CGame::getHMTrans(float x, float y)
{
	return theMap->Altitude(x + int(MAP_SIZE / 2), y + int(MAP_SIZE / 2)) - HM_DISPLACEMENT - 20;
}

void CGame::handleInput()
{
	keyboardInput();
	camera->Mouse_Move(640,480);
}

void CGame::keyboardInput()
{
	if((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80))
		camera->Move_Camera( CAMERASPEED, theMap);

	if((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80))
		camera->Move_Camera(-CAMERASPEED, theMap);

	if((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80))
		camera->Strafe_Camera(-CAMERASPEED, theMap);

	if((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80))
		camera->Strafe_Camera( CAMERASPEED, theMap);
}

void CGame::setText(int time, GLuint mask, GLuint text) {

	text_time = time;
	t_mask = mask;
	t_text = text;

}

bool CGame::displayText() {

	if (text_time > 0) {
		text_time--;
		return true;
	}

	return false;

}