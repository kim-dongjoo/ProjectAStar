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

	// 엔진 설정 로드
	LoadEngineSettings();
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
	float targetFrameRate = settings.framerate == 0.0f ? 60.0f : settings.framerate;

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

			// 제목에 FPS 출력
			char title[50] = {};
			sprintf_s(title, 50, "FPS: %f", (1.0f / deltaTime));
			SetConsoleTitleA(title);

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

void Engine::LoadEngineSettings()
{
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");

	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings. \n";
		__debugbreak();
		return;
	}

	// 로드

	// FP(File Position) 포인터를 가장 뒤로 옮기기
	fseek(file, 0, SEEK_END);

	// 이 위치 구하기
	size_t fileSize = ftell(file);

	// 다시 첫 위치로 되돌리기
	rewind(file);

	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// 내용 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// 파싱(Parcing, 구문 해석->필요한 정보를 얻는 과정)
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	// 구문 분석
	while (token != nullptr)
	{
		// 키/값 분리
		char header[16] = { };
		sscanf_s(token, "%s", header, 16);

		// 헤더 문자열 비교
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}

		// 그 다음 줄 분리
		token = strtok_s(nullptr, "\n", &context);

	}

	SafeDeleteArray(buffer);

	// 파일 닫기
	fclose(file);



}
