typedef enum process_state { READY, RUNNING } process_state_t;

typedef struct process_context
{
 int eax, ecx, edx, ebx, esp, ebp, esi, edi, eip;
} process_context_t;

typedef struct process
{
 int pid;
 process_context_t context;
 process_state_t state;
 void (*base_address)();
} process_t;

process_t *processes [15];

int processes_count, curr_pid;

void process_init();
void process_create (void (*)(), process_t *);