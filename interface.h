#ifndef HEADER_INTER
#define HEADER_INTER
//incluir uma vez

//#include <stdio.h>
//#include <stdlib.h> inclusos no grid.h
#include "grid.h"

int tratar_String(char* string, int* a, int* b );

void posicionando_Embarcacoes(board* _jogador, board* _computador);

int efetuar_Disparo(game* _g);

#endif