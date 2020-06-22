#pragma once
#include "AbstractBullet.h"
#include "AbstractWeapon.h"
#include "AbstractTarget.h"

#include "Cannonball.h"
#include "Target.h"

class FlyingObjects
{
public:
	FlyingObjects();
	~FlyingObjects();

public:
	void EraseAllData();

	void DrawFlyingObj();
	void UpdateFlyingObj(float dt);

	//Init
	void InitEffectBackCont(EffectsContainer* effContBack);
	void InitEffectFrontCont(EffectsContainer* effContFront);

	void InitBullet();
	void InitTarget(std::string targetTextID, int hp, float scale);
	void Init();

	//Get
	int GetNumDestroyedTargets();

private:
	void CheckCollision();
	void CheckTargetHit();

	float DistanceBetweenBalls(FPoint c1, FPoint c2);

	void InitEffect(EffectsContainer* _effCont, std::string nameEff, float x, float y);

	void RemoveCollision(AbstractTarget* targetI, AbstractTarget* targetJ, float radI, float radJ, float betweenBalls);

private:
	//-------------------------------------------

	float _hp1;
	float _hp2;

	float _scale1;
	float _scale2;

	float _switch;

	int _numTargets1;
	int _numTargets2;

	//-------------------------------------------

	int _numTargetsOnScr;
	int _targetsDestroyed;

	float _hitZone;

	std::vector<AbstractTarget*> _targets;		//вектор мишеней
	std::vector<AbstractBullet*> _bullets;		//вектор снарядов

	ParticleEffectPtr _effPointer;
	EffectsContainer* _effContFrontPointer;			//указатель на внешний контейнер с эффектами
	EffectsContainer* _effContBackPointer;			//указатель на внешний контейнер с эффектами
};

