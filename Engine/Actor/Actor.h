#pragma once

#include "Core.h"
#include "../Math/Vector2.h"
#include "RTTI.h"
#include <Windows.h>

// 위치
// 그리기
// 엔진의 이벤트 함수 호출(BeginPlay/Tick/Draw)

// 색상
enum class Color : int
{
	Blue =	1,
	Green = 2,
	Red = 4,
	White = Red | Green | Blue,
	Intensity = 8
};

class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(const char image = ' ', Color color = Color::White);
	virtual ~Actor();

	// 이벤트 함수
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	// BeginPlay 호출 여부 확인
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// 위치 설정/값 읽는 함수
	void SetPosition(const Vector2& newPosition);
	Vector2 GetPosition() const;

private:
	Vector2 position;

	// 그릴 값
	char image = ' ';

	// 색상
	Color color ;

	// BeginPlay가 호출 되었는지 확인
	bool hasBeganPlay = false;

};

