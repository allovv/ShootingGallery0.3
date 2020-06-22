#pragma once
#include "GameSettings.h"
#include "Cannon.h"

class OverheatedCannon : public Cannon
{
public:
	//OverheatedCannon();
	~OverheatedCannon();
	OverheatedCannon(std::string cannon, std::string cannonFront, std::string cannonPlatform, std::string aim);

public:
	void DrawBack() override;
	void DrawFront() override;
	void Update(float dt) override;

	bool CheckShot() override;

	void Init(int num, FPoint iPos, EffectsContainer* _effContPtr);

private:
	void CheckFor—ooling();
	void CheckForOverheating();

	void CheckDelay(float dt);

	void SpotTimeAfterShoot(float dt);
	
private:
	enum GunStates {
		CANSHOOT,
		DELAY,
		COOLING
	};
	GunStates _gunState;

private:
	float _timeAfterShot;
	float _timeToCooling;

	float _colorAlpha;
	float _heatingDelta;

	float _heatingGun;
	float _gunOverheatingLimit;

	Color _overheatingColor;
};

