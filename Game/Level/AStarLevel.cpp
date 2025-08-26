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

	if (isGameClear)
	{
		Utils::SetConsolePosition({ 30, 0 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "==== Game Clear! ====";
	}

}

void AStarLevel::ReadMapFile(const char* filename)
{
	// 최종 애셋 경로 완성
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Contents/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// 예외 처리
	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패 (" << filename << ")" << std::endl;
		__debugbreak();
		return;
	}

	// 파싱
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 확인한 파일 크기를 활용해 버퍼 할당.
	char* buffer = new char[fileSize + 1];
	// memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	buffer[fileSize] = '\0';

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize. \n";
	}

	// 배열 순회를 위한 인덱스 변수
	int index = 0;

	// 문자열 길이값
	int size = (int)readSize;

	// x, y 좌표
	Vector2 position;

	// 그리드 사이즈 예약
	grids.reserve(size);

	// 행 데이터 받아올 임시 행 벡터
	std::vector<LevelGrid> row;

	// 문자 배열 순회
	while (index < size)
	{
		// 맵 문자 확인
		char mapCharacter = buffer[index++];

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			// 그리드 행 삽입 후 변수 초기화
			grids.push_back(row);
			row.clear();

			++position.y;
			position.x = 0;

			// 테스트 코드
			std::cout << std::endl;
			continue;
		}

		switch (mapCharacter)
		{
			LevelGrid* grid;
		case '#':
		case '1':
			grid = new LevelGrid(position, '1', Color::White, GridType::Wall);
			row.push_back(*grid);
			SpawnActor(grid);
			break;
		case ' ':
			grid = new LevelGrid(position, ' ', Color::White, GridType::Ground);
			row.push_back(*grid);
			SpawnActor(grid);
			break;
		case '*':
			grid = new LevelGrid(position, ' ', Color::White, GridType::Ground);
			row.push_back(*grid);
			SpawnActor(grid);

			// 플레이어(*)도 스폰
			SpawnActor(new Player(position));
			break;
		case 'S':
			// 시작 노드 값 설정
			startNode = new Node(position.x, position.y);

			grid = new LevelGrid(position, 'S', Color::Green, GridType::Start);
			row.push_back(*grid);
			SpawnActor(grid);
			break;
		case 'G':
			// 목표 노드 값 설정
			goalNode = new Node(position.x, position.y);

			grid = new LevelGrid(position, 'G', Color::Red, GridType::Goal);
			row.push_back(*grid);
			SpawnActor(grid);
			break;
		}

		// x 좌표 증가 처리
		++position.x;
	}

	// 맵 사이즈 저장
	Size.y = grids.size();
	Size.x = grids[0].size();

	// 버퍼 해제
	delete[] buffer;

	// 파일 닫기
	fclose(file);
}

bool AStarLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
	// 게임 클리어 여부 확인 및 종료 처리
	if (isGameClear)
	{
		return false;
	}

	// 이동할 위치가 맵 벗어나는지 확인
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

void AStarLevel::UpdateStartPosition(Vector2 position)
{
}

void AStarLevel::UpdateGoalPosition(Vector2 position)
{
}

void AStarLevel::StartAStar()
{
	std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grids);

	// 경로 탐색에 성공한 경우 관련 정보 출력.
	if (!path.empty())
	{
		// 경로 탐색 결과 2차원 맵 출력.
		std::cout << "경로를 맵에 표시한 결과:\n";
		aStar.DisplayGridWithPath(grids, path);
	}
}