#pragma once
#include "GameSettings.h"
#include "Game.h"
#include "Button.h"

class StartWidget: public GUI::Widget
{
public:
	StartWidget(const std::string& name, rapidxml::xml_node<>* elem);

public:
	void Draw() override;
	void Update(float dt) override;

	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;

public:
	void Init();

private:
	float _scale;

	Button _startButton;
	Button _closeButton;
	Button _settingsButton;

	Render::Texture* _cursorTex;
	Render::Texture* _startScreenTex;
};

