#include "Ground.h"

Ground::Ground(const Vector2& position) : Actor('.', Color::White, position)
{
	SetRenderSortingOrder(0);
}