#pragma once

#include "Core.h"
#include "../Math/Vector2.h"

// 위치
// 그리기
// 엔진의 이벤트 함수 호출(BeginPlay/Tick/Draw)

class Engine_API Actor
{
public:
	Actor();
	virtual ~Actor();

	// 이벤트 함수
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	Vector2 position;

	// 그릴 값
	char image = ' ';

	// BeginPlay가 호출 되었는지 확인
	bool hasBeganPlay = false;

};

