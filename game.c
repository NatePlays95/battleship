#include <stdio.h>
#include "grid.h"
#include "interface.h"
#include "ai.h"

//alternancia de turnos.
void gameLoop(game* _g){
    while(1){
        if (_g->turn){ //vez do humano
            efetuar_Disparo(_g);
        } else { //vez da IA
            efetuar_DisparoIA(_g);
        }
        //testar o placar.
        resultado = testForDefeat(_g);
        if(resultado!=0){
            if (resultado==1) printf("Jogador Humano venceu a batalha!\n\n");
            else printf("Computador venceu a batalha.\n\n");
            
            break;
        }
    }
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
    gameloop(g);
    
    // while(1){
    //     printBoards(g->playerboard, g->aiboard);
    //     efetuar_Disparo(g->aiboard);
    //     efetuar_DisparoIA(g->playerboard);
    // }

    return EXIT_SUCCESS;
}