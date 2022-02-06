//#include <stdlib.h>
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
        if(_dir == 0) return tileCheckShip(_t->up, _dir);
        else if(_dir == 1) return tileCheckShip(_t->right, _dir);
        else if(_dir == 2) return tileCheckShip(_t->down, _dir);
        else if(_dir == 3) return tileCheckShip(_t->left, _dir);
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
            if(_dir == 0) return tileCheckShipHit(_t->up, _dir);
            else if(_dir == 1) return tileCheckShipHit(_t->right, _dir);
            else if(_dir == 2) return tileCheckShipHit(_t->down, _dir);
            else if(_dir == 3) return tileCheckShipHit(_t->left, _dir);
        } else return false;
    }
}

void sinkShipMessage(game* _g){
    //count salva quantos # a função encontrou.
    // >2 = porta avioes
    // >0 = destroyer
    //  0 = fragata
    if (_g->__count > 2){
        printf("Afundou um Porta Avioes.\n");
    } else if (_g->__count > 0){
        printf("Afundou um Destroyer.\n");
    } else {
        printf("Afundou uma Fragata.\n");
    }
    _g->__count = 0;
}
void tileSinkShip(game* _g, tile* _t, int _dir){
    // (0 = ^)      (1 = >)      (2 = v)      (3 = <)
    if(_t == NULL) return;
    
    if(!_t->sunk){
        
        //punir o jogador por atirar em uma jangada
        if (_t->data == '&'){
            _t->sunk = true;
            printf("Afundou uma jangada.\n");
            removeSubmarine(_g);
            _g->turn = !(_g->turn); //passar o turno.

            return; 
        }

        if (_t->data == '@'){
            _t->sunk = true;
            printf("Afundou um submarino.\n");
            return;
        } 
        
        if (_t->data == '#'){
            _t->sunk = true;
            _g->__count++; // 0 para fragata, >0 para destroyer, >2 para porta-avioes.
            if(_dir == 0) return tileSinkShip(_g,_t->up, _dir);
            else if(_dir == 1) tileSinkShip(_g,_t->right, _dir);
            else if(_dir == 2) tileSinkShip(_g,_t->down, _dir);
            else if(_dir == 3) tileSinkShip(_g,_t->left, _dir);
        }
        
        else if(_dir == 0 && _t->data == '^') {
            _t->sunk = true; 
            sinkShipMessage(_g);
            return;
        }
        else if(_dir == 2 && _t->data == 'v') {
            _t->sunk = true; 
            sinkShipMessage(_g);
            return;
        }
        else if(_dir == 1 && _t->data == '>') {
            _t->sunk = true; 
            sinkShipMessage(_g);
            return;
        }
        else if(_dir == 3 && _t->data == '<') { 
            _t->sunk = true; 
            sinkShipMessage(_g);
            return;
        }

    }
}

//função para -tentar- atirar numa posição do tabuleiro
bool shootTile(game* _g, board* _board, int _x, int _y){
    if (_x < 1 || _x > 12) return false;
    if (_y < 1 || _y > 12) return false;

    tile* _t = BoardGetTileAt(_board, _x, _y);

    //não atirar no tile se já atirou antes.
    if (_t->hit) return false;
    else{
        hitTile(_g, _t);
        return true;
    }
}
//função para quando se atira num quadrado do tabuleiro.
void hitTile(game* _g, tile* _t){
    _g->__count = 0; //definir qual barco grande foi atingido
    
    _t->hit = true;
    char _d = _t->data; 

    //agua
    if(_d == ' '){
        printf("Disparo errou.\n");
        _g->turn = !(_g->turn); //passar o turno.
    } 
    else printf("Disparo acertou algo!\n");

    //agua, jangadas e submarinos são simples
    if (_d == ' ') return;
    else if (_d == '@' || _d == '&'){
        tileSinkShip(_g,_t, 0);  return;
    }

    // (0 = ^)      (1 = >)      (2 = v)      (3 = <)
    else if (_d == 'v') {
        if (tileCheckShipHit(_t->up, 0) == true){
            //printf("BOOOM");
            _t->sunk = true;
            tileSinkShip(_g,_t->up, 0); 
            return ;
        }   
    }
    else if (_d == '<') {
        if (tileCheckShipHit(_t->right, 1)){
            //printf("BOOOoooM");
            _t->sunk = true;
            tileSinkShip(_g,_t->right, 1); 
            return;
        }
    }
    else if (_d == '^') {
        if (tileCheckShipHit(_t->down, 2)){
            //printf("BoooOOOM");
            _t->sunk = true;
            tileSinkShip(_g,_t->down, 2); 
            return;
        }
    }
    else if (_d == '>') {
        if (tileCheckShipHit(_t->left, 3)){
            //printf("BO0000OOM");
            _t->sunk = true;
            tileSinkShip(_g,_t->left, 3); 
            return;
        }
    }
    

    else if (_d == '#'){ //desambiguar a direção
        int _orientation = 0; //1 para horizontal, 2 para vertical.
        
        //teste horizontal
        if (tileCheckShip(_t, 1) && tileCheckShip(_t, 3)) _orientation = 1;
        //teste vertical
        if (tileCheckShip(_t, 0) && tileCheckShip(_t, 2)) _orientation = 2;
        //printf("orientação: %d", _orientation); //debug

        if (_orientation == 1){
            if (tileCheckShipHit(_t, 1) && tileCheckShipHit(_t, 3)){
                tileSinkShip(_g,_t, 3); tileSinkShip(_g,_t, 1); //nota, vai checar o meio duas vezes
            }
        } else if (_orientation == 2) {
            if (tileCheckShipHit(_t, 0) && tileCheckShipHit(_t, 2)){
                tileSinkShip(_g,_t, 0); tileSinkShip(_g,_t, 2); //nota, vai checar o meio duas vezes
            }
        }
        return;
    }
    

}

