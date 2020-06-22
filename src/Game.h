#pragma once
#include "GameSettings.h"

#include "AbstractBullet.h"
#include "AbstractWeapon.h"
#include "AbstractTarget.h"

#include "Cannon.h"
#include "Cannonball.h"
#include "Target.h"
#include "FlyingObjects.h"
#include "OverheatedCannon.h"

#include "GameInfo.cpp"

class Game
{
enum GameStates {
	PAUSE,
	STARTSCREEN,
	GAMEPLAY,
	ENDGAME,
	CLOSE,
	SETTINGS
};

public:
	Game();
	~Game();

public:
	void Draw();
	void Init();
	void Update(float dt);

private:
	void DrawInfo();

public:
	//Game objects
	OverheatedCannon _cannon;
	FlyingObjects _flyingObj;

private:
	float _scale;
	float _clockTimer;

	int _shootSample;

	//Effects
	EffectsContainer _effContBack;
	EffectsContainer _effContFront;
	ParticleEffectPtr _eff;

	//Textures
	//------------------------------------------

	Render::Texture* _clockTex;
	Render::Texture* _nameplateTex;

	Render::Texture* _backgroundTex;

	//------------------------------------------
};

