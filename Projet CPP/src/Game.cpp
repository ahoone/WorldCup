#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"

#include "ECS/Entity.hpp"
#include "ECS/Components.hpp"
#include "ECS/Sprite.hpp"
#include "ECS/Transform.hpp"
#include "ECS/Collider.hpp"

#include "Vector.hpp"
#include "Collision.hpp"

//=======================================

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayer,
	groupEnemies,
	groupColliders
};

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
		//Load the default map.

		//std::cout << "alright" << std::endl;

		//*****************************
		//*** ENTITY IMPLEMENTATION ***
		//*****************************

		player.addComponent<TransformComponent>(2);
		player.addComponent<SpriteComponent>("../assets/j1b.bmp", 2, 500);
		player.addComponent<Keyboard>();
		player.addComponent<ColliderComponent>("player");
		player.addGroup(groupPlayer);

		/*
		wall.addComponent<TransformComponent>(300, 300, 300, 20, 1);
		wall.addComponent<SpriteComponent>("../assets/dirt.bmp");
		wall.addComponent<ColliderComponent>("wall");
		wall.addGroup(groupMap);
		*/

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

	//***************************
	//*** TESTS UNITAIRES ECS ***
	//***************************

	// if(Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
	// {
	// 	std::cout << "Wall hit" << std::endl;
	// 	player.getComponent<TransformComponent>().velocity * -2;
	// }

	//player.getComponent<TransformComponent>().position.Add(Vector(5,0));

	//if(player.getComponent<TransformComponent>().position.x() > 200) player.getComponent<SpriteComponent>().setText("../assets/enemy.bmp");

	//if(player.getComponent<TransformComponent>().x() > 100) player.getComponent<SpriteComponent>().setText("../assets/enemy.bmp");

	//std::cout << player.getComponent<TransformComponent>().x() << "," << player.getComponent<TransformComponent>().y() << std::endl;

}

//Liste pour accéder aux éléments de chaque groupe.
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayer));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render()
{
	SDL_RenderClear(renderer);

	for(auto& t : tiles)
		t->draw();

	for(auto& p : players)
		p->draw();

	for(auto& e : enemies)
		e->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "End running" << std::endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}