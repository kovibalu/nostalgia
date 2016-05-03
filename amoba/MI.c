#include <stdio.h>
#include <stdlib.h>
#include "MI.h"
#include "bifa.h"
#include "sconio.h"

#define MIOff 19
#define MIDef 16

#define URESSABLONDB 15
#define ELLSABLONDB 5
#define ULEPDB 8 /* Utolso hany lepest nezzuk a lolepesnel */

extern unsigned zobtabla[16][16][3];
static int sulysor, sulyosl;  /* Az aktualis jatekallas kozepenek koordinatai */
static PBIFA root = NULL; /* A mentett allasok fajanak a gyokere, root1-re es */
static PBIFA roots[2]; /* kettore azert van szukseg, ha ket gepi jatekos van */
/* 
	Ebbe vannak elrendezve az aktualis 
	jatekallas mezoi, az aktualis kozepponttol valo tavolsag alapjan
*/
static int csiga[16 * 16][2];


/* 10 fele lougras van [fajta][sor][oszlop] */
static int lougras[10][16][16];
static int lougrasdb[10];
static int loutolso[10];

/* A sablonokon belul 
	a 9 ertek olyan mezot jelol, melynek erteke mindegy,
	a 0 ertek ures mezot,
	az 1 ertek sajat mezot (vagyis int jatekos mezot, mert a fuggvenynek megadjuk, hogy melyik jatekosra nezzuk),
	a 2 ertek ellenfel mezot jelol.
*/

/* 
	uressablonok[k][0]: sablon hossza
	uressablonok[k][1]: hol van benne a vizsgalando ures mezo
*/

static int uressablonok[URESSABLONDB][7] = {
	{5, 1, 0, 1, 1, 1, 1}, // 0.  /33000
	{5, 2, 1, 0, 1, 1, 1}, // 1.  /4500
	{5, 3, 1, 1, 0, 1, 1}, // 2.  /3900
	{5, 4, 1, 1, 1, 0, 1}, // 3.  /4100
	{4, 1, 0, 1, 1, 1, 9}, // 4.  /789
	{4, 2, 1, 0, 1, 1, 9}, // 5.  /410
	{4, 3, 1, 1, 0, 1, 9}, // 6.  /350
	{5, 1, 0, 0, 1, 1, 1}, // 7.  /550
	{3, 1, 0, 1, 1, 9, 9}, // 8.  /250
	{3, 2, 1, 0, 1, 9, 9}, // 9.  /185
	{4, 1, 0, 0, 1, 1, 9}, // 10. /175
	{4, 2, 1, 0, 0, 1, 9}, // 11. /160
	{5, 1, 0, 1, 0, 1, 0}, // 12. /300
	{4, 1, 0, 1, 0, 1, 9}, // 13. /115
	{2, 1, 0, 1, 9, 9, 9} //  14. /5
};

static int uresmulti[9] = {2, 6, 4, 2, 3, 4, 2, 2, 2};

static int ponturessablonok[URESSABLONDB] = {
	33000,
	4500,
	3900,
	4100,
	789,
	410,
	350,
	550,
	250,
	185,
	175,
	160,
	300,
	115,
	5
};

/* Itt az elso elem nem a hossz, mert mindegyiknek ugyanannyi a hossza */
static int ellsablonok_majdnem5[ELLSABLONDB][5] = {
	{0, 1, 1, 1, 1}, // 0.
	{1, 0, 1, 1, 1}, // 1.
	{1, 1, 0, 1, 1}, // 2.
	{1, 1, 1, 0, 1}, // 3.
	{1, 1, 1, 1, 0}  // 4.
};

static int ellsablonok_harom[4][7] = {
	{6, 0, 0, 1, 1, 1, 0},
	{6, 0, 1, 1, 1, 0, 0},
	{6, 0, 1, 0, 1, 1, 0},
	{6, 0, 1, 1, 0, 1, 0}
};

