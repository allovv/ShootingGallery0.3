#pragma once
class Functions
{
public:
	Functions();
	~Functions();

public:
	//получить угол между двумя векторами в градусах
	static float ToRadians(float angle);
	static float ToDegrees(float angle);

	static float GetVectorLen(FPoint first, FPoint second);

	static float FastDistanceBetween(FPoint p1, FPoint p2);

	static float GetAngleInRadians(FPoint first, FPoint second, FPoint begin);
	static float GetAngleInDegrees(FPoint first, FPoint second, FPoint begin);

private:
	static float GetAngleRadians(FPoint first, FPoint second, FPoint begin);

public:
	static const float _pi;
	static const float _radToDegrees;
	static const float _degrToRadians;
};

