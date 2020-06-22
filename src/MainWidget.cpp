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

	//������� ����������
	Render::BindFont("arial2");
	Render::PrintString(30, GameSettings::WINDOW_HEIGHT - 80, std::string("Bullets: ") + utils::lexical_cast(_game._cannon.GetNumBullets()), 1.0f, LeftAlign, BottomAlign);
	Render::PrintString(30, GameSettings::WINDOW_HEIGHT - 110, std::string("Targets destroyed: ") + utils::lexical_cast(_game._flyingObj.GetNumDestroyedTargets()), 1.0f, LeftAlign, BottomAlign);
	Render::PrintString(30, GameSettings::WINDOW_HEIGHT - 50, std::string("Time: ") + utils::lexical_cast(math::round(_time)), 1.0f, LeftAlign, BottomAlign);
}

void MainWidget::Update(float dt)
{
	//
	// dt - �������� ������� � ��������, ��������� �� ����������� �����.
	// ��� ����� ��������� ������ ��������, � ����������� �� ������������������ �������
	// � ��������� �����.
	//
	// ��� ����, ����� ���� �������� �������� ������ �� �������, � �� �������� ��
	// ������������������ �������, �� ������ ������������ � �� ����� ��������.
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
	// ������� ����� ���������� ��������� � �����������.

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void MainWidget::KeyPressed(int keyCode)
{
	// keyCode - ����������� ��� �������.
	// � �������� �������� ��� �������� ����� ������������ ��������� VK_.

	if (keyCode == VK_ESCAPE) {
		// ������� �� ������� ������ A
	}
}

void MainWidget::CharPressed(int unicodeChar)
{
	// unicodeChar - Unicode ��� ��������� �������

	if (unicodeChar == L'�') {
		// ������� �� ���� ������� '�'
	}
}

void MainWidget::SaveInfo()
{
	SingletonGameInfo::GameInfo::getInstance().setTime(_time);
	SingletonGameInfo::GameInfo::getInstance().setNumBullets(_game._cannon.GetNumBullets());
	SingletonGameInfo::GameInfo::getInstance().setNumTargets(_game._flyingObj.GetNumDestroyedTargets());
}
