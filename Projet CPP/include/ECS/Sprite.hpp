#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

class SpriteComponent : public Component
{

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {setText(path); }

	void setText(const char* path) {_texture = TextureManager::LoadTexture(path); }

	void init() override
	{
		_position = &entity->getComponent<PositionComponent>();

		_srcRect.x = _srcRect.y = 0;
		_srcRect.w = _srcRect.h = 32;
		_destRect.w = _destRect.h = 64;
	}

	void update() override
	{
		_destRect.x = _position->x();
		_destRect.y = _position->y();
	}

	void draw() override
	{
		TextureManager::Draw(_texture, _srcRect, _destRect);
	}



private:
	PositionComponent* _position;
	SDL_Texture* _texture;

	SDL_Rect _srcRect, _destRect;

};

