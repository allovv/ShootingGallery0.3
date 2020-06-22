#pragma once
#include "GameSettings.h"
#include "Functions.h"

#include "AbstractBullet.h"


class AbstractWeapon
{
public:
	AbstractWeapon();
	~AbstractWeapon();

public:
	virtual void DrawBack() = 0;
	virtual void DrawFront() = 0;
	virtual bool CheckShot() = 0;
	virtual void Update(float dt) = 0;

	int GetNumBullets();
	void IncNumBullets();
	void DecNumBullets();

protected:
	float GetVerticalAngleInDegr();

protected:
	float _timer;			//регулирование частоты выстрелов

	float _scale;
	float _angleDegr;

	int _numBullets;
	FPoint _initialPos;			
};

