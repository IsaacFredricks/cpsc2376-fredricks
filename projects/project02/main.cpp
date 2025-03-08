#include <iostream>//no ai used
#include <vector>//for game Board
#include <limits>//for edge testing
#include <string>//for getLine
#include "connectFour.h"//works fine in vs if its just .h. Change to .cpp if using codebin or github codespaces
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
int getInt(const std::string& prompt);

int main() {

    ConnectFour currentGame {};//makes game object

    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
        << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
        << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
        << "*Pieces will go down to the lowest possible row\n"
        << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";

    currentGame.display();

    while (true) {
        std::cout << '\n';

         //index starts at 0 so has to be one less than player's input
        if (currentGame.getTurns() % 2 == 0) {
            std::cout << "Player 2, ";
        }

        else if (currentGame.getTurns() % 2 > 0) {
            std::cout << "Player 1, ";
        }

        int col{ getInt("Enter what column you want to play: ") - 1 };

        if (currentGame.canMakeMove(col)) {
            currentGame.play(col);
        }

        else {
            std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
        }
        
        currentGame.incrementTurn();//the first time running it should increment turns to 1

        currentGame.display();

        //check to see who won
        ConnectFour::Status stats = currentGame.status();

        if (stats == ConnectFour::PLAYER_1_WINS || stats == ConnectFour::PLAYER_2_WINS
            || stats == ConnectFour::DRAW) {
            //print who won
            std::cout << "Total number of turns: " << currentGame.getTurns() << '\n';

            if (stats == ConnectFour::PLAYER_1_WINS) {
                std::cout << "Player 1 wins!\n";
            }

            else if (stats == ConnectFour::PLAYER_2_WINS) {
                std::cout << "Player 2 wins!\n";
            }

            else if (stats == ConnectFour::DRAW) {
                std::cout << "Draw!\n";
            }

            bool replay{ playAgain() };

            if (replay) {
                std::cout << "Starting a new game. Clearing the board\n\n";
                currentGame = ConnectFour{};//resets game

                std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
                    << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
                    << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
                    << "*Pieces will go down to the lowest possible row\n"
                    << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";

                currentGame.display();

            }

            else {
                std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }


    }

    return 0;
}

int getInt(const std::string& prompt) {
    int num{};

    while (true) {
        std::cout << prompt;
        std::cin >> num;

        if (std::cin.fail() || std::cin.peek() != '\n' || num > 7 || num < 1) {//peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }

    return num;
}

bool playAgain() {//doesn't use instance variables so dont put in class
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

