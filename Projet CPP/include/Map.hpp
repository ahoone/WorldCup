#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>

#define SIZE_X 32
#define SIZE_Y 24

class Map
{

public:
	Map();
	~Map();

	void LoadMap(int array[SIZE_Y][SIZE_X]);
	
	//void DrawMap();

private:

	//**********************
	//*** OLD MAP SYSTEM ***
	//**********************

	/*
	SDL_Rect _src, _dest;
	SDL_Texture* _dirt;
	SDL_Texture* _grass;
	SDL_Texture* _water;
	*/

};