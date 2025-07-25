#pragma once

#include "Core.h"
#include <Windows.h>

/*
* TODO :  2025년 7월 25일
	- Engine 싱글톤(Singleton) 구현
* 
*/

class Level;

class Engine_API Engine
{
	struct KeyState
	{
		// 현재 프레임에 키가 눌렸는지
		bool isKeyDown = false;
		// 이전 프레임에 키가 눌렸는지
		bool previousKeyDown = false;
	};

public:
	// 생성자
	Engine();

	// 소멸자
	~Engine();

	// 엔진 실행 함수
	void Run();

	// 레벨 추가 함수
	void AddLevel(Level* newLevel);

	// 키 확인 함수
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	// 엔진 종료 함수
	void Quit();

	// 싱글톤 접근 함수
	static Engine& GetEngine();

private:
	void ProcessInput();
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

private:
	// 엔진 종료 플래그
	bool isQuit = false;

	// 키 입력 정보 관리 변수
	KeyState keyStates[255];

	// 메인 레벨
	Level* mainLevel = nullptr;

	// 싱글톤 변수
	static Engine* instance;

};

