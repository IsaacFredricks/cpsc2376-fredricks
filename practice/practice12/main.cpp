/*

// main.cpp. used chatgpt "can you give me an example of chipmunk for c++"
#include <chipmunk/chipmunk.h>
#include <iostream>

int main() {
    // Create a new Chipmunk space
    cpSpace* space = cpSpaceNew();
    cpVect gravity = cpv(0, -100);
    cpSpaceSetGravity(space, gravity);

    // Create static ground
    cpBody* staticBody = cpSpaceGetStaticBody(space);
    cpShape* ground = cpSegmentShapeNew(staticBody, cpv(-300, 0), cpv(300, 0), 0);
    cpShapeSetFriction(ground, 1.0);
    cpSpaceAddShape(space, ground);

    // Create a dynamic body (a ball)
    cpFloat mass = 1.0;
    cpFloat radius = 15.0;
    cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
    cpBody* ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    cpBodySetPosition(ballBody, cpv(0, 100));

    cpShape* ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
    cpShapeSetFriction(ballShape, 0.7);

    // Simulate for 2 seconds at 60 FPS
    const double timeStep = 1.0 / 60.0;
    for (int i = 0; i < 120; ++i) {
        cpSpaceStep(space, timeStep);
        cpVect pos = cpBodyGetPosition(ballBody);
        std::cout << "Time: " << (i + 1) * timeStep << "s - Ball position: ("
            << pos.x << ", " << pos.y << ")\n";
    }

    // Cleanup
    cpShapeFree(ballShape);
    cpBodyFree(ballBody);
    cpShapeFree(ground);
    cpSpaceFree(space);

    return 0;
}
*/

#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//used chatgpt : "give me an example of a simple c++ program"
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {//checks if able to display video
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(//makes window
        "Red Rectangle - Press ESC to Quit",
        SDL_WINDOWPOS_CENTERED,//can also do undefined
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN//makes windows visible
        
    );

    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//like a paintbrush. can pass to other functions
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    
    SDL_Event event;

    bool isSpaceDown = false;
    int x = 0;

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

                if (event.key.keysym.sym == SDLK_SPACE) {
                    isSpaceDown = true;
                }
            }

            else if (event.type == SDL_KEYUP) {//when key goes back up
               
                if (event.key.keysym.sym == SDLK_SPACE) {
                    isSpaceDown = false;
                }
            }

            else if (event.type - SDL_MOUSEMOTION) {
                x = event.motion.x;
            }
        }
        //actually draws background here

        // Clear the screen with a background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
        SDL_RenderClear(renderer);

        // Draw a red rectangle
        SDL_Rect rect = { x, 200, 200, 150 }; // x, y, width, height
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
        SDL_RenderFillRect(renderer, &rect);

        SDL_Rect rect2 = { 400, 300, 300, 450 };

        SDL_RenderFillRect(renderer, &rect2);

        if (isSpaceDown) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // black background
        }

        // Present the rendered frame
        SDL_RenderPresent(renderer);//presents hidden frame

        // Optional: Limit framerate
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();//needed. cleans up resources

    return 0;
}


