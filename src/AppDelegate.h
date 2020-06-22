#ifndef __TESTAPPDELEGATE_H__
#define __TESTAPPDELEGATE_H__

#pragma once
//��������� ��������������, ������ �������� ���������� ���������
//����� ��������� #pragma once ������������ ���� ������������ � ������ ������ ���� ���

//��������� ������ ��������� �������������� � ������������, ������� ��������� � cpp �����
//��������� ������� ��� �� ����������
//����������� ������ ������, ��������� ������� ������, ���� ������ � cpp �����

//"" ��������, ��� ����, ������� ����� ���������� ����� ����� ������ ������� 

#include "GameSettings.h"

class AppDelegate : public Core::EngineAppDelegate {
public:
	AppDelegate();

	virtual void GameContentSize(int deviceWidth, int deviceHeight, int &width, int &height) override;
	virtual void ScreenMode(DeviceMode &mode) override;

	virtual void RegisterTypes() override;

	virtual void LoadResources() override;
	virtual void OnResourceLoaded() override;

	virtual void OnPostDraw() override;


};

#endif // __TESTAPPDELEGATE_H__
