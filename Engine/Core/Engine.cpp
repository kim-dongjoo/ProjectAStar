#include "Engine.h"
#include <iostream>
#include "../Level//Level.h"

// 윈도우즈
// 단순 입력 처리(키보드)
//


Engine::Engine()
{
}

Engine::~Engine()
{
	if (mainLevel)
	{
		delete mainLevel;
	}
}

void Engine::Run()
{
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;

	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 주파수 가져오기
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 타겟 프레임 레이트
	float targetFrameRate = 60.0f;

	// 타겟 한 프레임 길이
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop
	while (true)
	{
		// 엔진 종료 여부 확인
		if (isQuit)
			break;

		// 프레임 시간 계산
		// (현재 시간 - 이전 시간) / 주파수
		QueryPerformanceCounter(&currentTime);

		// 프레임 시간
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;
		QueryPerformanceCounter(&currentTime);

		ProcessInput();

		// 프레임 60 이하로 제한
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록
			for (int idx = 0; idx < 255; ++idx)
			{
				keyStates[idx].previousKeyDown = keyStates[idx].isKeyDown;
			}
		}
	}
}

void Engine::AddLevel(Level* newLevel)
{
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

bool Engine::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int keyCode)
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].previousKeyDown;
}

bool Engine::GetKeyUp(int keyCode)
{
	return !keyStates[keyCode].isKeyDown && keyStates[keyCode].previousKeyDown;
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// 키 입력 확인
	for (int idx = 0; idx < 255; ++idx)
	{
		keyStates[idx].isKeyDown = GetAsyncKeyState(idx) & 0x8000;
	}

	// ESC 키 눌림 확인
	// if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	//	Quit();
}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	//std::cout
	//<< "DeltaTime : " << deltaTime
	//<< ", FPS : " << (1.0f/deltaTime)
	//<< "\n";

	// 레벨 업데이트
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}

	if (GetKeyDown(VK_ESCAPE)) { Quit(); }
}

void Engine::Render()
{
	if (mainLevel)
	{
		mainLevel->Render();
	}
}
