extern volatile unsigned char *video;

extern int currLine, nextTextPos;

void screen_init();
void print( char * );
void println();
void printi( int );
void print_hex(unsigned int);