#include <iostream>//no ai used
#include <vector>//for game Board
#include <limits>//for edge testing
#include <string>//for getLine


/*GOALS:
* make a text-based game
*I'm going to make connect 4
*7x6 two dimensional array
*Use C and O for pieces
*Function for Make grid with | and _
*Way to replay the game
*Functions to check input
*If at end no person wins, its a draw
*/

//namespace for checking the status of the game
namespace Statuses{//used learn c++ for enums chapter 13
    enum class Status{
        ONGOING,
        PLAYER_1_WINS,
        PLAYER_2_WINS,
        DRAW,
    };
}

namespace Pieces{
    enum class Piece{
        O,
        C,
    };

    char pieceToChar(Piece p){
        if(p == Pieces::Piece::O){
            return 'O';
        }

        return 'C';
    }
}

//forward declarations here
int getInt(const std::string& prompt);
void printBoard(const std::vector<std::vector<char>>& board);//don't want to change the board with this one so const
std::vector<std::vector<char>> makeBoard();
bool canMakeMove(std::vector<std::vector<char>>& board, int col, Pieces::Piece gamePiece);
void makeMove(std::vector<std::vector<char>>& board, int col, Pieces::Piece gamePiece);
Statuses::Status gameStatus(const std::vector<std::vector<char>>& board);
bool playAgain();
void play(std::vector<std::vector<char>>& board);

int main(){
    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins." 
    << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
    << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
    << "*Pieces will go down to the lowest possible row\n\n";

    auto board{ makeBoard() };

    printBoard(board);

    play(board);//where all of the game stuff happens

    return 0;
}

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

