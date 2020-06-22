#pragma once
class GameSettings
{
public:
	GameSettings();
	~GameSettings();

public:
	static const float matchTime;

	//-------------------------------------

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;

	//-------------------------------------

	static const int NUM_BULLETS = 1000;
	static const float bulletScale;

	static const int bulletSpeed = 500;
	static const int bulletGamage = 50;
	static const int bulletG = 7;

	//-------------------------------------

	static const float targetScale1;
	static const float targetScale2;

	static const int NUM_TARGETS1_HP = 50;
	static const int NUM_TARGETS2_HP = 100;

	static const int NUM_TARGETS1 = 30;
	static const int NUM_TARGETS2 = 50;

	static const int NUM_TARGETS_ON_SCREEN = 12;

	//-------------------------------------

	static const FPoint cannonPos;
	static const float gunScale;


	//-------------------------------------

	static const float delayOfShoots;
	static const int gunOverheatingLim = 400;

	//-------------------------------------

	static const int spawnTargTopBorger = WINDOW_HEIGHT;
	static const int spawnTargDownBorger = WINDOW_HEIGHT / 4;
	static const int spawnTargLeftBorger = 0;
	static const int spawnTargRightBorger = WINDOW_WIDTH;

	//-------------------------------------

	static const float buttonScale;

private:
	static const int cannonPX = WINDOW_WIDTH / 2;
	static const int cannonPY = 70;
};

