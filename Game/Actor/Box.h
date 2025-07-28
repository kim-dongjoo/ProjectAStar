#pragma once

#include "Actor/Actor.h"

class Box : public Actor
{
	RTTI_DECLARATIONS(Box, Actor)

public:
	Box(const Vector2& position);
};