#include "Input.h"
#include <Windows.h>

// static 변수 정의
Input* Input::instance = nullptr;

Input::Input()
{
	// 싱글톤 실행을 위해 instance 변수 설정
	instance = this;
}

void Input::ProcessInput()
{
	// 키 입력 확인
	for (int idx = 0; idx < 255; ++idx)
	{
		keyStates[idx].isKeyDown = GetAsyncKeyState(idx) & 0x8000;
	}
}

void Input::SavePreviousKeyStates()
{
	// 현재 프레임의 입력을 기록
	for (int idx = 0; idx < 255; ++idx)
	{
		keyStates[idx].previousKeyDown = keyStates[idx].isKeyDown;
	}
}

bool Input::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyDown(int keyCode)
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].previousKeyDown;
}

bool Input::GetKeyUp(int keyCode)
{
	return !keyStates[keyCode].isKeyDown && keyStates[keyCode].previousKeyDown;
}

Input& Input::GetInput()
{
	return *instance;
}