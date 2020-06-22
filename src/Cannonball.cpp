#include "stdafx.h"
#include "Cannonball.h"


Cannonball::Cannonball(std::string cannonball)
{
	_cannonBallTex = Core::resourceManager.Get<Render::Texture>(cannonball);
}

Cannonball::~Cannonball()
{
}

void Cannonball::Init(float horizAnglDegr, FPoint pos)
{
	_damage = GameSettings::bulletGamage;
	_time = 0;

	_visible = true;
	_scale = GameSettings::bulletScale;

	_speed = GameSettings::bulletSpeed;
	_g = GameSettings::bulletG;

	_radius = _cannonBallTex->Width() * _scale / 2;

	InitFirstPosVec(pos.x, pos.y, 0);
	InitMotionVector(horizAnglDegr, _speed);
}

void Cannonball::UpdatePos(float dt)
{
	if ((0 <= _flPosV.x && _flPosV.x <= GameSettings::WINDOW_WIDTH) && -_radius <= _flPosV.y)
	{
		MoveBullet(dt * 2);

		UpdateEffect();
	}
	else if (0 >= _flPosV.x - _radius || _flPosV.x + _radius >= GameSettings::WINDOW_WIDTH)
	{
		ReverseX();
		MoveBullet(dt * 2);
	}
	else
	{
		SetVisible(false);
	}

}

void Cannonball::Draw()
{
	if (_visible)
	{
		float cbH = (_cannonBallTex->Height()) * _scale / 2;
		float cbW = (_cannonBallTex->Width()) * _scale / 2;

		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_flPosV.x - cbW, _flPosV.y - cbH, 0);
		Render::device.MatrixScale(_scale);
		_cannonBallTex->Draw();
		Render::device.PopMatrix();
	}
}

void Cannonball::SetVisible(bool visible)
{
	_visible = visible;
	if (!_visible)
	{
		ÑompleteEffect();
	}
}

void Cannonball::InitEffect(EffectsContainer* _effContPointer)
{
	_effPointer = (*_effContPointer).AddEffect("BallEffect");
	_effPointer->posX = _flPosV.x - 5.f;
	_effPointer->posY = _flPosV.y - 5.f;
	_effPointer->Reset();
}

void Cannonball::UpdateEffect()
{
	if (_effPointer)
	{
		_effPointer->posX = _flPosV.x - 5.f;
		_effPointer->posY = _flPosV.y - 5.f;
	}
}

void Cannonball::ÑompleteEffect()
{
	if (_effPointer)
	{
		_effPointer->Finish();
		_effPointer = NULL;
		_effPointer = NULL;
	}
}
