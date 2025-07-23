#pragma once

#include "Core.h"
#include <vector>

class Actor;

class Engine_API Level
{
public:
	Level();
	~Level();

	void SpawnActor(Actor* newActor);

	// 엔진 이벤트 함수
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

private:
	std::vector<Actor*> actors;


};

