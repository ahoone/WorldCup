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
	
	void event();
	void update();
	void render();
	void clean();

	bool running() {return _running;};

	static SDL_Renderer* renderer;

private:
	int _count;
	bool _running;
	SDL_Window* window;

};