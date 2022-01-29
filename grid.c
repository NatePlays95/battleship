#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> //para testes
#include "grid.h"

//  TILE

//constructor
tile* newTile(){
    tile* _t = malloc(sizeof(tile));
    //_t->data = 0; //valor padrão de data.
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

//  BOARD

//boa sorte decifrando esse daqui
board* newBoard(){
    board* _b = malloc(sizeof(board));
    _b->root = newTile(); //A1
    //preencher a lista.
    tile* currentY = _b->root;
    for(int y = 1; y <= 12; y++){
        
        tile* currentX = currentY;
        for(int x = 1; x <= 12; x++){
            //printf("(%d-%d) ", x, y);
            currentX->right = newTile();
            currentX = currentX->right;
        }
        //printf("\n");
        currentY->down = newTile();
        currentY = currentY->down;
    }

    return _b;
}

tile* BoardGetTileAt(board* _board, int _x, int _y){
    //x são as letras, y são os numeros. ambos começam em 1 e terminam em 12
    //if (_x>12 || _y>12) return NULL;
    tile* current = _board->root;
    
    //navegar o eixo x(letras), começando em 1
    for(int i = 1; i < _x; i++){
        current = current->right;
    }
    //navegar o eixo y(numeros), começando em 1
    for(int i = 1; i < _y; i++){
        current = current->down;
    }

    return current;
}
