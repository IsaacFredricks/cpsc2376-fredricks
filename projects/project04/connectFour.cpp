#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <iostream>
#include <vector>
#include <limits>
#include "connectFour.h"
#include "engine.h"


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

void ConnectFour::draw(Engine* engine, int col) {//replace using sdl
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

    int radius{ 40 };

    //for loop for row numbers. gave me blobs in other loop.
    engine->drawRectangle(350, 180, 700, 40, { 0, 0, 0, 120 });
    for (int i{ 1 }; i <= 7; i++) {
        int cx{ 50 + 100 * (i - 1) };
        engine->drawText(std::to_string(i), cx, 180, { 0, 240, 120, 255 });
    }

    //double for loop for board. put an X or o depending on the vector. find starting point and center x and center y
    for (int r{0}; r < board.size(); r++) {
        for (int c{ 0 }; c < board.at(0).size(); c++) {
            
            //print circles then increment the center x
            //use Engine.h:
            int cx{ 50 + 100 * c };
            
            int cy{ 250 + 100 * r };
            engine->drawRectangle(cx, cy, 95, 95, { 255, 255, 255, 255 });

            if (c == col) {
                engine->drawRectangle(cx, cy, 95, 95, { 0, 255, 0, 255 });
            }

            if (board.at(r).at(c) == 'O') {//make it red
                engine->drawRectangle(cx, cy, 95, 95, { 120, 240, 0, 255 });
                engine->drawCircle(cx + 5, cy + 5, radius, { 0, 0, 0, 100 });//drop shadow
                engine->drawCircle(cx, cy, radius, { 200, 20, 0, 255 });
            }

            else if (board.at(r).at(c) == 'C') {
                engine->drawRectangle(cx, cy, 95, 95, { 120, 240, 0, 255 });
                engine->drawCircle(cx + 5, cy + 5, radius, { 0, 0, 0, 100 });//drop shadow
                engine->drawCircle(cx, cy, radius, { 0, 10, 192, 255 });//make it blue
            }

        }
    }

    //engine->flip();//causes flickering
}

bool ConnectFour::canMakeMove(int col) {
    if ( status() != ConnectFour::ONGOING || board.at(0).at(col) == 'C' || board.at(0).at(col) == 'O') {
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