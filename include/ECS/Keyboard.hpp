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

	Keyboard() = default;
	Keyboard(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right)
	{
		_up = up;
		_down = down;
		_left = left;
		_right = right;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	//Les switch ne sont pas utilisables dans cette fonction
	//car la valeur des case doit être décidée à la compilation
	//ce qui n'est pas le cas ici car on donne 2 keyboard
	//différents à chaque player.
	//On perd un peu en efficacité pour gagner en adaptabilité.
	void update() override
	{
		if(Game::event.type == SDL_KEYDOWN)
		{
			if(Game::event.key.keysym.sym == _up)
				transform->velocity.y(-1);

			if(Game::event.key.keysym.sym == _down)
				transform->velocity.y(1);

			if(Game::event.key.keysym.sym == _left)
				transform->velocity.x(-1);

			if(Game::event.key.keysym.sym == _right)
				transform->velocity.x(1);

			/*
			switch(Game::event.key.keysym.sym)
			{
			case _up:
				transform->velocity.y(-1);
				break;
			case _down:
				transform->velocity.y(1);
				break;
			case _left:
				transform->velocity.x(-1);
				break;
			case _right:
				transform->velocity.x(1);
				break;
			default:
				break;
			}
			*/
		}

		if(Game::event.type == SDL_KEYUP)
		{
			if(Game::event.key.keysym.sym == _up)
				transform->velocity.y(0);

			if(Game::event.key.keysym.sym == _down)
				transform->velocity.y(0);

			if(Game::event.key.keysym.sym == _left)
				transform->velocity.x(0);

			if(Game::event.key.keysym.sym == _right)
				transform->velocity.x(0);

			/*
			switch(Game::event.key.keysym.sym)
			{
			case _up:
				transform->velocity.y(0);
				break;
			case _down:
				transform->velocity.y(0);
				break;
			case _left:
				transform->velocity.x(0);
				break;
			case _right:
				transform->velocity.x(0);
				break;
			default:
				break;
			}
			*/
		}
	}

private:

	SDL_Keycode _up;
	SDL_Keycode _down; 
	SDL_Keycode _left; 
	SDL_Keycode _right;

};
