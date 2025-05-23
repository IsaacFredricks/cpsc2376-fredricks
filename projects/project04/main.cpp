﻿#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <SDL2/SDL2_gfxPrimitives.h>//for circles
#include <iostream>//some ai used. I used the ai summary feature for google search for making clickable buttons and drawing lines using sdl and some chatgpt for black screen error in sdl
#include <vector>//for game Board
#include <limits>//for edge testing
#include <string>//for getline and to_string
#include "connectFour.h"//works fine in vs if its just .h. Change to .cpp if using codebin or github codespaces
#include "engine.h"

/*GOALS:
*[x] make game class/object oriented
*[x] make connect 4
*[x] 7x6 two dimensional array
*[X] Use circles for pieces using sdl
*[x] Functions to check input
*[x] If at end no person wins, its a draw
*[X] replace all text except for rules using sdl
*[x] display game pieces and board in display function
*[x] implement the game logic with the sdl
*[X] have a way to replay the game
*[x] have a title screen
*/

//forward declaration here
void drawTitleScreen(ConnectFour::Status stats, Engine& engine, ConnectFour& currentGame);//do later
void drawWinScreen(ConnectFour::Status stats, Engine& engine, ConnectFour& currentGame);

int main(int argc, char* argv[]) {//copied from chipmunkSDLExample

    bool running{ true };
    bool mouseClicked{ false };
    bool pressedStart{ false };
    SDL_Event event;
    Engine engine{"Connect four - press escape to exit"};
    ConnectFour currentGame{};//makes game object
    int col{};
    int row{};
    bool isError{};//for error message

    //the actual game
    while (running) {
        engine.clear();

        // Handle events
        while (SDL_PollEvent(&event)) {//pass in with info. in out parameter
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }

                else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {//if keypress is enter
                    if (currentGame.status() != ConnectFour::ONGOING) currentGame = ConnectFour();//resets game
                    pressedStart = false;
                }

                else if (event.key.keysym.sym == SDLK_SPACE && !pressedStart) {//if keypress is enter
                    pressedStart = true;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && !mouseClicked) {
                //check which item is clicked
                col = event.button.x / 100;//so no accidental moves
                row = event.button.y / 100;//want to only play inside the gameboard

                if (col >= 0 && row >= 2 && currentGame.canMakeMove(col) && pressedStart) {
                    currentGame.play(col);
                    isError = false;
                    //std::cout << "column clicked on and turn is " << currentGame.getTurns() << '\n';


                    // Flush any lingering mouse click events to prevent phantom inputs
                    SDL_PumpEvents(); // Update the event queue
                    SDL_FlushEvent(SDL_MOUSEBUTTONDOWN); // Remove mouse down events
                }

                //hides error if click on window before starting the game
                else if (event.key.keysym.sym == SDLK_SPACE && !pressedStart) {
                    pressedStart = true;
                    isError = false;
                }

                mouseClicked = true;
            }

            else if (event.type == SDL_MOUSEMOTION && !mouseClicked) {
                //check which item is clicked
                col = event.motion.x / 100;//so no accidental moves

                if (currentGame.status() != ConnectFour::ONGOING) col = -1;
            }

            if (event.type == SDL_MOUSEBUTTONUP) {//undoes bool so no infinite moves
                mouseClicked = false;
            }
        }

        //makes gameboard
        currentGame.draw(&engine, col, pressedStart);

        //index starts at 0 so has to be one less than player's input
        if (currentGame.getTurns() % 2 == 0 && pressedStart) {
            //std::cout << "Player 2, click on the grey button to choose the column: ";
            engine.drawText("Player 2, click on the column you want to play: ", 175, 150);
        }

        else if (currentGame.getTurns() % 2 > 0 && pressedStart) {
            //std::cout << "Player 1, click on the grey button to choose the column: ";
            engine.drawText("Player 1, click on the column you want to play: ", 175, 150);
        }

        ConnectFour::Status stats = currentGame.status();

        if (isError && pressedStart && stats == ConnectFour::ONGOING) {//so it doesn't show a message during the title screen or end screen
            //std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
            engine.drawText("UNABLE TO PLACE PIECE THERE! Place in another column!", 350, 100);
        }


        if (stats == ConnectFour::PLAYER_1_WINS || stats == ConnectFour::PLAYER_2_WINS
        || stats == ConnectFour::DRAW) {
            currentGame.draw(&engine);
            drawWinScreen(stats, engine, currentGame);
        }

        if (!pressedStart) {
            drawTitleScreen(stats, engine, currentGame);
        }

        //logo
        engine.drawText("======== Connect 4 =======", 350, 25);

        //presents hidden frame
        engine.flip();

        SDL_Delay(16);//fps: 60
    }
    return 0;
}

