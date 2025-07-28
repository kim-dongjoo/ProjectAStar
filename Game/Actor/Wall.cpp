#include "Wall.h"

Wall::Wall(const Vector2& position) : Actor('#', Color::White, position)
{
	SetRenderSortingOrder(0);
}
