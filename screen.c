#include "screen.h"

void screen_init()
{
    video = (volatile unsigned char *)0xB8000;
    nextTextPos = 0;
    currLine = 0;
}
