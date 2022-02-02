#ifndef INTER_GRID
#define INTER_GRID
//incluir uma vez

//#include <stdio.h>
//#include <stdlib.h> inclusos no grid.h
#include "grid.h"

int tratar_String(char* string, int* a, int* b );

void posicionando_Embarcacoes(struct _Board* _board);

int efetuar_Disparo(struct _Board* _board);

#endif