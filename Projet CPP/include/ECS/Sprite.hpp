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

};