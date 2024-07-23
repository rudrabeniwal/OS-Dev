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


void print_cr0() 
{
    unsigned int cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    print("CR0 Value in int: ");
    printi(cr0);
    println();
    print("CR0 Value in hex: ");
    print_hex(cr0);
    println();
}

void kernel_main()
{
    heap_init();
    paging_init();

    screen_init();

    print_cr0();
    
    unsigned int cr3;
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    print("CR3 Value in int: ");
    printi(cr3);
    println();
    print("CR3 Value in hex: ");
    print_hex(cr3);
    println();
    
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
