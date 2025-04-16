#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <SDL2/SDL2_gfxPrimitives.h>//for circles
#include <iostream>//some ai used. I used the ai summary feature for google search for making clickable buttons and drawing lines using sdl and some chatgpt for black screen error in sdl
#include <vector>//for game Board
#include <limits>//for edge testing
#include <string>//for getLine
#include "connectFour.h"//works fine in vs if its just .h. Change to .cpp if using codebin or github codespaces
//#include "Engine.h"

/*GOALS:
*[x] make game class/object oriented
*[x] make a text-based game
*[x] make connect 4
*[x] 7x6 two dimensional array
*[ ] Use x's and o's for pieces using sdl
*[x] Way to replay the game
*[x] Functions to check input
*[x] If at end no person wins, its a draw
*[ ] replace all text using sdl
*[ ] display game pieces and board in display function
*[ ] implement the game logic with the sdl
*/

//forward declaration here
bool playAgain();
struct ClickableItem {
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color defaultColor;
    SDL_Color clickedColor;
    bool isClicked;

    ClickableItem(int x, int y, int w, int h, SDL_Color defaultColor, SDL_Color clickedColor) : rect({x, y, w, h}), defaultColor(defaultColor), clickedColor(clickedColor), isClicked(false) {}

    void handleEvent(const SDL_Event& event) {//checks if clicked and not clicked
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.x >= rect.x && event.button.x <= rect.x + rect.w &&
                event.button.y >= rect.y && event.button.y <= rect.y + rect.h) {
                isClicked = true;
                color = clickedColor;
            }
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            isClicked = false;
            color = defaultColor;
        }
    }

    void render(SDL_Renderer* renderer) {//displays in window
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
};//from chipmunksdl example

int main(int argc, char* argv[]){//copied from chipmunkSDLExample
    bool mouseClicked{ false };

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {//checks if able to display video
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {//checks if able to display text
        std::cerr << "SDL_ttf Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(//makes window
        "Connect4 - Press ESC to Quit",
        SDL_WINDOWPOS_CENTERED,//can also do undefined
        SDL_WINDOWPOS_CENTERED,
        700, 800,
        SDL_WINDOW_SHOWN//makes windows visible

    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//like a paintbrush. can pass to other functions
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //source: https://thenumb.at/cpp-course/sdl2/07/07.html
    TTF_Font* font = TTF_OpenFont("OpenSans-Regular.ttf", 12);//font source: https://www.fontsquirrel.com/fonts/open-sans
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    SDL_Color color = { 255, 255, 255 };

    SDL_Surface* text = TTF_RenderText_Blended_Wrapped(font, "======== Connect 4 =======\nRules:\n*1st person to get 4 in a row in any diraction horizontally, vertically,\n and diagonally wins.\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n*Player1 is X and Player 2 is O.\n*Pieces will go down to the lowest possible row\n*ONLY Y OR N if you want to play again!\n\n", color, 800);

    //the blended wrapped ttf allows for line breaking after a certain length
  
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);


    SDL_Color defaultColor{ 255, 255, 255, 0 };//not done here. make the column transparent later
    SDL_Color clickedColor{ 0, 255, 0, 255 };
    ClickableItem column1(5, 200, 90, 25, defaultColor, clickedColor);
    ClickableItem column2(105, 200, 90, 25, defaultColor, clickedColor);
    ClickableItem column3(205, 200, 90, 25, defaultColor, clickedColor);
    ClickableItem column4(305, 200, 90, 25, defaultColor, clickedColor);
    ClickableItem column5(405, 200, 90, 25, defaultColor, clickedColor);
    ClickableItem column6(505, 200, 90, 25, defaultColor, clickedColor);
    ClickableItem column7(605, 200, 90, 25, defaultColor, clickedColor);
    bool running = true;

    SDL_Event event;//reads events from event queue

    //Engine engine;
    ConnectFour currentGame{};//makes game object


    while (running) {
        int col{ -1 };//so no accidental moves

        // Handle events
        while (SDL_PollEvent(&event)) {//pass in with info. in out parameter
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }

            column1.handleEvent(event);
            column2.handleEvent(event);
            column3.handleEvent(event);
            column4.handleEvent(event);
            column5.handleEvent(event);
            column6.handleEvent(event);
            column7.handleEvent(event);

            if (event.type == SDL_MOUSEBUTTONDOWN && !mouseClicked) {
                //check which item is clicked

                //col is 1 less than the actual value
                if (column1.isClicked) col = 0;
                else if (column2.isClicked) col = 1;
                else if (column3.isClicked) col = 2;
                else if (column4.isClicked) col = 3;
                else if (column5.isClicked) col = 4;
                else if (column6.isClicked) col = 5;
                else if (column7.isClicked) col = 6;
            
                if (col >= 0 && currentGame.canMakeMove(col)) {
                    currentGame.play(col);
                    //std::cout << "column clicked on and turn is " << currentGame.getTurns() << '\n';
                }

                else {
                    //std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";//find a way to print this to the sdl text thingy
                }

                mouseClicked = true;
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
        
        ConnectFour::Status stats = currentGame.status();

        if (stats == ConnectFour::PLAYER_1_WINS || stats == ConnectFour::PLAYER_2_WINS
            || stats == ConnectFour::DRAW) {
            //print who won
            //std::cout << "Total number of turns: " << currentGame.getTurns() << '\n';

            if (stats == ConnectFour::PLAYER_1_WINS) {
                //std::cout << "Player 1 wins!\n";
            }

            else if (stats == ConnectFour::PLAYER_2_WINS) {
                //std::cout << "Player 2 wins!\n";
            }

            else if (stats == ConnectFour::DRAW) {
                //std::cout << "Draw!\n";
            }

            bool replay{ playAgain() };

            if (replay) {
                //std::cout << "Starting a new game. Clearing the board\n\n";
                currentGame = ConnectFour{};//resets game

                currentGame.display(renderer);
            }

            else {
                //std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }

        //actually draws background here

        SDL_SetRenderDrawColor(renderer, 25, 50, 100, 255);//set background to red
        SDL_RenderClear(renderer);//paints whole screen that color

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);//render texture to the renderer. null gives everything

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //makes gameboard:
        currentGame.display(renderer);

        column1.render(renderer);
        column2.render(renderer);
        column3.render(renderer);
        column4.render(renderer);
        column5.render(renderer);
        column6.render(renderer);
        column7.render(renderer);

        SDL_RenderPresent(renderer);
        //presents hidden frame

    }
    //cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();//needed. cleans up resources

    return 0;
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

*/