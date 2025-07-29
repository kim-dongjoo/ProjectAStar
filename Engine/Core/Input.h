#pragma once

#include "Core.h"

class Engine_API Input
{
	// freend 선언
	friend class Engine;


	struct KeyState
	{
		// 현재 프레임에 키가 눌렸는지
		bool isKeyDown = false;
		// 이전 프레임에 키가 눌렸는지
		bool previousKeyDown = false;
	};

public:
	Input();

	// 키 확인 함수
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);



	static Input& GetInput();

private:
	void ProcessInput();
	void SavePreviousKeyStates();

private:
	// 키 입력 정보 관리 변수
	KeyState keyStates[255];

	static Input* instance;
};
