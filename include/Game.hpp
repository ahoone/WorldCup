#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

class ColliderComponent;

class Game
{

public:
	Game();
	~Game();

	//**********************
	//*** INITIALISATION ***
	//**********************

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void initEntities();
	void placeWall();
	void placeGoal();

	//*********************
	//*** BOUCLE DE JEU ***
	//*********************
	
	void effect();
	void update();
	void render();
	void clean();

	bool running() {return _running; };

	//******************************
	//*** GÉRER LES INTERACTIONS ***
	//******************************

	static void AddTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	int _count;
	bool _running;
	SDL_Window* window;

};