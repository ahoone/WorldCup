#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void effect();
	void update();
	void render();
	void clean();

	bool running() {return _running; };

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	int _count;
	bool _running;
	SDL_Window* window;

};