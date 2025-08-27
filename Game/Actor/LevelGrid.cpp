#include "LevelGrid.h"
#include <iostream>

LevelGrid::LevelGrid(const Vector2& position, const char image, Color color, GridType type) : Actor(image, color, position), type(type)
{
	SetRenderSortingOrder(1);
}