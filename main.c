#include "screen.h"
#include "scheduler.h"
#include "paging.h"
#include "heap.h"

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
unsigned int heap_base = 0x100000;
unsigned int *page_directory;

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
    heap_init();
    paging_init();
    screen_init();
    process_init();
    scheduler_init();

    process_create( &processA );
    process_create( &processB );
    process_create( &processC );
    process_create( &processD );

    while(1);
}
void interrupt_handler (int interrupt_number)
{
    println();
    print("Interrupt Received");
    printi(interrupt_number);
}