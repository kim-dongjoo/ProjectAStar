#pragma once

#include "Level/Level.h"
#include "AStar/AStar.h"
#include "AStar/Node.h"
#include "Actor/LevelGrid.h"
#include "Interface//ICanPlayerMove.h"

class AStarLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(AStarLevel, Level)

public:
	AStarLevel();

	virtual void Render() override;

	// ICanPlayerMove��(��) ���� ��ӵ�
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;



	// ���� ��ġ ������Ʈ
	void UpdateStartPosition(Vector2 position);

	// ��ǥ ��ġ ������Ʈ
	void UpdateGoalPosition(Vector2 position);

	// A-star �˰����� ���� �̵� ����
	void StartAStar();

private:
	void ReadMapFile(const char* filename);

	//  ���� Ŭ���� Ȯ���ϴ� �Լ�
	bool CheckGameClear();

private:
	// =======================
	// TODO : ���� ���� �ʿ�

	// ���� Ŭ��� ���� ����
	int targetScore = 0;

	// ���� Ŭ���� ���� Ȯ�� ����
	bool isGameClear = false;
	// =======================

	// A* ��ü
	AStar aStar;

	// �� �׸���
	std::vector<std::vector<LevelGrid>> grids;

	// �� ������
	Vector2 Size;

	// ���� ��ġ�� ��ǥ��ġ ���.
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};