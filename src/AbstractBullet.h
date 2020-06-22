#pragma once
#include "GameSettings.h"

#include "Functions.h"

class AbstractBullet
{
public:
	AbstractBullet();
	~AbstractBullet();

public:
	virtual void Draw() = 0;
	virtual void UpdatePos(float dt) = 0;
	virtual void SetVisible(bool visible);

	bool IsVisible();

	//Get
	float GetDamage();
	float GetRadius();
	FPoint GetPositionCoords();

protected:
	void ReverseX();
	void ReverseY();

	void MoveBullet(float dt);

	//Init
	void InitMotionVector(float angleDegr, float speed);
	void InitFirstPosVec(float x, float y, float z);

protected:
	math::Vector3 _speedV;
	math::Vector3 _flPosV;
	math::Vector3 _initPosV;					//����� ������� ������
	math::Vector3 _directionV;

	float _scale;
	float _radius;
	bool _visible;								//� ���� ������ ��� ���

	float _g;									//�����
	float _speed;								//�������� ������ �������

	float _time;								//�����, ��������� � ������ ������ (������ �������� ����� ��� ������� ������ �������)

	float _damage;
};

