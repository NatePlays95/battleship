#ifndef HEADER_GRID
#define HEADER_GRID
//incluir uma vez

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

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

bool tileCheckShip(tile* _t, int _dir);
bool tileCheckShipHit(tile* _t, int _dir);
void tileSinkShip(tile* _t, int _dir);

void hitTile(tile* _t);

char tilePrintDataPlayer(tile* _t);
char tilePrintDataAi(tile* _t);

//  BOARD
//board é o tabuleiro, conjunto de tiles
typedef struct _Board {
    struct _Tile* root; //quadrado A1
} board;

board* newBoard();

tile* BoardGetTileAt(board* _board, int _x, int _y);
void BoardRandomPopulate(board * _board);

bool BoardPlaceBoat(board* _board, int _x, int _y);
bool BoardPlaceSubmarine(board* _board, int _x, int _y);
bool BoardPlaceShip(board* _board, int _x, int _y, char _ori);
bool BoardPlaceDestroyer(board* _board, int _x, int _y, char _ori);
bool BoardPlaceCarrier(board* _board, int _x, int _y, char _ori);

#endif