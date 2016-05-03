#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sconio.h"
#include "amoba.h"
#include "menu.h"
#include "MI.h"
#include "bifa.h"

/* Memoriafoglalas a jatek szamara */
PJATEKALLAS InitJatek(void)
{
	PJATEKALLAS jatek;
	if ((jatek = (PJATEKALLAS)malloc(sizeof(JATEKALLAS))) == NULL) {
		fprintf(stderr, "Elfogyott a memoria !\n");
		exit(-1);
	}

	return jatek;
}

/* A tabla feltoltese ures mezokkel */
void ClearJatek(PJATEKALLAS jatek)
{
	int i;

	jatek->kijon = 1;
	jatek->lepes = 0;

	for (i = 0; i < 16 * 16; i++) {
		jatek->lepesek[i].sor = -1;
		jatek->lepesek[i].osl = -1;
	}

	jatek->jatekosok[0] = 0;
	jatek->jatekosok[1] = 0;
}

/* Letorli a tablat */
void ClearTabla(PJATEKALLAS jatek)
{
	int i;

	for (i = 0; i < jatek->SOR; i++) {
		jatek->tabla[i] = 0;
	}
}

/* A tabla kiirasa */
void TablaKiir(PJATEKALLAS jatek)
{
	int i, j, k;
	int middlex = 0, middley = 0;
	char hatter;

	getsize(&middlex, &middley);
	middlex /= 2;
	middley /= 2;

	gotoxy(middlex - jatek->OSL/2*4 - 2,3);
	for (i = 0; i < jatek->OSL; i++) {
		cprintf("%3d ", i + 1);
	}
	gotoxy(middlex - jatek->OSL/2*4 - 2, 4);
	cprintf("+");
	for (i = 0; i < jatek->OSL; i++) {
		cprintf("---+");
	}
	for (i = 0; i < jatek->SOR; i++) {
		gotoxy(middlex - jatek->OSL/2*4 - 5, 5 + i*2);
		cprintf("%2d |", i + 1);
		for (j = 0; j < jatek->OSL; j++) {
			if (jatek->lepes > 0 && i == jatek->lepesek[jatek->lepes - 1].sor &&
				j == jatek->lepesek[jatek->lepes - 1].osl) {
				hatter = WHITE;
			} else {
				hatter = BLACK;
			}
			switch (GetTabla(jatek->tabla, i, j)) {
				case 0:
					cprintf("   ");
					break;
				case 1:
					settextcolor(LIGHTGREEN, hatter);
					cprintf(" O ");
					settextcolor(LIGHTGRAY, BLACK);
					break;
				case 2:
					settextcolor(LIGHTRED, hatter);
					cprintf(" X ");
					settextcolor(LIGHTGRAY, BLACK);
					break;
			}
			cprintf("|");
		}
		gotoxy(middlex - jatek->OSL/2*4 - 2, 5 + i*2 + 1);
		cprintf("+");
		for (k = 0; k < jatek->OSL; k++) {
			cprintf("---+");
		}
	}
}

