#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <iostream>//some ai used. I used the ai summary feature for google search for making clickable buttons and drawing lines using sdl
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
*[x] display text using sdl
*[ ] display game board using sdl
*[ ] implement the game logic with the sdl
*/



//forward declaration here
bool playAgain();
int getInt(const std::string& prompt);
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
        800, 800,
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
    TTF_Font* font = TTF_OpenFont("OpenSans-Regular.ttf", 14);//font source: https://www.fontsquirrel.com/fonts/open-sans
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    SDL_Surface* text;
    SDL_Color color = { 255, 255, 255 };

    //the blended wrapped ttf allows for line breaking after a certain length
    text = TTF_RenderText_Blended_Wrapped(font, "======== Connect 4 =======\nRules:\n*1st person to get 4 in a row in any diraction horizontally, vertically,\n and diagonally wins.\n*If all of the spaces are taken and no one has won, the game ends in a draw.\n*Player one is green while Player 2 is blue.\n*Player 1 starts first.\n*Pieces will go down to the lowest possible row\n ONLY Y OR N if you want to play again!\n\n", color, 800);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);
    
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

   
    SDL_Color defaultColor{ 255, 255, 255, 25 };//white
    SDL_Color clickedColor{ 0, 255, 0, 255 };
    ClickableItem centerColumn(300, 225, 100, 575, defaultColor, clickedColor);

    bool running = true;

    SDL_Event event;//reads events from event queue

    ConnectFour currentGame{};//makes game object


    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {//pass in with info. in out parameter
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }

            centerColumn.handleEvent(event);
        }
        //actually draws background here

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//set background to red
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //makes gameboard:
        //currentGame.display();//eventually move the draw lines into the display function

        //vertical lines
        SDL_RenderDrawLine(renderer, 100, 225, 100, 800);

        SDL_RenderDrawLine(renderer, 200, 225, 200, 800);

        SDL_RenderDrawLine(renderer, 300, 225, 300, 800);

        SDL_RenderDrawLine(renderer, 400, 225, 400, 800);

        SDL_RenderDrawLine(renderer, 500, 225, 500, 800);

        SDL_RenderDrawLine(renderer, 600, 225, 600, 800);

        //horizontal lines
        SDL_RenderDrawLine(renderer, 25, 300, 675, 300);

        SDL_RenderDrawLine(renderer, 25, 400, 675, 400);

        SDL_RenderDrawLine(renderer, 25, 500, 675, 500);

        SDL_RenderDrawLine(renderer, 25, 600, 675, 600);

        SDL_RenderDrawLine(renderer, 25, 700, 675, 700);

        centerColumn.render(renderer);
        //eventually print out the pieces on the board by iterating through the vector
        //find out how to print a line to see who's turn it is
        
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
