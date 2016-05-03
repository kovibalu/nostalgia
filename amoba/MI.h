#ifndef MI_H
#define MI_H

#include "amoba.h"

#define MEDDIGDB 8

typedef struct {
	int sor;
	int osl;
	int pont;
} URESMEZO, *PURESMEZO;

void MI(PJATEKALLAS jatek, int jatekos, int *sor, int *osl, int depth);
void MIInit(void);
void MIExit(void);

#endif //MI_H
