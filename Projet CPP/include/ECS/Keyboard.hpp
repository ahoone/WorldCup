#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Game.hpp"
#include "Entity.hpp"
#include "Components.hpp"

class Keyboard : public Component
{

public:

	TransformComponent* transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{

		if(Game::event.type == SDL_KEYDOWN)
		{
			switch(Game::event.key.keysym.sym)
			{
			case SDLK_z:
				transform->velocity.y(-1);
				break;
			case SDLK_s:
				transform->velocity.y(1);
				break;
			case SDLK_q:
				transform->velocity.x(-1);
				break;
			case SDLK_d:
				transform->velocity.x(1);
				break;
			default:
				break;
			}
		}

		if(Game::event.type == SDL_KEYUP)
		{
			switch(Game::event.key.keysym.sym)
			{
			case SDLK_z:
				transform->velocity.y(0);
				break;
			case SDLK_s:
				transform->velocity.y(0);
				break;
			case SDLK_q:
				transform->velocity.x(0);
				break;
			case SDLK_d:
				transform->velocity.x(0);
				break;
			default:
				break;
			}
		}
	}

private:



};
