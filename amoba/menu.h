#ifndef MENU_H
#define MENU_H

typedef struct {
	char nev[50]; /* A menupont neve */
	int id; /* A menupont azonositoja */
	int enabled; /* Engedelyezett-e, ha nem, akkor nem lehet ralepni */
} MENUPONT;

int MakeMenu(char *cim, MENUPONT *menupontok, int n);

#endif //MENU_H
