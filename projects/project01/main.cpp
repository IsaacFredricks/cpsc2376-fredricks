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
void printBoard(const std::vector<std::vector<char>>& board);//don't want to change the board with this one
std::vector<std::vector<char>> makeBoard();
bool canMakeMove(std::vector<std::vector<char>>& board, int col, char c);
void makeMove(std::vector<std::vector<char>>& board, int col, char c);
bool isOver(const std::vector<std::vector<char>>& board, const std::string& player1, const std::string& player2);//not done
bool playAgain();


int main(){
    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins." 
    << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
    << "*Player one uses O's while Player 2 uses @'s.\n*Player 1 starts first.\n\n";

    std::cout << "Player 1, enter your name: ";
    std::string player1{};
    std::string player2{};
    std::getline(std::cin, player1);

    while(true){//checks to see if the names are the same
        std::cout << "\nPlayer 2, enter your name: ";
        std::getline(std::cin, player2);
        if(player1 == player2){
            std::cout << "Pick a different name.\n";
        }

        else{
            break;
        }
    }

    //std::cin.ignore();//helps any wierdness going between

    auto gameBoard{ makeBoard() };

    printBoard(gameBoard);

    int turn{1};// tells what turn it is. Odd is player 1, even is player 2
    char piece {};//game piece. changes based off of person

    while (true) {
        if (turn % 2 == 0) {
            std::cout << player2 << ", ";
            piece = '@';
        }

        else {
            std::cout << player1 << ", ";
            piece = 'O';
        }

        int col{ getInt("Enter the column you want to play: ") - 1 };
        
        if(canMakeMove(gameBoard, col, piece)){
            makeMove(gameBoard, col, piece);
            turn++;//increments turn only if able to make a moove
        }

        else{
            std::cout << "Unable to make move there. Try another spot\n";
        }

        printBoard(gameBoard);

        //check to see who won
        //uncomment when done
        if (isOver(gameBoard, player1, player2)) {
            //print who won
            bool replay{ playAgain() };

            if (replay) {
                std::cout << "Starting a new game. Clearing the board\n";
                gameBoard = makeBoard();
                turn = 1;
            }

            else {
                std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }

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

    for(int i {board.at(0).size() - 1}; i >= 0; i--){
        if(board.at(i).at(col) == ' '){
            board.at(i).at(col) = c;//changes row to current char
        }
    }
    
}


bool isOver(const std::vector<std::vector<char>>& board, const std::string& player1, const std::string& player2){//not done

    int player1X {};
    int player1Y {};
    int player1Z {};//z means diagonally here

    int player2X {};
    int player2Y {};
    int player2Z {};

    for(int i {0}; i < board.size(); i++){//checks if 4 in a row

        for(int col {0}; col < board.at(i).size(); col++){//i am going insane

            std::cout << "Checking 4 in a row horizontally...\n";

            if(col < 6 && board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == 'O'){//checks horizontally
                player1X++;
            }

            else if(col < 6 && board.at(i).at(col) == '@' && board.at(i).at(col + 1) == '@'){
                player2X++;
            }

            else if(col < 6 && player2X < 2 && board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == '@'){
                player1X++;
                player2X = 0;
            }

            else if(col < 6 && player1X < 2 && board.at(i).at(col) == '@' && board.at(i).at(col + 1) == 'O'){
                player2X++;
                player1X = 0;
            }

            else if(col < 6 && player2X < 2 && board.at(i).at(col) == '@' && board.at(i).at(col + 1) == ' '){
                player2X = 0;
            }

            else if(col < 6 && player1X < 2 && board.at(i).at(col) == 'O' && board.at(i).at(col + 1) == ' '){
                player1X = 0;
            }

            else{
                std::cout << "No 4 in a row in this row\n";
            }

            std::cout << "Checking 4 in a row vertically...\n";

            if(i < 7 && board.at(i).at(col) == 'O' && board.at(i  + 1).at(col) == 'O'){//checks vertically
                player1Y++;
            }

            else if(i < 7 && board.at(i).at(col) == '@' && board.at(i  + 1).at(col) == '@'){
                player2Y++;
            }

            else if(col < 6 && player2Y < 2 && board.at(i).at(col) == 'O' && board.at(i + 1).at(col) == '@'){
                player1Y++;
                player2Y = 0;
            }

            else if(col < 6 && player1Y < 2 && board.at(i).at(col) == '@' && board.at(i + 1).at(col) == 'O'){
                player2Y++;
                player1Y = 0;
            }

            else if(col < 6 && player2Y < 2 && board.at(i).at(col) == '@' && board.at(i + 1).at(col) == ' '){
                player2Y = 0;
            }

            else if(col < 6 && player1Y < 2 && board.at(i).at(col) == 'O' && board.at(i + 1).at(col) == ' '){
                player1Y = 0;
            }

            else{
                std::cout << "No 4 in a row in this column\n";
            }

            if(player1X == 2 || player1Y == 2 || player1Z == 2){
                std::cout << player1 << " won!\n";
                return true;
            }

            else if(player2X == 2 || player2Y || player2Z){
                std::cout << player2 << " won!\n";
                return true;
            }

        }

        
        //resets the x & y variables
        player1X = 0;
        player2X = 0;
        player1Y = 0;
        player2Y = 0;

    }

    std::cout << "Checking for 4 in a row diagonally\n";
    //need a normal for loop for this one and a revverse for loop to check diagonally
    for(int i {0}; i < board.size(); i++){

    }
    

    //checks if draw
    if(board.at(0).at(0) != ' ' && board.at(0).at(1) != ' ' && board.at(0).at(2) != ' ' 
    && board.at(0).at(3) != ' ' && board.at(0).at(4) != ' ' && board.at(0).at(5) != ' ') {
        std::cout << "It's a draw!\n";
        return true;
    }

    return false;
    //checks who won or if its a draw
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