/*#pragma once//from wednesday's class recording
#define SDL_MAIN_HANDLED//fixes error in visual studio for sdl
#include <SDL2/SDL.h>//for graphics
#include <SDL2/SDL_ttf.h>//for text graphics
#include <SDL2/SDL2_gfxPrimitives.h>//for circles

class Engine {
private:


public:
	Engine() {}

	~Engine();

	void flip();

	void draw();

	void drawCircle(int venterX, int centerY, int radius, SDL_Color color = { 255, 0, 0, 255 });

	void clear(SDL_Color color = { 255, 0, 0, 255 });

	void drawRectangle(int centerX, int centerY, int w, int h, SDL_Color color);

};*/