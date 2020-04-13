#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

class label {

	string word; 
	DWORD color;
	COORD coord;

	label(string word, COORD coord)
	{
		this->word = word; 
		this->coord = coord;
	}
	string getWord() {
		return word;
	}
	void setWord(string word)
	{
		this->word = word;
	}
	COORD getCoord() {
		return coord;
	}
	void setCoord(COORD coord)
	{
		this->coord = coord;
	}
    void setColor(DWORD fg, DWORD bg){
        this.color = fg | bg;
    }
	void printLableToConsole()
	{
		auto outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(outHandle, coord);
        setConsoleTextAttribute(outHandle, color);
		cout << word;
		CONSOLE_CURSOR_INFO info = {1,0};
		SetConsoleCursorInfo(outHandle, &info);
	}
};