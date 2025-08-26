#pragma once

#include "Actor/Actor.h"

#include <iostream>

class Node : public Actor
{
	RTTI_DECLARATIONS(Node, Actor)

public:
	Node(int x, int y, Node* parentNode = nullptr) : parent(parentNode)
	{
		position.x = x;
		position.y = y;
	}

	Vector2 operator-(const Node& other)
	{
		return Vector2(
			position.x - other.position.x,
			position.y - other.position.y
		);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x && position.y == other.position.y;
	}

public:
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Node* parent = nullptr;
};