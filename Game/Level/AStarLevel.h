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

	// ICanPlayerMove��(��) ���� ��ӵ�
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;

	// �׸��� ����
	void ModifyGrid(Vector2 position, GridType type);

	// A-star �˰����� ���� �̵� ����
	void StartAStar();

private:
	void ReadMapFile(const char* filename);

private:
	// A* ��ü
	AStar aStar;

	// �� �׸���
	std::vector<std::vector<LevelGrid>> grids;

	// �� ������
	Vector2 Size;

	// ���� ��ġ�� ��ǥ��ġ ���.
	Node* startNode = nullptr;
	Node* goalNode = nullptr;

	// �޽���
	Message* msg;
};