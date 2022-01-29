#ifndef HEADER_GRID
#define HEADER_GRID
//include once

#include <stdlib.h>
#include <stdbool.h>

//  TILE
//tile representa cada quadrado do mapa 
typedef struct _Tile {
    char data; //guarda o que está no quadrado
    bool hit; //se o quadrado foi acertado ou não
    bool sunk; //se uma embarcação foi afundada completamente

    //ponteiros para os vizinhos
    struct _Tile* up;
    struct _Tile* down;
    struct _Tile* left;
    struct _Tile* right;
} tile;

tile* newTile(); //constructor

void tileChangeData(tile* _tile, char _data);
char tileDataToPrint(tile* _tile);

//  BOARD
//board é o tabuleiro, conjunto de tiles
typedef struct _Board {
    struct _Tile* root; //quadrado A1
} board;

board* newBoard();

tile* BoardGetTileAt(board* _board, int _x, int _y);

#endif