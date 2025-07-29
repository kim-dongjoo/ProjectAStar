#include "Engine.h"
#include <iostream>
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"

// 윈도우즈
// 단순 입력 처리(키보드)
//

Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
		case CTRL_CLOSE_EVENT:
		//Engine의 메모리 해제
		Engine::GetEngine().CleanUp();
		return false;


	}

	return false;

}

Engine::Engine()
{
	instance = this;

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	//콘솔 커서 끄기
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	// 콘솔 창 이벤트 등록
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

}

Engine::~Engine()
{
	CleanUp();
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

		input.ProcessInput();

		// 프레임 60 이하로 제한
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록
			input.SavePreviousKeyStates();
		}
	}

	// 텍스트 색상 다시 흰색으로 설정

	Utils::SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}

void Engine::AddLevel(Level* newLevel)
{
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	// 레벨 삭제
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	isQuit = true;
}

Engine& Engine::GetEngine()
{
	return *instance;
}

//void Engine::ProcessInput()
//{
//	// 키 입력 확인
//	for (int idx = 0; idx < 255; ++idx)
//	{
//		keyStates[idx].isKeyDown = GetAsyncKeyState(idx) & 0x8000;
//	}
//
//	// ESC 키 눌림 확인
//	// if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
//	//	Quit();
//}

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

	// if (GetKeyDown(VK_ESCAPE)) { Quit(); }
}

void Engine::Render()
{
	Utils::SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	/*SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	);*/

	if (mainLevel)
	{
		mainLevel->Render();
	}
}
