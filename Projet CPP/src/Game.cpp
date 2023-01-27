#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"

#include "ECS/Entity.hpp"
#include "ECS/Components.hpp"
#include "ECS/Sprite.hpp"
#include "ECS/Transform.hpp"
#include "ECS/Collider.hpp"
#include "ECS/MultiSprite.hpp"

#include "Vector.hpp"
#include "Collision.hpp"

//====================================
//=== DÉCLARATION COMPOSANTES JEUX ===
//====================================

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player1(manager.addEntity());
auto& player2(manager.addEntity());

auto& ball(manager.addEntity());

auto& wall1(manager.addEntity());
auto& wall2(manager.addEntity());
auto& wall3(manager.addEntity());
auto& wall4(manager.addEntity());
auto& wall5(manager.addEntity());
auto& wall6(manager.addEntity());

auto& goal1(manager.addEntity());
auto& goal2(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupItems,
	groupColliders
};

//====================================

Game::Game()
{}

Game::~Game()
{}


//Initialise la SDL et les variables des composantes
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

		//Load the default map.
		map = new Map();

		initEntities();
		placeWall();
		placeGoal();
	}
}

void Game::initEntities()
{
	//**************************
	//*** ECS IMPLEMENTATION ***
	//**************************

	player1.addComponent<TransformComponent>(256, 384, 32, 32, 2);
	player1.addComponent<MultiSpriteComponent>("../assets/j1.bmp", 2, 500);
	player1.addComponent<Keyboard>(SDLK_z, SDLK_s, SDLK_q, SDLK_d);
	player1.addComponent<ColliderComponent>("player1");
	player1.addGroup(groupPlayers);

	player2.addComponent<TransformComponent>(768, 384, 32, 32, 2);
	player2.addComponent<MultiSpriteComponent>("../assets/j2.bmp", 2, 500);
	player2.addComponent<Keyboard>(SDLK_i, SDLK_k, SDLK_j, SDLK_l);
	player2.addComponent<ColliderComponent>("player2");
	player2.addGroup(groupPlayers);

	ball.addComponent<TransformComponent>(512, 384, 32, 32, 1);
	ball.addComponent<SpriteComponent>("../assets/ball.bmp");
	ball.addComponent<ColliderComponent>("ball");
	ball.addGroup(groupItems);

}

void Game::placeWall()
{
	wall1.addComponent<TransformComponent>(32, 32, 96, 256, 1);
	wall1.addComponent<ColliderComponent>("wall1");
	wall1.addGroup(groupColliders);

	wall2.addComponent<TransformComponent>(32, 0, 960, 32, 1);
	wall2.addComponent<ColliderComponent>("wall2");
	wall2.addGroup(groupColliders);

	wall3.addComponent<TransformComponent>(896, 32, 96, 256, 1);
	wall3.addComponent<ColliderComponent>("wall3");
	wall3.addGroup(groupColliders);

	wall4.addComponent<TransformComponent>(896, 480, 96, 256, 1);
	wall4.addComponent<ColliderComponent>("wall4");
	wall4.addGroup(groupColliders);

	wall5.addComponent<TransformComponent>(32, 736, 960, 32, 1);
	wall5.addComponent<ColliderComponent>("wall5");
	wall5.addGroup(groupColliders);

	wall6.addComponent<TransformComponent>(32, 480, 96, 256, 1);
	wall6.addComponent<ColliderComponent>("wall6");
	wall6.addGroup(groupColliders);

	//Pour vérifier que les murs sont bien placés.

	// wall1.addComponent<SpriteComponent>("../assets/water.bmp");
	// wall2.addComponent<SpriteComponent>("../assets/water.bmp");
	// wall3.addComponent<SpriteComponent>("../assets/water.bmp");
	// wall4.addComponent<SpriteComponent>("../assets/water.bmp");
	// wall5.addComponent<SpriteComponent>("../assets/water.bmp");
	// wall6.addComponent<SpriteComponent>("../assets/water.bmp");
}

void Game::placeGoal()
{
	goal1.addComponent<TransformComponent>(32, 288, 96, 192, 1);
	goal1.addComponent<ColliderComponent>("goal1");
	goal1.addGroup(groupColliders);

	goal2.addComponent<TransformComponent>(896, 288, 96, 192, 1);
	goal2.addComponent<ColliderComponent>("goal2");
	goal2.addGroup(groupColliders);

	//Pour vérifier que les goals sont bien placés.

	// goal1.addComponent<SpriteComponent>("../assets/water.bmp");
	// goal2.addComponent<SpriteComponent>("../assets/water.bmp");
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

//Liste pour accéder aux éléments de chaque groupe.
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& items(manager.getGroup(groupItems));
auto& colliderss(manager.getGroup(groupColliders));

void Game::update()
{
	manager.actualize();
	manager.update();

	//***********************************************
	//*** IMPLÉMENTATION COMPORTEMENTS COLLISIONS ***
	//***********************************************

	//Collisions joueurs/bordures
	for(auto& p : players)
	{
		for(auto& c : colliderss)
			if(Collision::AABB(p->getComponent<ColliderComponent>().collider, c->getComponent<ColliderComponent>().collider))
				p->getComponent<TransformComponent>().velocity * -1;
	}

	//Collisions balle/bordures
	for(auto& c : colliderss)
		if(Collision::AABB(ball.getComponent<ColliderComponent>().collider, c->getComponent<ColliderComponent>().collider))
		{
			if(c->getComponent<ColliderComponent>().tag == "goal1" || c->getComponent<ColliderComponent>().tag == "goal2")
			{
				ball.getComponent<TransformComponent>().velocity.Zero();
				ball.getComponent<TransformComponent>().setPos(512, 384);
			}
			else if(c->getComponent<ColliderComponent>().tag == "wall2" || c->getComponent<ColliderComponent>().tag == "wall5")
			{
				ball.getComponent<TransformComponent>().velocity.OpposeY();
			}
			else
			{
				ball.getComponent<TransformComponent>().velocity.OpposeX();
			}
		}

	//Collisions balle/joueurs
	for(auto& p : players)
		if(Collision::AABB(ball.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
			(ball.getComponent<TransformComponent>().velocity=p->getComponent<TransformComponent>().velocity)*3;

	/*
	for(auto& p : players)
		for(auto& c : colliders)
			if(Collision::AABB(p->getComponent<ColliderComponent>().collider, c->getComponent<ColliderComponent>().collider))
			{
				std::cout << "Wall hit" << std::endl;
				p->getComponent<TransformComponent>().velocity * -1;
			}
	*/

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

void Game::render()
{
	SDL_RenderClear(renderer);

	for(auto& t : tiles)
		t->draw();

	for(auto& p : players)
		p->draw();

	for(auto& i : items)
		i->draw();

	for(auto& c : colliderss)
		c->draw();

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