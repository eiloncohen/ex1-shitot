#include "label.h"

int main(int argc , char * argv[])
{
    label l = new label("my new label" , {10,7}); 
    l.printLableToConsole();
    l.setColor(FOREGROUND_BLUE , BACKGROUND_RED)
    while(1);
    return 0;
}



