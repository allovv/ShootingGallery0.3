//Precompiled Headers
#include "stdafx.h"
#include "MainWidget.h"
#include "EndWidget.h"


MainWidget::MainWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	_time(0.f)
{
	Init();
}

void MainWidget::Init()
{
	_game.Init();
	_time = 0;
}

void MainWidget::Draw()
{
	_game.Draw();

	//игровая информация
	Render::BindFont("arial2");
	Render::PrintString(30, GameSettings::WINDOW_HEIGHT - 80, std::string("Bullets: ") + utils::lexical_cast(_game._cannon.GetNumBullets()), 1.0f, LeftAlign, BottomAlign);
	Render::PrintString(30, GameSettings::WINDOW_HEIGHT - 110, std::string("Targets destroyed: ") + utils::lexical_cast(_game._flyingObj.GetNumDestroyedTargets()), 1.0f, LeftAlign, BottomAlign);
	Render::PrintString(30, GameSettings::WINDOW_HEIGHT - 50, std::string("Time: ") + utils::lexical_cast(math::round(_time)), 1.0f, LeftAlign, BottomAlign);
}

void MainWidget::Update(float dt)
{
	//
	// dt - значение времени в секундах, прошедшее от предыдущего кадра.
	// Оно может принимать разные значения, в зависимости от производительности системы
	// и сложности сцены.
	//
	// Для того, чтобы наша анимация зависела только от времени, и не зависела от
	// производительности системы, мы должны рассчитывать её от этого значения.
	//

	if (_time >= GameSettings::matchTime)
	{
		SaveInfo();
		Core::mainScreen.popLayer();
		Core::mainScreen.pushLayer("EndLayer");

		EndWidget* endWidget = static_cast<EndWidget*>(Core::mainScreen.GetTopLayer()->getWidget("EndWidget"));
		if (endWidget != NULL)
		{
			endWidget->Init();
		}

	}
	_time += dt;

	_game.Update(dt);
}

bool MainWidget::MouseDown(const IPoint &mouse_pos)
{
	return false;
}

void MainWidget::MouseMove(const IPoint &mouse_pos)
{
}

void MainWidget::MouseUp(const IPoint &mouse_pos)
{
}

void MainWidget::AcceptMessage(const Message& message)
{
	// Виджету могут посылаться сообщения с параметрами.

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void MainWidget::KeyPressed(int keyCode)
{
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.

	if (keyCode == VK_ESCAPE) {
		// Реакция на нажатие кнопки A
	}
}

void MainWidget::CharPressed(int unicodeChar)
{
	// unicodeChar - Unicode код введённого символа

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}

void MainWidget::SaveInfo()
{
	SingletonGameInfo::GameInfo::getInstance().setTime(_time);
	SingletonGameInfo::GameInfo::getInstance().setNumBullets(_game._cannon.GetNumBullets());
	SingletonGameInfo::GameInfo::getInstance().setNumTargets(_game._flyingObj.GetNumDestroyedTargets());
}
