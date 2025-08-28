#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

class Message
{
public:
	Message();
	~Message();

	void ShowMessage(string message);
	void ShowMessage(string message, COORD position);
	void ShowMessage(string message, COORD position, int color);

private:
	HANDLE handle;

	string message = "";

	COORD position = { 0, 20 };

	int color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
};