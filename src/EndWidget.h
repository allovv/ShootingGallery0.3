#pragma once
#include "GameSettings.h"
#include "Game.h"
#include "Button.h"

#include "MainWidget.h"

class EndWidget: public GUI::Widget
{
public:
	EndWidget(const std::string& name, rapidxml::xml_node<>* elem);

public:
	void Draw() override;
	void Update(float dt) override;

	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;

	void RestartGame();
	void ChangeLayer();
public:
	void Init();

private:
	float _scale;

	Button _restartButton;

	Render::Texture* _cursorTex;
	Render::Texture* _endgameTex;
	Render::Texture* _restartButtonTex;
};

