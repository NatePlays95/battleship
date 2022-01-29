#include <stdio.h>
#include "grid.h"

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

void printBoards(game* _game){
    printf("      Humano         Computador  \n");
    printf("   ABCDEFGHIJKL     ABCDEFGHIJKL \n");
    printf("  +------------+   +------------+\n");
    printf(" 1|            |  1|            |\n");
    printf(" 2|            |  2|            |\n");
    printf(" 3|            |  3|            |\n");
    printf(" 4|            |  4|            |\n");
    printf(" 5|            |  5|            |\n");
    printf(" 6|            |  6|            |\n");
    printf(" 7|            |  7|            |\n");
    printf(" 8|            |  8|            |\n");
    printf(" 9|            |  9|            |\n");
    printf("10|            | 10|            |\n");
    printf("11|            | 11|            |\n");
    printf("12|            | 12|            |\n");
    printf("  +------------+   +------------+\n");
}