#include <iostream>
#include <vector>

#include "AStarLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/LevelGrid.h"
#include "Utils/Utils.h"


AStarLevel::AStarLevel()
{
	ReadMapFile("Map.txt");
}

void AStarLevel::Render()
{
	super::Render();

	// Render Pass
	int width = grids[0].size();
	int height = grids.size();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			grids[y][x].Render();
		}
	}
}

void AStarLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Contents/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ���� (" << filename << ")" << std::endl;
		__debugbreak();
		return;
	}

	// �Ľ�
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	// memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	//buffer[fileSize] = '\0';

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize. \n";
	}

	// �迭 ��ȸ�� ���� �ε��� ����
	int index = 0;

	// ���ڿ� ���̰�
	int size = (int)readSize;

	// x, y ��ǥ
	Vector2 position;

	// �׸��� ������ ����
	grids.reserve(size);

	// �� ������ �޾ƿ� �ӽ� �� ����
	std::vector<LevelGrid> row;

	// ���� �迭 ��ȸ
	while (index < size)
	{
		// �� ���� Ȯ��
		char mapCharacter = buffer[index];
		index++;

		// ���� ���� ó��
		if (mapCharacter == '\n')
		{
			// �׸��� �� ���� �� ���� �ʱ�ȭ
			grids.push_back(row);
			row.clear();

			++position.y;
			position.x = 0;

			continue;
		}

		switch (mapCharacter)
		{
			LevelGrid* grid;
		case '#':
		case '1':
			grid = new LevelGrid(position, '1', Color::White, GridType::Wall);
			row.push_back(*grid);
			break;
		case ' ':
			grid = new LevelGrid(position, ' ', Color::White, GridType::Ground);
			row.push_back(*grid);
			break;
		case '*':
			grid = new LevelGrid(position, ' ', Color::White, GridType::Ground);
			row.push_back(*grid);

			// �÷��̾�(*)�� ����
			SpawnActor(new Player(position));
			break;
		case 'S':
			// ���� ��� �� ����
			startNode = new Node(position.x, position.y);

			grid = new LevelGrid(position, 'S', Color::Green, GridType::Start);
			grid->SetRenderSortingOrder(5);
			row.push_back(*grid);
			break;
		case 'G':
			// ��ǥ ��� �� ����
			goalNode = new Node(position.x, position.y);

			grid = new LevelGrid(position, 'G', Color::Red, GridType::Goal);
			grid->SetRenderSortingOrder(5);
			row.push_back(*grid);
			break;
		}

		// x ��ǥ ���� ó��
		++position.x;
	}

	// �� ������ ����
	Size.y = grids.size();
	Size.x = grids[0].size();

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}

bool AStarLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
	// ���� Ŭ���� ���� Ȯ�� �� ���� ó��
	if (isGameClear)
	{
		return false;
	}

	// �̵��� ��ġ�� �� ������� Ȯ��
	if (newPosition.x > Size.x - 1 || newPosition.y > Size.y - 1)
	{
		return false;
	}

	if (grids[newPosition.y][newPosition.x].GetType() == GridType::Wall)
	{
		return false;
	}

	return true;
}

void AStarLevel::ModifyGrid(Vector2 position, GridType type)
{
	// 1. ���� ��ġ ���� �� ���� ���� ��ġ ����
	if (type == GridType::Start)
	{
		if (grids[position.y][position.x].GetType() == GridType::Wall || grids[position.y][position.x].GetType() == GridType::Goal)
		{
			// ���� ��ġ�� ���������� �� �� �����ϴ�.
			std::cout << "���� ��ġ�� ���������� �� �� �����ϴ�.";
		}
		else if (grids[position.y][position.x].GetType() == GridType::Ground)
		{
			// ���� ���� ��ġ ����
			Vector2 prevPosition = startNode->GetPosition();
			grids[prevPosition.y][prevPosition.x].SetType(GridType::Ground);
			grids[prevPosition.y][prevPosition.x].SetImage(' ');
			grids[prevPosition.y][prevPosition.x].SetColor(Color::White);
			delete startNode;

			// ���ο� ������ ����
			grids[position.y][position.x].SetType(GridType::Start);
			grids[position.y][position.x].SetImage('S');
			grids[position.y][position.x].SetColor(Color::Green);
			startNode = new Node(position.x, position.y);
		}
	}

	// 2. ��ǥ ��ġ ���� �� ���� ��ǥ ��ġ ����
	if (type == GridType::Goal)
	{
		if (grids[position.y][position.x].GetType() == GridType::Wall || grids[position.y][position.x].GetType() == GridType::Start)
		{
			// ���� ��ġ�� ��ǥ �������� �� �� �����ϴ�.
			std::cout << "���� ��ġ�� ��ǥ �������� �� �� �����ϴ�.";
		}
		else if (grids[position.y][position.x].GetType() == GridType::Ground)
		{
			// ���� ���� ��ġ ����
			Vector2 prevPosition = goalNode->GetPosition();
			grids[prevPosition.y][prevPosition.x].SetType(GridType::Ground);
			grids[prevPosition.y][prevPosition.x].SetImage(' ');
			grids[prevPosition.y][prevPosition.x].SetColor(Color::White);
			delete goalNode;

			// ���ο� ������ ����
			grids[position.y][position.x].SetType(GridType::Goal);
			grids[position.y][position.x].SetImage('G');
			grids[position.y][position.x].SetColor(Color::Red);
			goalNode = new Node(position.x, position.y);
		}
	}

	// 3 ��ֹ� ���� �Ǵ� ���� 
	if (type == GridType::Wall)
	{
		if (grids[position.y][position.x].GetType() == GridType::Start || grids[position.y][position.x].GetType() == GridType::Goal)
		{
			// ���� ��ġ�� ��ǥ ��ġ���� ��ֹ��� ��ġ�� �� �����ϴ�.
			std::cout << "���� ��ġ�� ��ǥ ��ġ���� ��ֹ��� ��ġ�� �� �����ϴ�.";
		}
		else if (grids[position.y][position.x].GetType() == GridType::Ground) // Ground -> Wall
		{
			grids[position.y][position.x].SetType(GridType::Wall);
			grids[position.y][position.x].SetImage('1');
		}
		else if (grids[position.y][position.x].GetType() == GridType::Wall) // Wall -> Ground
		{
			grids[position.y][position.x].SetType(GridType::Ground);
			grids[position.y][position.x].SetImage(' ');
		}
	}
}

void AStarLevel::StartAStar()
{
	std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grids);

	// ��� Ž���� ������ ��� ���� ���� ���.
	if (!path.empty())
	{
		// ��� Ž�� ��� 2���� �� ���.
		std::cout << "��θ� �ʿ� ǥ���� ���:\n";
		aStar.DisplayGridWithPath(grids, path);
	}
}