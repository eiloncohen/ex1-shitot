#ifndef TEXT_BOX_H
#define TEXT_BOX_H
#include <windows.h>
#include <iostream>

using namespace std;

#define BORDER_OFFSET (1)
#define TOP_LEFT_CORNER '\xDA'
#define TOP_RIGHT_CORNER '\xBF'
#define BTM_LEFT_CORNER '\xC0'
#define BTM_RIGHT_CORNER '\xD9'
#define LINE_VERTICAL '\xB3'
#define LINE_HORIZONTAL '\xC4'
#define BACKSPACE '\x08'
#define SPACE '\x20'
#define CHAR_RESET '\x0'
#define ENTER '\x0D'



class TextBox {
protected:
	CONSOLE_SCREEN_BUFFER_INFO _cursor;
	COORD _tbPos, _tbSize;
	HANDLE _in, _out;

public:
	TextBox(COORD tbSize = {0,0}, COORD tbPos = { 0,0 });
	~TextBox() {}

	void setColor(DWORD color);
	void drawTB();
	void draw(char open_sym, char mid_sym, char close_sym);
	void textInput();

};

void printTitle();

#endif