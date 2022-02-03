#include <stdio.h>
#include "grid.h"
#include "interface.h"
#include "ai.h"

//  GAME MANAGER
//salva os tabuleiros e turnos.

typedef struct _GameManager{
    bool turn; //true = jogador, false = cpu
    board* playerboard;
    board* aiboard;
} game;

game* newGame(){
    game* _g = malloc(sizeof(game));
    _g->turn = true;
    _g->playerboard = newBoard();
    _g->aiboard = newBoard();
    return _g;
}

//para testes
int main(){
    srand(time(NULL));
    game* g = newGame();

    //debug
    //BoardRandomPopulate(g->aiboard);
    //debug

    posicionando_EmbarcacoesIA(g->aiboard);
    
    posicionando_EmbarcacoesIA(g->playerboard); //autocolocar barcos
    //posicionando_Embarcacoes(g->playerboard, g->aiboard);
   
    printf("\nComeca a Batalha Naval!\n\n");
    while(1){
        printBoards(g->playerboard, g->aiboard);
        efetuar_Disparo(g->aiboard);
        efetuar_DisparoIA(g->playerboard);
    }

    return EXIT_SUCCESS;
}