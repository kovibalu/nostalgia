#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sconio.h"
#include "menu.h"

int MakeMenu(char *cim, MENUPONT *menupontok, int n)
{
	int pos, i, j, middlex, middley, maxlength = 0, cimlength;
	int strlength[20];

	for (i = 0; i < n; i++)
		strlength[i] = strlen(menupontok[i].nev);

	cimlength = strlen(cim);

	for (i = n - 1; i >= 0; i--) {
		if (menupontok[i].enabled == 1)
			pos = i;

		if (maxlength < strlength[i])
			maxlength = strlength[i];
	}
	if (maxlength < cimlength)
		maxlength = cimlength;

	maxlength += 2;

	getsize(&middlex, &middley);
	middlex /= 2;
	middley /= 2;
	
	clrscr();
	setcursortype(0);

	for (;;) {
		gotoxy(middlex - maxlength/2 - 1, 3);
		settextcolor(LIGHTGRAY,BLACK);
		cprintf("+");
		for (i = 0; i < maxlength; i++) {
			cprintf("-");
		}
		cprintf("+");
		gotoxy(middlex - maxlength/2 - 1, 4);
		cprintf("|");
		for (i = 0; i < (maxlength - cimlength)/2; i++) {
			cprintf(" ");
		}
		cprintf("%s", cim);
		for (i = 0; i < (maxlength - cimlength + 1)/2; i++) {
			cprintf(" ");
		}
		cprintf("|");
		gotoxy(middlex - maxlength/2 - 1, 5);
		cprintf("+");
		for (i = 0; i < maxlength; i++) {
			cprintf("-");
		}
		cprintf("+");
		for (i = 0; i < n; i++) {
			gotoxy(middlex - maxlength/2 - 1, 6 + i);
			cprintf("|");
			if (i == pos) {
				settextcolor(BLACK,LIGHTGRAY);
			} else if (menupontok[i].enabled == 1) {
				settextcolor(LIGHTGRAY,BLACK);
			} else {
				settextcolor(CYAN,BLACK);
			}
			for (j = 0; j < (maxlength - strlength[i] + 1)/2; j++) {
				cprintf(" ");
			}
			cprintf("%s", menupontok[i].nev);
			for (j = 0; j < (maxlength - strlength[i])/2; j++) {
				cprintf(" ");
			}
			settextcolor(LIGHTGRAY,BLACK);
			cprintf("|");
		}
		gotoxy(middlex - maxlength/2 - 1, 6 + n);
		cprintf("+");
		for (i = 0; i < maxlength; i++) {
			cprintf("-");
		}
		cprintf("+");
		switch (getkey()) {
			case UP:
				do {
					if (pos > 0) {
						pos--;
					} else {
						pos = n - 1;
					}
				} while (menupontok[pos].enabled != 1);
				break;
			case DOWN:
				do {
					if (pos < n - 1) {
						pos++;
					} else {
						pos = 0;
					}
				} while (menupontok[pos].enabled != 1);
				break;
			case SPACE:
			case ENTER:
				clrscr();
				setcursortype(20);
				return menupontok[pos].id;
			case ESC:
				clrscr();
				setcursortype(20);
				return -1;
		}
	}
}
