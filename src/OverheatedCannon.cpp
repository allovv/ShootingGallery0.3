#include "stdafx.h"
#include "OverheatedCannon.h"


OverheatedCannon::OverheatedCannon(std::string cannon, std::string cannonFront, std::string cannonPlatform, std::string aim):

	Cannon(cannon, cannonFront, cannonPlatform, aim), 

	_gunState(CANSHOOT),

	_timeAfterShot(0),
	_timeToCooling(2),

	_overheatingColor(255, 0, 0, 0),
	_gunOverheatingLimit(0.f),
	_heatingGun(0.f),

	_heatingDelta(0.f),
	_colorAlpha(0.f)
{
	_colorAlpha = 10;
	_heatingDelta = 30;
}

OverheatedCannon::~OverheatedCannon()
{
}

void OverheatedCannon::Update(float dt)
{
	CheckDelay(dt);

	//обновляем время, прошедшее после выстрела
	SpotTimeAfterShoot(dt);
}

void OverheatedCannon::DrawFront()
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

	Render::BeginColor(_overheatingColor);
	_cannonFrontTex->Draw();
	Render::EndColor();

	Render::device.PopMatrix();


	//информация о нагреве
	Render::BindFont("arial2.2");
	Render::PrintString(_initialPos.x + 80, 20.0, std::string("Overheating: ") + utils::lexical_cast(math::round(_heatingGun)), 1.0f, LeftAlign, BottomAlign);
}

void OverheatedCannon::DrawBack()
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

	//дополнительный цвет
	Render::BeginColor(_overheatingColor);
	_cannonTex->Draw();
	Render::EndColor();

	Render::device.PopMatrix();

	if (_gunState == COOLING)
	{
		Render::BindFont("arial3");
		Render::PrintString(GameSettings::WINDOW_WIDTH / 2, GameSettings::WINDOW_HEIGHT / 2, std::string("Cooling!!!"), 1.0f, CenterAlign, CenterAlign);
	}
}

bool OverheatedCannon::CheckShot()
{
	CheckForСooling();

	if (Core::mainInput.GetMouseLeftButton() && _gunState == CANSHOOT && _numBullets != 0)
	{
		CheckForOverheating();

		if (_heatingGun < _gunOverheatingLimit)
		{
			_gunState = DELAY;
			_timeAfterShot = 0;

			_runAnimation = true;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void OverheatedCannon::Init(int num, FPoint iPos, EffectsContainer * _effContPtr)
{
	_effContPointer = _effContPtr;

	_numBullets = num;
	_initialPos = iPos;
	_angleDegr = 0;
	_scale = GameSettings::gunScale;
	_standScale = _scale;

	_gunOverheatingLimit = GameSettings::gunOverheatingLim;
	_timeAfterShot = 0;

	_heatingGun = 0;
	_overheatingColor.alpha = 0;

	_timer = 0;
	_timeAfterShot = 0;
}

void OverheatedCannon::SpotTimeAfterShoot(float dt)
{
	_timeAfterShot += dt;
	if (_timeAfterShot > 60)
	{
		_timeAfterShot = 30;
	}
}

void OverheatedCannon::CheckForOverheating()
{
	if (_timeAfterShot < GameSettings::delayOfShoots + _timeToCooling && _heatingGun < _gunOverheatingLimit)
	{
		_heatingGun += _heatingDelta;
		if (_overheatingColor.alpha < 255 - _colorAlpha) {
			_overheatingColor.alpha += _colorAlpha;
		}
		else
		{
			_overheatingColor.alpha  = 255;
		}
	}
	else
	{
		InitEffect(_effContPointer, "Overheating");
		_gunState = COOLING;
	}
}

void OverheatedCannon::CheckForСooling()
{
	if (_timeAfterShot > 2 * GameSettings::delayOfShoots)
	{
		if (_heatingGun > 0)
		{
			_heatingGun -= _heatingDelta / 10;
		}
		else
		{
			_heatingGun = 0;
		}

		if (_overheatingColor.alpha > 0)
		{
			_overheatingColor.alpha -= _colorAlpha / 10;
		}
		else
		{
			_overheatingColor.alpha = 0;
		}

		if (_heatingGun < 0)
		{
			_heatingGun = 0;
		}
	}

	if (_gunState == COOLING)
	{
		if (_heatingGun > 0)
		{
			_heatingGun -= _heatingDelta / 10;
		}
		else
		{
			_heatingGun = 0;
		}

		if (_overheatingColor.alpha > 0)
		{
			_overheatingColor.alpha -= _colorAlpha / 10;
		}
		else
		{
			_overheatingColor.alpha = 0;
		}

		if (_heatingGun < _gunOverheatingLimit * 0.7)
		{
			_gunState = CANSHOOT;
		}
	}
}

void OverheatedCannon::CheckDelay(float dt)
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
