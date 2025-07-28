#include "TestActor.h"
#include <iostream>
#include "Engine.h"
#include <Windows.h>

TestActor::TestActor() : super('P', Color::Blue)
{
}

void TestActor::Tick(float deltaTime)
{
	// Actor::Tick(deltaTime);
	super::Tick(deltaTime);

	//std::cout 
	//	<< "TestACtor::Tick. FPS: "
	//	<< (1.0f / deltaTime)
	//	<< std::endl;

	if (Engine::GetEngine().GetKey(VK_RIGHT) && GetPosition().x < 30)
	{
		Vector2 position = GetPosition();
		position.x += 1;
		SetPosition(position);
	}

	if (Engine::GetEngine().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		Vector2 position = GetPosition();
		position.x -= 1;
		SetPosition(position);
	}

	if (Engine::GetEngine().GetKey(VK_UP) && GetPosition().y > 0)
	{
		Vector2 position = GetPosition();
		position.y -= 1;
		SetPosition(position);
	}

	if (Engine::GetEngine().GetKey(VK_DOWN) && GetPosition().y < 30)
	{
		Vector2 position = GetPosition();
		position.y += 1;
		SetPosition(position);
	}



	if (Engine::GetEngine().GetKeyDown(VK_ESCAPE))
	{
		Engine::GetEngine().Quit();
	}
}
