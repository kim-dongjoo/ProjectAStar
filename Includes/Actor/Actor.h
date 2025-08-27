#pragma once

#include "Core.h"
#include "../Math/Vector2.h"
#include "RTTI.h"
#include <Windows.h>

// 색상
enum class Color : int
{
	Blue =	1,
	Green = 2,
	Red = 4,
	White = Red | Green | Blue,
	Intensity = 8
};

class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(const char image = ' ', Color color = Color::White, const Vector2& position = Vector2::Zero);
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

	// Render Sorting Order 설정
	void SetRenderSortingOrder(unsigned int renderSortingOrder);

	// 오너십 설정
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// 게임 종료 요청 함수
	void QuitGame();

protected:
	Vector2 position;

	// 그릴 값
	char image = ' ';

	// 색상
	Color color ;

	// BeginPlay가 호출 되었는지 확인
	bool hasBeganPlay = false;

	// 렌더 정렬 순서
	unsigned int renderSortingOrder = 0;

	// 소유 레벨(오너십)
	Level* owner = nullptr;

};