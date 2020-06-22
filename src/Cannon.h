#pragma once
#include "GameSettings.h"

#include "AbstractWeapon.h"
#include "AbstractBullet.h"

#include "Functions.h"

class Cannon : public AbstractWeapon
{
public:
	//Cannon();
	~Cannon();
	Cannon(std::string cannon, std::string cannonFront, std::string cannonPlatform, std::string aim);

public:
	void DrawBack() override;
	void DrawFront() override;
	bool CheckShot() override; 
	void Update(float dt) override;

	void DrawAim();

	int GetGunState();

	void ShotEffect(float dt);
	void InitEffect(EffectsContainer* _effContPointer, std::string nameEf);

	void Init(int num, FPoint iPos, EffectsContainer* _effContPtr);

private:
	void CheckDelay(float dt);

private:
	enum GunStates {
		DELAY,
		CANSHOOT
	};
	GunStates _gunState;

protected:
	float _standScale;

	float _deltaScale;
	bool _runAnimation;

	Render::Texture* _cannonTex;
	Render::Texture* _cannonFrontTex;
	Render::Texture* _cannonPlatformTex;

	Render::Texture* _aimTex;

	ParticleEffectPtr _effPointer;
	EffectsContainer* _effContPointer;			//указатель на внешний контейнер с эффектами
};

