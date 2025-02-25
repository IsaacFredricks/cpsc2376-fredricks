#include <iostream>//no ai used
#include <vector>//for game Board
#include <limits>//for edge testing
#include <string>//for getLine
#include "connectFour.h"

/*GOALS:
* make game class/object oriented
* make a text-based game
*I'm going to make connect 4
*7x6 two dimensional array
*Use C and O for pieces
*Function for Make grid with | and _
*Way to replay the game
*Functions to check input
*If at end no person wins, its a draw
*/



//forward declaration here
bool playAgain();

int main() {
    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
        << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
        << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
        << "*Pieces will go down to the lowest possible row\n"
        << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";

    auto board{ makeBoard() };

    printBoard(board);

    int turns{ 1 };// tells what turn it is. Odd is player 1, even is player 2


    while (true) {

        play(board, turns);
        turns++;

        std::cout << '\n';
        printBoard(board);

        //check to see who won
        Status stats = ConnectFour::gameStatus(board);

        if (stats == Status::PLAYER_1_WINS || stats == Status::PLAYER_2_WINS
            || stats == Status::DRAW) {
            //print who won
            std::cout << "Total number of turns: " << turns << '\n';

            if (stats == Status::PLAYER_1_WINS) {
                std::cout << "Player 1 wins!\n";
            }

            else if (stats == Statuses::Status::PLAYER_2_WINS) {
                std::cout << "Player 2 wins!\n";
            }

            else if (stats == Statuses::Status::DRAW) {
                std::cout << "Draw!\n";
            }

            bool replay{ playAgain() };

            if (replay) {
                std::cout << "Starting a new game. Clearing the board\n\n";
                board = makeBoard();

                std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
                    << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
                    << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
                    << "*Pieces will go down to the lowest possible row\n"
                    << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";

                printBoard(board);

                turns = 1;
            }

            else {
                std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }


    }

    return 0;
}




bool playAgain() {
    while (true) {
        std::cout << "Want to play again? y or n: ";
        std::string letter{};
        getline(std::cin, letter);

        if (letter == "y" || letter == "Y") {
            std::cout << "Here we go again!\n";
            return true;
        }

        else if (letter == "n" || letter == "N") {
            return false;
        }

        else if (letter.size() > 1) {
            std::cout << "Too long of an input. Don't input anything more than Y or N\n";
        }

        else if (letter.size() == 0) {
            std::cout << "You inputed nothing! Try again\n";
        }

        else {
            std::cout << "Invalid input. Try again\n";
        }

    }
}

