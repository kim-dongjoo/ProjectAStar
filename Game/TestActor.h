#pragma once

#include "Actor/Actor.h"

class TestActor : public Actor
{
	RTTI_DECLARATIONS(TestActor, Actor)

public:
	virtual void Tick(float deltaTime) override;
};