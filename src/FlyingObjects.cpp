#include "stdafx.h"
#include "FlyingObjects.h"



FlyingObjects::FlyingObjects() :
	_numTargetsOnScr(0),

	_numTargets1(GameSettings::NUM_TARGETS1),
	_numTargets2(GameSettings::NUM_TARGETS2),

	_scale1(GameSettings::targetScale1),
	_scale2(GameSettings::targetScale2),

	_hp1(GameSettings::NUM_TARGETS1_HP),
	_hp2(GameSettings::NUM_TARGETS2_HP),

	_switch(0.f),

	_hitZone(0.9),
	_targetsDestroyed(0)
{
	_effContFrontPointer = NULL;
	_effContBackPointer = NULL;
}

FlyingObjects::~FlyingObjects()
{
}

void FlyingObjects::Init()
{
	_numTargetsOnScr = 0;

	_numTargets1 = GameSettings::NUM_TARGETS1;
	_numTargets2 = GameSettings::NUM_TARGETS2;

	_scale1 = GameSettings::targetScale1;
	_scale2 = GameSettings::targetScale2;

	_hp1 = GameSettings::NUM_TARGETS1_HP;
	_hp2 = GameSettings::NUM_TARGETS2_HP;

	_switch = 0.f;

	_hitZone = 0.9;
	_targetsDestroyed = 0;

	_switch = 1;
}

void FlyingObjects::UpdateFlyingObj(float dt)
{
	if (_numTargetsOnScr < GameSettings::NUM_TARGETS_ON_SCREEN && _numTargets1 > 0 && _numTargets2 > 0)
	{

		if (_switch == 1)
		{
			InitTarget("Target1", _hp1, _scale1);
			++_numTargetsOnScr;
			--_numTargets1;

			_switch = 2;
		}
		if (_switch == 2)
		{
			InitTarget("Target2" ,_hp2, _scale2);
			++_numTargetsOnScr;
			--_numTargets2;

			_switch = 1;
		}

	} 

	auto itTarget = _targets.begin();
	while (itTarget != _targets.end())
	{
		if ((*itTarget)->IsVisible())
		{
			(*itTarget)->Update(dt);
			itTarget++;
		}
		else
		{
			delete *itTarget;
			--_numTargetsOnScr;
			itTarget = _targets.erase(itTarget);
		}
	}
	

	auto itBullet = _bullets.begin();
	while (itBullet != _bullets.end())
	{
		if ((*itBullet)->IsVisible())
		{
			(*itBullet)->UpdatePos(dt);
			itBullet++;
		}
		else
		{
			delete *itBullet;
			itBullet = _bullets.erase(itBullet);
		}
	}

	CheckTargetHit();
	CheckCollision();
}

void FlyingObjects::DrawFlyingObj()
{
	for (auto i : _targets)
	{
		i->Draw();
	}

	for (auto i : _bullets)
	{
		i->Draw();
	}
}

void FlyingObjects::InitBullet()
{
	FPoint first;
	FPoint second;
	FPoint begin;

	first = Core::mainInput.GetMousePos();
	begin = GameSettings::cannonPos;
	second.y = GameSettings::cannonPos.y;
	second.x = GameSettings::WINDOW_WIDTH;

	float horizAngleDegr = Functions::GetAngleInDegrees(first, second, begin);

	FPoint pos;
	pos.x = GameSettings::cannonPos.x;
	pos.y = GameSettings::cannonPos.y;

	Cannonball* cb = new Cannonball("Cannonball");

	cb->Init(horizAngleDegr, pos);
	cb->InitEffect(_effContBackPointer);
	_bullets.push_back(cb);
}

void FlyingObjects::InitTarget(std::string targetTextID, int hp, float scale)
{
	Target *targ = new Target(targetTextID);

	targ->Init(hp, scale);
	_targets.push_back(targ);
}

void FlyingObjects::InitEffect(EffectsContainer* _effCont, std::string nameEff, float x, float y)
{
	_effPointer = (*_effCont).AddEffect(nameEff);
	_effPointer->posX = x;
	_effPointer->posY = y;
	_effPointer->Reset();
}

void FlyingObjects::CheckCollision()
{ 
	//в цикле чтобы решить все коллизии попарно
	int counter = 0;
	int numOfCollision;

	do
	{
		numOfCollision = 0;

		for (auto i = _targets.begin(); i < _targets.end(); i++)
		{
			for (auto j = _targets.begin(); j < _targets.end(); j++)
			{
				if (j != i)
				{
					FPoint posI = (*i)->GetPositionCoords();
					float rI = (*i)->GetRadius();

					FPoint posJ = (*j)->GetPositionCoords();
					float rJ = (*j)->GetRadius();

					float betweenBalls = DistanceBetweenBalls(posI, posJ);
					//float betweenBalls = sqrt(math::sqr(posI.x - posJ.x) + math::sqr(posI.y - posJ.y));

					if (betweenBalls <= (rI + rJ))
					{
						numOfCollision++;
						RemoveCollision(*i, *j, rI, rJ, betweenBalls);

						InitEffect(_effContFrontPointer, "TargetCollision", (posI.x + posJ.x) / 2, (posI.y + posJ.y) / 2);
					}
				}
			}
		}
		counter++;
	} while (counter < 3 && numOfCollision != 0);
}