/* A lougras vektort tolti fel */
static void InitLougras(PJATEKALLAS jatek, int jatekos)
{
	int a, b, i, j, k, ellen = 3 - jatekos;

	for (a = 0; a < 10; a++) {
		for (i = 0; i < jatek->SOR; i++) {
			for (j = 0; j < jatek->OSL; j++) {
				lougras[a][i][j] = -1;
			}
		}
		lougrasdb[a] = 0;
		loutolso[a] = 0;
	}

	for (b = 0; b < 2; b++) { /* Koruljaras */
		for (a = 0; a < 5; a++) { /* Eltolas */
			for (i = 0; i < jatek->SOR; i++) {
				/* 
					Ha b == 0, akkor 2-vel kell szorozni,
					ha b == 1, akkor 3-mal 
				*/
				for (j = (i * (2 + b)) % 5 + a; j < jatek->OSL; j += 5) {
					if (GetTabla(jatek->tabla, i, j) == ellen) {
						/* Az ellenfel utolso (10) lepesei kozul valo-e */
						for (k = 0; k < ULEPDB; k++) {
							/* Ha ez a lepes nem tortent meg */
							if (jatek->lepes - 1 - 2*k < 0) {
								break;
							}
							if (jatek->lepesek[jatek->lepes - 1 - 2*k].sor == i &&
								jatek->lepesek[jatek->lepes - 1 - 2*k].osl == j) {
								lougrasdb[a + b*5]++;
								/* Ha az utolso lepes lolepes volt */
								if (k == 0) {
									loutolso[a + b*5] = 1;
								}
								break;
							}
						}
					} else if (GetTabla(jatek->tabla, i, j) == 0) {
						lougras[a + b*5][i][j] = 0;
					}
				}
			}
		}
	}
}

/* Az aktualis jatekallas kozepet szamolja ki */
static void InitSulykozep(PJATEKALLAS jatek)
{
	int i, j, db = 0, sumsor = 0, sumosl = 0;

	for (i = 0; i < jatek->SOR; i++) {
		for (j = 0; j < jatek->OSL; j++) {
			if (GetTabla(jatek->tabla, i, j) != 0) {
				sumsor += i;
				sumosl += j;
				db++;
			}
		}
	}
	sulysor = sumsor / db;
	sulyosl = sumosl / db;
}

/* Egy pont tavolsagat szamolja ki az aktualis kozepponttol [kozepsor, kozeposl] */
static int Dest2(int sor, int osl, int kozepsor, int kozeposl)
{
	return ((sor - kozepsor)*(sor - kozepsor) + (osl - kozeposl)*(osl - kozeposl));
}

static int cmp(const void *a, const void *b)
{
	int *v , *w;

	v = (int *)a;
	w = (int *)b;

	return Dest2(v[0], v[1], sulysor, sulyosl) - Dest2(w[0], w[1], sulysor, sulyosl);
}

/* 
	Feltolti a csiga[][] valtozot
	El kell rendezni a kozeli ures mezoket, hogy jobb eredmenyt kapjunk
	Az aktualis jatekallas alapjan szamitott kozepponttol szamitott tavolsag alapjan rendezunk 
*/
static void InitCsiga(PJATEKALLAS jatek)
{
	int i, j, k;

	for (i = 0, k = 0; i < jatek->SOR; i++) {
		for (j = 0; j < jatek->OSL; j++, k++) {
			csiga[k][0] = i;
			csiga[k][1] = j;
		}
	}

	qsort(csiga, k, 2 * sizeof(int), cmp);
}

/* Iranytol fuggoen beallitja az esor, eosl valtozokat */
static void Getesoreosl(int irany, int *esor, int *eosl)
{
	if (irany == 3 || irany == 4 || irany == 5) {
		*esor = 1;
	} else if (irany == 7 || irany == 0 || irany == 1) {
		*esor = -1;
	} else {
		*esor = 0;
	}
	if (irany == 1 || irany == 2 || irany == 3) {
		*eosl = 1;
	} else if (irany == 5 || irany == 6 || irany == 7) {
		*eosl = -1;
	} else {
		*eosl = 0;
	}
}

