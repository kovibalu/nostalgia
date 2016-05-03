#ifndef SCONIO_H
#define SCONIO_H

enum {
   BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
   DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

#define LEFT 	0x2500
#define UP		0x2600
#define RIGHT	0x2700
#define DOWN	0x2800
#define ESC		0x1B
#define SPACE	0x20
#define ENTER	0x0D

void endconio(void);
void clrscr(void);
void gotoxy(int x, int y);
void getsize(int *w, int *h);
void settextcolor(char color, char bgcolor);
void setcursortype(int cur);
short getkey(void);
void cprintf(char *format, ...);
void cgets(char *s, int maxsize);
int gettime(void);

#endif //SCONIO_H
