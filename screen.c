#include "screen.h"

void screen_init()
{
    video = (volatile unsigned char *)0xB8000;
    nextTextPos = 0;
    currLine = 0;
}

//Print

void print(char *str)
{
    int currCharLocationInVidMem, currColorLocationInVidMem;

    while (*str != '\0')
    {
        currCharLocationInVidMem = nextTextPos * 2;
        currColorLocationInVidMem = currCharLocationInVidMem + 1;

        video[currCharLocationInVidMem] = *str;
        video[currColorLocationInVidMem]=  15;

        nextTextPos++;

        str++;
    }
}

void println()
{
    nextTextPos = ++currLine * 80;
}

void printi (int number)
{
    char* digitToStr[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    if (number>= 0 && number<= 9)
    {
        print(digitToStr[number]);
        return;
    }
    else{
        int remaining = number % 10;
        number = number/10;

        printi(number);
        printi(remaining);
    }
}

void print_hex(unsigned int value) {
    char hex_chars[] = "0123456789ABCDEF";
    char buffer[9];
    buffer[8] = '\0';  // Null-terminate the string

    for (int i = 7; i >= 0; i--) {
        buffer[i] = hex_chars[value & 0xF];
        value >>= 4;
    }

    print(buffer);
    println();
}
