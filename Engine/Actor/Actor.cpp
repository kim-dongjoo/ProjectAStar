#include "Actor.h"
#include <Windows.h>
#include <iostream>

Actor::Actor(const char image, Color color) : image(image), color(color)
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
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	SetConsoleCursorPosition(handle, coord);

	// 색상
	SetConsoleTextAttribute(handle, (WORD)color);

	// 그리기
	std::cout << image;
	
}

void Actor::SetPosition(const Vector2& newPosition)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	SetConsoleCursorPosition(handle, coord);

	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::GetPosition() const
{
	return position;
}