/* Egy ures mezo erteket adja vissza (sablonok alapjan szamol) */
static int UresErtek(PJATEKALLAS jatek, int sor, int osl, int tavolsag, int jatekos)
{
	int k, i, j, l, jo, a, b;
	int pont = 0;
	int multi;
	int irany;
	int elodb, mogdb;
	int elotte, mogotte;
	int esor, eosl; 

	for (a = 0; a < 4; a++) {
		/* 
			Leellenorizzuk, hogy a mezo belefer-e barhogyan egy 
			ot hosszu keretbe ugy, hogy nincs benne az ellenfelnek jele 
			es azt is osszeszamoljuk, hogy elotte es mogotte mennyi hely van
			ugy, hogy nincs benne az ellenfelnek jele, ezt azert tudjuk hasznalni,
			mert a sablonokban nincs olyan, amiben van ellenfel jel
		*/
		irany = a;
		elodb = mogdb = 0;
		Getesoreosl(irany, &esor, &eosl);
		for (i = sor + esor, j = osl + eosl, l = 0; l < 4;
			i += esor, j += eosl, l++) {
			if (i < jatek->SOR && i >= 0 && j < jatek->OSL && j >= 0) {
				if (GetTabla(jatek->tabla, i, j) == 3 - jatekos) {
					break;
				}
			} else {
				break;
			}
			elodb++;
		}
		for (i = sor - esor, j = osl - eosl, l = 0; l < 4;
		i -= esor, j -= eosl, l++) {
			if (i < jatek->SOR && i >= 0 && j < jatek->OSL && j >= 0) {
				if (GetTabla(jatek->tabla, i, j) == 3 - jatekos) {
					break;
				}
			} else {
				break;
			}
			mogdb++;
		}
		/* Nem fer bele egy otos keretbe */
		if (elodb + mogdb + 1 < 5) {
			continue;
		}
		for (b = 0; b < 2; b++) {
			irany = a + b*4;
			elotte = (b == 0) ? elodb : mogdb;
			mogotte = (b == 0) ? mogdb : elodb;
			Getesoreosl(irany, &esor, &eosl);
			for (k = 0; k < URESSABLONDB; k++) {
				if ((k != 7 && k != 10 && tavolsag == 1) || (k == 7 || k == 10)) {
					/* Ellenorizzuk, hogy nem log-e tul a tablan */
					if (mogotte >= uressablonok[k][1] - 1 &&
						elotte >= uressablonok[k][0] - uressablonok[k][1]) {
						jo = 1;
						for (i = sor - esor*(uressablonok[k][1] - 1), j = osl - eosl*(uressablonok[k][1] - 1), l = 2; 
							l < uressablonok[k][0] + 2; 
							i += esor, j += eosl, l++) {
							switch (uressablonok[k][l]) {
								case 0:
									if (GetTabla(jatek->tabla, i, j) != 0)
										jo = 0;
									break;
								case 1:
									if (GetTabla(jatek->tabla, i, j) != jatekos)
										jo = 0;
									break;
								case 2:
									if (GetTabla(jatek->tabla, i, j) != 3 - jatekos)
										jo = 0;
									break;
							}
							if (jo == 0)
								break;
						}
						if (jo == 1) {
							multi = 1;
							/* 
								Ha meg a sablon utan a megfelelo iranyba van egy ures mezo, 
								megszorozzuk a ponterteket a megfelelo multival 
							*/
							if ((i = sor + esor*(uressablonok[k][0] - uressablonok[k][1] + 1)) < jatek->SOR && 
								i >= 0 &&
								(j = osl + eosl*(uressablonok[k][0] - uressablonok[k][1] + 1)) < jatek->OSL && 
								j >= 0 &&
								GetTabla(jatek->tabla, i, j) == 0) {
								if (k <= 8)
									multi = uresmulti[k];
							}
							pont += ponturessablonok[k] * multi;
							break; /* Ha talal egy egyezo sablont, uj irannyal folytatja */
						}
					}
				} 
			}
		}
	}
	return pont;
}

