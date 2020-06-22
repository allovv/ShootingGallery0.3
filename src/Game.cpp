#include "stdafx.h"
#include "Game.h"


//Game основной класс программы

Game::Game() :
	_scale(0.1),
	_clockTimer(0.f),

	_cannon("Cannon", "CannonFront", "CannonPlatform", "Aim")

{
	Init();
}

Game::~Game()
{
}


void Game::Init()
{
	_nameplateTex = Core::resourceManager.Get<Render::Texture>("Nameplate");

	//»гровое окно
	_clockTex = Core::resourceManager.Get<Render::Texture>("Clock");

	//Ёкраны
	_backgroundTex = Core::resourceManager.Get<Render::Texture>(SingletonGameInfo::GameInfo::getInstance().getGameTex());

	//инициализаци€ объектов
	_cannon.Init(GameSettings::NUM_BULLETS, GameSettings::cannonPos, &_effContFront);


	_flyingObj.EraseAllData();

	_flyingObj.InitEffectBackCont(&_effContBack);
	_flyingObj.InitEffectFrontCont(&_effContFront);

	_flyingObj.Init();
}

void Game::Update(float dt)
{
	_effContBack.Update(dt);
	_effContFront.Update(dt);

	_flyingObj.UpdateFlyingObj(dt);
	_cannon.Update(dt);

	_cannon.ShotEffect(dt);
	if (_cannon.CheckShot())
	{
		_flyingObj.InitBullet();
		_cannon.DecNumBullets();

		int sample = MM::manager.PlaySample("Shoot");
		MM::manager.SetVolume(sample, 0.1);
	}


	_clockTimer += dt * 4;
	while (_clockTimer > 2 * math::PI)
	{
		_clockTimer -= 2 * math::PI;
	}
	_scale = 0.8f + 0.15f * sinf(_clockTimer);
}

void Game::Draw()
{
	_backgroundTex->Draw();

	_effContBack.Draw();

	_cannon.DrawBack();

	//отрисовываем все эффекты

	_flyingObj.DrawFlyingObj();
	_cannon.DrawAim();
	_cannon.DrawFront();

	_effContFront.Draw();

	DrawInfo();
}


void Game::DrawInfo()
{
	float shift = 20;
	float H = _nameplateTex->Height() * 0.5;
	float W = _nameplateTex->Width() * 0.5;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(shift, GameSettings::WINDOW_HEIGHT - H - shift, 0);
	Render::device.MatrixScale(0.5);
	_nameplateTex->Draw();
	Render::device.PopMatrix();

	float clockH = _clockTex->Height();
	float clockW = _clockTex->Width();

	H = _clockTex->Height() * _scale / 2;
	W = _clockTex->Width() * _scale / 2;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(shift + (_nameplateTex->Width() >> 1) * 0.5 - W, GameSettings::WINDOW_HEIGHT - _nameplateTex->Height() * 0.5 - clockW / 2 - H, 0);
	Render::device.MatrixScale(_scale);
	_clockTex->Draw();
	Render::device.PopMatrix();
}

