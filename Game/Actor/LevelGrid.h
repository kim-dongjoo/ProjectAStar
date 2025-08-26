#pragma once

#include "Actor/Actor.h"

enum class GridType
{
	Ground = 1,
	Wall = 2,
	Start = 3,
	Goal = 4,
	Path = 5
};

class LevelGrid : public Actor
{
	RTTI_DECLARATIONS(LevelGrid, Actor)

	LevelGrid(const Vector2& position, const char image, Color color, GridType type);

	const GridType& GetType() const { return type; }
	void SetType(const GridType type)
	{
		this->type = type;
	}

private:
	GridType type = GridType::Ground;
};