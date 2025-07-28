#include "Box.h"

Box::Box(const Vector2& position) : Actor('B', Color::Green, position)
{
	SetRenderSortingOrder(2);
}
