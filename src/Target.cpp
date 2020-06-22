#include "stdafx.h"
#include "Target.h"


Target::Target(std::string target) :
	d(5, 5)
{
	_targetTex = Core::resourceManager.Get<Render::Texture>(target);
	_dx = 0; 
	_dy = 0;
}


Target::~Target()
{
}

void Target::Draw()
{
	if (_visible)
	{
		float cbH = (_targetTex->Height()) * _scale / 2;
		float cbW = (_targetTex->Width()) * _scale / 2;

		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_positionV.x - cbW, _positionV.y - cbH, 0);
		Render::device.MatrixScale(_scale);



		IRect texRect = _targetTex->getBitmapRect();
		_dx += 0.00300;
		_dy += 0.00300;
		d.SetRenderRect(texRect);

		d.SetDisplacement(50, 50, _dx, _dy, RefPoint::Center);
		d.SetTextureCoord(50, 50, _dx, _dy);

		_targetTex->Bind();
		d.Draw();



		//_targetTex->Draw();
		Render::device.PopMatrix();
	}
	else if (_hp <= 0)
	{
		float cbH = (_targetTex->Height()) * _scale / 2;
		float cbW = (_targetTex->Width()) * _scale / 2;

		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_positionV.x - cbW, _positionV.y - cbH, 0);
		Render::device.MatrixScale(_scale);

		Color clor{ 255, 0, 0, 255 };
		Render::BeginColor(clor);
		_targetTex->Draw();
		Render::EndColor();
		Render::device.PopMatrix();
	}
}

void Target::Update(float dt)
{
	MoveTarget(dt);
}

void Target::Init(int hp, float scale)
{
	_hp = hp;

	_scale = scale;
	_visible = true;

	_radius = _targetTex->Height() * _scale / 2;


	float angle = rand() % 360;
	float speed = 100 + rand() % (150   );

	int roundRad = +1 + round(_radius);

	//положение на экране
	float x, y, z;

	int bin = 1 + rand() % 2;
	if (bin == 1)
	{
		x = roundRad + GameSettings::spawnTargLeftBorger - 2 * roundRad;
	}
	else
	{
		x = roundRad + GameSettings::spawnTargRightBorger + 2 * roundRad;
	}


	y = (roundRad + GameSettings::spawnTargDownBorger) + rand() % (GameSettings::spawnTargTopBorger - (roundRad * 2 + GameSettings::spawnTargDownBorger));
	z = 0;


	InitPositionVec(x, y, z);
	InitMotionVector(angle, speed);
}

void Target::DistortionTexture()
{
	Distortion d(20, 20);

	IRect texRect = _targetTex->getBitmapRect();

	d.SetRenderRect(texRect);

	d.SetDisplacement(30, 30, 1.5, 1.5, RefPoint::Center);

	_targetTex->Bind();
	d.Draw();

}
