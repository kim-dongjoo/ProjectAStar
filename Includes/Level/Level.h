#pragma once

#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	void SpawnActor(Actor* newActor);

	// 엔진 이벤트 함수
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

private:
	void SortActorsByRenderSortingOrder();

protected:
	std::vector<Actor*> actors;
};