//funções pra escolher o que mostrar no display
char tilePrintDataPlayer(tile* _t){
    if (_t->data == ' '){ //água, atingida ou não
        if (_t->hit) { return 'O'; } else return ' ';
    } 

    else if (_t->sunk) {
        return '*';
    }


    else if (_t->hit) { //navios derrubados são atingidos tambem
        return '*';
    }
    else return _t->data;
}
char tilePrintDataAi(tile* _t){
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
    printf("-a\n");
    srand(time(NULL));
    printf("-b\n");
    for(int i = 0; i < 10; i++){
        printf("-c%d\n", i);
        
        tile* t = BoardGetTileAt(_board,1+(rand()%12),1+(rand()%12));
        t->data = '#';
        t = BoardGetTileAt(_board,1+(rand()%12),1+(rand()%12));
        t->data = 'v';

    }
}

//funções para colocar as embarcações
//retornam verdadeiro ou falso para interagir com o loop
//na interface do programa.

//submarino
bool BoardPlaceSubmarine(board* _board, int _x, int _y){
    if (_x < 1 || _x > 12) return false;
    if (_y < 1 || _y > 12) return false;

    tile* _t = BoardGetTileAt(_board, _x, _y);

    if (_t->data == ' '){
        _t->data = '@';
        return true;
    }
    else return false;
}
//jangada
bool BoardPlaceBoat(board* _board, int _x, int _y){
    if (_x < 1 || _x > 12) return false;
    if (_y < 1 || _y > 12) return false;

    tile* _t = BoardGetTileAt(_board, _x, _y);

    if (_t->data == ' '){
        _t->data = '&';
        return true;
    }
    else return false;
}
//fragata
bool BoardPlaceShip(board* _board, int _x, int _y, char _ori){
    //orientação, horizontal ou vertical.
    if (_ori != 'h' && _ori != 'v') return false;
    if (_ori == 'h' && _x > 11) return false; //não cabe
    if (_ori == 'v' && _y > 11) return false; //não cabe

    tile* _t = BoardGetTileAt(_board, _x, _y);
    
    if (_t->data != ' ') return false; //primeiro tile
    else{
        tile* _t2;
        if (_ori == 'h') _t2 = _t->right; 
        else if (_ori == 'v') _t2 = _t->down;

        if (_t2 == NULL) return false;
        if (_t2->data != ' ') return false; //segundo tile
        else{
            if (_ori == 'h') {
                _t->data = '<'; _t2->data = '>';
            }
            else if (_ori == 'v'){
                _t->data = '^'; _t2->data = 'v';
            }
            return true;
        }   
    }
}
//destroyer
bool BoardPlaceDestroyer(board* _board, int _x, int _y, char _ori){
    //orientação, horizontal ou vertical.
    if (_ori != 'h' && _ori != 'v') return false;
    if (_ori == 'h' && _x > 10) return false; //não cabe
    if (_ori == 'v' && _y > 10) return false; //não cabe

    tile* _t = BoardGetTileAt(_board, _x, _y);
    
    if (_t->data != ' ') return false; //primeiro tile
    else{
        tile* _t2;
        if (_ori == 'h') _t2 = _t->right; 
        else if (_ori == 'v') _t2 = _t->down;

        if (_t2 == NULL) return false;
        if (_t2->data != ' ') return false; //segundo tile
        else{
            tile* _t3;
            if (_ori == 'h') _t3 = _t2->right; 
            else if (_ori == 'v') _t3 = _t2->down;

            if (_t3 == NULL) return false;
            if (_t3->data != ' ') return false; //terceiro tile
            else{
                if (_ori == 'h') {
                    _t->data = '<';
                    _t2->data = '#';
                    _t3->data = '>';
                }
                else if (_ori == 'v'){
                    _t->data = '^';
                    _t2->data = '#';
                    _t3->data = 'v';
                }
                return true;
            }  
        }   
    }
}
//porta-avioes
bool BoardPlaceCarrier(board* _board, int _x, int _y, char _ori){
    if (_x < 1 || _y < 1) return false;
    //orientação, horizontal ou vertical.
    if (_ori != 'h' && _ori != 'v') return false;
    if (_ori == 'h' && _x > 8) return false; //não cabe
    if (_ori == 'v' && _y > 8) return false; //não cabe

    tile* _t = BoardGetTileAt(_board, _x, _y);
    if (_t->data != ' ') return false;
    else{
        tile* _t2; tile* _t3; tile* _t4; tile* _t5;
        if (_ori == 'h'){
            _t2 = _t->right; 
            _t3 = _t2->right;
            _t4 = _t3->right; 
            _t5 = _t4->right;
        } else if (_ori == 'v'){
            _t2 = _t->down; 
            _t3 = _t2->down;
            _t4 = _t3->down; 
            _t5 = _t4->down;
        }

        if (_t2->data == ' ' && _t3->data == ' ' 
            && _t4->data == ' ' && _t5->data == ' '){
        
            if (_ori == 'h'){
                _t->data = '<';                                                             
                _t5->data = '>';
            } else if (_ori == 'v'){
                _t->data = '^';
                _t5->data = 'v';
            }
            _t2->data = '#';
            _t3->data = '#';
            _t4->data = '#';
            
            return true;
        }
        else return false;
    }
}



