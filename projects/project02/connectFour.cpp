#include <iostream>
#include <vector>
#include <limits>
#include "connectFour.h"


/*functions to add :
* printBoard()
* makeBoard()
* play()
* canMakeMove()
* makeMove()
* getGameStatus()
* setCol
*/
char ConnectFour::pieceToChar(){
    if(gamePiece == O){
        return 'O';
    }

    return 'C';
}

void ConnectFour::setCol() {
    int num{};

    while (true) {
        std::cout << "Enter what column you want to play: ";
        std::cin >> num;

        if (std::cin.fail() || num < 1 || num > 7 || std::cin.peek() != '\n') {//peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            col = num - 1;
            //discards any extra input
            break;//exits loop
        }
    }
}


void ConnectFour::setPiece(Piece gamePiece) {
    this->gamePiece = gamePiece;
}

void ConnectFour::makeBoard() {
    board =
    { {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '} };
}

void ConnectFour::setTurns(int turns) {
    this->turns = turns;
}

int ConnectFour::getTurns() {
    return turns;
}

void ConnectFour::incrementTurn() {
    turns++;
}

void ConnectFour::printBoard() {
    std::cout << " 1  2  3  4  5  6  7\n";
    std::cout << "----------------------\n";

    for (auto row : board) {
        for (auto c : row) {
            std::cout << "| " << c;
        }

        std::cout << '|';
        std::cout << '\n';
    }
    std::cout << "----------------------\n";
}

bool ConnectFour::canMakeMove() {
    if (board.at(0).at(col) == 'C' || board.at(0).at(col) == 'O') {
        std::cout << "All spots on this row are taken. please try again\n";
        return false;
    }

    else {
        return true;
    }
}

void ConnectFour::makeMove() {
    //make a for loop that starts at the end and then works itself backwards until it reaches a spot that isn't taken

    for (int i{ static_cast<int>(board.size()) - 1 }; i >= 0; i--) {
        if (board.at(i).at(col) == ' ') {
            board.at(i).at(col) = pieceToChar();//changes row to current char
            break;
        }
    }

}

ConnectFour::Status ConnectFour::gameStatus() {

    //the for loops check each spot and the one right next to it to see if there is a 4 in a row

    //std::cout << "checking horizontally\n";

    for (int i{ 0 }; i < board.size(); i++) {//checks if 4 in a row

        for (int col{ 0 }; col < board.at(i).size(); col++) {

            if (col <= 3) {
                if ((board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == 'O' && board.at(i).at(col + 2) == 'O' && board.at(i).at(col + 3) == 'O')) {
                    //std::cout << "won by z\n";
                    return PLAYER_1_WINS;
                }


                else if ((board.at(i).at(col) == 'C' && board.at(i).at(col + 1) == 'C' && board.at(i).at(col + 2) == 'C' && board.at(i).at(col + 3) == 'C')) {
                    //std::cout << "won by z\n";
                    return PLAYER_2_WINS;
                }

            }

        }
    }

    //std::cout << "checking vertically\n";

    for (int i{ 0 }; i < board.size(); i++) {//checks if 4 in a row

        for (int col{ 0 }; col < board.at(i).size(); col++) {//checks vertically
            if (i <= 2) {
                if ((board.at(i).at(col) == 'O' && board.at(i + 1).at(col) == 'O' && board.at(i + 2).at(col) == 'O' && board.at(i + 3).at(col) == 'O')) {
                    //std::cout << "won by z\n";
                    return PLAYER_1_WINS;
                }


                else if ((board.at(i).at(col) == 'C' && board.at(i + 1).at(col) == 'C' && board.at(i + 2).at(col) == 'C' && board.at(i + 3).at(col) == 'C')) {
                    //std::cout << "won by z\n";
                    return PLAYER_2_WINS;
                }
            }

        }
    }

    //std::cout << "checking diagonal\n";

    for (int i{ 0 }; i < board.size(); i++) {

        for (int col{ 0 }; col < board.at(i).size(); col++) {

            if (i <= 2 && col <= 3) {

                if ((board.at(i).at(col) == 'O' && board.at(i + 1).at(col + 1) == 'O' && board.at(i + 2).at(col + 2) == 'O' && board.at(i + 3).at(col + 3) == 'O')) {
                    //std::cout << "won by z\n";
                    return PLAYER_1_WINS;
                }


                else if ((board.at(i).at(col) == 'C' && board.at(i + 1).at(col + 1) == 'C' && board.at(i + 2).at(col + 2) == 'C' && board.at(i + 3).at(col + 3) == 'C')) {
                    //std::cout << "won by z\n";
                    return PLAYER_2_WINS;
                }

            }

            if (i >= 2 && col <= 3) {
                if ((board.at(i).at(col) == 'O' && board.at(i - 1).at(col + 1) == 'O' && board.at(i - 2).at(col + 2) == 'O' && board.at(i - 3).at(col + 3) == 'O')) {
                    //std::cout << "won by z\n";
                    return PLAYER_1_WINS;
                }


                else if ((board.at(i).at(col) == 'C' && board.at(i - 1).at(col + 1) == 'C' && board.at(i - 2).at(col + 2) == 'C' && board.at(i - 3).at(col + 3) == 'C')) {
                    //std::cout << "won by z\n";
                    return PLAYER_2_WINS;
                }
            }

        }

    }

    //checks if draw. should be a draw if all of the spots are taken and no one has one yet
    if (board.at(0).at(0) != ' ' && board.at(0).at(1) != ' ' && board.at(0).at(2) != ' '
        && board.at(0).at(3) != ' ' && board.at(0).at(4) != ' ' && board.at(0).at(5) != ' ') {
        return DRAW;
    }

    return ONGOING;
}

void ConnectFour::play() {
    while (true) {

        std::cout << '\n';

        if (turns % 2 == 0) {
            setPiece(C);
            std::cout << "Player 2, ";

            setCol();

            if (canMakeMove()) {
                makeMove();
                break;
            }

            else {
                std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
            }
        }

        else {
            setPiece(O);
            std::cout << "Player 1, ";

            setCol();

            if (canMakeMove()) {
                makeMove();
                break;
            }

            else {
                std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
            }
        }
    }

    //creator: Isaac Fredricks
}