#pragma once

#include <iostream>
#include <windows.h>
#include <vector>

typedef enum
{
	SUCCESS,
	ERROR_READ_CONSOLE_INPUT,
	UNKNOWN_EVENT_TYPE
} ErrorCode;

using namespace std;

class CheckList
{

private:
	int count;
	HANDLE in, out;
	COORD coord, dim, curr;
	DWORD fdwMode;
	void keyEventProc(KEY_EVENT_RECORD ker);

public:
	CheckList(int count, COORD dim, COORD pos);
	~CheckList();

	void setFmMode(DWORD fdwMode);
	DWORD getFmMode();
	HANDLE getIn();
	ErrorCode inHandle();
	void draw();
	void print(string brac, string opt, size_t num);
	void choosen();
};
COORD GetConsoleCursorPosition(HANDLE out);
