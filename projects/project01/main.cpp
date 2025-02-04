#include <iostream>//no ai used
#include <array>//for game Board
#include <limits>//for edge testing


/*GOALS:
* make a text-based game
*I'm going to make connect 4
*7x6 two dimensional array
*Use chars @ and O
*Function for Make grid with | and _
*Way to replay the game
*Functions to check input
*If at end no person wins, it’s a draw
*/

//forward declarations here

void printBoard(std::array<std::array<char, 6>, 7>& board);
std::array<std::array<char, 6>, 7>& makeBoard();
bool isOver(std::array<std::array<char, 6>, 7>& board);


int main(){
    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules: 1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins.\n";

    auto gameBoard{ makeBoard() };

    printBoard(gameBoard);

    while (true) {

        //check to see who won
        if (isOver(gameBoard)) {
            //print who won


        }

        
    }
    return 0;//creator: Isaac Fredricks
}

//functions down here
void printBoard(std::array<std::array<char, 6>, 7>& board) {
    std::cout << "-------------------\n";

    for (auto row : board) {
        for (auto c : row) {
            std::cout << ' ' << c << ' ';
        }
    
        std::cout << '\n';
    }
    std::cout << "-------------------\n";
}

std::array<std::array<char, 6>, 7>& makeBoard(){
    std::array<std::array< char, 6>, 7> board;

    return board;
}

bool isOver(std::array<std::array<char, 6>, 7>& board) {
    //checks who won or if its a draw
}