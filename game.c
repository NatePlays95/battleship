// 510613 - Murilo Vinicius 
// 511800 - Natan Maia 

#include <stdio.h>
#include "grid.h"
#include "interface.h"
#include "ai.h"

//alternancia de turnos.
void gameLoop(game* _g){
    while(1){
        printBoards(_g->playerboard, _g->aiboard);
        if (_g->turn){ //vez do humano
            printf("\n  Vez do Humano  \n\n");
            efetuar_Disparo(_g);
        } else { //vez da IA
            printf("\n  Vez do Computador  \n\n");
            efetuar_DisparoIA(_g);
        }
        //testar o placar.
        int resultado = testForDefeat(_g);
        if(resultado!=0){
            if (resultado==1) printf("Computador venceu a batalha.\n\n");
            else printf("Jogador Humano venceu a batalha!\n\n");
            
            break;
        }
    }
}

//para testes
int main(){
    srand(time(NULL));
    game* g = newGame();

    posicionando_EmbarcacoesIA(g->aiboard);
    posicionando_EmbarcacoesIA(g->playerboard); //autocolocar barcos
    //posicionando_Embarcacoes(g->playerboard, g->aiboard); //jogador coloca os barcos
   
    printf("\nComeca a Batalha Naval!\n\n");
    gameLoop(g);
    

    return EXIT_SUCCESS;
}