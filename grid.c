#include <stdlib.h>
#include "grid.h"

//  TILE

//constructor
tile* newTile(){
    tile* _t = malloc(sizeof(tile));
    //_t->data = 0; //valor padrão de data.
    
    _t->data = ' ';
    _t->hit = false;
    _t->sunk = false;

    _t->up = NULL; 
    _t->down = NULL; 
    _t->left = NULL;
    _t->right = NULL;
    return _t;
}

//funções
void tileChangeData(tile* _tile, char _data){
    _tile->data = _data;
}
char tilePrintPlayer(tile* _tile){
    char _c = ' ';
}

//problema 1:
//
//+abcdefg
//1  ^
//2  #^
//3 @##<>
//4  v#
//5   #
//6   v
//
//ao escolher C3, como saber quais
//partes pertencem ao mesmo navio?

bool tileCheckNeighbors(tile* _t, int _dir){
    //função retorna verdadeiro se encontrou uma ponta de embarcação valida
    //por exemplo, achar uma ponta (v) indo para a direita indica que
    //provavelmente não é da mesma embarcação.
    //no entanto, achar uma ponta (v) indo para baixo só pode ser da
    //mesma embarcação.
    
    //direções são: 
    // 0 = baixo para cima (^), 1 = esquerda para a direita (>), 
    // 2 = cima para baixo (v), 3 = direita para a esquerda (<).
    // (0 = ^)      (1 = >)      (2 = v)      (3 = <)

    //se o ponteiro não existe (bordas), retornar falso
    if(_t == NULL) return false;

    //se vindo de baixo para cima, e encontrou um final ^, retornar verdadeiro
    if(_dir == 0 && _t->data == '^') return true;
    //se vindo de cima para baixo, e encontrou um final v, retornar verdadeiro
    else if(_dir == 2 && _t->data == 'v') return true;
    //se vindo da esquerda para a direita, e encontrou um final >, retornar verdadeiro
    else if(_dir == 1 && _t->data == '>') return true;
    //se vindo da direita para a esquerda, e encontrou um final <, retornar verdadeiro
    else if(_dir == 3 && _t->data == '<') return true;

    //se encontrou um corpo #, continuar na direção atual
    else if (_t->data == '#'){
        if(_dir == 0) return tileCheckNeighbors(_t->up, _dir);
        else if(_dir == 1) return tileCheckNeighbors(_t->right, _dir);
        else if(_dir == 2) return tileCheckNeighbors(_t->down, _dir);
        else if(_dir == 3) return tileCheckNeighbors(_t->left, _dir);
    }
    
    //se nenhum desses casos é valido 
    //(por exemplo, achou um '@' ou '&' ou ' ')
    //retornar falso
    else return false;
}


//  BOARD

board* newBoard(){
    //cria um board, e preenche com 12x12 tiles a partir de A1.
    board* _b = malloc(sizeof(board));
    _b->root = newTile(); //A1
    //preencher a lista.
    tile* currentY = _b->root;
    for(int y = 1; y <= 12; y++){
        
        tile* currentX = currentY;
        for(int x = 1; x <= 12; x++){ //cria uma fila no Y atual
            //printf("(%d-%d) ", x, y);
            currentX->right = newTile();
            currentX->right->left = currentX; //conecta todas as fileiras horizontalmente

            currentX = currentX->right;
        }
        //printf("\n");
        currentY->down = newTile();
        currentY->down->up = currentY; //conecta a coluna A verticalmente

        currentY = currentY->down;
    }
    //note que, fora os tiles em A, os outros tiles 
    //não estão conectados verticalmente (ponteiros up e down)
    //agora, conectar todos os tiles.
    tile* upperY = _b->root;
    tile* lowerY = _b->root->down;

    for(int y = 1; y < 12; y++){
        //dessa vez até 11, pois estamos checando y e y+1

        tile* upperX = upperY;
        tile* lowerX = lowerY;
        for(int x = 1; x <= 12; x++){
            upperX->down = lowerX;
            lowerX->up = upperX;

            upperX = upperX->right;
            lowerX = lowerX->right;
        }

        lowerY = lowerY->down;
        upperY = upperY->down;
    }
    //agora todos os tiles devem estar conectados.

    return _b;
}

tile* BoardGetTileAt(board* _board, int _x, int _y){
    //x são as letras, y são os numeros. ambos começam em 1 e terminam em 12
    //if (_x>12 || _y>12) return NULL;
    tile* current = _board->root;
    
    //navegar o eixo y(numeros), começando em 1
    for(int i = 1; i < _y; i++){
        current = current->down;
    }

    //navegar o eixo x(letras), começando em 1
    for(int i = 1; i < _x; i++){
        current = current->right;
    }
    
    return current;
}
