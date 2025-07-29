#include "SokobanLevel.h"
#include <iostream>
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Utils/Utils.h"

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Stage1.txt");
}

void SokobanLevel::Render()
{
	super::Render();

	if (isGameClear)
	{
		Utils::SetConsolePosition({ 30, 0 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "==== Game Clear! ====";
	}

}

void SokobanLevel::ReadMapFile(const char* filename)
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

	// 문자 배열 순회
	while (index < size)
	{
		// 맵 문자 확인
		char mapCharacter = buffer[index++];

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;

			// 테스트 코드
			std::cout << std::endl;
			continue;
		}

		switch (mapCharacter)
		{
		case '#':
		case '1':
			SpawnActor(new Wall(position));
			// std::cout << "#";
			break;
		case '.':
			SpawnActor(new Ground(position));
			// std::cout << ".";
			break;
		case 'p':
			// 땅도 같이 생성
			SpawnActor(new Ground(position));
			// std::cout << "p";
			SpawnActor(new Player(position));
			break;
		case 'b':
			// 땅도 같이 생성
			SpawnActor(new Ground(position));
			SpawnActor(new Box(position));
			// std::cout << "b";
			break;
		case 't':
			SpawnActor(new Target(position));
			targetScore++;
			// std::cout << "t";
			break;
		}

		// x 좌표 증가 처리
		++position.x;
	}

	// 버퍼 해제
	delete[] buffer;

	// 파일 닫기
	fclose(file);

}

bool SokobanLevel::CheckGameClear()
{
	//  박스가 타겟 위치에 모두 옮겨졌는지 확인
	int currentScore = 0;

	// 타겟 액터 벡터에 저장
	std::vector<Actor*> targetActors;
	std::vector<Actor*> boxActors;

	for (Actor* const actor : actors)
	{
		// 타겟 액터인지 확인
		if (actor->As<Target>())
		{
			targetActors.emplace_back(actor);
			continue;
		}

		// 박스 액터인지 확인
		if (actor->As<Box>())
		{
			boxActors.emplace_back(actor);
		}
	}

	// 박스와 타겟 위치 비교
	for (Actor* const targetActor : targetActors)
	{
		for (Actor* const boxActor : boxActors)
		{
			if (targetActor->GetPosition() == boxActor->GetPosition())
			{
				// 점수 증가
				++currentScore;
			}
		}
	}


	return currentScore == targetScore;



	return false;
}

bool SokobanLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
	// 게임 클리어 여부 확인 및 종료 처리
	if (isGameClear)
	{
		return false;
	}

	// 박스 처리
	std::vector<Box*> boxActors;
	for (Actor* const actor : actors)
	{
		Box* box = actor->As<Box>();
		if (box)
		{
			boxActors.emplace_back(box);
		}
	}

	// 이동하려는 위치에 박스가 있는지 확인
	Box* searchedBox = nullptr;
	for (Box* const boxActor : boxActors)
	{
		// 플레이어가 이동하려는 위치와 박스의 위치가 같은지 비교
		if (boxActor->GetPosition() == newPosition)
		{
			// 같은 위치에 있는 박스 저장 후 루프 종료
			searchedBox = boxActor;
			break;
		}
	}

	// 이동하려는 위치에 박스가 있는 경우 처리
	if (searchedBox)
	{
		// 1. 박스를 이동시키려는 위치에 다른 박스가 있는지 확인.
		Vector2 direction = newPosition - playerPosition;
		Vector2 nextPosition = searchedBox->GetPosition() + direction;

		for (Box* const otherBox : boxActors)
		{
			// 같은 박스는 건너뛰기
			if (otherBox == searchedBox)
				continue;

			if (otherBox->GetPosition() == nextPosition)
			{
				// 플레이어 이동 못함
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->GetPosition() == nextPosition)
			{
				// 2. 박스를 이동시키려는 위치에 벽이 있는지 확인

				if (actor->As<Wall>())
				{
					// 플레이어 이동 못함
					return false;
				}

				// 3. 이동 가능한 경우(그라운드/타겟) 이동처리
				if (actor->As<Ground>() || actor->As<Target>())
				{
					// 박스 이동 처리
					searchedBox->SetPosition(nextPosition);

					// 게임 클리어 여부 확인
					isGameClear = CheckGameClear();

					// 플레이어 이동 가능
						return true;
				}
			}
		}
	}

	// 플레이어가 이동하려는 위치에 박스가 없는 경우
	for (Actor* const actor : actors)
	{
		if (actor->GetPosition() == newPosition)
		{
			// 벽이면 이동 불가
			if (actor->As<Wall>())
			{
				return false;
			}

			// 그라운드 or 타겟
			return true;
		}
	}

	return false;
}
