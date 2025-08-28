#include "Message.h"

Message::Message()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

Message::~Message()
{
	delete handle;
}

void Message::ShowMessage(string message)
{
	// 기존 메시지가 남아있다면 공백으로 덮어쓰기
	if (this->message.size() != 0)
	{
		SetConsoleCursorPosition(handle, position);
		for (int i = 0; i < this->message.size(); i++)
		{
			cout << " ";
		}
	}

	SetConsoleCursorPosition(handle, position);
	this->message = message;
	cout << message;
}

void Message::ShowMessage(string message, COORD position)
{
	// 기존 메시지가 남아있다면 공백으로 덮어쓰기
	if (this->message.size() != 0)
	{
		SetConsoleCursorPosition(handle, this->position);
		for (int i = 0; i < this->message.size(); i++)
		{
			cout << " ";
		}
	}

	SetConsoleCursorPosition(handle, position);
	this->message = message;
	cout << message;
}

void Message::ShowMessage(string message, COORD position, int color)
{
	// 기존 메시지가 남아있다면 공백으로 덮어쓰기
	if (this->message.size() != 0)
	{
		SetConsoleCursorPosition(handle, this->position);
		for (int i = 0; i < this->message.size(); i++)
		{
			cout << " ";
		}
	}

	SetConsoleTextAttribute(handle, color);
	SetConsoleCursorPosition(handle, position);
	this->message = message;
	cout << message;
}