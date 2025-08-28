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
	// 방향 처리를 위한 구조체
	struct Direction
	{
		// 위치
		int x = 0;
		int y = 0;

		// 이동 비용.
		float cost = 0.0f;
	};

public:
	AStar();
	~AStar();

	// 경로 탐색 함수
	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		vector<vector<LevelGrid>>& grids
	);

	// 완성된 경로 출력
	void DisplayConstructedPath(std::vector<std::vector<LevelGrid>>& grids, const std::vector<Node*>& path);

	// 경로 탐색 출력
	void DisplayPathSearch(std::vector<std::vector<LevelGrid>>& grids);

	// 경로 초기화(경로 탐색 실패 시 호출)
	void ClearPath(std::vector<std::vector<LevelGrid>>& grids);

private:
	// 탐색을 마친 후에 경로를 조립해 반환하는 함수
	// 목표 노드에서 부모 노드를 참조해 시작 노드까지 역추적하며 경로를 구함.
	std::vector<Node*> ConstructPath(Node* goalNode);

	// 탐색하려는 노드가 목표 노드인지 확인
	bool IsDestination(const Node* node);

	// 그리드 안에 있는지 확인
	bool IsInRange(int x, int y, const vector<vector<LevelGrid>>& grids);

	// 이미 방문했는지 확인하는 함수
	bool HasVisited(int x, int y, float gCost);

	// 현재 지점에서 목표 지점까지의 추정 비용 계산 함수
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

private:
	// 열린 리스트(방문할 노드의 목록)
	vector<Node*> openList;

	// 닫힌 리스트(방문한 노드의 목록)
	vector<Node*> closedList;

	// 시작 노드.
	Node* startNode = nullptr;

	// 목표 노드.
	Node* goalNode = nullptr;
};
