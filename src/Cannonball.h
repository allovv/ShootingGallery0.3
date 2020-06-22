#pragma once
#include "GameSettings.h"

#include "AbstractBullet.h"

#include "Functions.h"

class Cannonball : public AbstractBullet
{
public:
	//Cannonball();
	~Cannonball();
	Cannonball(std::string cannonball);

public:
	void Draw() override;
	void UpdatePos(float dt) override;
	void SetVisible(bool visible) override;

	void UpdateEffect();
	void ÑompleteEffect();
	void InitEffect(EffectsContainer* _effContPointer);
	void Init(float horizAnglDegr, FPoint pos);

private:
	ParticleEffectPtr _effPointer;

	Render::Texture* _cannonBallTex;
};

