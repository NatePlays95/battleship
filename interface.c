#include "grid.h"
#include "interface.h"

//Função tratar string, separa a entrada em dois inteiros, exemplo A10, vira  1 e 10;
// uma parte importante dela é se ela encontrar qualquer coisa não planejada, ela para na hora e retorna 0, oq pode ser usada pra achar erros
// outro ponto, o scanf q eu criei não recebe letras dps de L, justamente para caso alguém digite A10M, seja uma entrada inválida, pois é algo desconhecido;
// se o scanf ficasse formatado para n receber M, ele receberia A10 como entrada ainda assim, o que não é coerente que uma entrada dessa funcione, por isso,
// se a entrada estiver um pouco fora dos conformes, mesmo que "POSSAMOS" utiliza-la, não iremos, pois A10M, por exemplo é incorreto

//detalhe: a e b viram 0 quando encontramos algo estranho só pra evitar possíveis bugs, não encontrei nenhum, mas vai que né
int tratar_String(char* string, int* a, int* b ){
    //limpar os ints antigos
    *a = 0; *b = 0;

    for(int i = 0; i<10; i++){
        if (string[i] == '\0') break;
        //caracteres especiais
        else if(string[i]<48) continue;
        
        //numeros
        else if(string[i]<58){
            (*b) = 10*(*b) + (string[i] - 48);
        } 

        //letras maiusculas
        else if(string[i]>64 && string[i]<77) (*a) = string[i] - 64;

        //letras minusculas
        else if(string[i]>96 && string[i]<109) (*a) = string[i] - 96;

        //caracteres especiais
        else {
            *a = 0;
            *b = 0;
            return 0;
        }
    }
    return 1;
}

//basicamente sequencia de inserções, junto de tratar string, detalhe, sempre "Limpar" as coordenadas e a orientação e o buffer de entrada(ver isso dps)
//enviar tabuleiro pra funçao
void posicionando_Embarcacoes(board* _jogador, board* _computador){
    char entrada[10];
    int coordenadaX, coordenadaY, contador = 0;
    char orientacao;
    bool val; //se a jogada é valida ou não
    while(1){
        
        printBoards(_jogador,_computador);
        
        printf("Digite a coordenada da Jangada: ");
        scanf(" %[A-Z a-z 0-9 ,]", entrada);
        tratar_String(entrada, &coordenadaX, &coordenadaY);
        //If com chamar Função de posicionar Jangada com (X,Y), se a função retornar true, Mensagem, se não, erro
        val = BoardPlaceBoat(_jogador, coordenadaX, coordenadaY);
        if(val){
            printf("Jangada Posicionada com Sucesso!\n");
            break;
        }
        else{
            printf("Erro. Digite Novamente!");
        }
    }
    
    while(contador < 2){
        
        printBoards(_jogador,_computador);

        coordenadaX, coordenadaY = 0;
        entrada[0] = '\0';
        printf("Digite a coordenada da submarino: ");
        scanf(" %[A-Z a-z 0-9 ,]", entrada);
        tratar_String(entrada, &coordenadaX, &coordenadaY);
        //Mesma coisa da Jangada :/
        val = BoardPlaceSubmarine(_jogador, coordenadaX, coordenadaY);
        if(val){
            printf("submarino Posicionado com Sucesso!\n");
            contador++;
        }
        else{
            printf("Erro. Digite Novamente!");
        }
    }
    contador = 0;

    while(contador<3){
        
        printBoards(_jogador,_computador);
        
        coordenadaX, coordenadaY = 0;
        entrada[0] = '\0';
        printf("Digite a coordenada da Fragatas: ");
        scanf(" %[A-Z a-z 0-9 ,]", entrada);
        printf("Digite a Orientação do Navio: \n h para Horizontal;\n v para Vertical\n");
        scanf(" %c", &orientacao);
        tratar_String(entrada, &coordenadaX, &coordenadaY);
        //If com chamar Função de posicionar fragata com (X,Y, orientacao), se a função retornar true, Mensagem de sucesso, se não, erro
        val = BoardPlaceShip(_jogador, coordenadaX, coordenadaY, orientacao);
        if(val){
            printf("Fragata Posicionada com Sucesso!\n");
            contador++;
        }
        else{
            printf("Erro. Digite Novamente!");
        }
    }
    contador = 0;
    while(contador<2){
        
        printBoards(_jogador,_computador);
        
        coordenadaX, coordenadaY = 0;
        entrada[0] = '\0';
        printf("Digite a coordenada da Destroyer: ");
        scanf(" %[A-Z a-z 0-9 ,]", entrada);
        printf("Digite a Orientação do Navio: \n h para Horizontal;\n v para Vertical\n");
        scanf(" %c", &orientacao);
        tratar_String(entrada, &coordenadaX, &coordenadaY);
        //mesmo das fragatas
        val = BoardPlaceDestroyer(_jogador, coordenadaX, coordenadaY, orientacao);
        if(val){
            printf("Destroyer Posicionada com Sucesso!\n");
            contador++;
        }
        else{
            printf("Erro. Digite Novamente!");
        }
    }
    while(1){
        
        printBoards(_jogador,_computador);
        
        coordenadaX, coordenadaY = 0;
        entrada[0] = '\0';
        printf("Digite a coordenada do Porta-Avioes: ");
        scanf(" %[A-Z a-z 0-9 ,]", entrada);
        printf("Digite a Orientação do Porta-Avioes: \n h para Horizontal;\n v para Vertical\n");
        scanf(" %c", &orientacao);
        tratar_String(entrada, &coordenadaX, &coordenadaY);
        //mesmo das fragatas
        val = BoardPlaceCarrier(_jogador, coordenadaX, coordenadaY, orientacao);
        if(val){
            printf("Porta-Avioes Posicionado com Sucesso!\n");
            break;
        }
        else{
            printf("Erro. Digite Novamente!");
        }
    }
    
}
// __fpurge(stdin); caso precise limpar o buffer de entrada, considerando q fflush não limpa no Linux aparentemente, colocar no começo dos while, mas cuidado com erros
    //Sugestão: Talvez a função de posicionamento de barcos possa retornar outros valores, como números para especificar o Porque do erro, 
    //por exemplo, coordenada ocupada ou coordenada inexistente etc
/* POSICIONANDO:1 PORTA AVIÕES (05 CASAS)
                2 DESTROYERS (03 CASAS)
                3 FRAGATAS (02 CASAS)
                2 SUBMARINOS (01 CASA)
                1 JANGADA (01 CASA)   
    */


int efetuar_Disparo(game* _g){
    board* _board = _g->aiboard; //atirando contra o computador
    char entrada[10];
    int coordenadaX, coordenadaY;
    while(1){
        coordenadaX, coordenadaY = 0;
        entrada[0] = '\0';
        printf("Digite a coordenada do disparo: ");
        scanf(" %[A-Z a-z 0-9 ,]", entrada);
        tratar_String(entrada, &coordenadaX, &coordenadaY);
        //no if função pra ver se o lugar já foi disparado ou não, caso tenha sido em um lugar existe e ok, else if, para acerto ou não
        if(shootTile(_g, _board, coordenadaX, coordenadaY)){
            break;
        }
        else{
            printf("Erro. Digite Novamente!\n");
        }
    }
}