void printBoards(board* _player, board* _ai){
    printf("      Humano         Computador  \n");
    printf("   ABCDEFGHIJKL     ABCDEFGHIJKL \n");
    printf("  +------------+   +------------+\n");
    
    //template da fileira: printf(" 1|            |  1|            |\n");
    //printar cada fileira
    for(int f = 1; f <= 12; f++){
        //separador
        if (f < 10) printf(" "); printf("%d|", f); //" 1|"

        //lado humano
        tile* current = BoardGetTileAt(_player, 1, f);
        for(int x = 1; x <= 12; x++){
            printf("%c", tilePrintDataPlayer(current));
            current = current->right;
        }
        
        //separador
        printf("| "); if (f < 10) printf(" "); printf("%d|", f); //"| 1|"

        //lado computador
        current = BoardGetTileAt(_ai, 1, f);
        for(int x = 1; x <= 12; x++){
            //printf("%c", tilePrintDataPlayer(current)); //debug: mostrar a ia
            printf("%c", tilePrintDataAi(current));
            current = current->right;
        }
        printf("|\n");
    }
    printf("  +------------+   +------------+\n");
}


//  GAME MANAGER
//salva os tabuleiros e turnos e outras variaveis 'globais'
game* newGame(){
    game* _g = malloc(sizeof(game));
    _g->turn = true;
    _g->playerboard = newBoard();
    _g->aiboard = newBoard();
    _g->__count = 0;
    return _g;
}

bool removeSubmarine(game* _g){
    board* b;
    if (_g->turn){
        b = _g->playerboard;
    } else {
        b = _g->aiboard;
    }

    tile* sub1 = NULL; tile* sub2 = NULL; //existem 2 submarinos
    //pegar os 2 submarinos
    tile* current;
    for(int x = 1; x <= 12; x++){
        for(int y = 1; y <= 12; y++){
            current = BoardGetTileAt(b, x, y);
            if (current->data == '@' && !current->sunk){
                if (sub1 == NULL) sub1 = current;
                else if (sub2 == NULL) sub2 = current;
            }
        }
    }
    //escolher um submarino para afundar.
    if (sub1 != NULL){
        while(1){
            int random = 1+ rand()%2;

            if (random == 0){
                if (sub1 == NULL) continue;
                else {
                    hitTile(_g, sub1);
                    break;
                }
            } else {
                if (sub2 == NULL) continue;
                else {
                    hitTile(_g, sub2);
                    break;
                }
            }
        }
    }
}

int testForDefeat(game* _g){ 
    //0 para continuar, 1 para humano ganhou, 2 para comp ganhou
    int naviosHumano = 0;
    int naviosComput = 0;

    tile* currentX; tile* currentY;
    //lado humano
    currentX = _g->playerboard->root;
    for(int x = 1; x <= 12; x++){
        currentY = currentX;
        for(int y = 1; y <= 12; y++){
            
            //embarcações, fora a jangada, valem pontos.
            if (currentY->data != ' ' && currentY->data != '&'){
                if(currentY->hit) naviosHumano++;
                //marca ponto se o navio foi acertado
            }
            currentY = currentY->down;
        }
        currentX = currentX->right;
    }
    //2x1 + 3x2 + 2x3 + 1x5 = 19 pontos quando se afunda todos os barcos.
    if (naviosHumano >= 19) return 1; //computador ganhou

    //lado computador
    currentX = _g->aiboard->root;
    for(int x = 1; x <= 12; x++){
        currentY = currentX;
        for(int y = 1; y <= 12; y++){
            if (currentY->data != ' ' && currentY->data != '&'){
                if(currentY->hit) naviosComput++;
            }
            currentY = currentY->down;
        }
        currentX = currentX->right;
    }
    if (naviosComput >= 19) return 2; //humano ganhou
    return 0;
}