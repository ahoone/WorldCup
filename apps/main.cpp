#include <iostream>

#include "Game.hpp"

int main(int argc, char const *argv[])
{

	//Réglage FPS
	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	unsigned long int frameStart;
	int frameTime;

	Game *game = nullptr;

	game = new Game();

	game->init("WorldCup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, false);

	//Boucle de jeu
	while(game->running()) {

		frameStart = SDL_GetTicks();

		game->effect();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

	}

	game->clean();

	return 0;
}