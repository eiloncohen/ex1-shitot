#include "textbox.h"
#include "label.h"

#define TBC (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE)
#define REG (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define TB_HEIGHT (2)
#define TB_WIDTH (25)
#define SCREEN_POS_X (30)
#define SCREEN_POS_Y (10)

int main()
{
	// label test
	label l = new label("my new label" , {10,7}); 
    l.printLableToConsole();
    l.setColor(FOREGROUND_BLUE , BACKGROUND_RED);
    while(1); 

	// textBox test
	
	COORD tb_size = {TB_WIDTH, TB_HEIGHT};
	COORD tb_pos = {SCREEN_POS_X, SCREEN_POS_Y};


	TextBox text_box(tb_size, tb_pos);
	printTitle();
	text_box.setColor(TBC);
	text_box.drawTB();
	int count = 0;
	while (count < 100)
	{
		text_box.textInput();
		count++;
	}
	text_box.setColor(REG);

	return 1;
}
