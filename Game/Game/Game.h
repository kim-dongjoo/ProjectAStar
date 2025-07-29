#pragma once

#include "Engine.h"

class Level;

class Game : public Engine
{
public:
	Game();
	~Game();

	// 메뉴 전환 함수
	void ToggledMenu();

	virtual void CleanUp() override;

	static Game& GetGame();



private:

	// 메뉴 레벨
	Level* menuLevel = nullptr;

	Level* backLevel = nullptr;

	// 현재 메뉴를 보여주고 있는지를 나타냄
	bool showMenu = false;



	static Game* instance;

};