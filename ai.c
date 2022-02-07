#include "grid.h"
#include "ai.h"

void posicionando_EmbarcacoesIA(board* _computador){
    int coordenadaX, coordenadaY, contador = 0;
    char orientacao;
    bool val; //se a jogada é valida ou não

    while(1){
        //computador escolhe posições aleatórias
        coordenadaX = 1+(rand()%12); coordenadaY = 1+(rand()%12);

        //If com chamar Função de posicionar Jangada com (X,Y), se a função retornar true, Mensagem, se não, erro
        val = BoardPlaceBoat(_computador, coordenadaX, coordenadaY);
        if(val){
            //printf("Jangada Posicionada em %d-%d!\n", coordenadaX, coordenadaY);
            break;
        }
    }
    
    while(contador < 2){
        //computador escolhe posições aleatórias
        coordenadaX = 1+(rand()%12); coordenadaY = 1+(rand()%12);

        //Mesma coisa da Jangada :/
        val = BoardPlaceSubmarine(_computador, coordenadaX, coordenadaY);
        if(val){
            //printf("submarino Posicionado em %d-%d!\n", coordenadaX, coordenadaY);
            contador++;
        }

    }
    contador = 0;

    while(contador<3){
        //computador escolhe posições aleatórias
        coordenadaX = 1+(rand()%12); coordenadaY = 1+(rand()%12);
        //orientação também aleatória
        if (rand()%2 == 0) orientacao = 'h'; else orientacao = 'v';

        //If com chamar Função de posicionar fragata com (X,Y, orientacao), se a função retornar true, Mensagem de sucesso, se não, erro
        val = BoardPlaceShip(_computador, coordenadaX, coordenadaY, orientacao);
        if(val){
            //printf("Fragata Posicionada em %d-%d!\n", coordenadaX, coordenadaY);
            contador++;
        }
    }
    contador = 0;
    while(contador<2){
        //computador escolhe posições aleatórias
        coordenadaX = 1+(rand()%12); coordenadaY = 1+(rand()%12);
        //orientação também aleatória
        if (rand()%2 == 0) orientacao = 'h'; else orientacao = 'v';
        
        //mesmo das fragatas
        val = BoardPlaceDestroyer(_computador, coordenadaX, coordenadaY, orientacao);
        if(val){
            //printf("Destroyer Posicionada em %d-%d!\n", coordenadaX, coordenadaY);
            contador++;
        }
    }
    
    int tentativas = 1;
    while(1){
        //printf("tent %d; ",tentativas);
        //computador escolhe posições aleatórias
        coordenadaX = 1+(rand()%12); coordenadaY = 1+(rand()%12);
        //orientação também aleatória
        if (rand()%2 == 0) orientacao = 'h'; else orientacao = 'v';
        
        //mesmo das fragatas
        val = BoardPlaceCarrier(_computador, coordenadaX, coordenadaY, orientacao);
        if(val){
            //printf("Porta-Avioes Posicionado em %d-%d!\n", coordenadaX, coordenadaY);
            break;
        }
        else {
            tentativas++;
        }
    }
    
}

//TODO: criar a IA avançada (escolher posições próximas a acertos)
int efetuar_DisparoIA(game* _g){
    board* _board = _g->playerboard; //atirando contra o humano
    int coordenadaX, coordenadaY;
    while(1){
        coordenadaX = 1+(rand()%12); coordenadaY = 1+(rand()%12);
        //no if função pra ver se o lugar já foi disparado ou não, caso tenha sido em um lugar existe e ok, else if, para acerto ou não
        if(shootTile(_g, _board, coordenadaX, coordenadaY)){
            break;
        }
    }
}