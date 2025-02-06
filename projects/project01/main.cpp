#include <iostream>//no ai used
#include <vector>//for game Board
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
*If at end no person wins, its a draw
*/

//forward declarations here
int getInt(const std::string& prompt);
Statuses::Status printBoard(const std::vector<std::vector<char>>& board);//don't want to change the board with this one
std::vector<std::vector<char>> makeBoard();
bool canMakeMove(std::vector<std::vector<char>>& board, int col, char c);
void makeMove(std::vector<std::vector<char>>& board, int col, char c);
bool gameStatus(const std::vector<std::vector<char>>& board);
bool playAgain();
void play(std::vector<std::vector<char>>& board);

//namespace for checking the status of the game
namespace Statuses{
    enum class Status{
        ONGOING,
        PLAYER_1_WINS,
        PLAYER_2_WINS,
        DRAW,
    };
}

int main(){
    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins." 
    << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
    << "*Player one uses O's while Player 2 uses @'s.\n*Player 1 starts first.\n"
    << "Pieces will go down to the lowest possible row\n\n";


    //std::cin.ignore();

    auto board{ makeBoard() };

    printBoard(board);

    play(board);

    return 0;
}

void printBoard(const std::vector<std::vector<char>>& board) {
    
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

std::vector<std::vector<char>> makeBoard(){
    std::vector<std::vector<char>> board = 
        {{' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    return board;
}

bool canMakeMove(std::vector<std::vector<char>>& board, int col, char c){
    if(board.at(0).at(col) == '@' || board.at(0).at(col) == 'O'){
            std::cout << "All spots on this row are taken. please try again\n";
            return false;
    }

    else{
        return true;
    }
}

void makeMove(std::vector<std::vector<char>>& board, int col, char c) {
    //make a for loop that starts at the end and then works itself backwards until it reaches a spot that isn't taken

    for(int i {static_cast<int>(board.size()) - 1}; i >= 0; i--){
        if(board.at(i).at(col) == ' '){
            board.at(i).at(col) = c;//changes row to current char
            break;
        }
    }
    
}

Statuses::Status gameStatus(const std::vector<std::vector<char>>& board){

    int player1X {};
    int player1Y {};
    int player2X {};
    int player2Y {};
    //the for loops check each spot and the one right next to it to see if there is a 4 in a row

    //std::cout << "checking horizontally\n";
    
    for(int i {0}; i < board.size(); i++){//checks if 4 in a row

        //std::cout << "player 1 x: " << player1X << '\n';//comment out later
       // std::cout << "player 2 x: " << player2X << '\n';

        for(int col {0}; col < board.at(i).size(); col++){//checks horizontally
            
            if(player1X == 3){
                std::cout << "Player 1 won!\n";
                return true;
            }

            if(player2X == 3){
                std::cout << "Player 2 won!\n";
                return true;
            }

            if(col < 6){

                if(board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == 'O'){
                    player1X++;
                }

                else if(board.at(i).at(col) == '@' && board.at(i).at(col + 1) == '@'){
                    player2X++;
                }

                else if(player1X > 1 && board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == '@'){
                    player1X = 0;
                }

                else if(player2X > 1 && board.at(i).at(col) == '@' && board.at(i).at(col + 1) == 'O'){
                    player2X = 0;
                }
              
            }
            
        }
    }

    //std::cout << "checking vertically\n";

    for(int i {0}; i < board.size(); i++){//checks if 4 in a row

        //std::cout << "player 1 y: " << player1Y << '\n';
        //std::cout << "player 2 y: " << player2Y << '\n';

        for(int col {0}; col < board.at(i).size(); col++){//checks vertically

            if(player1Y == 3){
                std::cout << "Player 1 won!\n";
                return true;
            }

            if(player2Y == 3){
                std::cout << "Player 2 won!\n";
                return true;
            }

            if(i < 5){
                
                if(board.at(i).at(col) == 'O' && board.at(i + 1).at(col) == 'O'){
                    player1Y++;
                }

                else if(board.at(i).at(col) == '@' && board.at(i + 1).at(col) == '@'){
                    player2Y++;
                }

                else if(player1Y > 1 && board.at(i).at(col) == 'O' && board.at(i + 1).at(col) == '@'){
                    player1Y = 0;
                }

                else if(player2Y > 1 && board.at(i).at(col) == '@' && board.at(i + 1).at(col) == 'O'){
                    player2Y = 0;
                }

            }
            
        }
    }
    
    //std::cout << "checking diagonal\n";

    for(int i {0}; i < board.size(); i++){

        for(int col {0}; col < board.at(i).size(); col++){

            if (i <= 2 && col <= 3) {

                if ((board.at(i).at(col) == 'O' && board.at(i + 1).at(col + 1) == 'O' && board.at(i + 2).at(col + 2) == 'O' && board.at(i + 3).at(col + 3) == 'O')) {
                    std::cout << "Player 1 won!\n";
                    return true;
                }
                
                
                else if ((board.at(i).at(col) == '@' && board.at(i + 1).at(col + 1) == '@' && board.at(i + 2).at(col + 2) == '@' && board.at(i + 3).at(col + 3) == '@')) {
                    std::cout << "Player 2 won!\n";
                    return true;
                }

            }

            if (i >= 2 && col <= 3) {
                if ((board.at(i).at(col) == 'O' && board.at(i - 1).at(col + 1) == 'O' && board.at(i - 2).at(col + 2) == 'O' && board.at(i - 3).at(col + 3) == 'O')) {
                    std::cout << "Player 1 won!\n";
                    return true;
                }


                else if ((board.at(i).at(col) == '@' && board.at(i - 1).at(col + 1) == '@' && board.at(i - 2).at(col + 2) == '@' && board.at(i - 3).at(col + 3) == '@')) {
                    std::cout << "Player 2 won!\n";
                    return true;
                }
            }
            
        }

    }

    //checks if draw
    if(board.at(0).at(0) != ' ' && board.at(0).at(1) != ' ' && board.at(0).at(2) != ' ' 
    && board.at(0).at(3) != ' ' && board.at(0).at(4) != ' ' && board.at(0).at(5) != ' ') {
        std::cout << "It's a draw!\n";
        return true;
    }

    return false;
}


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

void play(std::vector<std::vector<char>>& board){

    int turns{1};// tells what turn it is. Odd is player 1, even is player 2
    char piece{};
     while (true) {
        std::cout << '\n';

        if (turns % 2 == 0) {
            std::cout << "Player 2, ";
            piece = '@';
        }

        else {
            std::cout << "Player 1, ";
            piece = 'O';
        }

        int col{ getInt("Enter the column you want to play: ") - 1 };
        
        if(canMakeMove(board, col, piece)){
            makeMove(board, col, piece);
            turns++;//increments turn only if able to make a moove
        }

        else{
            std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
        }


        std::cout << '\n';
        printBoard(board);

        //check to see who won

        if (gameStatus(board)){
            //print who won
            std::cout << "Total number of turns: " << turns << '\n';
            bool replay{ playAgain() };

            if (replay) {
                std::cout << "Starting a new game. Clearing the board\n";
                board = makeBoard();

                printBoard(board);

                turns = 1;
            }

            else {
                std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }

    }
    //creator: Isaac Fredricks
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
