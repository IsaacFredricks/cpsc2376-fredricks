#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <iostream>

#include <iostream>//no ai used

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {//checks if able to display video
		std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (TTF_Init() != 0) {//CHECKS IF ABLE TO DISPLAY VIDEO
		std::cerr << "SDL_ttf Init Error: " << TTF_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(//makes window
		"myProgram - Press ESC to Quit",
		SDL_WINDOWPOS_CENTERED,//can also do undefined
		SDL_WINDOWPOS_CENTERED,
		1280, 600,
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
	SDL_Color color = { 0, 0, 255 };

	text = TTF_RenderText_Solid(font, "making a text program: please just work. by isaac fredricks", color);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

	SDL_Rect textRect;
	textRect.x = 45;
	textRect.y = 45;
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	bool running = true;

	SDL_Event event;//reads events from event queue
	
	while (running) {
		//handles events
		while (SDL_PollEvent(&event)) {//keyboard mouse inputs
			if (event.type == SDL_QUIT) {
				running = false;
			}

			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Rect rect = { 400, 400, 400, 400 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(16);//fps

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();//cleans up resources

	return 0;
}