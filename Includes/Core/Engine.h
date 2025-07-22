#pragma once

#include "Core.h"
#include <Windows.h>

class Engine_API Engine
{
public:
	// 생성자
	Engine();

	// 소멸자
	~Engine();

	// 엔진 실행 함수
	void Run();

	// 엔진 종료 함수
	void Quit();

private:
	void ProcessInput();
	void Update(float deltaTime = 0.0f);
	void Render();

private:
	// 엔진 종료 플래그
	bool isQuit = false;
};

