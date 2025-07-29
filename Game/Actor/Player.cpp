#include "Player.h"
#include "Engine.h"
#include "Game//Game.h"
#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

#include <iostream>

Player::Player(const Vector2& position) : Actor('P', Color::Red, position)
{
	SetRenderSortingOrder(3);
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// 인터페이스 얻어오기
	if (GetOwner())
	{
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owner level to ICanPlayerMove. \n";
		}

	}
	
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::GetInput().GetKeyDown(VK_ESCAPE))
	{
		// Engine::GetEngine().Quit();
		// QuitGame();

		Game::GetGame().ToggledMenu();
		return;
	}

	// 입력 처리 

	// 이동 로직 - 이동하기 전에 이동할 위치로 갈 수 있는지 판단 후 이동
	if (Input::GetInput().GetKeyDown(VK_RIGHT))
	{
		// 이동 전에 이동 가능한지 확인.
		if (canPlayerMoveInterface->CanPlayerMove(GetPosition(), Vector2(GetPosition().x + 1, GetPosition().y)))
		{
			Vector2 position = GetPosition();
			position.x += 1;
			SetPosition(position);
		}
	}
	if (Input::GetInput().GetKeyDown(VK_LEFT))
	{
		bool result = canPlayerMoveInterface->CanPlayerMove(GetPosition(), Vector2(GetPosition().x - 1, GetPosition().y));

		if (result)
		{
			Vector2 position = GetPosition();
			position.x -= 1;
			SetPosition(position);
		}
	}
	if (Input::GetInput().GetKeyDown(VK_UP))
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetPosition(), Vector2(GetPosition().x, GetPosition().y - 1)))
		{
			Vector2 position = GetPosition();
			position.y -= 1;
			SetPosition(position);
		}
	}
	if (Input::GetInput().GetKeyDown(VK_DOWN))
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetPosition(), Vector2(GetPosition().x, GetPosition().y + 1)))
		{
			Vector2 position = GetPosition();
			position.y += 1;
			SetPosition(position);
		}
	}
}
