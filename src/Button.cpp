#include "stdafx.h"
#include "Button.h"


Button::Button():
	_scale(0.f),
	_x(0.f),
	_y(0.f),
	_len(0.f),
	_height(0.f),
	_buttonState(USUAL)
{

}


Button::~Button()
{
}

void Button::DrawButton()
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);

	Render::device.MatrixScale(_scale);
	_buttonTex->Draw();
	Render::device.PopMatrix();
}

void Button::DrawPressedButton()
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);

	Render::device.MatrixScale(_scale);
	_buttonPressedTex->Draw();
	Render::device.PopMatrix();
}

void Button::Draw()
{
	if (_buttonState == USUAL)
	{
		DrawButton();
	}
	else if (_buttonState == PRESSED)
	{
		if (_buttonPressedTex != NULL)
		{
			DrawPressedButton();
		}
		else {
			DrawButton();
		}
	}
}

void Button::Init(std::string buttonTexture, std::string buttonPressedTexture, float xPos, float yPos)
{
	_buttonTex = Core::resourceManager.Get<Render::Texture>(buttonTexture);
	_buttonPressedTex = Core::resourceManager.Get<Render::Texture>(buttonPressedTexture);

	_scale = GameSettings::buttonScale;

	_height = (_buttonTex->Height()) * _scale;
	_len = (_buttonTex->Width()) * _scale;
	_x = xPos - _len / 2;
	_y = yPos - _height / 2;
}

bool Button::IsPressed()
{
	return _buttonState == PRESSED;
}

void Button::ResetState()
{
	_buttonState = USUAL;
}

void Button::Init(std::string buttonTexture, float xPos, float yPos)
{
	_buttonTex = Core::resourceManager.Get<Render::Texture>(buttonTexture);
	_buttonPressedTex = NULL;

	_scale = GameSettings::buttonScale;

	_len = (_buttonTex->Width()) * _scale;
	_height = (_buttonTex->Height()) * _scale;

	_x = xPos - _len / 2;
	_y = yPos - _height / 2;
}

void Button::CheckAndUpdateState()
{
	if (ButtonIsPressed())
	{
		_buttonState = PRESSED;
	}
}

bool Button::ButtonIsPressed()
{
	FPoint mousePos = Core::mainInput.GetMousePos();
	return mousePos.x >= _x &&
		mousePos.x <= _x + _len &&
		mousePos.y >= _y &&
		mousePos.y <= _y + _height &&
		Core::mainInput.GetMouseLeftButton();
}
