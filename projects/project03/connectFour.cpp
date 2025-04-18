#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <vector>
#include <limits>
#include "connectFour.h"


char ConnectFour::pieceToChar() const{
    if (gamePiece == O) {
        return 'O';
    }

    return 'C';
}

void ConnectFour::setPiece(Piece gamePiece) {
    this->gamePiece = gamePiece;
}

ConnectFour::ConnectFour() {
    board =
    { {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '} };

    turns = 1;//player one starts first

    gamePiece = O;
}

int ConnectFour::getTurns() const {
    return turns;
}

void ConnectFour::display(SDL_Renderer* renderer) const {//replace using sdl
    /*std::cout << " 1  2  3  4  5  6  7\n";
    std::cout << "----------------------\n";

    for (auto row : board) {
        for (auto c : row) {
            std::cout << "| " << c;//find a way to display the pieces
        }

        std::cout << '|';
        std::cout << '\n';
    }
    std::cout << "----------------------\n";*/

    //vertical lines
    int minX{ 100 };
    for (int i{ 0 }; i < 6; i++) {
        SDL_RenderDrawLine(renderer, minX, 225, minX, 800);
        minX += 100;
    }
    

    //horizontal lines
    int minY{ 300 };
    for (int i{ 0 }; i < 6; i++) {
        SDL_RenderDrawLine(renderer, 0, minY, 700, minY);
        minY += 100;
    }
    

    //double for loop. put an X or o depending on the vector. find starting point and center x and center y
    /*for (int row{0}; row < board.size(); row++) {
        for (int col{ 0 }; col < board.at(0).size(); col++) {
        //print circles then increment the starting x
        //use Engine.h:
        if(turns % 2 > 0){//make it red
            //engine.drawCircle();
        }

        if(turns & 2 == 0){
            //engine.drawCircle();//make it blue
        }
        
        }

        increment the starting y here
    }*/



    
}

bool ConnectFour::canMakeMove(int col) {
    if (board.at(0).at(col) == 'C' || board.at(0).at(col) == 'O') {
        //std::cout << "All spots on this row are taken. please try again\n";
        return false;
    }

    else {
        return true;
    }
}

void ConnectFour::makeMove(int col) {
    //make a for loop that starts at the end and then works itself backwards until it reaches a spot that isn't taken

    for (int i{ static_cast<int>(board.size()) - 1 }; i >= 0; i--) {
        if (board.at(i).at(col) == ' ') {
            board.at(i).at(col) = pieceToChar();//changes row to current char
            break;
        }
    }

}

ConnectFour::Status ConnectFour::status() {

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

void ConnectFour::play(int col) {
    while (true) {


        if (turns % 2 == 0) {
            setPiece(C);
            if (canMakeMove(col)) {
                makeMove(col);
                turns++;
                break;
            }

            /*else {
                //std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
            }*/
        }

        else {
            setPiece(O);
            if (canMakeMove(col)) {
                makeMove(col);
                turns++;
                break;
            }

            /*else {
                std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
            }*/
        }
    }

    //creator: Isaac Fredricks
}