static int UresPontoz(PJATEKALLAS jatek, int jatekos, URESMEZO *nears, int neardb)
{
	int i;
	int pont = 0;

	/* Osszeadjuk a pontokat az osszes kozeli uresmezore */
	for (i = 0; i < neardb; i++) {
		pont += UresErtek(jatek, nears[i].sor, nears[i].osl, nears[i].pont, jatekos);
	}
	return pont;
}

/*
	_XXXX
	X_XXX
	XX_XX
	XXX_X
	XXXX_

	^
	|
	fele allasok keresese, ilyenkor biztosan egy meghatarozott helyre kell lepni, hogy
	biztos gyozzon, vagy elkerulje a biztos vereseget
*/
static int MIEll_majdnem5(PJATEKALLAS jatek, int jatekos, int *sor, int *osl)
{
	int i, j, k, l, irany, jo;
	int esor, eosl, msor, mosl;


	for (irany = 2; irany < 6; irany++) {
		Getesoreosl(irany, &esor, &eosl);
		for (msor = 0; msor < jatek->SOR; msor++) {
			for (mosl = 0; mosl < jatek->OSL; mosl++) {
				for (k = 0; k < ELLSABLONDB; k++) { /* Vegigmegy az osszes sablonon */
					/* Ellenorizzuk, hogy nem log-e tul a tablan */
					if (msor + esor*4 < jatek->SOR && 
						msor + esor*4 >= 0 &&
						mosl + eosl*4 < jatek->OSL && 
						mosl + eosl*4 >= 0) {
						jo = 1;
						for (i = msor, j = mosl, l = 0; l < 5; 
							i += esor, j += eosl, l++) {
							switch (ellsablonok_majdnem5[k][l]) {
								case 0:
									if (GetTabla(jatek->tabla, i, j) != 0)
										jo = 0;
									break;
								case 1:
									if (GetTabla(jatek->tabla, i, j) != jatekos)
										jo = 0;
									break;
								case 2:
									if (GetTabla(jatek->tabla, i, j) != 3 - jatekos)
										jo = 0;
									break;
							}
							if (jo == 0)
								break;
						}
						if (jo == 1) {
							*sor = msor + esor * k; /* Igy definialtuk a tombot */
							*osl = mosl + eosl * k;
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

static int MIEll_harom(JATEKALLAS *jatek, int jatekos)
{
	int i, j, l, k, msor, mosl;
	int irany;
	int esor, eosl, jo;

	
	for (irany = 2; irany < 6; irany++) {
		Getesoreosl(irany, &esor, &eosl);
		for (k = 0; k < 4; k++) { /* Vegigmegy az osszes sablonon */		
			for (msor = 0; msor < jatek->SOR; msor++) {
				for (mosl = 0; mosl < jatek->OSL; mosl++) {
					if (msor + esor*(ellsablonok_harom[k][0] - 1) < jatek->SOR &&
						mosl + eosl*(ellsablonok_harom[k][0] - 1) >= 0 && 
						mosl + eosl*(ellsablonok_harom[k][0] - 1) < jatek->OSL) {
						jo = 1;
						for (i = msor, j = mosl, l = 1; l < ellsablonok_harom[k][0] + 1; 
							i += esor, j += eosl, l++) {
							switch (ellsablonok_harom[k][l]) {
								case 0:
									if (GetTabla(jatek->tabla, i, j) != 0)
										jo = 0;
									break;
								case 1:
									if (GetTabla(jatek->tabla, i, j) != jatekos)
										jo = 0;
									break;
								case 2:
									if (GetTabla(jatek->tabla, i, j) != 3 - jatekos)
										jo = 0;
									break;
							}
							if (jo == 0)
								break;
						}
						if (jo == 1) {
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

/* 
	Az aktualis tabla alapjan, egy uresmezo sorozatot csinal 
	(csak azok vannak benne, amik 1 vagy 2 tavolsagra vannak a nemures mezoktol)
*/
static void GetNears(PJATEKALLAS jatek, URESMEZO *nears, int *neardb)
{
	int i, j, db = 0, asor, aosl;
	MEZO sor[16 * 16];
	int szint[16][16];
	int sorelso = 0, sorutolso = 0;

	for (i = 0; i < 16 * 16; i++) {
		nears[i].sor = nears[i].osl = -1;
		nears[i].pont = 0;
		asor = csiga[i][0];
		aosl = csiga[i][1];
		szint[asor][aosl] = -1;
		if (GetTabla(jatek->tabla, asor, aosl) != 0) {
			sor[sorutolso].sor = asor;
			sor[sorutolso].osl = aosl;
			szint[asor][aosl] = 0;
			sorutolso++;
		}
	}

	while (sorutolso > sorelso) {
		asor = sor[sorelso].sor;
		aosl = sor[sorelso].osl;
		if (szint[asor][aosl] < 2) {
			for (i = -1; i <= 1; i++) {
				for (j = -1; j <= 1; j++) {
					/* Ha nem log ki es meg nem neztuk (ekkor persze ures) */
					if (asor + i >= 0 && asor + i < jatek->SOR &&
					aosl + j >= 0 && aosl + j < jatek->OSL && 
					(i != 0 || j != 0) && szint[asor + i][aosl + j] == -1) {
						if (szint[asor][aosl] == 0) {
							sor[sorutolso].sor = asor + i;
							sor[sorutolso].osl = aosl + j;
							sorutolso++;
						}
						nears[db].sor = asor + i;
						nears[db].osl = aosl + j;
						nears[db].pont = szint[asor + i][aosl + j] = szint[asor][aosl] + 1;					
						db++;
					}
				}
			}
		}
		sorelso++;
	}
	*neardb = db;
}

/*
	Az aktualis jatekallas legjobb MEDDIGDB mezojet irja 
	bele a best vektorba, ertek szerint csokkeno sorrendben
*/
static void GetBest(PJATEKALLAS jatek, int kilep, MEZO *best, URESMEZO *nears, int neardb)
{
	int i, k, ertek;
	int pontok[MEDDIGDB];

	for (k = 0; k < MEDDIGDB; k++) {
		best[k].sor = best[k].osl = -1;
		pontok[k] = -1000000000;
	}
	/* 
		Mindig MEDDIGDB dbot szamolunk ki, mert ez nem lassit sokat, 
		es igy ha a faban taroljuk, barmelyik melysegen hasznalhato 
	*/
	for (i = 0; i < neardb; i++) {
		ertek = 19*UresErtek(jatek, nears[i].sor, nears[i].osl, nears[i].pont, kilep) + 
		16*UresErtek(jatek, nears[i].sor, nears[i].osl, nears[i].pont, 3 - kilep);		
		for (k = MEDDIGDB - 1; k >= 0; k--) {
			if (ertek > pontok[k]) {
				if (k < MEDDIGDB - 1) {
					best[k + 1] = best[k];
					pontok[k + 1] = pontok[k];
				}
				best[k].sor = nears[i].sor;
				best[k].osl = nears[i].osl;
				pontok[k] = ertek;
			}
		}
	}
}

static int GetMeddig(int vdepth)
{
	switch (vdepth) {
		case 1:
			return MEDDIGDB;
		case 2:
		case 3:
			return MEDDIGDB - 3;
		case 4:
		case 5:
			return MEDDIGDB - 4;
		case 6:
		case 7:
			return MEDDIGDB - 5;
		default:
			return MEDDIGDB - 6;
	}
}

static int NegaScoutMem(PJATEKALLAS jatek, int kilep, int alpha, int beta, int depth, int vdepth, unsigned hash)
{
	int meddig, k, l;
	int a, b;
	int ujhash;
	int masol;
	int valpha = alpha, vbeta = beta;
	URESMEZO nears[16 * 16];
	MEZO tmp;
	int neardb;
	ADAT adat;

	if (Gyoz(jatek, kilep) == 1) {
		return 90000000 + depth; /* Ha elobb tud nyerni, az jobb (+ depth) */
	}
	if (Gyoz(jatek, 3 - kilep) == 1) {
		return -90000000 - depth;
	}
	if (depth == 0 || vdepth + jatek->lepes >= jatek->SOR * jatek->OSL) {
		GetNears(jatek, nears, &neardb);
		if ((vdepth & 1) == 0) { /* Eredeti jatekos */
			return MIOff*UresPontoz(jatek, kilep, nears, neardb) - MIDef*UresPontoz(jatek, 3 - kilep, nears, neardb);
		} else { /* Ellenfel jatekos */
			return MIDef*UresPontoz(jatek, kilep, nears, neardb) - MIOff*UresPontoz(jatek, 3 - kilep, nears, neardb);
		}
	}

	meddig = GetMeddig(vdepth);

	if (SearchBifa(root, hash, jatek, &adat) == 1) { /* Ha megtalalta */
		if (adat.regi != 1) {
			if (adat.lower >= beta) {
				return adat.lower;
			}
			if (adat.upper <= alpha) {
				return adat.upper;
			}
			if (adat.lower > alpha) {
				alpha = adat.lower;
			}
			if (adat.upper < beta) {
				beta = adat.upper;
			}
		} else {
			adat.lower = -1000000000;
			adat.upper = 1000000000;
			adat.vdepth = vdepth;
			adat.regi = 0;
		}
		
	} else { /* Ha nem talalta meg */
		adat.lower = -1000000000;
		adat.upper = 1000000000;
		adat.vdepth = vdepth;
		adat.regi = 0;
		GetNears(jatek, nears, &neardb);
		GetBest(jatek, kilep, adat.best, nears, neardb);
	}

	if (alpha >= beta) {
		goto end; /* Ilyenkor a vegere ugrunk */
	}

	b = beta;
	for (k = 0; k < meddig; k++) {
		masol = 0;
		if (adat.best[k].sor == -1) {
			break;
		}
		SetTabla(jatek->tabla, adat.best[k].sor, adat.best[k].osl, kilep);

		/* Zobrist hasing, x ^ 0 == x, ezert 0-val nem XORolunk */
		ujhash = hash ^ zobtabla[adat.best[k].sor][adat.best[k].osl][kilep];
		/* Proba: Null-window search */
		a = -NegaScoutMem(jatek, 3 - kilep, -b, -alpha, depth - 1, vdepth + 1, ujhash);
		SetTabla(jatek->tabla, adat.best[k].sor, adat.best[k].osl, 0);
		if (a > alpha) {
			alpha = a;
			masol = 1; /* Megvaltoztatjuk a best-ek sorrendjet, mivel ez jobb, mint az elozoek */
		}
		if (alpha >= beta) {
			break;
		}
		if (alpha >= b) { /* Ha a Null-window search nem volt jo, ujra keresunk */
			SetTabla(jatek->tabla, adat.best[k].sor, adat.best[k].osl, kilep);
			ujhash = hash ^ zobtabla[adat.best[k].sor][adat.best[k].osl][kilep];
			alpha = -NegaScoutMem(jatek, 3 - kilep, -beta, -alpha, depth - 1, vdepth + 1, ujhash);
			SetTabla(jatek->tabla, adat.best[k].sor, adat.best[k].osl, 0);
			if (alpha >= beta) {
				break;
			}
		}
		/* Bestek sorrendjenek megvaltoztatasa */
		if (masol == 1) {
			tmp = adat.best[k];
			for (l = 0; l < k; l++) {
				adat.best[l + 1] = adat.best[l];
			}
			adat.best[0] = tmp;
		}
		/* Uj Null-window beallitasa */
		b = alpha + 1;
	}
	if (alpha < vbeta) {
		adat.upper = alpha;
	}
	if (alpha > valpha) {
		adat.lower = alpha;
	}
end:
	root = AddBifa(root, hash, jatek, &adat); /* Uj pont hozzaadasa a fahoz, vagy egy regi frissitese */
	return alpha;
}

static void FirstNegaScout(PJATEKALLAS jatek, int kilep, int *sor, int *osl, int depth, unsigned hash)
{
	MEZO best[MEDDIGDB];
	int josor = 0, joosl = 0;
	int alpha = -1000000000, beta = 1000000000;
	int a, b, k;
	int ujhash;
	URESMEZO nears[16 * 16];
	int neardb;
	
	GetNears(jatek, nears, &neardb);
	GetBest(jatek, kilep, best, nears, neardb);

	b = beta;
	for (k = 0; k < MEDDIGDB; k++) {
		if (best[k].sor == -1) {
			break;
		} 
		SetTabla(jatek->tabla, best[k].sor, best[k].osl, kilep);
		ujhash = hash ^ zobtabla[best[k].sor][best[k].osl][kilep];
		a = -NegaScoutMem(jatek, 3 - kilep, -b, -alpha, depth - 1, 1, ujhash);
		fprintf(stderr, "a: %d, alpha: %d, sor: %d, osl: %d\n", a, alpha, best[k].sor + 1, best[k].osl + 1);
		SetTabla(jatek->tabla, best[k].sor, best[k].osl, 0);
		if (a > alpha) {
			fprintf(stderr, "a: %d, alpha: %d, regisor: %d, regiosl: %d, ujsor: %d, ujosl: %d\n", a, alpha, josor + 1, joosl + 1, best[k].sor + 1, best[k].osl + 1);
			josor = best[k].sor;
			joosl = best[k].osl;
			alpha = a;
		}
		if (alpha >= beta) {
			break;
		}
		if (alpha >= b) {
			SetTabla(jatek->tabla, best[k].sor, best[k].osl, kilep);
			ujhash = hash ^ zobtabla[best[k].sor][best[k].osl][kilep];
			alpha = -NegaScoutMem(jatek, 3 - kilep, -beta, -alpha, depth - 1, 1, ujhash);
			SetTabla(jatek->tabla, best[k].sor, best[k].osl, 0);
			if (alpha >= beta) {
				break;
			}
		}
		b = alpha + 1;
	}
	*sor = josor;
	*osl = joosl;
	fprintf(stderr, "vegsosor: %d, vegsoosl: %d\n", josor + 1, joosl + 1);
	return;
}

static void LougrasFirstNegaScout(PJATEKALLAS jatek, int kilep, int *sor, int *osl, int depth, unsigned hash, int aktlo)
{
	MEZO best[MEDDIGDB];
	int josor = 0, joosl = 0;
	int alpha = -1000000000, beta = 1000000000;
	int i, j;
	int a, b, k;
	int ujhash;
	URESMEZO nears[16 * 16];
	int neardb;
	URESMEZO ujnears[16 * 16];
	int ujneardb = 0;
	int vanlo = 0;
	
	GetNears(jatek, nears, &neardb);

	/*
		A nears vektorbol kivesszuk azokat, 
		melyek az aktualis lougrasban is benne vannak
	*/
	for (k = 0; k < neardb; k++) {
		for (i = 0; i < jatek->SOR; i++) {
			for (j = 0; j < jatek->OSL; j++) {
				if (nears[k].sor == i && nears[k].osl == j && 
					lougras[aktlo][i][j] == 0) {
					ujnears[ujneardb++] = nears[k];
					vanlo = 1;
				}
			}
		}
	}

	if (vanlo == 1) { /* Ha volt lougrasos ures hely */
		GetBest(jatek, kilep, best, ujnears, ujneardb);
	} else {
		GetBest(jatek, kilep, best, nears, neardb);
	}

	josor = best[0].sor;
	joosl = best[0].osl;
	b = beta;
	for (k = 0; k < (MEDDIGDB < ujneardb ? MEDDIGDB : ujneardb); k++) {
		if (best[k].sor == -1) {
			break;
		} 
		SetTabla(jatek->tabla, best[k].sor, best[k].osl, kilep);
		ujhash = hash ^ zobtabla[best[k].sor][best[k].osl][kilep];
		a = -NegaScoutMem(jatek, 3 - kilep, -b, -alpha, depth - 1, 1, ujhash);
		SetTabla(jatek->tabla, best[k].sor, best[k].osl, 0);
		if (a > alpha) {
			josor = best[k].sor;
			joosl = best[k].osl;
			alpha = a;
		}
		if (alpha >= beta) {
			break;
		}
		if (alpha >= b) {
			SetTabla(jatek->tabla, best[k].sor, best[k].osl, kilep);
			ujhash = hash ^ zobtabla[best[k].sor][best[k].osl][kilep];
			alpha = -NegaScoutMem(jatek, 3 - kilep, -beta, -alpha, depth - 1, 1, ujhash);
			SetTabla(jatek->tabla, best[k].sor, best[k].osl, 0);
			if (alpha >= beta) {
				break;
			}
		}
		b = alpha + 1;
	}
	*sor = josor;
	*osl = joosl;
	return;
}

void MI(PJATEKALLAS jatek, int jatekos, int *sor, int *osl, int depth)
{
	int i, maxlo = 0, ellenlepesdb = (jatek->lepes - 3 + jatekos)/2 + 1;

	fprintf(stderr, "---------------------------\n");
	fprintf(stderr, "---------- %d. lepes ------\n", jatek->lepes);
	if (MIEll_majdnem5(jatek, jatekos, sor, osl) == 1 || 
		MIEll_majdnem5(jatek, 3 - jatekos, sor, osl) == 1) {
		fprintf(stderr, "vegsosor: %d, vegsoosl: %d\n", *sor + 1, *osl + 1);
		return;
	}
	root = roots[jatekos - 1];
	InitSulykozep(jatek);
	InitCsiga(jatek);
	if (ellenlepesdb >= 3 && 
		MIEll_harom(jatek, jatekos) != 1 &&
		MIEll_harom(jatek, 3 - jatekos) != 1) {
		InitLougras(jatek, jatekos);
		/* Megkeresi a legtobbszor hasznalt lougrast */
		for (i = 0; i < 10; i++) {
			if (lougrasdb[maxlo] < lougrasdb[i]) {
				maxlo = i;
			}
		}
		/* 
			Ha eleg nagy hanyada lolepes az utolso lepesek kozott es
			az ellenfel utolso lepese lolepes volt 
			es az a legtobbszor hasznalt lolepesbol valo 
		*/
		if (lougrasdb[maxlo] > ULEPDB * 2/3 && loutolso[maxlo] == 1) {
			LougrasFirstNegaScout(jatek, jatekos, sor, osl, depth, ZobristHash(jatek), maxlo);
		} else {
			FirstNegaScout(jatek, jatekos, sor, osl, depth, ZobristHash(jatek));
		}
	} else {
		FirstNegaScout(jatek, jatekos, sor, osl, depth, ZobristHash(jatek));
	}
	fprintf(stderr, "sima : %d\n", GetBifaNodeCount(root));
	fprintf(stderr, "teljes : %d\n", GetFullBifaCount(root));
	fprintf(stderr, "szintek szama : %d\n", GetBifaLevelCount(root));
	root = RefreshBifa(root);
	fprintf(stderr, "sima : %d\n", GetBifaNodeCount(root));
	fprintf(stderr, "teljes : %d\n", GetFullBifaCount(root));
	fprintf(stderr, "szintek szama : %d\n", GetBifaLevelCount(root));
	fprintf(stderr, "---------------------------\n");
	fprintf(stderr, "\n");
	roots[jatekos - 1] = root;
}

void MIInit(void)
{
	root = roots[0] = roots[1] = NULL;
	sulysor = sulyosl = 0;
}

void MIExit(void)
{
	roots[0] = DestroyBifa(roots[0]);
	roots[1] = DestroyBifa(roots[1]);
	root = NULL;
}
