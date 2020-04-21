#pragma once
#include "checkbox.h"

DWORD fdwSaveOldMode;

int main(int argc, char const* argv[])
{
	CheckList checkList(7, { 10, 4 }, { 10, 10 });
	checkList.draw();

	int counter = 0;

	// Save the current input mode, to be restored on exit.

	if (!GetConsoleMode(checkList.getIn(), &fdwSaveOldMode))
		cout << "GetConsoleMode";

	// Enable the window and mouse input events.
	checkList.setFmMode(ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	if (!SetConsoleMode(checkList.getIn(), checkList.getFmMode()))
		cout << "SetConsoleMode";

	// Loop to read and handle the next 100 input events.

	while (counter++ <= 100)
	{
		if (checkList.inHandle() != UNKNOWN_EVENT_TYPE)
		{
			cout << "ErrorInEventType";
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(checkList.getIn(), fdwSaveOldMode);

	return 0;
}
