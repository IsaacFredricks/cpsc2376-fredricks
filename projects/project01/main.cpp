#include <iostream>//no ai used
#include <array>//for game Board
#include <limits>//for edge testing
#include <string>//for getLine


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
int getInt(const std::string& prompt);
void printBoard(const std::array<std::array<char, 7>, 6>& board);//don't want to change the board with this one
std::array<std::array<char, 7>, 6>& makeBoard();
void makeMove(std::array<std::array<char, 7>, 6>& board, int col, char c);
//bool isOver(std::array<std::array<char, 7>, 6>& board);//not done
bool playAgain();


int main(){
    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules: 1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins.\n"
    << "Player one uses O's while Player 2 uses @'s. Player 1 starts first.\n";

    std::cout << "Player 1, enter your name: ";
    std::string player1{};
    std::getline(std::cin, player1);

    std::cout << "Player 2, enter your name: ";
    std::string player2{};
    std::getline(std::cin, player2);

    std::cin.ignore();//helps any wierdness going between

    auto gameBoard{ makeBoard() };

    printBoard(gameBoard);

    int turn{1};// tells what turn it is. Odd is player 1, even is player 2
    while (true) {
        if (turn % 2 == 0) {
                std::cout << player2 << " ";
                int col{ getInt("Enter the column you want to play") };
                makeMove(gameBoard, col, '@');
        }

        else {
            std::cout << player1 << " ";
            int col{ getInt("Enter the column you want to play") };
            makeMove(gameBoard, col, 'O');
        }


        //check to see who won
        //uncomment when done
        /*if (isOver(gameBoard)) {
            //print who won
            bool replay{ playAgain() };

            if (replay) {
                std::cout << "Starting a new game. Clearing the board\n";
                gameBoard = makeBoard();
            }

            else {
                std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }*/

        turn++;//increments turn
    }
    return 0;//creator: Isaac Fredricks
}

//functions down here
int getInt(const std::string& prompt) {//like getInt from practice01

    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input < 1 || input > 7) {
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
            //discards any extra input
            break;//exits loop
        }
    }

}

void printBoard(std::array<std::array<char, 7>, 6>& board) {
    std::cout << "-------------------\n";

    for (auto row : board) {
        for (auto c : row) {
            std::cout << ' ' << c << ' ';
        }
    
        std::cout << '\n';
    }
    std::cout << "-------------------\n";
}

std::array<std::array<char, 7>, 6>& makeBoard(){
    std::array<std::array< char, 7>, 6> board;

    return board;
}

void makeMove(std::array<std::array<char, 7>, 6>& board, int col, char c) {//not done

}

/*
bool isOver(std::array<std::array<char, 7>, 6>& board) {//not done


    if(player one got a 4 in a row){
        std::cout << "Player One Won";


    //checks who won or if its a draw
}
*/

bool playAgain() {
    while (true) {
        std::cout << "Want to play again? y or n: ";
        char c{};
        std::cin >> c;
        
        if (c == 'y' || c == 'Y') {
            std::cout << "Here we go again!\n";
            return true;
        }

        else if (c == 'n' || c == 'N') {
            return false;
        }

        else {
            std::cout << "Invalid input. Try again\n";
        }

    }
}