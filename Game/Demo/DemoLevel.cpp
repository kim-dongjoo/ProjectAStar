#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	SpawnActor(new TestActor());

	// �׽�Ʈ�� �� ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, "../Contents/Map.txt", "rb");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "Failed to open Map.txt file." << std::endl;
		__debugbreak();
		return;
	}

	// ���� ũ�� Ȯ��
	// ���� ��ġ Ŀ���� ���� ������ �̵�.
	fseek(file, 0, SEEK_END);

	// �̵��� ������ ��ġ Ȯ��
	size_t fileSize = ftell(file);

	// ���� ��ġ Ŀ�� �ǵ�����
	rewind(file);

	// ������ ������ ���� ���� �Ҵ�.
	// char* buffer = new char[fileSize + 1];
	char buffer[256] = {};


	// ���� ���� �������� �ݺ�
	while (!feof(file))
	{
		// �� �پ� �б�
		fgets(buffer, 256, file);

		// �� �� ���ڿ��� ���̰� ���ϱ�
		int linelength = (int)strlen(buffer);

		// �Ľ�
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

	// ���� �ݱ�
	fclose(file);

}