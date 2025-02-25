#include "connectFour.h"
#include <vector>


/*functions to add :
* printBoard()
* makeBoard()
* play()
* canMakeMove()
* makeMove()
* getGameStatus()
* setCol
*/

ConnectFour::ConnectFour() {//constructor
    turns = 1;
}

void ConnectFour::setCol() {

}
//used learn c++ for enums chapter 13
static enum class Status {ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW};
//static b/c don't need multiple of the same status and pieces

static enum class Piece {O, C};

char ConnectFour::pieceToChar(Piece p) {
            if (p == Piece::O) {
                return 'O';
            }

            return 'C';
        }
}