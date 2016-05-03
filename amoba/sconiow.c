#ifdef _WIN32

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "sconio.h"

int initialized = 0;
int randinit = 0;
HANDLE hstdout = NULL, hstdin = NULL;
short defattr = 0;
int width = 0, height = 0;
COORD defcoord = {0, 0};

static void initconio(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hstdin = GetStdHandle(STD_INPUT_HANDLE);

	if (!GetConsoleScreenBufferInfo (hstdout, &csbi)) return;

	width = csbi.dwSize.X;
	height = csbi.dwSize.Y;
	defattr = csbi.wAttributes;
	defcoord.X = 0;
	defcoord.Y = 0;

	initialized = 1;

	clrscr();
}

void endconio(void)
{

}

void clrscr(void)
{
	if (!initialized) initconio();

    FillConsoleOutputCharacter(hstdout, ' ', width*height, defcoord, NULL);
    FillConsoleOutputAttribute(hstdout, defattr, width*height, defcoord, NULL);
    SetConsoleCursorPosition(hstdout, defcoord);
}

void gotoxy(int x, int y)
{
	COORD co;
	if (!initialized) initconio();
	co.X = (short)x;
	co.Y = (short)y;
	SetConsoleCursorPosition(hstdout, co);
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
	SetConsoleTextAttribute (hstdout, (WORD)(color | (bgcolor << 4)));
}

void setcursortype(int cur)
{
	CONSOLE_CURSOR_INFO curinf;
	if (!initialized) initconio();
	if (cur == 0) {
		curinf.dwSize = 20;
		curinf.bVisible = FALSE;
	} else {
		curinf.dwSize = cur;
		curinf.bVisible = TRUE;
	}
	SetConsoleCursorInfo (hstdout, &curinf);
}

short getkey(void)
{
	INPUT_RECORD rec;
	DWORD num;
	short rv;

	if (!initialized) initconio();

	FlushConsoleInputBuffer(hstdin);

	do {
		ReadConsoleInput(hstdin, &rec, 1, &num);
	} while (num == 0 || rec.EventType != KEY_EVENT || rec.Event.KeyEvent.bKeyDown == FALSE);

	rv = rec.Event.KeyEvent.uChar.AsciiChar;
	if (rv == 0) rv = (short)(rec.Event.KeyEvent.wVirtualKeyCode << 8);
	return rv;
}

void cprintf(char *format, ...)
{
	int l;
	va_list argp;
	char buffer[BUFSIZ];
	if (!initialized) initconio();
	va_start(argp, format);
	l = vsprintf(buffer, format, argp);
	va_end(argp);
	WriteConsoleA(hstdout, buffer, l, NULL, NULL);
}

void cgets(char *s, int maxsize)
{
	fgets(s, maxsize, stdin);	
}

int gettime(void)
{
	return (int)time(NULL);
}

#endif //_WIN32