std::vector<std::vector<char>> makeBoard(){//self explanitory
    std::vector<std::vector<char>> board = 
        {{' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    return board;
}

bool canMakeMove(std::vector<std::vector<char>>& board, int col, Pieces::Piece gamePiece){
    if(board.at(0).at(col) == 'C' || board.at(0).at(col) == 'O'){
            std::cout << "All spots on this row are taken. please try again\n";
            return false;
    }

    else{
        return true;
    }
}

void makeMove(std::vector<std::vector<char>>& board, int col, Pieces::Piece gamePiece) {
    //make a for loop that starts at the end and then works itself backwards until it reaches a spot that isn't taken

    for(int i {static_cast<int>(board.size()) - 1}; i >= 0; i--){
        if(board.at(i).at(col) == ' '){
            board.at(i).at(col) = Pieces::pieceToChar(gamePiece);//changes row to current char
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

        //std::cout << "player 1 x: " << player1X << '\n';
        //std::cout << "player 2 x: " << player2X << '\n';

        for(int col {0}; col < board.at(i).size(); col++){
            
            if(player1X == 3){
                //std::cout << "won by x\n";
                return Statuses::Status::PLAYER_1_WINS;
            }

            if(player2X == 3){
                //std::cout << "won by x\n";
                return Statuses::Status::PLAYER_2_WINS;
            }

            if(col < 6){

                if(board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == 'O'){
                    player1X++;
                }

                else if(board.at(i).at(col) == 'C' && board.at(i).at(col + 1) == 'C'){
                    player2X++;
                }

                else if(player1X > 1 && board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == 'C'){
                    player1X = 0;
                }

                else if(player2X > 1 && board.at(i).at(col) == 'C' && board.at(i).at(col + 1) == 'O'){
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
                //std::cout << "won by y\n";
                return Statuses::Status::PLAYER_1_WINS;
            }

            if(player2Y == 3){
                //std::cout << "won by y\n";
                return Statuses::Status::PLAYER_2_WINS;
            }

            if(i < 5){
                
                if(board.at(i).at(col) == 'O' && board.at(i + 1).at(col) == 'O'){
                    player1Y++;
                }

                else if(board.at(i).at(col) == 'C' && board.at(i + 1).at(col) == 'C'){
                    player2Y++;
                }

                else if(player1Y > 1 && board.at(i).at(col) == 'O' && board.at(i + 1).at(col) == 'C'){
                    player1Y = 0;
                }

                else if(player2Y > 1 && board.at(i).at(col) == 'C' && board.at(i + 1).at(col) == 'O'){
                    player2Y = 0;
                }

            }
            //resets after each row
            player1Y = 0;
            player2Y = 0;
            
        }
    }
    
    //std::cout << "checking diagonal\n";

    for(int i {0}; i < board.size(); i++){

        for(int col {0}; col < board.at(i).size(); col++){

            if (i <= 2 && col <= 3) {

                if ((board.at(i).at(col) == 'O' && board.at(i + 1).at(col + 1) == 'O' && board.at(i + 2).at(col + 2) == 'O' && board.at(i + 3).at(col + 3) == 'O')) {
                    //std::cout << "won by z\n";
                    return Statuses::Status::PLAYER_1_WINS;
                }
                
                
                else if ((board.at(i).at(col) == 'C' && board.at(i + 1).at(col + 1) == 'C' && board.at(i + 2).at(col + 2) == 'C' && board.at(i + 3).at(col + 3) == 'C')) {
                    //std::cout << "won by z\n";
                    return Statuses::Status::PLAYER_2_WINS;
                }

            }

            if (i >= 2 && col <= 3) {
                if ((board.at(i).at(col) == 'O' && board.at(i - 1).at(col + 1) == 'O' && board.at(i - 2).at(col + 2) == 'O' && board.at(i - 3).at(col + 3) == 'O')) {
                    //std::cout << "won by z\n";
                    return Statuses::Status::PLAYER_1_WINS;
                }


                else if ((board.at(i).at(col) == 'C' && board.at(i - 1).at(col + 1) == 'C' && board.at(i - 2).at(col + 2) == 'C' && board.at(i - 3).at(col + 3) == 'C')) {
                    //std::cout << "won by z\n";
                    return Statuses::Status::PLAYER_2_WINS;
                }
            }
            
        }

    }

    //checks if draw. should be a draw if all of the spots are taken and no one has one yet
    if(board.at(0).at(0) != ' ' && board.at(0).at(1) != ' ' && board.at(0).at(2) != ' ' 
    && board.at(0).at(3) != ' ' && board.at(0).at(4) != ' ' && board.at(0).at(5) != ' ') {
        return Statuses::Status::DRAW;
    }

    return Statuses::Status::ONGOING;
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
    Pieces::Piece player1Piece = Pieces::Piece::O;
    Pieces::Piece player2Piece = Pieces::Piece::C;
    

     while (true) {
        int col {};

        std::cout << '\n';

        if (turns % 2 == 0) {
            std::cout << "Player 2, ";

            col = getInt("Enter the column you want to play: ") - 1;
        
            if(canMakeMove(board, col, player2Piece)){
                makeMove(board, col, player2Piece);
                turns++;//increments turn only if able to make a moove
            }

            else{
                std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
            }
        }

        else {
            std::cout << "Player 1, ";

            col = getInt("Enter the column you want to play: ") - 1;
        
            if(canMakeMove(board, col, player1Piece)){
                makeMove(board, col, player1Piece);
                turns++;//increments turn only if able to make a moove
            }

            else{
                std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
            }
        }


        std::cout << '\n';
        printBoard(board);

        //check to see who won

        if (gameStatus(board) == Statuses::Status::PLAYER_1_WINS || gameStatus(board) == Statuses::Status::PLAYER_2_WINS\
        || gameStatus(board) == Statuses::Status::DRAW){
            //print who won
            std::cout << "Total number of turns: " << turns << '\n';

            if(gameStatus(board) == Statuses::Status::PLAYER_1_WINS){
                std::cout << "Player 1 wins!\n";
            }

            else if(gameStatus(board) == Statuses::Status::PLAYER_2_WINS){
                std::cout << "Player 2 wins!\n";
            }

            else if(gameStatus(board) == Statuses::Status::DRAW){
                std::cout << "Draw!\n";
            }

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