#include "Player.h"
#include "Engine.h"
#include "Input.h"

Player::Player(const Vector2& position) : Actor('P', Color::Red, position)
{
	SetRenderSortingOrder(3);
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::GetInput().GetKeyDown(VK_ESCAPE))
	{
		Engine::GetEngine().Quit();
		return;
	}

	// 입력 처리 
	if (Input::GetInput().GetKeyDown(VK_RIGHT))
	{
		Vector2 position = GetPosition();
		position.x += 1;
		SetPosition(position);
	}
	if (Input::GetInput().GetKeyDown(VK_LEFT))
	{
		Vector2 position = GetPosition();
		position.x -= 1;
		SetPosition(position);
	}
	if (Input::GetInput().GetKeyDown(VK_UP))
	{
		Vector2 position = GetPosition();
		position.y -= 1;
		SetPosition(position);
	}
	if (Input::GetInput().GetKeyDown(VK_DOWN))
	{
		Vector2 position = GetPosition();
		position.y += 1;
		SetPosition(position);
	}
}
