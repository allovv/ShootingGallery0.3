#include "stdafx.h"
#include "AbstractTarget.h"


AbstractTarget::AbstractTarget() :
	_hp(0), 
	_scale(0.f), 
	_visible(false), 
	_radius(0.f),
	_color{ 0, 0, 0, 0 }
{
	_speedV.x = 0;
	_speedV.y = 0;
	_speedV.z = 0;

	_positionV.x = 0;
	_positionV.y = 0;
	_positionV.z = 0;
}

AbstractTarget::~AbstractTarget()
{
}


void AbstractTarget::MoveTarget(float dt)
{
	_positionV += _speedV * dt;
	CheckScreenBorderCollision();
}


bool AbstractTarget::IsVisible()
{
	return _visible;
}

void AbstractTarget::ReduceHP(float damage)
{
	_hp -= damage;
}

bool AbstractTarget::CheckForDestruction()
{
	return _hp <= 0;
}

void AbstractTarget::ShiftTarget(float len)
{
	math::Vector3 normalSpeedV = NormalizeVec(_speedV);
	_positionV.x += normalSpeedV.x * len;
	_positionV.y += normalSpeedV.y * len;
}

float AbstractTarget::GetRadius()
{
	return _radius;
}

FPoint AbstractTarget::GetPositionCoords()
{
	FPoint pos;
	pos.x = _positionV.x;
	pos.y = _positionV.y;

	return pos;
}

math::Vector3 AbstractTarget::GetSpeedVect()
{
	return _speedV;
}

math::Vector3 AbstractTarget::GetDirectionVect()
{
	return _directionV;
}

float AbstractTarget::GetSpeed()
{
	return _speed;
}

float AbstractTarget::GetHP()
{
	return _hp;
}

void AbstractTarget::SetHP(float hp)
{
	_hp = hp;
}

void AbstractTarget::SetSpeed(float speed)
{
	_speedV.x = (_speedV.x / _speed) * speed;
	_speedV.y = (_speedV.y / _speed) * speed;
	_speed = speed;
}


void AbstractTarget::SetSpeedVect(math::Vector3 speedVect)
{
	_speedV = speedVect;
	_directionV = NormalizeVec(speedVect);
}

void AbstractTarget::SetDirectionVect(math::Vector3 dirVect)
{
	_directionV = NormalizeVec(dirVect);
	_speedV = _directionV * _speed;
}

void AbstractTarget::SetColor(Color color)
{
	_color = color;
}

void AbstractTarget::SetVisible(bool visible)
{
	_visible = visible;
}

void AbstractTarget::CheckScreenBorderCollision()
{
	if (_positionV.x - _radius <= GameSettings::spawnTargLeftBorger && _speedV.x < 0)
	{
		ReverseX();
	}
	else if (_positionV.x + _radius >= GameSettings::spawnTargRightBorger && _speedV.x > 0)
	{
		ReverseX();
	}
	
	if (_positionV.y - _radius <= GameSettings::spawnTargDownBorger && _speedV.y < 0)
	{
		ReverseY();
	}
	else if (_positionV.y + _radius >= GameSettings::spawnTargTopBorger && _speedV.y > 0)
	{
		ReverseY();
	}
}


void AbstractTarget::InitMotionVector(float angleDegr, float speed)
{
	_speed = speed;
	 
	_directionV.x = cosf(Functions::ToRadians(angleDegr));
	_directionV.y = sinf(Functions::ToRadians(angleDegr));
	_directionV.z = 0;

	_speedV = _directionV * speed;
}

void AbstractTarget::InitPositionVec(float x, float y, float z)
{
	_positionV.x = x;
	_positionV.y = y;
	_positionV.z = z;
}

void AbstractTarget::ReverseX()
{
	_speedV.x = -_speedV.x;
	_directionV.x = -_directionV.x;
}

void AbstractTarget::ReverseY()
{
	_speedV.y = -_speedV.y;
	_directionV.y = -_directionV.y;
}

math::Vector3 AbstractTarget::NormalizeVec(math::Vector3 vec)
{
	math::Vector3 normVect = vec;

	float vectorLen = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	normVect.x /= vectorLen;
	normVect.y /= vectorLen;
	normVect.z /= vectorLen;

	return normVect;
}
