#include "Level.h"
#include "../Actor/Actor.h"

Level::Level()
{

}

Level::~Level()
{
	// 메모리 해제
	for (Actor* actor : actors)
	{
		//if (actor)
		//{
		//	delete actor;
		//	actor = nullptr;
		//}

		SafeDelete(actor);
	}

}

void Level::SpawnActor(Actor* newActor)
{
	// TODO : 중복 여부 예외 처리

	actors.push_back(newActor);

	// 오너십 설정.
	newActor->SetOwner(this);
}

// 엔진 이벤트 함수
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	// 정렬
	SortActorsByRenderSortingOrder();

	// Render Pass
	for (Actor* const actor : actors)
	{
		// 검사
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// 같은 액터면 무시
			if (actor == otherActor)
				continue;

			if (actor->GetPosition() == otherActor->GetPosition())
			{
				if (actor->renderSortingOrder < otherActor->renderSortingOrder)
				{
					searchedActor = otherActor;
					break;
				}
			}
		}
		
		if (searchedActor)
		{
			continue;
		}

		// Draw Call
		actor->Render();
	}
}

void Level::SortActorsByRenderSortingOrder()
{
	for (int idx = 0; idx < (int)actors.size(); ++idx)
	{
		for (int jdx = 0; jdx < (int)actors.size() - 1; ++jdx)
		{
			if (actors[jdx]->renderSortingOrder > actors[jdx + 1]->renderSortingOrder)
			{
				std::swap(actors[jdx], actors[jdx + 1]);
			}
		}


	}
}