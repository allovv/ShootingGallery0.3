#pragma once
#include "GameSettings.h"

class Button
{
public:
	Button();
	~Button();

public:
	void Draw();

	void CheckAndUpdateState();

	void Init(std::string buttonTexture, float xPos, float yPos);
	void Init(std::string buttonTexture, std::string buttonPressedTexture, float xPos, float yPos);

	bool IsPressed();
	void ResetState();

private:
	void DrawButton();
	void DrawPressedButton();

	bool ButtonIsPressed();

private:
	enum ButtonStates {
		USUAL,
		PRESSED
	};
	ButtonStates _buttonState;

private:
	float _x;
	float _y;

	float _len;
	float _height;

	float _scale;

	Render::Texture* _buttonTex;
	Render::Texture* _buttonPressedTex;
};