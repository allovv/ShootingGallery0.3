#include "stdafx.h"
#include "AbstractBullet.h"


bool AbstractBullet::IsVisible()
{
	return _visible;
}

void AbstractBullet::SetVisible(bool visible)
{
	_visible = visible;
}

float AbstractBullet::GetDamage()
{
	return _damage;
}

float AbstractBullet::GetRadius()
{
	return _radius;
}

FPoint AbstractBullet::GetPositionCoords()
{
	FPoint pos;
	pos.x = _flPosV.x;
	pos.y = _flPosV.y;

	return pos;
}

AbstractBullet::AbstractBullet() :
	_scale(0.f), 
	_visible(false),
	_g(0.f),
	_speed(0.f),
	_time(0.f),
	_radius(0.f),
	_damage(0.f)
{
	_initPosV.x = 0;
	_initPosV.y = 0;
	_initPosV.z = 0;

	_flPosV.x = 0;
	_flPosV.y = 0;
	_flPosV.z = 0;
}

AbstractBullet::~AbstractBullet()
{
}

void AbstractBullet::MoveBullet(float dt)
{
	_flPosV.x += _speedV.x * dt;
	_flPosV.y += _speedV.y * dt - _g * _time * _time / 2;

	_time += dt;
}


void AbstractBullet::InitMotionVector(float angleDegr, float speed)
{
	_speed = speed;

	//значение угла должно быть в радианах
	_directionV.x = cosf(Functions::ToRadians(angleDegr));
	_directionV.y = sinf(Functions::ToRadians(angleDegr));
	_directionV.z = 0;

	_speedV = _directionV * speed;
}

void AbstractBullet::InitFirstPosVec(float x, float y, float z)
{
	_initPosV.x = x;
	_initPosV.y = y;
	_initPosV.z = z;

	_flPosV = _initPosV;
}

void AbstractBullet::ReverseX()
{
	_speedV.x = -_speedV.x;
	_directionV.x = -_directionV.x;
}

void AbstractBullet::ReverseY()
{
	_speedV.y = -_speedV.y;
	_directionV.y = -_directionV.y;

}