void FlyingObjects::CheckTargetHit()
{
	for (auto bullet = _bullets.begin(); bullet < _bullets.end(); bullet++)
	{
		FPoint posBullet = (*bullet)->GetPositionCoords();
		float rB = (*bullet)->GetRadius();

		for (auto target = _targets.begin(); target < _targets.end(); target++)
		{
				FPoint posTarget = (*target)->GetPositionCoords();
				float rT = (*target)->GetRadius();

				float betweenBalls = DistanceBetweenBalls(posBullet, posTarget);
				//float betweenBalls = sqrt(math::sqr(posBullet.x - posTarget.x) + math::sqr(posBullet.y - posTarget.y));

				if (betweenBalls <= (rB + rT) * _hitZone)
				{
					
					(*bullet)->SetVisible(false);
					(*target)->ReduceHP((*bullet)->GetDamage());

					if ((*target)->CheckForDestruction())
					{
						(*target)->SetVisible(false);
						_targetsDestroyed++;
					}

					InitEffect(_effContFrontPointer, "Hit", (posTarget.x + posBullet.x)/2, (posTarget.y + posBullet.y)/2);

					return;
				}
		}
	}
}

float FlyingObjects::DistanceBetweenBalls(FPoint c1, FPoint c2)
{
	int x1 = c1.x;
	int x2 = c2.x;
	int y1 = c1.y;
	int y2 = c2.y;

	int x = abs(x1 - x2);
	int y = abs(y1 - y2);

	int min = x > y ? y : x;

	return (x + y - (min >> 1) - (min >> 2) + (min >> 4));
}

void FlyingObjects::InitEffectFrontCont(EffectsContainer* effContFront)
{
	_effContFrontPointer = effContFront;
}

void FlyingObjects::InitEffectBackCont(EffectsContainer * effContBack)
{
	_effContBackPointer = effContBack;
}

int FlyingObjects::GetNumDestroyedTargets()
{
	return _targetsDestroyed;
}

void FlyingObjects::RemoveCollision(AbstractTarget* targetI, AbstractTarget* targetJ, float radI, float radJ, float betweenBalls)
{
	// ---------- Первый вариант столкновения ---------- 

	//глубина кллизии
	float pushAway = ((radI + radJ) - betweenBalls) / 2 + (targetI->GetRadius() + targetJ->GetRadius()) * 0.01;

	FPoint posI = targetI->GetPositionCoords();
	FPoint posJ = targetJ->GetPositionCoords();

	//находим вектор между шарами и нормализуем его
	float betweenBallsX = posJ.x - posI.x;
	float betweenBallsY = posJ.y - posI.y;

	float lengh = sqrt(math::sqr(betweenBallsX) + math::sqr(betweenBallsY));

	math::Vector3 betweenBallsVec;
	betweenBallsVec.x = betweenBallsX / lengh;
	betweenBallsVec.y = betweenBallsY / lengh;

	math::Vector3 newDirectVec;

	//новое направление движения
	newDirectVec = targetI->GetDirectionVect() + -betweenBallsVec;
	newDirectVec.z = 0;
	newDirectVec.z = 0;
	
	targetI->SetDirectionVect(newDirectVec);

	newDirectVec = targetJ->GetDirectionVect() + betweenBallsVec;
	targetJ->SetDirectionVect(newDirectVec);

	//новые скорости
	float bufSpeed = targetI->GetSpeed();
	targetI->SetSpeed(targetJ->GetSpeed());
	targetJ->SetSpeed(bufSpeed);

	//передвигаем мишени
	targetI->ShiftTarget(pushAway);
	targetJ->ShiftTarget(pushAway);

}

void FlyingObjects::EraseAllData()
{
	auto itTarget = _targets.begin();
	while (itTarget != _targets.end())
	{
		delete *itTarget;
		itTarget = _targets.erase(itTarget);
	}

	auto itBullet = _bullets.begin();
	while (itBullet != _bullets.end())
	{
		delete *itBullet;
		itBullet = _bullets.erase(itBullet);
	}

	if (_effContFrontPointer != NULL)
	{
		_effContFrontPointer->KillAllEffects();
	}
	if (_effContBackPointer != NULL)
	{
		_effContBackPointer->KillAllEffects();
	}
}
