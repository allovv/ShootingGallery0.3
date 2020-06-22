#include "stdafx.h"
#include "Functions.h"

const float Functions::_pi(3.1415926535);
const float Functions::_radToDegrees(57.29577951);			//	180 / pi
const float Functions::_degrToRadians(0.01745329);			// pi / 180

Functions::Functions()
{
}


Functions::~Functions()
{
}

float Functions::GetAngleInRadians(FPoint first, FPoint second, FPoint begin)
{
	return Functions::GetAngleRadians(first, second, begin);
}

float Functions::GetAngleInDegrees(FPoint first, FPoint second, FPoint begin)
{
	return Functions::GetAngleRadians(first, second, begin) * _radToDegrees;
}

float Functions::GetVectorLen(FPoint first, FPoint second)
{
	return sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
}

float Functions::FastDistanceBetween(FPoint p1, FPoint p2)
{
	int x1 = p1.x;
	int x2 = p2.x;
	int y1 = p1.y;
	int y2 = p2.y;

	int x = abs(x1 - x2);
	int y = abs(y1 - y2);

	int min = x > y ? y : x;
	return (x + y - (min >> 1) - (min >> 2) + (min >> 4));
}

float Functions::GetAngleRadians(FPoint first, FPoint second, FPoint begin)
{
	math::Vector3 firstV;
	firstV.x = first.x - begin.x;
	firstV.y = first.y - begin.y;
	firstV.z = 0.0;

	math::Vector3 secondV;
	secondV.x = second.x - begin.x;
	secondV.y = second.y - begin.y;
	secondV.z = 0.0;

	if ((firstV.x == 0 && firstV.y == 0 && firstV.z == 0)
		|| (secondV.x == 0 && secondV.y == 0 && secondV.z == 0))
	{
		return 0;
	}
	else
	{
		float digit = (firstV.x * secondV.x + firstV.y * secondV.y + firstV.z * secondV.z)
			/ (sqrt(pow(firstV.x, 2) + pow(firstV.y, 2) + pow(firstV.z, 2)) * sqrt(pow(secondV.x, 2) + pow(secondV.y, 2) + pow(secondV.z, 2)));

		return acosf(digit);
	}
}

float Functions::ToRadians(float angle)
{
	return angle * _degrToRadians;
}

float Functions::ToDegrees(float angle)
{
	return angle * _radToDegrees;
}
