#define PDE_NUM 3 //page directory entry (only 3 page tables are defined)
#define PTE_NUM 1024 //how many in those page table

extern void load_page_directory();
extern void enable_paging();

extern unsigned int *page_directory;

void paging_init();
int create_page_entry(int, char, char, char, char, char, char, char, char);