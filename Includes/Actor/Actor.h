#pragma once

#include "Core.h"
#include "../Math/Vector2.h"
#include "RTTI.h"
#include <Windows.h>

// ����
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

	// �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// ��ġ ����/�� �д� �Լ�
	void SetPosition(const Vector2& newPosition);
	Vector2 GetPosition() const;

	// Render Sorting Order ����
	void SetRenderSortingOrder(unsigned int renderSortingOrder);

	// ���ʽ� ����
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// ���� ���� ��û �Լ�
	void QuitGame();

protected:
	Vector2 position;

	// �׸� ��
	char image = ' ';

	// ����
	Color color ;

	// BeginPlay�� ȣ�� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

	// ���� ���� ����
	unsigned int renderSortingOrder = 0;

	// ���� ����(���ʽ�)
	Level* owner = nullptr;

};