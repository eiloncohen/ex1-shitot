#include "checkbox.h"

CheckList::CheckList(int count, COORD coord, COORD dim) : count(count), dim(dim), coord(coord)
{
	in = GetStdHandle(STD_INPUT_HANDLE);
	out = GetStdHandle(STD_OUTPUT_HANDLE);
	if (in == INVALID_HANDLE_VALUE || out == INVALID_HANDLE_VALUE)
	{
		cout << "constructor function, in or out io handle is invalid" << endl;
	}
}

CheckList::~CheckList() {}

COORD GetConsoleCursorPosition(HANDLE out) {
	CONSOLE_SCREEN_BUFFER_INFO console;
	if (GetConsoleScreenBufferInfo(out, &console)) {
		return console.dwCursorPosition;
	}
	else {
		return { 0, 0 };
	}
}

void CheckList::draw()
{
	COORD tmp;
	tmp.Y = coord.Y;
	SetConsoleCursorPosition(out, coord);
	cout << "Wellcome to our check box list!\n";
	coord.X = 10;
	coord.Y = tmp.Y + 1;
	SetConsoleCursorPosition(out, coord);
	for (int i = 0; i < count; i++)
	{
		print("[ ]", " Option number- ", i);
		coord.Y = coord.Y + 1;
		SetConsoleCursorPosition(out, coord);
	}
	SetConsoleCursorPosition(out, coord);
}

void CheckList::print(string brac, string opt, size_t num)
{
	cout << brac << opt << num;
}

void CheckList::choosen()
{
	//todo
}
void CheckList::keyEventProc(KEY_EVENT_RECORD ker)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(in, &info);
	curr = GetConsoleCursorPosition(out);
	if (ker.bKeyDown)
	{
		if (ker.wVirtualKeyCode)
		{
			if (0x28)
			{
				curr.Y++;
				SetConsoleCursorPosition(out, curr);
			}
			else if (VK_UP)
			{
				curr.Y--;
				SetConsoleCursorPosition(out, curr);
			}
			else if (VK_SPACE)
			{
				choosen();
			}
			
		}
	}
}
HANDLE CheckList::getIn() {
	return this->in;
}
void CheckList::setFmMode(DWORD fdwMode) {
	this->fdwMode = fdwMode;
}
DWORD CheckList::getFmMode() {
	return this->fdwMode;
}
ErrorCode CheckList::inHandle()
{
	INPUT_RECORD irInBuf;
	DWORD cNumRead;
	// Wait for the events.

	ReadConsoleInput(in, &irInBuf, 1, &cNumRead);
	SetConsoleMode(in, fdwMode);

	// Dispatch the events to the appropriate handler.

	for (DWORD i = 0; i < cNumRead; i++)
	{
		switch (irInBuf.EventType)
		{
		case KEY_EVENT: // keyboard input
			keyEventProc(irInBuf.Event.KeyEvent);
			break;

		default:
			return UNKNOWN_EVENT_TYPE;
		}
	}
	return SUCCESS;
}
