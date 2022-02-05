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

//  BOARD
//board é o tabuleiro, conjunto de tiles
typedef struct _Board {
    struct _Tile* root; //quadrado A1
} board;
board* newBoard(); //constructor


//  GAME MANAGER
//salva os tabuleiros e turnos e outras variaveis 'globais'
typedef struct _GameManager{
    bool turn; //true = jogador, false = cpu
    board* playerboard;
    board* aiboard;
    
    int __count; //conta quantos '#' foram encontrados ao derrubar um navio; para os printfs.

} game;
game* newGame(); //constructor



bool tileCheckShip(tile* _t, int _dir);
bool tileCheckShipHit(tile* _t, int _dir);
void tileSinkShip(game* _g, tile* _t, int _dir);

void hitTile(game* _g, tile* _t);

char tilePrintDataPlayer(tile* _t);
char tilePrintDataAi(tile* _t);





tile* BoardGetTileAt(board* _board, int _x, int _y);
void BoardRandomPopulate(board * _board);

bool BoardPlaceBoat(board* _board, int _x, int _y);
bool BoardPlaceSubmarine(board* _board, int _x, int _y);
bool BoardPlaceShip(board* _board, int _x, int _y, char _ori);
bool BoardPlaceDestroyer(board* _board, int _x, int _y, char _ori);
bool BoardPlaceCarrier(board* _board, int _x, int _y, char _ori);

bool shootTile(game* _g, board* _board, int _x, int _y);
void printBoards(board* _player, board* _ai);

int testForDefeat(game* _g);
bool removeSubmarine(game* _g);
#endif