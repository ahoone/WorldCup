#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Map
{

public:
	Map();
	~Map();

	void LoadMap(int array[20][25]);
	void DrawMap();

private:
	SDL_Rect _src, _dest;
	SDL_Texture* _dirt;
	SDL_Texture* _grass;
	SDL_Texture* _water;

	int _map[20][25];
};