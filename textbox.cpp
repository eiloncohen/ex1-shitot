#include "textbox.h"

static COORD GetCursorPosition(HANDLE h_out)
{
	CONSOLE_SCREEN_BUFFER_INFO cScreenInfo;
	if (GetConsoleScreenBufferInfo(h_out, &cScreenInfo))
	{
		return cScreenInfo.dwCursorPosition;
	}
	else
	{
		cout << "get curser position function faild corser position return is {0,0}" << endl;
		return {0, 0};
	}
}

TextBox::TextBox(COORD tbSize, COORD tbPos) : _tbSize(tbSize), _tbPos(tbPos), _stepCount(0)
{

	_hIn = GetStdHandle(STD_INPUT_HANDLE);
	_hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (_hIn == INVALID_HANDLE_VALUE || _hOut == INVALID_HANDLE_VALUE)
	{
		cout << "constructor function, in or out io handle is invalid" << endl;
	}
}

//draw text box
void TextBox::drawTB()
{

	SetConsoleCursorPosition(_hOut, _tbPos);

	draw(TOP_LEFT_CORNER, LINE_HORIZONTAL, TOP_RIGHT_CORNER);
	SetConsoleCursorPosition(_hOut, {_tbPos.X, _tbPos.Y + 1});

	for (size_t i = 0; i < _tbSize.Y; i++)
	{
		draw(LINE_VERTICAL, SPACE, LINE_VERTICAL);
		SetConsoleCursorPosition(_hOut, {_tbPos.X, _tbPos.Y + 2 + ((short)i)});
	}

	draw(BTM_LEFT_CORNER, LINE_HORIZONTAL, BTM_RIGHT_CORNER);
	SetConsoleCursorPosition(_hOut, {_tbPos.X + 1, _tbPos.Y + 1});
}

// draw by symbols:
void TextBox::draw(char open_sym, char mid_sym, char close_sym)
{

	for (size_t i = 0; i < _tbSize.X - 1; i++)
	{
		if (i == 0)
		{
			cout << open_sym;
		}
		else
		{
			cout << mid_sym;
		}
	}
	cout << close_sym;
}

// input handle:
void TextBox::textInput()
{
	INPUT_RECORD record;
	DWORD read_bytes, fdw_mode;
	CONSOLE_SCREEN_BUFFER_INFO info;

	fdw_mode = ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;

	ReadConsoleInput(_hIn, &record, 1, &read_bytes);
	SetConsoleMode(_hIn, fdw_mode);

	switch (record.EventType)
	{
	case KEY_EVENT:
		GetConsoleScreenBufferInfo(_hIn, &info);
		if (record.Event.KeyEvent.bKeyDown)
		{
			if (record.Event.KeyEvent.uChar.AsciiChar == BACKSPACE)
			{
				if (GetCursorPosition(_hOut).X - 1 == _tbPos.X)
				{
					if (GetCursorPosition(_hOut).Y - 1 > _tbPos.Y)
					{
						SetConsoleCursorPosition(_hOut, {_tbPos.X + _tbSize.X - BORDER_OFFSET, GetCursorPosition(_hOut).Y - ((short)1)});
						cout << CHAR_RESET;
						SetConsoleCursorPosition(_hOut, {GetCursorPosition(_hOut).X - 1, GetCursorPosition(_hOut).Y});
					}
					else
					{
						break;
					}
				}
				else
				{
					cout << BACKSPACE << CHAR_RESET;
					SetConsoleCursorPosition(_hOut, {GetCursorPosition(_hOut).X - 1, GetCursorPosition(_hOut).Y});
				}
			}
			else if (record.Event.KeyEvent.uChar.AsciiChar == ENTER)
			{
				if (GetCursorPosition(_hOut).Y < _tbSize.Y + _tbPos.Y)
				{
					SetConsoleCursorPosition(_hOut, {_tbPos.X + 1, GetCursorPosition(_hOut).Y + ((short)1)});
				}
				else
				{
					break;
				}
			}
			else if (record.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
			{
				if (0 == GetCursorPosition(_hOut).Y - _tbPos.Y - 1 && 0 == GetCursorPosition(_hOut).X - _tbPos.X - 1)
					break;
				else
				{
					if (GetCursorPosition(_hOut).X - _tbPos.X - 1 > 0)
					{
						SetConsoleCursorPosition(_hOut, {GetCursorPosition(_hOut).X - 1, GetCursorPosition(_hOut).Y});
						_stepCount++;
					}
					else if (GetCursorPosition(_hOut).X - _tbPos.X - 1 == 0 && GetCursorPosition(_hOut).Y > _tbPos.Y + 1)
					{
						SetConsoleCursorPosition(_hOut, {_tbPos.X + _tbSize.X - BORDER_OFFSET, GetCursorPosition(_hOut).Y - ((short)1)});
						_stepCount++;
					}
				}
			}
			else if (record.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
			{
				if (_stepCount == 0)
					break;
				else
				{
					if (GetCursorPosition(_hOut).X < _tbPos.X + _tbSize.X - BORDER_OFFSET)
					{
						SetConsoleCursorPosition(_hOut, {GetCursorPosition(_hOut).X + 1, GetCursorPosition(_hOut).Y});
						_stepCount--;
					}
					else if (GetCursorPosition(_hOut).X == _tbPos.X + _tbSize.X - BORDER_OFFSET && GetCursorPosition(_hOut).Y < _tbSize.Y + _tbPos.Y)
					{
						SetConsoleCursorPosition(_hOut, {_tbPos.X + 1, GetCursorPosition(_hOut).Y + ((short)1)});
						_stepCount--;
					}
				}
			}
			else if (GetCursorPosition(_hOut).X + 1 == _tbSize.X + _tbPos.X)
			{
				if (GetCursorPosition(_hOut).Y < _tbSize.Y + _tbPos.Y)
				{
					SetConsoleCursorPosition(_hOut, {_tbPos.X + 1, GetCursorPosition(_hOut).Y + ((short)1)});
				}
			}
			else
			{
				cout << record.Event.KeyEvent.uChar.AsciiChar;
			}
		}
		break;
	}
}

void TextBox::setColor(DWORD color)
{
	SetConsoleTextAttribute(_hOut, color);
}

void printTitle()
{
	cout << "text box:" << endl
		 << endl;
}