#include "Map.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

int defaultMap[20][25] = {
	{0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}; 

Map::Map()
{
	_dirt = TextureManager::LoadTexture("../assets/dirt.bmp");
	_grass = TextureManager::LoadTexture("../assets/grass.bmp");
	_water = TextureManager::LoadTexture("../assets/water.bmp");

	LoadMap(defaultMap);

	_src.x = _src.y = 0;
	_dest.x = _dest.y = 0;
	_src.w = _dest.w = 32;
	_src.h = _dest.h = 32;
}

Map::~Map()
{
	SDL_DestroyTexture(_grass);
	SDL_DestroyTexture(_water);
	SDL_DestroyTexture(_dirt);
}

void Map::LoadMap(int array[20][25])
{
	for(int i=0; i<20; i++)
		for(int j=0; j<25; j++)
			_map[i][j] = array[i][j];
}

void Map::DrawMap()
{
	int ref = 0;

	for(int i=0; i<20; i++)
		for(int j=0; j<25; j++)
		{
			ref = _map[i][j];
			
			_dest.x = j*32;
			_dest.y = i*32;

			switch(ref)
			{
				case 0:
					TextureManager::Draw(_water, _src, _dest);
					break;
				case 1:
					TextureManager::Draw(_grass, _src, _dest);
					break;
				case 2:
					TextureManager::Draw(_dirt, _src, _dest);
					break;
				default:
					break;
			}

		}
}