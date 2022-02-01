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

bool tileCheckShip(tile* _t, int _dir){
    //função retorna verdadeiro se encontrou uma ponta de embarcação valida
    //por exemplo, achar uma ponta (v) indo para a direita indica que
    //provavelmente não é da mesma embarcação.
    //no entanto, achar uma ponta (v) indo para baixo só pode ser da
    //mesma embarcação.
    //serve para achar em qual direção a embarcação está
    
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
bool tileCheckShipHit(tile* _t, int _dir){
    //checar se a embarcação atual foi completamente afundada.
    //verdadeiro se todas as partes até uma ponta foram atingidas.
    //falso se qualquer parte no caminho não foi atingida

    //direção funciona igual a função anterior

    if(_t == NULL) return false;
    if(_t->sunk) return false; //não pertence ao mesmo barco

    if(!_t->hit){
        return false;
    } else {
        //se vindo de baixo para cima, e encontrou um final ^, retornar verdadeiro
        if(_dir == 0 && _t->data == '^') return true;
        //se vindo de cima para baixo, e encontrou um final v, retornar verdadeiro
        else if(_dir == 2 && _t->data == 'v') return true;
        //se vindo da esquerda para a direita, e encontrou um final >, retornar verdadeiro
        else if(_dir == 1 && _t->data == '>') return true;
        //se vindo da direita para a esquerda, e encontrou um final <, retornar verdadeiro
        else if(_dir == 3 && _t->data == '<') return true;
        
        else if (_t->data == '#'){
            if(_dir == 0) return tileCheckNeighbors(_t->up, _dir);
            else if(_dir == 1) return tileCheckNeighbors(_t->right, _dir);
            else if(_dir == 2) return tileCheckNeighbors(_t->down, _dir);
            else if(_dir == 3) return tileCheckNeighbors(_t->left, _dir);
        } else return false;
    }
}
void tileSinkShip(tile* _t, int _dir){
    // (0 = ^)      (1 = >)      (2 = v)      (3 = <)
    if(_t == NULL) return;
    if(!_t->sunk){
        if (_t->data == '&' || _t->data == '@'){
            _t->sunk = true;
            return;
        } 
        
        else if (_t->data == '#'){
            _t->sunk = true;
            if(_dir == 0) return tileSinkShip(_t->up, _dir);
            else if(_dir == 1) return tileSinkShip(_t->right, _dir);
            else if(_dir == 2) return tileSinkShip(_t->down, _dir);
            else if(_dir == 3) return tileSinkShip(_t->left, _dir);
        }
        
        else if(_dir == 0 && _t->data == '^') _t->sunk = true;
        else if(_dir == 2 && _t->data == 'v') _t->sunk = true;
        else if(_dir == 1 && _t->data == '>') _t->sunk = true;
        else if(_dir == 3 && _t->data == '<') _t->sunk = true;
    }
}

//função para quando se atira num quadrado do tabuleiro.
void hitTile(tile* _t){
    _t->hit = true;
    char _d = _t->data; 

    //agua, jangadas e submarinos são simples
    if (_d == ' ') return;
    else if (_d == '@' || _d == '&'){
        tileSinkShip(_t, 0);  return;
    }

    // (0 = ^)      (1 = >)      (2 = v)      (3 = <)
    else if (_d == 'v') {
        if (tileCheckShipHit(_t, 0) == true){
            tileSinkShip(_t->up, 0); 
            return ;
        }   
    }
    else if (_d == '<') {
        if (tileCheckShipHit(_t, 1)){
            tileSinkShip(_t->right, 1); 
            return;
        }
    }
    else if (_d == '^') {
        if (tileCheckShipHit(_t, 2)){
            tileSinkShip(_t->down, 2); 
            return;
        }
    }
    else if (_d == '>') {
        if (tileCheckShipHit(_t, 3)){
            tileSinkShip(_t->left, 3); 
            return;
        }
    }
    

    else if (_d == '#'){ //desambiguar a direção
        int _orientation = 0; //1 para horizontal, 2 para vertical.
        
        //teste horizontal
        if (tileCheckShip(_t, 1) && tileCheckShip(_t, 3)) _orientation = 1;
        //teste vertical
        if (tileCheckShip(_t, 0) && tileCheckShip(_t, 2)) _orientation = 2;

        if (_orientation == 1){
            if (tileCheckShipHit(_t, 1) && tileCheckShipHit(_t, 3)){
                tileSinkShip(_t->left, 3); tileSinkShip(_t->right, 1);
            }
        } else if (_orientation == 2) {
            if (tileCheckShipHit(_t, 0) && tileCheckShipHit(_t, 2)){
                tileSinkShip(_t->up, 0); tileSinkShip(_t->down, 2);
            }
        }
        return;
    }
    

}

//funções pra escolher o que mostrar no display
char* tilePrintDataPlayer(tile* _t){
    if (_t->data == ' '){ //água, atingida ou não
        if (_t->hit) { return 'O'; } else return ' ';
    } 
    else if (_t->hit) { //navios derrubados são atingidos tambem
        return '*';
    }
    else return _t->data;
}
char* tilePrintDataAi(tile* _t){
    if (_t->data == ' '){ //água, atingida ou não
        if (_t->hit) { return 'O'; } else return ' ';
    } 
    else if (_t->sunk) { //navios derrubados são revelados
        return _t->data;
    }
    else if (_t->hit){ //navios atingidos são marcados com '*'
        return '*';
    }
    else return ' '; //outros tiles são escondidos.
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

void BoardRandomPopulate(board * _board){
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        
        tile* t = BoardGetTileAt(_board,1+(rand()/12),1+(rand()/12));
        t->data = '#';
        tile* t = BoardGetTileAt(_board,1+(rand()/12),1+(rand()/12));
        t->data = 'v';

    }
}