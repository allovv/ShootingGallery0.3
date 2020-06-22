#include "stdafx.h"
#include "AbstractWeapon.h"


AbstractWeapon::AbstractWeapon() :
	_numBullets(0),
	_scale(0.f),
	_timer(0.f),
	_angleDegr(0.f)
{
	_initialPos.x = 0;
	_initialPos.y = 0;
}

AbstractWeapon::~AbstractWeapon()
{
}


void AbstractWeapon::IncNumBullets()
{
	++_numBullets;
}
void AbstractWeapon::DecNumBullets()
{
	--_numBullets;
}

int AbstractWeapon::GetNumBullets()
{
	return _numBullets;
}

//угол от ветикали в градусах
float AbstractWeapon::GetVerticalAngleInDegr()
{
	FPoint mousePos = Core::mainInput.GetMousePos();
	float _angle;

	math::Vector3 first;
	first.x = _initialPos.x - _initialPos.x;
	first.y = mousePos.y - _initialPos.y;
	first.z = 0.0;

	math::Vector3 second;
	second.x = mousePos.x - _initialPos.x;
	second.y = mousePos.y - _initialPos.y;
	second.z = 0.0;

	if ((first.x == 0 && first.y == 0 && first.z == 0)
			|| (second.x == 0 && second.y == 0 && second.z == 0))
	{
		return 0;
	}
	else
	{
		float digit = (first.x * second.x + first.y * second.y + first.z * second.z)
			/ (sqrt(pow(first.x, 2) + pow(first.y, 2) + pow(first.z, 2)) * sqrt(pow(second.x, 2) + pow(second.y, 2) + pow(second.z, 2)));

		_angle = acosf(digit) * Functions::_radToDegrees;

		if (mousePos.x > _initialPos.x)
		{
			_angle = -_angle;
		}

		return _angle;
	}
}
