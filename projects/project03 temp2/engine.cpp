#include "engine.h"
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <SDL2/SDL2_gfxPrimitives.h>//for circles
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

Engine::Engine(const std::string& title, int width, int height,
	const std::string& fontPath, int fontSize) : window(nullptr), renderer(nullptr){
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {//checks if able to display video
		std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error("sdl init failed");
	}

	if (TTF_Init() != 0) {//checks if able to display text
		std::cerr << "SDL_ttf Init Error: " << TTF_GetError() << std::endl;
		//SDL_QUIT();//gives me an error
		throw std::runtime_error("ttf init failed");
	}

	SDL_Window* window = SDL_CreateWindow(//makes window
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,//can also do undefined
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN//makes windows visible
	);
	
	if (!window) {//checks if window is able to open
		std::cerr << "window can't be made! sdl error: " << SDL_GetError() << '\n';
		TTF_Quit();
		SDL_Quit();
		throw std::runtime_error("sdl_createwindow failed");
	}

	//makes renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "renderer couldn't be created sdl error: " << SDL_GetError() << '\n';
		TTF_Quit();
		SDL_Quit();
		throw std::runtime_error("SDL_CreateRenderer Failed");
	}

	//loads font from ttf file
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) {
		std::cerr << "failed to load font! ttf_error: " << TTF_GetError() << '\n';
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		SDL_Quit();
		throw std::runtime_error("ttf openfont failed");

	}
}

Engine::~Engine(){//cleans up ptrs so no memory leaks
	if (font) {
		TTF_CloseFont(font);
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	TTF_Quit();
	SDL_Quit();
}

SDL_Renderer* Engine::getRendrerer() const {
	return renderer;
}

void Engine::flip(){//presents frame
	SDL_RenderPresent(renderer);
}

void Engine::clear(SDL_Color color){
	//clear screen (set background to blue):
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

void Engine::drawRectangle(int centerX, int centerY, int w, int h, SDL_Color color) {
	
	SDL_Rect rect;
	rect.x = centerX - w / 2;
	rect.y = centerY - h / 2;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Engine::drawCircle(int centerX, int centerY, int radius, SDL_Color color) {
	filledCircleRGBA(renderer, centerX, centerY, radius, color.r, color.g, color.b, color.a);
}

void Engine::drawText(const std::string& text, int centerX, int centerY, SDL_Color color) {
	int lineHeight = TTF_FontLineSkip(font);
	int yOffSet = 0;

	std::istringstream stream(text);
	std::string line{};

	while (std::getline(stream, line)) {
		//render the text to a surface using the loaded font
		SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

		if (!textSurface) {
			std::cerr << "unable to render text surface! ttf error: " << TTF_GetError() << '\n';
			return;
		}

		//make texture from surface
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (!textTexture) {
			std::cerr << "unable to render text texture from rendered text! sdl error: " << SDL_GetError() << '\n';
			SDL_FreeSurface(textSurface);
			return;
		}

		//calculate destination rectangle to center the text
		SDL_Rect destRect;
		destRect.w = textSurface->w;
		destRect.h = textSurface->h;
		destRect.x = centerX - destRect.w / 2;
		destRect.y = centerY - destRect.h / 2 + yOffSet;

		SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);
		
		yOffSet += lineHeight;

		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
	}
	
}