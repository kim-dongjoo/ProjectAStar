#pragma once

#include <vector>

template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

class Node;
class LevelGrid;

using namespace std;

class AStar
{
	// ���� ó���� ���� ����ü
	struct Direction
	{
		// ��ġ
		int x = 0;
		int y = 0;

		// �̵� ���.
		float cost = 0.0f;
	};

public:
	AStar();
	~AStar();

	// ��� Ž�� �Լ�
	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		vector<vector<LevelGrid>>& grids
	);

	// �ϼ��� ��� ���
	void DisplayConstructedPath(std::vector<std::vector<LevelGrid>>& grids, const std::vector<Node*>& path);

	// ��� Ž�� ���
	void DisplayPathSearch(std::vector<std::vector<LevelGrid>>& grids);

	// ��� �ʱ�ȭ(��� Ž�� ���� �� ȣ��)
	void ClearPath(std::vector<std::vector<LevelGrid>>& grids);

private:
	// Ž���� ��ģ �Ŀ� ��θ� ������ ��ȯ�ϴ� �Լ�
	// ��ǥ ��忡�� �θ� ��带 ������ ���� ������ �������ϸ� ��θ� ����.
	std::vector<Node*> ConstructPath(Node* goalNode);

	// Ž���Ϸ��� ��尡 ��ǥ ������� Ȯ��
	bool IsDestination(const Node* node);

	// �׸��� �ȿ� �ִ��� Ȯ��
	bool IsInRange(int x, int y, const vector<vector<LevelGrid>>& grids);

	// �̹� �湮�ߴ��� Ȯ���ϴ� �Լ�
	bool HasVisited(int x, int y, float gCost);

	// ���� �������� ��ǥ ���������� ���� ��� ��� �Լ�
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

private:
	// ���� ����Ʈ(�湮�� ����� ���)
	vector<Node*> openList;

	// ���� ����Ʈ(�湮�� ����� ���)
	vector<Node*> closedList;

	// ���� ���.
	Node* startNode = nullptr;

	// ��ǥ ���.
	Node* goalNode = nullptr;
};
