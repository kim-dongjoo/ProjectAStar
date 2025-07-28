#include "SokobanLevel.h"
#include <iostream>
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::ReadMapFile(const char* filename)
{
	// 최종 애셋 경로 완성
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Contents/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rb");

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
