#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Utils/Utils.h"
#include "Engine.h"

Actor::Actor(const char image, Color color, const Vector2& position) : image(image), color(color), position(position)
{
}

Actor::~Actor()
{
}

// 
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

void Actor::Tick(float deltaTime)
{
}

void Actor::Render()
{
	// Win32 API
	// 커서 위치 이동.
	// static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 위치 값 생성
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	// 커서 이동
	// SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);

	// 색상
	Utils::SetConsoleTextColor((WORD)color);

	// 그리기
	std::cout << image;
	
}

void Actor::SetPosition(const Vector2& newPosition)
{
	// static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	Utils::SetConsolePosition(coord);

	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::GetPosition() const
{
	return position;
}

void Actor::SetRenderSortingOrder(unsigned int renderSortingOrder)
{
	this->renderSortingOrder = renderSortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::QuitGame()
{
	Engine::GetEngine().Quit();
}
