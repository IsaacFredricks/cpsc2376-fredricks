#pragma once//from wednesday's class recording
#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <SDL2/SDL2_gfxPrimitives.h>//for circles
#include <string>

class Engine {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	int fontSize;

public:
	//constructor for sdl stuff
	Engine(const std::string& title = "Engine Window",
	int width = 700, int height = 800,
	const std::string& fontPath = "OpenSans-Regular.ttf",
	int fontSize = 14);

	//destructor to clean up resources like the ptrs
	~Engine();

	//expose the renderer ptr if further customization is needed
	SDL_Renderer* getRendrerer() const;

	void flip();//presents frame

	void clear(SDL_Color color = { 25, 50, 100, 255 });

	//creates a filled circle
	void drawCircle(int centerX, int centerY, int radius, SDL_Color color = { 255, 0, 0, 255 });

	void drawRectangle(int centerX, int centerY, int w, int h, SDL_Color color);

	//draws text at specific coordinates
	void drawText(const std::string& text, int centerX, int centerY, SDL_Color color = {255, 255, 255, 255});
	
};