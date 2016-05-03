#if defined(__linux__) || defined(__sun)

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <curses.h>
#include "sconio.h"

int initialized = 0;
int randinit = 0;
int width, height;
WINDOW *win;

static int colortab(int a)
{
	switch(a) {
	case BLACK:
	case BROWN:
		return COLOR_BLACK;
	case BLUE:
	case LIGHTBLUE:
		return COLOR_BLUE;
	case GREEN:
	case LIGHTGREEN:
		return COLOR_GREEN;
	case CYAN:
	case LIGHTCYAN:
		return COLOR_CYAN;
	case RED:
	case LIGHTRED:
		return COLOR_RED;
	case MAGENTA:
	case LIGHTMAGENTA:
		return COLOR_MAGENTA;
	case YELLOW:
		return COLOR_YELLOW;
	case WHITE:
	case LIGHTGRAY:
	case DARKGRAY:
		return COLOR_WHITE;
	}
	return COLOR_WHITE;
}

static void initconio(void)
{
	int x, y;
	initialized = 1;

	initscr();
	start_color();
	nonl();
	raw();
	noecho();
	win = newwin(0,0,0,0);
	keypad(win,TRUE);
	meta(win,TRUE);
	idlok(win,TRUE);
	scrollok(win,TRUE);

	getmaxyx(win, height, width);

	/* Color initialization */

	for (x = 0; x < 8; x++) {
		for (y = 0; y < 8; y++) {
			init_pair((y<<3)+x, x, y);
		}
	}
	settextcolor(WHITE, BLACK);
}

void endconio(void)
{
	endwin();
}


void clrscr(void)
{
	if (!initialized) initconio();
	wclear(win);
	wmove(win, 0, 0);
	wrefresh(win);
}

void gotoxy(int x, int y)
{
	if (!initialized) initconio();
	wmove(win, y, x);
	wrefresh(win);
}

void getsize(int *w, int *h)
{
	if (!initialized) initconio();
    *w = width;
    *h = height;
}

void settextcolor(char color, char bgcolor)
{
	if (!initialized) initconio();
	wattrset(win, 0);
	wattron(win, COLOR_PAIR((colortab(bgcolor) << 3) + colortab(color)));
}

void setcursortype(int cur)
{
	if (!initialized) initconio();
	if (cur == 0) curs_set(0);
	else curs_set(1);
}

static int flushin(void)
{
    int i;
	nodelay(win, TRUE);
	for (i = 0; wgetch(win) != ERR; i++);
	nodelay(win, FALSE);
	return i;
}

short getkey(void)
{
	int c, i;
	flushin();
	c = wgetch(win);
	if (flushin()) return 0;
	if (c < 0) return 0;
	if (c <= 255) return c;
	switch (c) {
	case KEY_LEFT:
		return LEFT;
	case KEY_UP:
		return UP;
	case KEY_RIGHT:
		return RIGHT;
	case KEY_DOWN:
		return DOWN;
	}
	return 0;
}

void cprintf(char *format, ...)
{
	char buffer[BUFSIZ];
	va_list argp;
	if (!initialized) initconio();
	va_start(argp, format);
	vsprintf(buffer, format, argp);
	va_end(argp);
	waddstr(win, buffer);
	wrefresh(win);
}

void cgets(char *s, int maxsize)
{
	if (!initialized) initconio();
	echo();
	wgetnstr(win, s, maxsize);
	noecho();
}

int gettime(void)
{
	return (int)time(NULL);
}

#endif //__linux__
