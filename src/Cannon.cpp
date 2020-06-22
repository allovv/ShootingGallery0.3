#include "stdafx.h"
#include "Cannon.h"
#include "Cannonball.h"

Cannon::Cannon(std::string cannon, std::string cannonFront, std::string cannonPlatform, std::string aim) :
	_gunState(CANSHOOT),

	_deltaScale(0.f),
	_runAnimation(false),

	_standScale(0.f)
{
	_timer = 0;

	_cannonTex = Core::resourceManager.Get<Render::Texture>(cannon);
	_cannonFrontTex = Core::resourceManager.Get<Render::Texture>(cannonFront);
	_cannonPlatformTex = Core::resourceManager.Get<Render::Texture>(cannonPlatform);
	_aimTex = Core::resourceManager.Get<Render::Texture>(aim);
}

Cannon::~Cannon()
{
}

void Cannon::Init(int num, FPoint iPos, EffectsContainer* _effContPtr)
{
	_effContPointer = _effContPtr;

	_numBullets = num;
	_initialPos = iPos;
	_angleDegr = 0;
	_scale = GameSettings::gunScale;
	_standScale = _scale;

	_timer = 0;
}

void Cannon::Update(float dt)
{
	CheckDelay(dt);
}

void Cannon::DrawBack()
{
	//отрисовываем платформу
	float platH = (_cannonTex->Height()) * (_standScale + 0.05) / 1.5;
	float platW = (_cannonPlatformTex->Width()) * (_standScale + 0.1) / 2;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_initialPos.x - platW, _initialPos.y - platH, 0);
	Render::device.MatrixScale(_standScale + 0.1);
	_cannonPlatformTex->Draw();
	Render::device.PopMatrix();

	//отрисовываем пушку
	_angleDegr = Cannon::GetVerticalAngleInDegr();
	float cannonH = (_cannonTex->Height()) * _scale / 2;
	float cannonW = (_cannonTex->Width()) * _scale / 2;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_initialPos.x - cannonW, _initialPos.y - cannonH, 0);

	Render::device.MatrixTranslate(+cannonW, +cannonH, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angleDegr);
	Render::device.MatrixTranslate(-cannonW, -cannonH, 0);
	
	Render::device.MatrixScale(_scale);
	_cannonTex->Draw();
	Render::device.PopMatrix();
}


void Cannon::DrawFront()
{
	//отрисовываем переднюю текстуру пушки
	_angleDegr = Cannon::GetVerticalAngleInDegr();
	float cannonH = (_cannonFrontTex->Height()) * _scale / 2;
	float cannonW = (_cannonFrontTex->Width()) * _scale / 2;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_initialPos.x - cannonW, _initialPos.y - cannonH, 0);

	Render::device.MatrixTranslate(+cannonW, +cannonH, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angleDegr);
	Render::device.MatrixTranslate(-cannonW, -cannonH, 0);

	Render::device.MatrixScale(_scale);
	_cannonFrontTex->Draw();

	Render::device.PopMatrix();
}

void Cannon::DrawAim()
{
	//отрисовывем прицел
	FPoint mousePos = Core::mainInput.GetMousePos();
	float aimH = (_aimTex->Height()) * _scale / 2;
	float aimW = (_aimTex->Width()) * _scale / 2;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(mousePos.x - aimW, mousePos.y - aimH, 0);
	Render::device.MatrixScale(_scale);
	_aimTex->Draw();
	Render::device.PopMatrix();
}

void Cannon::CheckDelay(float dt)
{
	if (_timer < GameSettings::delayOfShoots && _gunState == DELAY)
	{
		_timer += dt;
	}
	else if (_timer > GameSettings::delayOfShoots && _gunState == DELAY)
	{
		_timer = 0;
		_gunState = CANSHOOT;
	}
}

bool Cannon::CheckShot()
{
	if (Core::mainInput.GetMouseLeftButton() && _gunState == CANSHOOT && _numBullets != 0)
	{
		_gunState = DELAY;

		_runAnimation = true;

		return true;
	}
	else
	{
		return false;
	}
}

int Cannon::GetGunState()
{
	return _gunState;
}

void Cannon::InitEffect(EffectsContainer * _effContPointer, std::string nameEff)
{
	_effPointer = (*_effContPointer).AddEffect(nameEff);
	_effPointer->posX = _initialPos.x;
	_effPointer->posY = _initialPos.y;
	_effPointer->Reset();
}

void Cannon::ShotEffect(float dt)
{
	if (_runAnimation)
	{
		_deltaScale += dt * 20;

		if (_deltaScale <= math::PI)
		{
			if (_deltaScale < math::PI / 2)
			{
				_scale += sinf(_deltaScale) / 100;
			}
			else
			{
				_scale -= sinf(_deltaScale) / 100;
			}
		}
		else
		{
			_scale = GameSettings::gunScale;
			_runAnimation = false;
			_deltaScale = 0;
		}
	}
}
