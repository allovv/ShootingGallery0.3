#pragma once
#include "GameSettings.h"

#include "AbstractTarget.h"

class Target : public AbstractTarget
{
public:
	//Target();
	~Target();
	Target(std::string target);

public:
	void Draw() override;
	void Update(float dt) override;
	void Init(int hp, float scale);

	void DistortionTexture();

private:
	float _dx, _dy;
	Distortion d;
};

