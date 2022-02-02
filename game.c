#include <stdio.h>
#include "grid.h"
#include "interface.h"

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
    
    //template da fileira: printf(" 1|            |  1|            |\n");
    //printar cada fileira
    for(int f = 1; f <= 12; f++){
        //separador
        if (f < 10) printf(" "); printf("%d|", f); //" 1|"

        //lado humano
        tile* current = BoardGetTileAt(_game->playerboard, 1, f);
        for(int x = 1; x <= 12; x++){
            printf("%c", tilePrintDataPlayer(current));
            current = current->right;
        }
        
        //separador
        printf("| "); if (f < 10) printf(" "); printf("%d|", f); //"| 1|"

        //lado computador
        current = BoardGetTileAt(_game->aiboard, 1, f);
        for(int x = 1; x <= 12; x++){
            printf("%c", tilePrintDataAi(current));
            current = current->right;
        }
        printf("|\n");
    }
    printf("  +------------+   +------------+\n");
}


//para testes
int main(){
    game* g = newGame();
    //debug
    BoardRandomPopulate(g->aiboard);
    printBoards(g);

    posicionando_Embarcacoes(g->playerboard);
    printBoards(g);
    //debug

    return EXIT_SUCCESS;
}