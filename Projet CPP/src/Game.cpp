#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"

#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"
#include "ECS/Sprite.hpp"
#include "ECS/Transform.hpp"

#include "Vector.hpp"

//=======================================

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& player(manager.addEntity());

//=======================================

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if(fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "SDL_Init Error" << std::endl;
		_running = false;
	} 
	else
	{
		std::cout << "Subsystem Initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(!window)
			std::cout << "SDL_CreateWindow Error" << std::endl;
		else
			std::cout << "Window Created" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(!renderer)
			std::cout << "SDL_CreateRenderer Error" << std::endl;
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		_running = true;
		_count = 0;


		map = new Map();

		player.addComponent<TransformComponent>(0,0);
		player.addComponent<SpriteComponent>("../assets/enemy.bmp");
		player.addComponent<Keyboard>();
	}
}

void Game::effect()
{
	
	SDL_PollEvent(&event);
	switch(event.type)
	{
		case SDL_QUIT:
			_running = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	manager.actualize();
	manager.update();

	//player.getComponent<TransformComponent>().position.Add(Vector(5,0));

	//if(player.getComponent<TransformComponent>().position.x() > 200) player.getComponent<SpriteComponent>().setText("../assets/enemy.bmp");

	//if(player.getComponent<TransformComponent>().x() > 100) player.getComponent<SpriteComponent>().setText("../assets/enemy.bmp");

	std::cout << player.getComponent<TransformComponent>().x() << "," << player.getComponent<TransformComponent>().y() << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "End running" << std::endl;
}