/* Az amoba jatek */
void Jatek(PJATEKALLAS jatek)
{
	int posx = jatek->OSL/2, posy =jatek->SOR/2, gyoz = 0;
	int a, b, va = 0, vb = 0, hovax = 0, hovay = 0;
	int kilep;
	int eltelt;
	int ido;
	int middlex = 0, middley = 0;

	getsize(&middlex, &middley);
	middlex /= 2;
	middley /= 2;

	clrscr();
	setcursortype(0);
	TablaKiir(jatek);

	for(;;) {
		if (jatek->jatekosok[jatek->kijon - 1] == 0) { /* Elo jatekos */
			kilep = 0;
			/* Kurzor helyzetenek beallitasa a legutolso lepesre */
			if (jatek->lepes > 0) {
				posy = jatek->lepesek[jatek->lepes - 1].sor;
				posx = jatek->lepesek[jatek->lepes - 1].osl;
			}
			do {
				TablaKiir(jatek);
				/* A "kurzor" kirajzolasa */
				gotoxy(middlex - jatek->OSL/2*4 + posx*4, 3 + posy*2 + 2);
				if (GetTabla(jatek->tabla, posy, posx) == 0) {
					settextcolor(BLACK, CYAN);
					if (jatek->kijon == 1) {
						cprintf("O");
					} else {
						cprintf("X");
					}
				} else {
					settextcolor(BLACK, YELLOW);
					if (GetTabla(jatek->tabla, posy, posx) == 1) {
						cprintf("O");
					} else {
						cprintf("X");
					}
				}
				gotoxy(0, 0);

				settextcolor(LIGHTGRAY, BLACK);

				switch (getkey()) {
					case '\b': /* Lepesvisszavonas */
						if (jatek->lepes == 0)
							break;
						if (jatek->jatekosok[2 - jatek->kijon] == 0) { /* Ha a masik jatekos elo */
							TorolLepes(jatek);
							TablaKiir(jatek);
							ClearText(jatek->SOR, 5);
							kilep = 1;
						} else if (jatek->jatekosok[2 - jatek->kijon] != 0 && jatek->lepes >= 2) {
							TorolLepes(jatek);          /* Ha a masik jatekos gepi */
							TorolLepes(jatek);          /* az o lepeset is torolni kell */
							TablaKiir(jatek);
							ClearText(jatek->SOR, 5);
							gotoxy(0, 3 + jatek->SOR*2 + 3);
							cprintf("A jatek a %d. lepesnel tart.", jatek->lepes);
							if (jatek->lepes > 0) {
								posy = jatek->lepesek[jatek->lepes - 1].sor;
								posx = jatek->lepesek[jatek->lepes - 1].osl;
							}
						}
						break;
					case 's': /* Segitsegkeres */
						if (jatek->lepes != 0) {
							ClearText(jatek->SOR, 5);
							gotoxy(0, 3 + jatek->SOR*2 + 3);
							cprintf("A jatekos a szamitogep segitseget kerte, a segito jatekos lep.\n");
							MI(jatek, jatek->kijon, &hovax, &hovay, 7);
							AddLepes(jatek, hovax, hovay, jatek->kijon);
							TablaKiir(jatek);
							kilep = 1;
						}
						break;
					case UP:
					case 'k':
						if (posy > 0) {
							posy--;
						} else {
							posy = jatek->SOR - 1;
						}
						break;
					case DOWN:
					case 'j':
						if (posy < jatek->SOR - 1) {
							posy++;
						} else {
							posy = 0;
						}
						break;
					case LEFT:
					case 'h':
						if (posx > 0) {
							posx--;
						} else {
							posx = jatek->OSL - 1;
						}
						break;
					case RIGHT:
					case 'l':
						if (posx < jatek->OSL - 1) {
							posx++;
						} else {
							posx = 0;
						}
						break;
					case SPACE:
					case ENTER:
						if (GetTabla(jatek->tabla, posy, posx) == 0) {
							AddLepes(jatek, posy, posx, jatek->kijon);
							TablaKiir(jatek);
							kilep = 1;
						}
						break;
					case ESC:
						return;
				}
			} while (kilep != 1);
			if (Gyoz(jatek, jatek->kijon) == 1) { /* Ha gyozott */
				gyoz = jatek->kijon;
				break;
			}
			if (jatek->lepes == jatek->SOR * jatek->OSL) { /* Betelt a tabla */
				break;
			}
		} else if (jatek->jatekosok[jatek->kijon - 1] >= 1) { /* Gepi jatekos */
			ClearText(jatek->SOR, 5);
			gotoxy(0, 3 + jatek->SOR*2 + 3);
			cprintf("A(z) %d-es jatekos (MI - %d nehezseg) lep.\n", jatek->kijon,
				jatek->jatekosok[jatek->kijon - 1]);
			if (jatek->kijon == 1) {
				cprintf("\"O\" karakter\n");
			} else {
				cprintf("\"X\" karakter\n");
			}
			cprintf("A jatek a %d. lepesnel tart.", jatek->lepes);
			if (jatek->lepes == 0) { /* Kezdolepes */
				ido = gettime();
				hovax = (jatek->SOR - 1)/2;
				hovay = (jatek->OSL - 1)/2;
				eltelt = gettime() - ido;
			} else if (jatek->lepes == 1) { /* Ha meg csak egy lepes tortent */
				ido = gettime();
				for (a = 0; a < jatek->SOR; a++) {
					for (b = 0; b < jatek->OSL; b++) {
						if (GetTabla(jatek->tabla, a, b) != 0) {
							va = a;
							vb = b;
							goto ex;
						}
					}
				}
ex:
				hovax = (va < jatek->SOR/2 ? 1 : -1) + va;
				hovay = (vb < jatek->OSL/2 ? 1 : -1) + vb;
				eltelt = gettime() - ido;
			} else {
				int depth;

				ido = gettime();
				switch (jatek->jatekosok[jatek->kijon - 1]) {
					case 1:
						depth = 5;
						break;
					case 2:
					case 3:
					case 4:
					case 5:
						depth = jatek->jatekosok[jatek->kijon - 1] + 5;
						break;
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
						depth = jatek->jatekosok[jatek->kijon - 1] + 7;
						break;
				}
				MI(jatek, jatek->kijon, &hovax, &hovay, depth); /* MI */
				eltelt = gettime() - ido;
			}
			AddLepes(jatek, hovax, hovay, jatek->kijon);
			TablaKiir(jatek);
			ClearText(jatek->SOR, 5);
			gotoxy(0, 3 + jatek->SOR*2 + 3);
			cprintf("%d. jatekos (MI - %d nehezseg) %d %d mezore lepett.\n", jatek->kijon,
				jatek->jatekosok[jatek->kijon - 1], hovax + 1, hovay + 1);
			cprintf("A szamitogep %d sec alatt lepett.\n", eltelt);
			cprintf("A jatek a %d. lepesnel tart.", jatek->lepes);
			if (Gyoz(jatek, jatek->kijon) == 1) { /* Ha gyozott */
				gyoz = jatek->kijon;
				break;
			}
			if (jatek->lepes == jatek->SOR * jatek->OSL) /* Betelt a tabla */
				break;
		}
		jatek->kijon = 3 - jatek->kijon;
	}
	if (gyoz != 0) { /* Valaki gyozott */
		ClearText(jatek->SOR, 5);
		gotoxy(0, 3 + jatek->SOR*2 + 3);
		if (jatek->jatekosok[gyoz - 1] == 0) {
			cprintf("%d. jatekos gyozott (elo jatekos) a(z) %d. lepesben !\n", gyoz, jatek->lepes);
		} else {
			cprintf("%d. jatekos gyozott (MI - %d nehezseg) a(z) %d. lepesben !\n",
				gyoz, jatek->jatekosok[gyoz - 1], jatek->lepes);
		}
		ClearJatek(jatek); /* Befejezett jatek */
		cprintf("\n(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
		getkey();
		setcursortype(20);
		MIExit();
		return;
	}
	if (jatek->lepes == jatek->SOR * jatek->OSL) {
		ClearText(jatek->SOR, 5);
		gotoxy(0, 3 + jatek->SOR*2 + 3);
		cprintf("Dontetlen !\n");
		ClearJatek(jatek); /* Befejezett jatek */
		cprintf("\n(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
		getkey();
		setcursortype(20);
		MIExit();
		return;
	}
}

/* Letorli a tabla alatti db szamu sort */
void ClearText(int sor, int db)
{
	int i, w, h;

	getsize(&w, &h);
	gotoxy(0, 3 + sor*2 + 2);
	for (i = 0; i < w * db; i++) {
		cprintf(" ");
	}
}

void Betolt(PJATEKALLAS jatek)
{
	FILE *fp;
	int i, db = 0, choose;
	fpos_t cimek[MAXMENT];
	char *azonositok[MAXMENT];
	MENUPONT mentesmenu[MAXMENT];

	setcursortype(0);
	for (i = 0; i < MAXMENT; i++) {
		if ((azonositok[i] = (char *)malloc(50 * sizeof(char))) == NULL) {
			fprintf(stderr, "Elfogyott a memoria !\n");
			exit(-1);
		}
		mentesmenu[i].enabled = 1;
		mentesmenu[i].id = i;
	}
	fp = fopen("amoba.dat", "rb");
	if (fp == NULL) {
		cprintf("Fajl olvasasi hiba !\n(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
		getkey();
		setcursortype(20);
		return;
	}
	while (db < MAXMENT) { /* A mentett allasok betoltese */
		fgetpos(fp, &cimek[db]);
		if (fread(azonositok[db], 50 * sizeof(char), 1, fp) == 1) {
			fseek(fp, sizeof(JATEKALLAS), SEEK_CUR);
			db++;
		} else {
			break;
		}
	}
	if (db == 0) {
		cprintf("Nincs mentett fajl.\n(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
		getkey();
		setcursortype(20);
		for (i = 0; i < MAXMENT; i++) {
			free(azonositok[i]);
		}
		return;
	}
	for (i = 0; i < db; i++) {
		strcpy(mentesmenu[i].nev, azonositok[i]);
	}
	/* Mentett allasok kozotti valasztas */
	choose = MakeMenu("Mentett jatekok", mentesmenu, db);
	if (choose == -1) {
		for (i = 0; i < MAXMENT; i++) {
			free(azonositok[i]);
		}
		return;
	}
	/* Mostani mentett allasok (MI) felszabaditasa */
	MIExit();
	/* Valasztott allas betoltese */
	fsetpos(fp, &cimek[choose]);
	fseek(fp, 50 * sizeof(char), SEEK_CUR);
	fread(jatek, sizeof(JATEKALLAS), 1, fp);
	fclose(fp);
	MIInit();
	setcursortype(0);
	cprintf("A mentest sikeresen betoltottem.\n(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
	getkey();
	setcursortype(20);

	/* Felszabaditas */
	for (i = 0; i < MAXMENT; i++) {
		free(azonositok[i]);
	}
}

void Elment(PJATEKALLAS jatek)
{
	FILE *fp;
	int i, db = 0;
	char space = ' ';
	char s[50];

	fp = fopen("amoba.dat", "ab");
	if (fp == NULL) {
		setcursortype(0);
		cprintf("Fajl olvasasi hiba !\n(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
		getkey();
		setcursortype(20);
		return;
	}
	cprintf("Irja be a kivant azonositot a mentes azonositasara.\n");
	cgets(s, 50);
	fflush(stdin);
	/* Kivesszuk a \n es a \t karaktereket az azonositobol */
	for (i = 0; i < 50; i++) {
		if (s[i] == '\n' || s[i] == '\t') {
			db++;
		} else {
			fwrite(&(s[i]), sizeof(char), 1, fp);
		}
	}
	for (i = 0; i < db; i++) {
		fwrite(&space, sizeof(char), 1, fp);
	}
	fwrite(jatek, sizeof(JATEKALLAS), 1, fp);
	fclose(fp);
	setcursortype(0);
	cprintf("A jatekallast sikeresen elmentettem.\n(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
	getkey();
	setcursortype(20);
}

void Sugo(void)
{
	int middlex, middley;
	char *tmp;
	int i;

	clrscr();
	getsize(&middlex, &middley);
	middlex /= 2;
	setcursortype(0);

	tmp = "====  Amoba program - Sugo  ====";
	gotoxy(middlex - (int)strlen(tmp)/2, 3);
	cprintf("%s",tmp);

	tmp = "* Az amoba jatekrol *";
	gotoxy(middlex - (int)strlen(tmp)/2, 6);
	for (i = 0; i < (int)strlen(tmp); i++) {
		cprintf("*");
	}
	gotoxy(middlex - (int)strlen(tmp)/2, 7);
	cprintf("%s",tmp);
	gotoxy(middlex - (int)strlen(tmp)/2, 8);
	for (i = 0; i < (int)strlen(tmp); i++) {
		cprintf("*");
	}
	cprintf("\n\n");
	cprintf("Az amoba jatekot egy mezokre felosztott teglalap alaku tablan jatsszak. A ket jatekos felvaltva rak egy-"
	"egy jelet, az gyoz, akinek elobb jon ossze ot jel egymas utan sorban, oszlopban vagy atlosan. A jatek "
	"dontetlen, ha a tabla betelik, es nincs senkinek se otose.");

	tmp = "* A fomenurol *";
	gotoxy(middlex - (int)strlen(tmp)/2, 15);
	for (i = 0; i < (int)strlen(tmp); i++) {
		cprintf("*");
	}
	gotoxy(middlex - (int)strlen(tmp)/2, 16);
	cprintf("%s", tmp);
	gotoxy(middlex - (int)strlen(tmp)/2, 17);
	for (i = 0; i < (int)strlen(tmp); i++) {
		cprintf("*");
	}
	cprintf("\n\n");
	cprintf("A fomenuben a menupontok kozott a FEL, LE billentyuk hasznalataval valaszthatunk. "
		"A menupontba valo belepeshez az ENTER vagy a SPACE billentyut kell lenyomni. "
		"A \"Jatek mentese\" es \"Jatek folytatasa\" menupont csak akkor elerheto, ha mar van megkezdett jatek.");

	tmp = "* A jatekrol *";
	gotoxy(middlex - (int)strlen(tmp)/2, 24);
	for (i = 0; i < (int)strlen(tmp); i++) {
		cprintf("*");
	}
	gotoxy(middlex - (int)strlen(tmp)/2, 25);
	cprintf("%s",tmp);
	gotoxy(middlex - (int)strlen(tmp)/2, 26);
	for (i = 0; i < (int)strlen(tmp); i++) {
		cprintf("*");
	}
	cprintf("\n\n");
	cprintf("A jatekban minden menubol es a jatekterbol az ESC billentyu lenyomasaval a fomenube jutunk. "
		"A jatekban lehetoseg van tobbfele MI ellen, tobb nehezsegi szinten jatszani, "
		"vagy ezeket jatszatni egymas ellen, illetve ket elo ember is jatszhat egymas ellen.\n");
	cprintf("A tablan a FEL, LE, BALRA, JOBBRA billentyukkel mozoghatunk, "
		"es az ENTER vagy SPACE billentyuvel tehetunk le egy sajat jelet egy ures mezore. "
		"A BACKSPACE billentyuvel visszavonhatjuk lepeseinket. ");
	cprintf("Olyan lepest nem lehet visszavonni, mellyel a jatek veget ert. "
		"Jatek kozben segitseget kerhetunk a szamitogeptol az S billentyu lenyomasaval, "
		"ekkor a szamitogep lep helyettunk.\n\n");
	cprintf("Kellemes jatekot kivanok :)\n\n");
	cprintf("(Nyomjon le egy billentyut a fomenube valo visszatereshez)\n");
	gotoxy(0, 0);
	getkey();
	setcursortype(20);
}

/* 1-t ad vissza ha k gyozott, 0-t ha nem */
int Gyoz(JATEKALLAS *jatek, int k)
{
	int i, j, a, b;
	int hossz;

	for (i = 0; i < jatek->SOR; i++) { /*Vizszintes*/
		hossz = 0;
		for (j = 0; j < jatek->OSL; j++) {
			if (GetTabla(jatek->tabla, i, j) == k) {
				hossz++;
				if (hossz >= 5) {
					return 1;
				}
			} else {
				hossz = 0;
			}
		}
	}
	for (j = 0; j < jatek->OSL; j++) { /*Fuggoleges*/
		hossz = 0;
		for (i = 0; i < jatek->SOR; i++) {
			if (GetTabla(jatek->tabla, i, j) == k) {
				hossz++;
				if (hossz >= 5) {
					return 1;
				}
			} else {
				hossz = 0;
			}
		}
	}
	for (i = 0; i < jatek->SOR; i++) { /*ENY-DK*/
		hossz = 0;
		for (a = i, b = 0; a < jatek->SOR && b < jatek->OSL; a++, b++) {
			if (GetTabla(jatek->tabla, a, b) == k) {
				hossz++;
				if (hossz >= 5) {
					return 1;
				}
			} else {
				hossz = 0;
			}
		}
	}
	for (j = 1; j < jatek->OSL; j++) { /*ENY-DK*/
		hossz = 0;
		for (a = 0, b = j; a < jatek->SOR && b < jatek->OSL; a++, b++) {
			if (GetTabla(jatek->tabla, a, b) == k) {
				hossz++;
				if (hossz >= 5) {
					return 1;
				}
			} else {
				hossz = 0;
			}
		}
	}
	for (i = 0; i < jatek->SOR; i++) { /*EK-DNY*/
		hossz = 0;
		for (a = i, b = jatek->OSL - 1; a < jatek->SOR && b >= 0; a++, b--) {
			if (GetTabla(jatek->tabla, a, b) == k) {
				hossz++;
				if (hossz >= 5) {
					return 1;
				}
			} else {
				hossz = 0;
			}
		}
	}
	for (j = 0; j < jatek->OSL - 1; j++) /*EK-DNY*/ {
		hossz = 0;
		for (a = 0, b = j; a < jatek->SOR && b >= 0; a++, b--) {
			if (GetTabla(jatek->tabla, a, b) == k) {
				hossz++;
				if (hossz >= 5) {
					return 1;
				}
			} else {
				hossz = 0;
			}
		}
	}
	return 0;
}

void AddLepes(PJATEKALLAS jatek, int sor, int osl, int jatekos)
{
	if (jatek->lepes < jatek->SOR * jatek->OSL) {
		SetTabla(jatek->tabla, sor, osl, jatekos);
		jatek->lepesek[jatek->lepes].sor = sor;
		jatek->lepesek[jatek->lepes].osl = osl;
		jatek->lepes++;
	}
}

void TorolLepes(PJATEKALLAS jatek)
{
	if (jatek->lepes > 0) {
		jatek->lepes--;
		SetTabla(jatek->tabla,jatek->lepesek[jatek->lepes].sor, jatek->lepesek[jatek->lepes].osl, 0);
	}
}


void FreeJatek(PJATEKALLAS jatek)
{
	free(jatek);
}

int main(void)
{
	int kilep, jatekoskilep;
	int fomenuval;
	int elso, masodik;
	char s[100];
	PJATEKALLAS jatek;

	MENUPONT fomenu[6] = {
		{"Uj jatek inditasa", 0, 1},
		{"Jatek betoltese", 1, 1},
		{"Jatek elmentese", 2, 1},
		{"Jatek folytatasa", 3, 1},
		{"Sugo megnyitasa", 4, 1},
		{"Kilepes", 5, 1}
	};

	MENUPONT jatekosvalasztomenu[11] = {
		{"Elo jatekos", 0, 1},
		{"MI -  1 nehezseg (Szamitogep)", 1, 1},
		{"MI -  2 nehezseg (Szamitogep)", 2, 1},
		{"MI -  3 nehezseg (Szamitogep)", 3, 1},
		{"MI -  4 nehezseg (Szamitogep)", 4, 1},
		{"MI -  5 nehezseg (Szamitogep)", 5, 1},
		{"MI -  6 nehezseg (Szamitogep)", 6, 1},
		{"MI -  7 nehezseg (Szamitogep)", 7, 1},
		{"MI -  8 nehezseg (Szamitogep)", 8, 1},
		{"MI -  9 nehezseg (Szamitogep)", 9, 1},
		{"MI - 10 nehezseg (Szamitogep)", 10, 1}
	};

	jatek = InitJatek();
	ClearJatek(jatek);

	freopen("log.txt", "w", stderr);

	Sugo();

	do {
		kilep = 0;
		if (jatek->lepes != 0) {
			fomenu[2].enabled = 1;
			fomenu[3].enabled = 1;
		} else {
			fomenu[2].enabled = 0;
			fomenu[3].enabled = 0;
		}
		fomenuval = MakeMenu("Fomenu", fomenu, 6);
		switch (fomenuval) {
			case 0:
				jatekoskilep = 0;
				 /* A jatekosok tipusanak beolvasasa (ember vagy gep) */
				for (;;) {
					elso = MakeMenu("Valasszon elso jatekost", jatekosvalasztomenu, 11);
					if (elso == -1) {
						jatekoskilep = 1;
						break;
					}
					masodik = MakeMenu("Valasszon masodik jatekost", jatekosvalasztomenu, 11);
					if (masodik == -1) {
						continue;
					}
					break; /* Nem leptek ki ESC-el a masodikbol*/
				}
				if (jatekoskilep == 1) { /* Visszateres a fomenube */
					break;
				}
				/* Nem leptek ki ESC-el a fomenube */
				MIExit();
				ClearJatek(jatek);
				jatek->jatekosok[0] = elso;
				jatek->jatekosok[1] = masodik;
				for (;;) {
					cprintf("\nIrja be mekkora legyen egy sor. (3 - 16-ig)\n");
					cgets(s, sizeof(s));
					fflush(stdin);
					if (sscanf(s,"%d", &(jatek->SOR)) == 1) {
						if (jatek->SOR < 3 || jatek->SOR > 16) {
							cprintf("Rossz a beirt szam !\n\n");
							continue;
						}
					} else {
						cprintf("Nem megfelelo a beirt karaktersorozat !\n");
						continue;
					}
					cprintf("\nIrja be mekkora legyen egy oszlop. (3 - 16-ig)\n");
					cgets(s, sizeof(s));
					fflush(stdin);
					if (sscanf(s,"%d", &(jatek->OSL)) == 1) {
						if (jatek->OSL < 3 || jatek->OSL > 16) {
							cprintf("Rossz a beirt szam !\n\n");
							continue;
						} else
							break;
					} else {
						cprintf("Nem megfelelo a beirt karaktersorozat !\n");
						continue;
					}
				}
				ClearTabla(jatek);
				MIInit();
				Jatek(jatek);
				break;
			case 1:
				Betolt(jatek);
				break;
			case 2:
				Elment(jatek);
				break;
			case 3: /* Megkezdett jatek folytatasa */
				Jatek(jatek);
				break;
			case 4:
				Sugo();
				break;
			case 5:
			case -1:
				kilep = 1;
				break;
		}
	} while (kilep != 1);
	FreeJatek(jatek);
	endconio();
	fclose(stderr);
	return 0;
}
