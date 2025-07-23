#pragma once

#include "Actor/Actor.h"

class TestActor : public Actor
{
public:
	virtual void Tick(float deltaTime) override;
};