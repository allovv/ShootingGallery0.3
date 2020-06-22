#pragma once

namespace SingletonGameInfo {

	class GameInfo
	{
	public:
		GameInfo(const GameInfo &other) = delete;					//����������� �����������
		GameInfo & operator = (const GameInfo &other) = delete;		//�������� ������������

	public:
		//����������� ������� �� ��������� �� � ����� ����� ������
		//��������� � ��������� ������� ������ � ����� �������� ������ �� ���������� ���������
		static GameInfo &getInstance();

		void ChooseBackground();

		//-------------------------------------

		float &getTime();

		int &getNumBullets();

		int &getNumTargets();

		std::string &getStartTex();

		std::string &getGameTex();

		std::string &getEndTex();

		//-------------------------------------

		void setTime(float time);

		void setNumBullets(int numBullets);

		void setNumTargets(int destrTarg);

		void setStartTex(std::string startTex);

		void setGameTex(std::string gameTex);

		void setEndTex(std::string endTex);

		//-------------------------------------

	private:
		GameInfo();
		~GameInfo();

	private:
		//All data

		float _gameTime;
		int _numBullets;
		int _numDestroyedTargets;

		std::string _startBackTex;
		std::string _gameBackTex;
		std::string _endBackTex;
	};

}