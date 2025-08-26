#include "AStar.h"
#include "Node.h"
#include "Actor/LevelGrid.h"

#include <Windows.h>

AStar::AStar()
{
}

AStar::~AStar()
{
	// 메모리 해체
	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	openList.clear();

	for (Node* node : closedList)
	{
		SafeDelete(node);
	}
	closedList.clear();
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, vector<vector<LevelGrid>>& grids)
{
	// 시작 노드 / 목표 노드 저장
	this->startNode = startNode;
	this->goalNode = goalNode;

	// 시작 노드를 열린 목록(openlist)에 저장
	openList.emplace_back(startNode);

	// 상하좌우, 대각선 방향 및 비용.
	std::vector<Direction> directions =
	{
		// 하상우좌 이동.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// 대각선 이동.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f}, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};

	// 방문
	while (!openList.empty())
	{
		// 가장 비용이 작은 노드 선택
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		// fCost가 가장 낮은 노드를 현재 노드로 
		Node* currentNode = lowestNode;

		// 현재 노드가 목표 노드인지 확인.
		if (IsDestination(currentNode))
		{
			// 목표 노드라면, 지금까지의 경로를 계산해서 반환.
			return ConstructPath(currentNode);
		}

		// 닫힌 목록에 추가 (열린 목록에서는 제거)
		for (int idx = 0; idx < (int)openList.size(); ++idx)
		{
			// 위치 비교
			if (*openList[idx] == *currentNode)
			{
				// iterator를 활용해 동적 배열에서 노드 제거
				openList.erase(openList.begin() + idx);
				break;
			}
		}

		// 현재 노드를 닫힌 목록에 추가
		// 이미 있으면 추가 안하고 없으면 추가
		bool isNodeList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeList = true;
				break;
			}
		}

		// 방문 했으면 아래 단계 건너뛰기
		if (isNodeList)
		{
			continue;
		}

		// 목록에 추가
		closedList.emplace_back((currentNode));
	
		// 이웃 노드 방문
		for (const Direction& direction : directions)
		{
			// 다음에 이동하 ㄹ위치 설정
			int newX = currentNode->GetPosition().x + direction.x;
			int newY = currentNode->GetPosition().y + direction.y;

			// TODO : 그리드 밖인지 확인
			if (!IsInRange(newX, newY, grids))
			{
				// /그리드 밖이면 무시.
				continue;
			}

			// (옵션) 장애물인지 확인
			// 값이 1이면 장애물이라고 약속
			if (grids[newY][newX].GetType() == GridType::Wall)
			{
				continue;
			}

			// 이미 방문했어도 무시
			// 이미 방문했는지 확인하는 함수 작성 후 호출.
			float gCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, gCost))
			{
				continue;
			}

			// 방문을 위한 노드 생성
			// 비용도 계산
			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			// 휴리스틱 비용 계산 함수 작성 후 호출
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			// 이웃 노드가 열린 리스트에 있는지 확인
			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			if (openListNode == nullptr ||
				openListNode->gCost > neighborNode->gCost ||
				openListNode->fCost > neighborNode->fCost)
			{
				// 방문할 노드를 특정 값으로 설정
				grids[newY][newX].SetType(GridType::Path);

				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}

			// 딜레이
			DisplayGrid(grids);
			int delay = (int)(0.1f * 1000);
			Sleep(delay * 0.3);
		}
	}

	return std::vector<Node*>();
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	// TODO : 경로 반환하는 함수 로직 구현해야 함.


	vector<Node*> path;
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	// 지금까지의 경로는 목표 -> 시작 노드 방향
	// 따라서 이 순서를 뒤집어야 함.
	reverse(path.begin(), path.end());
	return path;
}

