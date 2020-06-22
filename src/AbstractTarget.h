#pragma once
#include "GameSettings.h"
#include "Functions.h"

class AbstractTarget
{
public:
	AbstractTarget();
	~AbstractTarget();

public:
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void SetVisible(bool visible);

	void MoveTarget(float dt);
	void ShiftTarget(float len);

	bool IsVisible();

	void ReduceHP(float damage);
	bool CheckForDestruction();

	//Get
	float GetHP();
	float GetRadius();
	float GetSpeed();
	FPoint GetPositionCoords();
	math::Vector3 GetSpeedVect();
	math::Vector3 GetDirectionVect();

	//Set
	void SetHP(float hp);
	void SetSpeed(float speed);
	void SetSpeedVect(math::Vector3 speedVect);
	void SetDirectionVect(math::Vector3 dirVect);

	void SetColor(Color color);

protected:
	void ReverseX();
	void ReverseY();

	void CheckScreenBorderCollision();

	math::Vector3 NormalizeVec(math::Vector3 vec);

	//Init
	void InitPositionVec(float x, float y, float z);
	void InitMotionVector(float angleDegr, float speed);

protected:
	int _hp;
	float _scale;
	bool _visible;

	float _speed;
	float _radius;

	Color _color;

	Render::Texture* _targetTex;

	math::Vector3 _speedV;
	math::Vector3 _positionV;
	math::Vector3 _directionV;
};

