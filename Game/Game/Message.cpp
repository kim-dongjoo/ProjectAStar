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
	// ���� �޽����� �����ִٸ� �������� �����
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
	// ���� �޽����� �����ִٸ� �������� �����
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
	// ���� �޽����� �����ִٸ� �������� �����
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