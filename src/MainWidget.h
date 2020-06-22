#pragma once
#include "GameSettings.h"
#include "Game.h"

#include "GameInfo.cpp"

//----------------------------------------------------------
//Все ресурсы в XML
//----------------------------------------------------------

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///

class MainWidget : public GUI::Widget
{
public:
	MainWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw() override;				
	void Update(float dt) override;			

	void AcceptMessage(const Message& message) override;

	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;

	void SaveInfo();

public:
	void Init();

private:
	Game _game;

	float _time;
};
