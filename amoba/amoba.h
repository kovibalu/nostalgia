#ifndef AMOBA_H
#define AMOBA_H

#define MAXMENT 50 /* Mentesek maximalis szama */

/* 
	a tabla unsigned[16] 
	i. sor, j. oszlop
	2 bitenkent tarol egy erteket

	a binaris fa tarolasa miatt kell, hogy kisebb helyen ferjen el
*/
#define SetTabla(t, i, j, e) ((t)[i] = ((t)[i] & (~(3 << ((j) << 1)))) | ((e) << ((j) << 1)))
#define GetTabla(t, i, j) ((int)(((t)[i] >> ((j) << 1)) & 3))

typedef struct {
	int sor;
	int osl;
} MEZO, *PMEZO;

typedef struct {
	unsigned tabla[16]; // Jatektabla
	int kijon; // Melyik jatekos jon
	int jatekosok[2]; // Jatekosok, 0 elo jatekos, 1-10 MI1
	int lepes; // Hany lepes volt eddig
	int SOR;
	int OSL;
	MEZO lepesek[16 * 16]; //[hanyadik lepes] itt taroljuk az aktualis jatek lepeseit
} JATEKALLAS, *PJATEKALLAS;

PJATEKALLAS InitJatek(void);
void ClearJatek(PJATEKALLAS jatek);
void ClearTabla(PJATEKALLAS jatek);
void TablaKiir(PJATEKALLAS jatek);
void ClearText(int sor, int db);
void Jatek(PJATEKALLAS jatek);
void Betolt(PJATEKALLAS jatek);
void Elment(PJATEKALLAS jatek);
void Sugo(void);
int Gyoz(PJATEKALLAS jatek, int k);
void AddLepes(PJATEKALLAS jatek, int sor, int osl, int jatekos);
void TorolLepes(PJATEKALLAS jatek);
void FreeJatek(PJATEKALLAS jatek);

#endif //AMOBA_H
