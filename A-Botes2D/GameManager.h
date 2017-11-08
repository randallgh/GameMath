#pragma once


enum PROGRAM_STATE
{
	_GAME_,
	_EDITOR_,
	_MAINMENU_
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	PROGRAM_STATE pState = PROGRAM_STATE::_EDITOR_;
};

