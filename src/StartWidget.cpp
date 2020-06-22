#include "stdafx.h"
#include "StartWidget.h"

StartWidget::StartWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
{
	Init();
	_scale = 1;
}

void StartWidget::Init()
{
	_scale = GameSettings::buttonScale;

	float centerX = GameSettings::WINDOW_WIDTH / 2;
	float heightY = GameSettings::WINDOW_HEIGHT * 0.6;
	float interval = 90;

	_startButton.Init("StartButton", "StartPrButton", centerX, heightY);
	_closeButton.Init("CloseButton", "ClosePrButton", centerX, heightY - interval);
	_settingsButton.Init("SettingsButton", "SettingsPrButton", centerX, heightY - interval - interval);

	_startScreenTex = Core::resourceManager.Get<Render::Texture>("StartScreen");
	_cursorTex = Core::resourceManager.Get<Render::Texture>("Cursor");
}

void StartWidget::Draw()
{
	_startScreenTex->Draw();

	_startButton.Draw();
	_closeButton.Draw();
	_settingsButton.Draw();

	//Курсор
	FPoint mousePos = Core::mainInput.GetMousePos();
	float aimH = (_cursorTex->Height()) * _scale / 2;
	float aimW = (_cursorTex->Width()) * _scale / 2;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(mousePos.x - aimW, mousePos.y - aimH, 0);
	Render::device.MatrixScale(_scale);
	_cursorTex->Draw();
	Render::device.PopMatrix();
}

void StartWidget::Update(float dt)
{
}

bool StartWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		_startButton.CheckAndUpdateState();
		if (_startButton.IsPressed())
		{
			Core::mainScreen.popLayer();
			Core::mainScreen.pushLayer("MainLayer");
			Core::mainScreen.GetTopLayer()->InitLayer();
			return false;
		}

		_closeButton.CheckAndUpdateState();
		if (_closeButton.IsPressed())
		{
			Core::appInstance->Stop();
			return false;
		}

		_settingsButton.CheckAndUpdateState();
	}
	return false;
}

void StartWidget::MouseMove(const IPoint &mouse_pos)
{
}

void StartWidget::MouseUp(const IPoint &mouse_pos)
{
}

void StartWidget::KeyPressed(int keyCode)
{
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.

	if (keyCode == VK_ESCAPE) {
		// Реакция на нажатие кнопки A
	}
}

void StartWidget::CharPressed(int unicodeChar)
{
	// unicodeChar - Unicode код введённого символа

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}
