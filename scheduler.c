#include "scheduler.h"
#include "screen.h"

void scheduler_init()
{
    next_sch_pid = 0;
    curr_sch_pid = 0;
}

process_t *get_next_process()
{
    process_t *next_process = processes [next_sch_pid];

    curr_sch_pid = next_sch_pid;
    next_sch_pid++;
    next_sch_pid = next_sch_pid % processes_count;

    return next_process;
}

void scheduler(int eip, int edi, int esi, int ebp, int esp, int ebx, int edx, int ecx, int eax)
{
    print(" EAX = ");
    printi(eax);
    process_t *curr_process;

    //...//
    
    //Part-1

    curr_process = processes[ curr_sch_pid ];

    //...//

    //Part-2

    if (curr_process->state == RUNNING)
    {
        curr_process->context.eax=eax;
        curr_process->context.ecx=ecx;
        curr_process->context.edx=edx;
        curr_process->context.ebx=ebx;
        curr_process->context.esp=esp;
        curr_process->context.ebp=ebp;
        curr_process->context.esi=esi;
        curr_process->context.edi=edi;
        curr_process->context.eip=eip;
    }

    curr_process->state = READY;

    //...//

    //Part-3

    asm( " mov %0, %%eax;  \
           mov %1, %%ecx;  \
           mov %2, %%ecx;  \
           mov %3, %%ebx;  \
           mov %4, %%esi;  \
           mov %5, %%edi;"
           :: "r" ( next_process->context.eax), "r"(
            next_process->context.ecx), "r" (
            next_process->context.edx), "r" (
            next_process->context.ebx), "r" (
            next_process->context.esi), "r" (
            next_process->context.edi ));

    next_process->state = RUNNING;
}

void run_next_process()
{
 asm( " sti;     \
        jmp*%0" :: "r" (next_process->context.eip));
}