void drawTitleScreen(ConnectFour::Status stats, Engine& engine, ConnectFour& currentGame) {
    engine.drawRectangle(350, 400, 700, 800, {128, 0, 128, 150});
    engine.drawText("Press Space to Start", 350, 500);

    engine.drawText("Rules:", 350, 50);
    engine.drawText("*1st person to get 4 in a row in any diraction horizontally, vertically, or diagonally wins", 350, 70);
    engine.drawText("*If all of the spaces are taken and no one has won, the game ends in a draw.", 350, 90);
    engine.drawText("*Player1 is red and Player 2 is blue.", 350, 110);
    engine.drawText("*Pieces will go down to the lowest possible row", 350, 130);
    engine.drawText("*If all of the spaces are taken and no one has won, the game ends in a draw.", 350, 150);
    engine.drawText("*Only click the row you want inside the game board! Else it won't count", 350, 170);
    engine.drawText("*Resetting the game will take you back to the title screen.", 350, 190);
    engine.drawText("*If you play in a full column, it won't count. Play on a not full column to get rid of error", 350, 210);
    
}

void drawWinScreen(ConnectFour::Status stats, Engine& engine, ConnectFour& currentGame)
{
    //print who won
    //std::cout << "Total number of turns: " << currentGame.getTurns() << '\n';//idk how to print the turns in sdl
    std::string msg;
    SDL_Color bgColor;
    SDL_Color textColor{ 200, 255, 0, 255 };

    if (stats == ConnectFour::PLAYER_1_WINS) {
       //std::cout << "Player 1 wins!\n";
            
       msg = "Player 1 Wins! ";
       bgColor = { 128, 0, 0, 128 };

    }

    else if (stats == ConnectFour::PLAYER_2_WINS) {
        //std::cout << "Player 2 wins!\n";

        msg = "Player 2 Wins! ";
        bgColor = { 0, 0, 128, 128 };
    }

    else if (stats == ConnectFour::DRAW) {
       //std::cout << "Draw!\n";

       msg = "Draw";
       bgColor = { 0, 128, 0, 128 };
    }

    engine.drawRectangle(350, 400, 700, 800, bgColor);
    engine.drawText(msg, 350, 350, textColor);
    engine.drawText("Press Enter to play again", 350, 500, textColor);
    engine.drawText("Total number of turns: " + std::to_string(currentGame.getTurns()), 100, 80, textColor);

}
//by Isaac Fredricks


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


text: on the if statement where its checking to see if I can play in that area and gives an unable to play there error if you can't, if finish a game, click on the screen while its in the title screen, and then start the game, it shows that unable to play piece there error. Is there a way to fix that?

*responce: Yes, you’ve pinpointed a subtle but common logic issue related to event order and state cleanup. Here’s what’s happening:

❗ Problem:
When you click after a game ends, and before starting a new game (while still on the title screen), that mouse click is stored. Once the game starts, that stored click is processed immediately, which causes it to trigger an invalid move — leading to the "UNABLE TO PLACE PIECE" error right after pressing space.

✅ Fix Overview:
You need to clear any pending mouse input when transitioning from the title screen to game start, so the game doesn't treat a previous click as part of the new session.

✅ Solution Option 1 (Recommended):
Manually flush the event queue right after the game starts by calling:

cpp
Copy
Edit
SDL_PumpEvents();
SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
🔧 Modify this part in your event loop:
Find this block:

cpp
Copy
Edit
else if (event.key.keysym.sym == SDLK_SPACE && !pressedStart) {
    pressedStart = true;
}
Update it to:

cpp
Copy
Edit
else if (event.key.keysym.sym == SDLK_SPACE && !pressedStart) {
    pressedStart = true;

    // Flush any lingering mouse click events to prevent phantom inputs
    SDL_PumpEvents(); // Update the event queue
    SDL_FlushEvent(SDL_MOUSEBUTTONDOWN); // Remove mouse down events
}
✅ Alternative Option 2: Reset isError at start
Another (less precise) way would be to also reset the isError flag to false when starting the game:

cpp
Copy
Edit
else if (event.key.keysym.sym == SDLK_SPACE && !pressedStart) {
    pressedStart = true;
    isError = false;
}
But this doesn't prevent a leftover mouse click from triggering an action, it just hides the error message — so Option 1 is preferred.
*/