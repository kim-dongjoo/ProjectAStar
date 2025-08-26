#include "AStar.h"
#include "Node.h"
#include "Actor/LevelGrid.h"

#include <Windows.h>

AStar::AStar()
{
}

AStar::~AStar()
{
	// �޸� ��ü
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
	// ���� ��� / ��ǥ ��� ����
	this->startNode = startNode;
	this->goalNode = goalNode;

	// ���� ��带 ���� ���(openlist)�� ����
	openList.emplace_back(startNode);

	// �����¿�, �밢�� ���� �� ���.
	std::vector<Direction> directions =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f}, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};

	// �湮
	while (!openList.empty())
	{
		// ���� ����� ���� ��� ����
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		// fCost�� ���� ���� ��带 ���� ���� 
		Node* currentNode = lowestNode;

		// ���� ��尡 ��ǥ ������� Ȯ��.
		if (IsDestination(currentNode))
		{
			// ��ǥ �����, ���ݱ����� ��θ� ����ؼ� ��ȯ.
			return ConstructPath(currentNode);
		}

		// ���� ��Ͽ� �߰� (���� ��Ͽ����� ����)
		for (int idx = 0; idx < (int)openList.size(); ++idx)
		{
			// ��ġ ��
			if (*openList[idx] == *currentNode)
			{
				// iterator�� Ȱ���� ���� �迭���� ��� ����
				openList.erase(openList.begin() + idx);
				break;
			}
		}

		// ���� ��带 ���� ��Ͽ� �߰�
		// �̹� ������ �߰� ���ϰ� ������ �߰�
		bool isNodeList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeList = true;
				break;
			}
		}

		// �湮 ������ �Ʒ� �ܰ� �ǳʶٱ�
		if (isNodeList)
		{
			continue;
		}

		// ��Ͽ� �߰�
		closedList.emplace_back((currentNode));
	
		// �̿� ��� �湮
		for (const Direction& direction : directions)
		{
			// ������ �̵��� ����ġ ����
			int newX = currentNode->GetPosition().x + direction.x;
			int newY = currentNode->GetPosition().y + direction.y;

			// TODO : �׸��� ������ Ȯ��
			if (!IsInRange(newX, newY, grids))
			{
				// /�׸��� ���̸� ����.
				continue;
			}

			// (�ɼ�) ��ֹ����� Ȯ��
			// ���� 1�̸� ��ֹ��̶�� ���
			if (grids[newY][newX].GetType() == GridType::Wall)
			{
				continue;
			}

			// �̹� �湮�߾ ����
			// �̹� �湮�ߴ��� Ȯ���ϴ� �Լ� �ۼ� �� ȣ��.
			float gCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, gCost))
			{
				continue;
			}

			// �湮�� ���� ��� ����
			// ��뵵 ���
			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			// �޸���ƽ ��� ��� �Լ� �ۼ� �� ȣ��
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			// �̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��
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
				// �湮�� ��带 Ư�� ������ ����
				grids[newY][newX].SetType(GridType::Path);

				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}

			// ������
			DisplayGrid(grids);
			int delay = (int)(0.1f * 1000);
			Sleep(delay * 0.3);
		}
	}

	return std::vector<Node*>();
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	// TODO : ��� ��ȯ�ϴ� �Լ� ���� �����ؾ� ��.


	vector<Node*> path;
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	// ���ݱ����� ��δ� ��ǥ -> ���� ��� ����
	// ���� �� ������ ������� ��.
	reverse(path.begin(), path.end());
	return path;
}

bool AStar::IsDestination(const Node* node)
{
	// ��尡 ��ǥ ���� ��ġ�� ������ ��.
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const vector<vector<LevelGrid>>& grid)
{
	// x, y ������ ����� false.
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// ���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��尡 ������ �湮�� ������ �Ǵ�
	for (int idx = 0; idx < (int)openList.size(); ++idx)
	{
		Node* node = openList[idx];
		if (node->GetPosition().x == x && node->GetPosition().y == y)
		{
			// ��ġ�� ����, ��뵵 �� ũ�� �湮�� ���� ����.
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
			// ��ġ�� ����, ��뵵 ������ �湮�� ���� ����.
			if (node->gCost < gCost)
			{
				return true;
			}
			// ��ġ�� ������ ����� �۴ٸ�, ���� ��� ����.
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
	// �ܼ� �Ÿ� ������� �޸���ƽ ������� Ȱ��
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

	// ������ ���� �����ߴ� ������ �ʱ�ȭ.
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

	//// ��θ� ������ �� ���.
	//for (int y = 0; y < grids.size(); ++y)
	//{
	//	for (int x = 0; x < grids[0].size(); ++x)
	//	{
	//		// ��ֹ�.
	//		if (grids[y][x].GetType() == GridType::Wall)
	//		{
	//			SetConsoleTextAttribute(handle, white);
	//			std::cout << "1";
	//		}


	//		// �� ����.
	//		else if (grids[y][x].GetType() == GridType::Ground)
	//		{
	//			SetConsoleTextAttribute(handle, white);
	//			std::cout << " ";
	//		}
	//	}

	//	std::cout << "\n";
	//}

	// ��� ���.
	for (const Node* node : path)
	{
		// ��δ� '2'�� ǥ��.
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
			// ���� ��ġ.
			if (grids[y][x].GetType() == GridType::Start)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "S";
			}

			// ��ǥ ��ġ.
			if (grids[y][x].GetType() == GridType::Goal)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "G";
			}

			// ��ֹ�.
			if (grids[y][x].GetType() == GridType::Wall)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "1";
			}

			// ���.
			else if (grids[y][x].GetType() == GridType::Path)
			{
				SetConsoleTextAttribute(handle, green);
				std::cout << "+";
			}

			// �� ����.
			else if (grids[y][x].GetType() == GridType::Ground)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << " ";
			}
		}

		std::cout << "\n";
	}
}