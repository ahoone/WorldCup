#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"
#include "../TextureManager.hpp"

#define SIZE_PLAYER 32

class SpriteComponent : public Component
{

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {setText(path); }
	SpriteComponent(const char* path, int f, int s)
	{
		setText(path);	//Path vers le fichier avec le/les sprite(s)
		_frames = f;	//Nombre frames animation
		_speed = s;		//Grande valeur => boucle lente
		_animated = true;
	}

	~SpriteComponent() {SDL_DestroyTexture(_texture); }

	void setText(const char* path) {_texture = TextureManager::LoadTexture(path); }

	void init() override
	{
		_position = &entity->getComponent<TransformComponent>();

		_srcRect.x = _srcRect.y = 0;
		_srcRect.w = _position->width;
		_srcRect.h = _position->height;
	}

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

	void draw() override
	{
		TextureManager::Draw(_texture, _srcRect, _destRect);
	}



private:
	TransformComponent* _position;
	SDL_Texture* _texture;

	SDL_Rect _srcRect, _destRect;

	bool _animated = false;
	int _frames = 0;
	int _speed = 100;

};