bool AStar::IsDestination(const Node* node)
{
	// 노드가 목표 노드와 위치가 같은지 비교.
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const vector<vector<LevelGrid>>& grid)
{
	// x, y 범위가 벗어나면 false.
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// 열린 리스트나 닫힌 리스트에 이미 해당 노드가 있으면 방문한 것으로 판단
	for (int idx = 0; idx < (int)openList.size(); ++idx)
	{
		Node* node = openList[idx];
		if (node->GetPosition().x == x && node->GetPosition().y == y)
		{
			// 위치가 같고, 비용도 더 크면 방문할 이유 없음.
			if (node->gCost < gCost)
			{
				return true;
			}
			else if (node->gCost > gCost)
			{
				openList.erase(openList.begin() + idx);
				SafeDelete(node);
			}
		}
	}

	for (int idx = 0; idx < (int)closedList.size(); ++idx)
	{
		Node* node = closedList[idx];
		if (node->GetPosition().x == x && node->GetPosition().y == y)
		{
			// 위치가 같고, 비용도 높으면 방문할 이유 없음.
			if (node->gCost < gCost)
			{
				return true;
			}
			// 위치는 같으나 비용이 작다면, 기존 노드 제거.
			else if (node->gCost > gCost)
			{
				closedList.erase(closedList.begin() + idx);
				SafeDelete(node);
			}
		}
	}

	return false;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
	// 단순 거리 계산으로 휴리스틱 비용으로 활용
	Vector2 diff = *currentNode - *goalNode;
	return (float)sqrt(diff.x * diff.x + diff.y * diff.y);
}

void AStar::DisplayGridWithPath(std::vector<std::vector<LevelGrid>>& grids, const std::vector<Node*>& path)
{
	static COORD position = { 0, 0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int green = FOREGROUND_GREEN;

	// 구분을 위해 설정했던 데이터 초기화.
	for (int y = 0; y < grids.size(); ++y)
	{
		for (int x = 0; x < grids[0].size(); ++x)
		{
			GridType type = grids[y][x].GetType();
			// 2, 3, 5 
			if (type == GridType::Start || type == GridType::Goal || type == GridType::Path)
			{
				grids[y][x].SetType(GridType::Goal);
			}
		}
	}

	//// 경로를 제외한 맵 출력.
	//for (int y = 0; y < grids.size(); ++y)
	//{
	//	for (int x = 0; x < grids[0].size(); ++x)
	//	{
	//		// 장애물.
	//		if (grids[y][x].GetType() == GridType::Wall)
	//		{
	//			SetConsoleTextAttribute(handle, white);
	//			std::cout << "1";
	//		}


	//		// 빈 공간.
	//		else if (grids[y][x].GetType() == GridType::Ground)
	//		{
	//			SetConsoleTextAttribute(handle, white);
	//			std::cout << " ";
	//		}
	//	}

	//	std::cout << "\n";
	//}

	// 경로 출력.
	for (const Node* node : path)
	{
		// 경로는 '2'로 표시.
		COORD position{ static_cast<short>(node->GetPosition().x), static_cast<short>(node->GetPosition().y)};
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE);

		std::cout << "+";
		int delay = static_cast<int>(0.05f * 1000);
		Sleep(delay);
	}
}

void AStar::DisplayGrid(std::vector<std::vector<LevelGrid>>& grids)
{
	static COORD position = { 0, 0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int green = FOREGROUND_GREEN;

	for (int y = 0; y < grids.size(); ++y)
	{
		for (int x = 0; x < grids[0].size(); ++x)
		{
			// 시작 위치.
			if (grids[y][x].GetType() == GridType::Start)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "S";
			}

			// 목표 위치.
			if (grids[y][x].GetType() == GridType::Goal)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "G";
			}

			// 장애물.
			if (grids[y][x].GetType() == GridType::Wall)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "1";
			}

			// 경로.
			else if (grids[y][x].GetType() == GridType::Path)
			{
				SetConsoleTextAttribute(handle, green);
				std::cout << "+";
			}

			// 빈 공간.
			else if (grids[y][x].GetType() == GridType::Ground)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << " ";
			}
		}

		std::cout << "\n";
	}
}