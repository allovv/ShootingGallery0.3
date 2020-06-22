#ifndef __TESTAPPDELEGATE_H__
#define __TESTAPPDELEGATE_H__

#pragma once
//директива проепроцессора, решает проблему повторного включения
//после директивы #pragma once заголовочный файл подключается в проект только один раз

//заголовок хранит интерфейс взаимодействия с функционалом, который определен в cpp файле
//прототипы функций без их реализации
//определение самого класса, прототипы методов класса, сами методы в cpp файле

//"" означает, что файл, который хотим подключить лежит среди файлов проекта 

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
