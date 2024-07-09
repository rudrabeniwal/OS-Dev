#include "screen.h"
#include "scheduler.h"

volatile unsigned char *video = (volatile unsigned char *)0xB8000;

// Define the global variables here
process_t *processes [15];  
int processes_count;
int curr_pid;
int next_sch_pid;
int curr_sch_pid;
process_t *next_process;
int nextTextPos = 0;
int currLine = 0;

//Print

void print(char*);
void println();
void printi(int);

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
/* for filling all the screen blue
volatile unsigned char *video = 0xA0000;


void kernel_main()
{
    for ( int currPixelPos = 0; currPixelPos < 320 * 200;currPixelPos++ )
        video[ currPixelPos ] = 9;
    
    while( 1 );
}
*/

void processA();
void processB();
void processC();
void processD();

void processA()
    {
        print("Process A,");

        while(1)
            asm("mov $5390, %eax");
    }
    void processB()
    {
        print("Process B,");

        while(1)
            asm("mov $5391, %eax");
    }
    void processC()
    {
        print("Process C,");

        while(1)
            asm("mov $5392, %eax");
    }
    void processD()
    {
        print("Process D,");

        while(1)
            asm("mov $5393, %eax");
    }

void kernel_main()
{
    process_t p1, p2, p3, p4;

    screen_init();
    process_init();
    scheduler_init();

    process_create( &processA, &p1);
    process_create( &processB, &p2);
    process_create( &processC, &p3);
    process_create( &processD, &p4);

    while(1);
}
void interrupt_handler (int interrupt_number)
{
    println();
    print("Interrupt Received");
    printi(interrupt_number);
}