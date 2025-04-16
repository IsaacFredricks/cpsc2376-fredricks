
/*
//google ai summary: how to make an interactable button that changes color in sdl c++
struct Button {
	SDL_Rect rect;
	SDL_Color color;
	SDL_Color defaultColor;
	SDL_Color clickedColor;
	bool clicked;

	Button(int x, int y, int w, int h, SDL_Color defaultColor, SDL_Color clickedColor) :
		rect({ x, y, w, h }),
		defaultColor(defaultColor),
		clickedColor(clickedColor),
		color(defaultColor),
		clicked(false) {
	}

	void handleEvent(const SDL_Event& event) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.x >= rect.x && event.button.x <= rect.x + rect.w &&
				event.button.y >= rect.y && event.button.y <= rect.y + rect.h) {
				clicked = true;
				color = clickedColor;
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			clicked = false;
			color = defaultColor;
		}
	}

	void render(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
};

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Clickable Item", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Color defaultColor = { 255, 0, 0, 255 }; // Red
	SDL_Color clickedColor = { 0, 255, 0, 255 }; // Green
	Button button(100, 100, 100, 50, defaultColor, clickedColor);

	SDL_Event event;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			button.handleEvent(event);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		button.render(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}*/