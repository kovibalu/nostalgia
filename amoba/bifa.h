#ifndef BIFA_H
#define BIFA_H

#include "amoba.h"
#include "MI.h"

/* 
	Egy binaris fa, melynek csucsai a hash szerint rendezettek,
	egy csucsban az azonos hashu tablak (+ adatok) tarolodnak.
*/

/* Adat */
typedef struct adat {
	int lower, upper; /* Also, felso becsles */
	MEZO best[MEDDIGDB]; /* Az aktualis allashoz tartozo legjobb mezok */
	int vdepth; /* Aktualis melyseg */
	int regi; /* Ez azert kell, hogy tudjuk mikor kell torolni, es tudjuk 
				melyikek a regi csucsok, mivel ezet lower, upperje elevul */
} ADAT, *PADAT;

/* Lancolt lista */
typedef struct faadat {
	ADAT adat;
	unsigned tabla[16]; /* Aktualis allas */
	struct faadat *kov; /* A lancolt lista kovetkezo elemere mutato pointer */
} FAADAT, *PFAADAT;

typedef struct fapont {
	unsigned hash; /* Hashertek */
	struct fapont *bal, *jobb; /* Gyermekek */
	PFAADAT elso; /* A lancolt lista elso eleme */
} BIFA, *PBIFA;

PBIFA AddBifa(PBIFA root, unsigned hash, PJATEKALLAS jatek, PADAT adat);
int SearchBifa(PBIFA root, unsigned hash, PJATEKALLAS jatek, PADAT adat);
PBIFA DestroyBifa(PBIFA root);
PBIFA RefreshBifa(PBIFA root);
int GetBifaNodeCount(PBIFA root);
int GetFullBifaCount(PBIFA root);
int GetBifaLevelCount(PBIFA root);
unsigned ZobristHash(PJATEKALLAS jatek);

#endif //BIFA_H
