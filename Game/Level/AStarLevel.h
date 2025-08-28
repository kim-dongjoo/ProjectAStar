#pragma once

#include "Level/Level.h"
#include "AStar/AStar.h"
#include "AStar/Node.h"
#include "Actor/LevelGrid.h"
#include "Interface//ICanPlayerMove.h"
#include "Game/Message.h"

class AStarLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(AStarLevel, Level)

public:
	AStarLevel();
	~AStarLevel();

	virtual void Render() override;

	// ICanPlayerMove을(를) 통해 상속됨
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;

	// 그리드 변경
	void ModifyGrid(Vector2 position, GridType type);

	// A-star 알고리즘을 통한 이동 시작
	void StartAStar();

private:
	void ReadMapFile(const char* filename);

private:
	// A* 객체
	AStar aStar;

	// 맵 그리드
	std::vector<std::vector<LevelGrid>> grids;

	// 맵 사이즈
	Vector2 Size;

	// 시작 위치와 목표위치 노드.
	Node* startNode = nullptr;
	Node* goalNode = nullptr;

	// 메시지
	Message* msg;
};