#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	SpawnActor(new TestActor());

	// 테스트로 맵 파일 읽기
	FILE* file = nullptr;
	fopen_s(&file, "../Contents/Map.txt", "rb");

	// 예외 처리
	if (file == nullptr)
	{
		std::cout << "Failed to open Map.txt file." << std::endl;
		__debugbreak();
		return;
	}

	// 파일 크기 확인
	// 파일 위치 커서를 가장 끝으로 이동.
	fseek(file, 0, SEEK_END);

	// 이동한 지점의 위치 확인
	size_t fileSize = ftell(file);

	// 파일 위치 커서 되돌리기
	rewind(file);

	// 데이터 저장을 위한 버퍼 할당.
	// char* buffer = new char[fileSize + 1];
	char buffer[256] = {};


	// 파일 종료 시점까지 반복
	while (!feof(file))
	{
		// 한 줄씩 읽기
		fgets(buffer, 256, file);

		// 한 줄 문자열의 길이값 구하기
		int linelength = (int)strlen(buffer);

		// 파싱
		for (int idx = 0; idx < linelength; ++idx)
		{
			char mapCharacter = buffer[idx];

			switch (mapCharacter)
			{
			case '#':
				std::cout << "#";
				break;
			case '.':
				std::cout << '.';
				break;
			case 'p':
				std::cout << 'p';
				break;
			case 'b':
				std::cout << 'b';
				break;
			case 't':
				std::cout << 't';
				break;
			}
		}

		std::cout << std::endl;
	}

	// 파일 닫기
	fclose(file);

}