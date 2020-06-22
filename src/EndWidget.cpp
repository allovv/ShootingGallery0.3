#include "stdafx.h"
#include "EndWidget.h"

EndWidget::EndWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
{
	Init();
	_scale = 1;
}

void EndWidget::Init()
{
	_scale = GameSettings::buttonScale;

	float centerX = GameSettings::WINDOW_WIDTH / 2;
	float heightY = GameSettings::WINDOW_HEIGHT * 0.6;

	_endgameTex = Core::resourceManager.Get<Render::Texture>("EndGame1");
	_cursorTex = Core::resourceManager.Get<Render::Texture>("Cursor");

	_restartButton.Init("RestartButton", centerX, heightY);
}

void EndWidget::Draw()
{
	_endgameTex->Draw();
	_restartButton.Draw();

	//Курсор
	FPoint mousePos = Core::mainInput.GetMousePos();
	float aimH = (_cursorTex->Height()) * _scale / 2;
	float aimW = (_cursorTex->Width()) * _scale / 2;

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(mousePos.x - aimW, mousePos.y - aimH, 0);
	Render::device.MatrixScale(_scale);
	_cursorTex->Draw();
	Render::device.PopMatrix();

	//игровая информация
	Render::BindFont("arial2.2");
	Render::PrintString(GameSettings::WINDOW_WIDTH / 2, GameSettings::WINDOW_HEIGHT / 3, std::string("Bullets: ") + utils::lexical_cast(SingletonGameInfo::GameInfo::getInstance().getNumBullets()), 1.0f, LeftAlign, CenterAlign);
	Render::PrintString(GameSettings::WINDOW_WIDTH / 2, GameSettings::WINDOW_HEIGHT / 3 - 30, std::string("Targets destroyed: ") + utils::lexical_cast(SingletonGameInfo::GameInfo::getInstance().getNumTargets()), 1.0f, LeftAlign, CenterAlign);
	Render::PrintString(GameSettings::WINDOW_WIDTH / 2, GameSettings::WINDOW_HEIGHT / 3 - 60, std::string("Time: ") + utils::lexical_cast(SingletonGameInfo::GameInfo::getInstance().getTime()), 1.0f, LeftAlign, CenterAlign);
}

void EndWidget::Update(float dt)
{
}

bool EndWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		_restartButton.CheckAndUpdateState();
		if (_restartButton.IsPressed())
		{
			_restartButton.ResetState();
			RestartGame();
			ChangeLayer();
			return false;
		}
	}
	return false;
}

void EndWidget::MouseMove(const IPoint &mouse_pos)
{
}

void EndWidget::MouseUp(const IPoint &mouse_pos)
{
}

void EndWidget::KeyPressed(int keyCode)
{
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.

	if (keyCode == VK_ESCAPE) {
		// Реакция на нажатие кнопки A
	}
}

void EndWidget::CharPressed(int unicodeChar)
{
	// unicodeChar - Unicode код введённого символа

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}

void EndWidget::RestartGame()
{
	SingletonGameInfo::GameInfo::getInstance().setTime(0);
	SingletonGameInfo::GameInfo::getInstance().setNumBullets(0);
	SingletonGameInfo::GameInfo::getInstance().setNumTargets(0);

	SingletonGameInfo::GameInfo::getInstance().ChooseBackground();
}

void EndWidget::ChangeLayer()
{
	Core::mainScreen.popLayer();
	Core::mainScreen.pushLayer("MainLayer");

	MainWidget* mainWidget = dynamic_cast<MainWidget*>(Core::mainScreen.GetTopLayer()->getWidget("MainWidget"));
	if (mainWidget != NULL)
	{
		mainWidget->Init();
	}
}
