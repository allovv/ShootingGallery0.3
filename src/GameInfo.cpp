#include "stdafx.h"
#include "GameInfo.h"


SingletonGameInfo::GameInfo::GameInfo()
{
	_gameTime = 0;
	_numBullets = 0;
	_numDestroyedTargets = 0;

	_startBackTex = "StartScreen";
	_gameBackTex = "";
	_endBackTex = "";
}


SingletonGameInfo::GameInfo::~GameInfo()
{
}

SingletonGameInfo::GameInfo & SingletonGameInfo::GameInfo::getInstance()
{
	//статическа€ переменна€ дл€ класса
	//инициализаци€ объекта info происходит один раз дл€ всех экземпл€ров класса
	static GameInfo info;
	return info;
}

void SingletonGameInfo::GameInfo::ChooseBackground()
{
	int background = 1 + rand() % (4 - 1);

	switch (background)
	{
	case 1:
	{
		_gameBackTex = "Background1";
		_endBackTex = "EndGame1";
		break;
	}

	case 2:
	{
		_gameBackTex = "Background2";
		_endBackTex = "EndGame2";
		break;
	}

	case 3:
	{
		_gameBackTex = "Background3";
		_endBackTex = "EndGame3";
		break;
	}

	default:
	{
		_gameBackTex = "Background1";
		_endBackTex = "EndGame1";
		break;
	}

	}
}

//-------------------------------------

float & SingletonGameInfo::GameInfo::getTime()
{
	return _gameTime;
}

int & SingletonGameInfo::GameInfo::getNumBullets()
{
	return _numBullets;
}

int & SingletonGameInfo::GameInfo::getNumTargets()
{
	return _numDestroyedTargets;
}

std::string & SingletonGameInfo::GameInfo::getStartTex()
{
	return _startBackTex;
}

std::string & SingletonGameInfo::GameInfo::getGameTex()
{
	return _gameBackTex;
}

std::string & SingletonGameInfo::GameInfo::getEndTex()
{
	return _endBackTex;
}

//-------------------------------------

void SingletonGameInfo::GameInfo::setTime(float time)
{
	_gameTime = time;
}

void SingletonGameInfo::GameInfo::setNumBullets(int numBullets)
{
	_numBullets = numBullets;
}

void SingletonGameInfo::GameInfo::setNumTargets(int destrTarg)
{
	_numDestroyedTargets = destrTarg;
}

void SingletonGameInfo::GameInfo::setStartTex(std::string startTex)
{
	_startBackTex = startTex;
}

void SingletonGameInfo::GameInfo::setGameTex(std::string gameTex)
{
	_gameBackTex = gameTex;
}

void SingletonGameInfo::GameInfo::setEndTex(std::string endTex)
{
	_endBackTex = endTex;
}