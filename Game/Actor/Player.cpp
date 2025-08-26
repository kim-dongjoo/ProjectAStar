#include "Player.h"
#include "Engine.h"
#include "Game//Game.h"
#include "Input.h"
#include "Level/Level.h"
#include "Level/AStarLevel.h"
#include "Interface/ICanPlayerMove.h"

#include <iostream>

Player::Player(const Vector2& position) : Actor('*', Color::Red, position)
{
	SetRenderSortingOrder(3);
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// �������̽� ������
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

	// TODO : Input Binding���� ó��
	// �Է� ó�� 

	/* ==================================================================================================== */
	// ����Ű�� ��ǥ �̵�
	// �̵� ���� - �̵��ϱ� ���� �̵��� ��ġ�� �� �� �ִ��� �Ǵ� �� �̵�
	if (Input::GetInput().GetKeyDown(VK_RIGHT))
	{
		// �̵� ���� �̵� �������� Ȯ��.
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

	/* ==================================================================================================== */
	// SŰ : ���� ��ġ ����
	// GŰ : ��ǥ ��ġ ����
	// WŰ : ��ֹ� ����
	// SpaceŰ : �̵� ����

	// SŰ
	if (Input::GetInput().GetKeyDown(0x53))
	{
		// TODO : ���� ��ġ �����ϴ� �Լ�
	}

	// GŰ
	if (Input::GetInput().GetKeyDown(0x47))
	{
		// TODO : ��ǥ ��ġ �����ϴ� �Լ�
	}

	// WŰ
	if (Input::GetInput().GetKeyDown(0x57))
	{
		// TODO : ��ֹ� �����ϴ� �Լ�
	}

	// �����̽� Ű
	if (Input::GetInput().GetKeyDown(VK_SPACE))
	{
		// TODO : A-star �˰����� ���� �̵� ����
		AStarLevel* level = GetOwner()->As<AStarLevel>();
		level->StartAStar();
	}


}
