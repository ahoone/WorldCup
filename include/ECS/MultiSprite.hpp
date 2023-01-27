#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.hpp"

//To handle animated sprite
class MultiSpriteComponent : public SpriteComponent
{

public:

	MultiSpriteComponent(const char* path, int f, int s)
	{
		setText(path);	//Path vers le fichier avec le/les sprite(s)
		_frames = f;	//Nombre frames animation
		_speed = s;		//Grande valeur => boucle lente
		_animated = true;
	}

	//On réécrit par dessus le update
	//de SpriteComponent en rajoutant
	//le changement de frame.
	void update() override
	{
		if(_animated)
		{
			_srcRect.x = _srcRect.w * static_cast<int>((SDL_GetTicks() / _speed) % _frames);
		}

		_destRect.x = static_cast<int>(_position->x());
		_destRect.y = static_cast<int>(_position->y());

		_destRect.w = _position->width * _position->scale;
		_destRect.h = _position->height * _position->scale;
	}

private:

	bool _animated = false;
	int _frames = 0;
	int _speed = 100;

};