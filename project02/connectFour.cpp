#include "connectFour.h"
#include <vector>

class ConnectFour {

private://private by default but good to put it out
	std::vector<std::vector<char>> board{};
	int turns{};
	int col{};

public:
	/*functions to add :
	* printBoard()
	* makeBoard()
	* play()
	* canMakeMove()
	* makeMove()
	* getGameStatus()
	* setCol
	*/

	ConnectFour() {//constructor
		turns = 1;
	}

	void setCol

    //used learn c++ for enums chapter 13
        static enum class Status {ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW};
		//static b/c don't need multiple of the same status and pieces

        static enum class Piece {O, C};

        char pieceToChar(Piece p) {
            if (p == Piece::O) {
                return 'O';
            }

            return 'C';
        }
};