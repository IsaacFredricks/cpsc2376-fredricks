#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <SDL2/SDL2_gfxPrimitives.h>//for circles
#include <iostream>//some ai used. I used the ai summary feature for google search for making clickable buttons and drawing lines using sdl and some chatgpt for black screen error in sdl
#include <vector>//for game Board
#include <limits>//for edge testing
#include <string>//for getLine
#include "connectFour.h"//works fine in vs if its just .h. Change to .cpp if using codebin or github codespaces
#include "engine.h"

/*GOALS:
*[x] make game class/object oriented
*[x] make a text-based game
*[x] make connect 4
*[x] 7x6 two dimensional array
*[X] Use circles for pieces using sdl
*[x] Way to replay the game
*[x] Functions to check input
*[x] If at end no person wins, its a draw
*[ ] startup screen maybe
*[ ] replace all text using sdl
*[x] display game pieces and board in display function
*[x] implement the game logic with the sdl
*/

//forward declaration here
bool playAgain();

int main(int argc, char* argv[]) {//copied from chipmunkSDLExample

    bool running{ true };
    bool mouseClicked{ false };
    SDL_Event event;
    Engine engine{"Connect four - press escape to exit"};
    ConnectFour currentGame{};//makes game object
    int col{};
    int row{};
     
    while (running) {
        engine.clear();

        //text doesn't show up
        engine.drawText("======== Connect 4 =======", 400, 25);
        
        // Handle events
        while (SDL_PollEvent(&event)) {//pass in with info. in out parameter
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && !mouseClicked) {
                //check which item is clicked
                col = event.button.x / 100;//so no accidental moves


                if (col >= 0 && currentGame.canMakeMove(col)) {
                    currentGame.play(col);
                    //std::cout << "column clicked on and turn is " << currentGame.getTurns() << '\n';
                }

                else {
                    //std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";//find a way to print this to the sdl text thingy
                }

                mouseClicked = true;
            }

            else if (event.type == SDL_MOUSEMOTION && !mouseClicked) {
                //check which item is clicked
                col = event.motion.x / 100;//so no accidental moves
            }

            if (event.type == SDL_MOUSEBUTTONUP) {//undoes bool so no infinite moves
                mouseClicked = false;
            }
        }

        //index starts at 0 so has to be one less than player's input
        if (currentGame.getTurns() % 2 == 0) {//doesn't currently work
            //std::cout << "Player 2, click on the grey button to choose the column: ";
        }

        else if (currentGame.getTurns() % 2 > 0) {
            //std::cout << "Player 1, click on the grey button to choose the column: ";
        }

        //makes gameboard
        currentGame.draw(&engine, col);

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
                //std::cout << "Starting a new game. Clearing the board\n\n";
                currentGame = ConnectFour{};//resets game

                engine.clear();
                currentGame.draw(&engine);
            }

            else {
                //std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }

        //presents hidden frame
        engine.flip();

    }
    return 0;
}

bool playAgain() {//doesn't use instance variables so dont put in class
    while (true) {
        std::cout << "Want to play again? y or n: ";
        std::string letter{};//make a button instead
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


/*chat gpt prompts:

*I am making a program using c++ and sdl for a connect four game. Currently I have the actual game board to print but as soon as I implement my game logic my screen goes black. can you explain why this is and how to fix this in bullet points? heres the code for main (the connect four class and header file I know already works): *from previous git pull*
*
*responce: I lost it when I accidently closed out of the tab without signing in but they told me to get rid of duplicate if statements and have render frames at the end of the program
*
* i made a program for connect four. however, when I try to click on one of the column buttons, my game says that I am unable to place a piece here. I already know my connectFour.cpp and connectFour.h files work properly and it does not matter if I restart the program. Can you please explain why it is not working in bullet points? here is the code: *from previos git pull*
*
*responce: Thanks for sharing the code — and nice job building out your Connect Four game with SDL! Since you said your connectFour.cpp and .h files are solid, and your main issue is that clicking on a column results in “UNABLE TO PLACE PIECE THERE!”, here’s a breakdown of why that’s likely happening, based on the code you shared:

🔍 Suspected Problem: isClicked State Is Not Set in Time
You're checking columnX.isClicked inside the SDL_MOUSEBUTTONDOWN block.

But you only call columnX.handleEvent(event) after that, meaning the isClicked flag hasn’t been updated yet when you check it.

✅ What's Happening Step by Step:
User clicks mouse – SDL_MOUSEBUTTONDOWN is triggered.

You check if any ClickableItem is clicked via columnX.isClicked.

But isClicked is still false, because you haven't yet called columnX.handleEvent(event).

So col remains -1, and the code hits the else block:

cpp
Copy
Edit
else {
    std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
}
✅ Solution: Reorder the Event Handling
You need to call each column’s handleEvent() before checking if one was clicked.

🔧 Fix:
Move these lines above the if (event.type == SDL_MOUSEBUTTONDOWN && !mouseClicked) block:

cpp
Copy
Edit
column1.handleEvent(event);
column2.handleEvent(event);
column3.handleEvent(event);
column4.handleEvent(event);
column5.handleEvent(event);
column6.handleEvent(event);
column7.handleEvent(event);
So the while (SDL_PollEvent(&event)) block should look like:

cpp
Copy
Edit
while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) running = false;
    if (event.key.keysym.sym == SDLK_ESCAPE) running = false;

    // ✅ Move this up before you check for clicks
    column1.handleEvent(event);
    column2.handleEvent(event);
    column3.handleEvent(event);
    column4.handleEvent(event);
    column5.handleEvent(event);
    column6.handleEvent(event);
    column7.handleEvent(event);

    if (event.type == SDL_MOUSEBUTTONDOWN && !mouseClicked) {
        if (column1.isClicked) col = 0;
        else if (column2.isClicked) col = 1;
        else if (column3.isClicked) col = 2;
        else if (column4.isClicked) col = 3;
        else if (column5.isClicked) col = 4;
        else if (column6.isClicked) col = 5;
        else if (column7.isClicked) col = 6;

        if (col >= 0 && currentGame.canMakeMove(col)) {
            currentGame.play(col);
            std::cout << "column clicked on and turn is " << currentGame.getTurns() << '\n';
        } else {
            std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
        }

        mouseClicked = true; // ✅ Add this so it's not constantly triggered
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        mouseClicked = false;
    }
}

*prompt: how do I easily make multi line text using sdl with my drawText() function and can you explain it in bullet points?
* responce:Update your drawText() function to split the string on \n and render each line one at a time.

🔧 Replace your drawText() with this:
cpp
Copy
Edit
void Engine::drawText(const std::string& text, int x, int y, SDL_Color color) {
    int lineHeight = TTF_FontLineSkip(font); // Space between lines
    int yOffset = 0;

    std::istringstream stream(text);
    std::string line;

    while (std::getline(stream, line)) {
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, line.c_str(), color);
        if (!textSurface) {
            std::cerr << "unable to render text surface! ttf error: " << TTF_GetError() << '\n';
            continue;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            std::cerr << "unable to render text texture from rendered text! sdl error: " << SDL_GetError() << '\n';
            SDL_FreeSurface(textSurface);
            continue;
        }

        SDL_Rect destRect;
        destRect.w = textSurface->w;
        destRect.h = textSurface->h;
        destRect.x = x;
        destRect.y = y + yOffset;

        SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);

        yOffset += lineHeight;
    }
}
🧠 What Changed?
We now split the string into lines using std::getline.

Each line is rendered at increasing Y positions using y + yOffset.

TTF_FontLineSkip() handles spacing automatically.



*/