#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics

#include <iostream>//no ai used
#include <vector>//for game Board
#include <limits>//for edge testing
#include <string>//for getLine
#include "connectFour.h"//works fine in vs if its just .h. Change to .cpp if using codebin or github codespaces
/*GOALS:
*[x] make game class/object oriented
*[x] make a text-based game
*[x] makeconnect 4
*[x] 7x6 two dimensional array
*[x] Use C and O for pieces
*[x] Function for Make grid with | and _
*[x] Way to replay the game
*[x] Functions to check input
*[x] If at end no person wins, its a draw
*[ ] display text and game board using sdl
*/



//forward declaration here
bool playAgain();
int getInt(const std::string& prompt);

void draw(SDL_Renderer* renderer, const std::string& text);

int main(int argc, char* argv[]) {//copied from chipmunkSDLExample

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {//checks if able to display video
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {//checks if able to display video
        std::cerr << "SDL_ttf Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(//makes window
        "Connect4 - Press ESC to Quit",
        SDL_WINDOWPOS_CENTERED,//can also do undefined
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
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
    TTF_Font* font = TTF_OpenFont("OpenSans-Regular.ttf", 24);//font source: https://www.fontsquirrel.com/fonts/open-sans
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    SDL_Surface* text;
    SDL_Color color = { 255, 255, 255 };

    text = TTF_RenderText_Solid(font, "Connect four: please just work", color);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);
    
    SDL_Rect textRect;
    textRect.x = 30;
    textRect.y = 30;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

    bool running = true;

    SDL_Event event;//reads events from event queue

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {//pass in with info. in out parameter
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }

        }
        //actually draws background here

        // Clear the screen with a background color
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
        
        // Present the rendered frame

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
        //presents hidden frame

        // Optional: Limit framerate
        SDL_Delay(16); // ~60 FPS
    }
    /*
    ConnectFour currentGame{};//makes game object

    std::cout << "\n======== Connect 4 =======\n\n";

    std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
        << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
        << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
        << "*Pieces will go down to the lowest possible row\n"
        << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";

    currentGame.display();

    while (true) {
        std::cout << '\n';

        //index starts at 0 so has to be one less than player's input
        if (currentGame.getTurns() % 2 == 0) {
            std::cout << "Player 2, ";
        }

        else if (currentGame.getTurns() % 2 > 0) {
            std::cout << "Player 1, ";
        }

        int col{ getInt("Enter what column you want to play: ") - 1 };

        if (currentGame.canMakeMove(col)) {
            currentGame.play(col);
        }

        else {
            std::cout << "UNABLE TO PLACE PIECE THERE! TRY ANOTHER SPOT\n";
        }
       
        currentGame.display();

        //check to see who won
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
                std::cout << "Starting a new game. Clearing the board\n\n";
                currentGame = ConnectFour{};//resets game

                std::cout << "Rules:\n*1st person to get 4 in a row in any diraction horizontally, vertically, and diagonally wins."
                    << "\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n"
                    << "*Player one uses O's while Player 2 uses C's.\n*Player 1 starts first.\n"
                    << "*Pieces will go down to the lowest possible row\n"
                    << "*Do not input Yes or No if you want to play again. ONLY Y OR N!\n\n";

                currentGame.display();

            }

            else {
                std::cout << "Ending the game. Goodbye!\n";
                break;//ends loop
            }
        }*/

        //cleanup
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();//needed. cleans up resources

    return 0;
}

int getInt(const std::string& prompt) {
    int num{};

    while (true) {
        std::cout << prompt;
        std::cin >> num;

        if (std::cin.fail() || std::cin.peek() != '\n' || num > 7 || num < 1) {//peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }

    return num;
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

