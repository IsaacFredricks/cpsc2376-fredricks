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

    ConnectFour currentGame;//makes game object
    currentGame.makeBoard();//creats a new game board

    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
        << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
        << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
        << "*Pieces will go down to the lowest possible row\n"
        << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";


    currentGame.printBoard();

    


    while (true) {

        currentGame.play();
        currentGame.incrementTurn();//the first time running it should increment turns to 1

        std::cout << '\n';
        currentGame.printBoard();

        //check to see who won
        Status stats = currentGame.gameStatus();

        if (stats == PLAYER_1_WINS || stats == PLAYER_2_WINS
            || stats == DRAW) {
            //print who won
            std::cout << "Total number of turns: " << currentGame.getTurns() << '\n';

            if (stats == PLAYER_1_WINS) {
                std::cout << "Player 1 wins!\n";
            }

            else if (stats == PLAYER_2_WINS) {
                std::cout << "Player 2 wins!\n";
            }

            else if (stats == DRAW) {
                std::cout << "Draw!\n";
            }

            bool replay{ playAgain() };

            if (replay) {
                std::cout << "Starting a new game. Clearing the board\n\n";
                currentGame.makeBoard();

                std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
                    << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
                    << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
                    << "*Pieces will go down to the lowest possible row\n"
                    << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";

                currentGame.printBoard();

                currentGame.setTurns(1);
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

