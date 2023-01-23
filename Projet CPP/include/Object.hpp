#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Object
{

public:
	Object();
	Object(const char* textureFile, int x, int y);
	~Object();

	void update();
	void render();

private:
	int _xpos, _ypos;

	SDL_Texture* _texture;
	SDL_Rect _srcRect, _destRect;


};