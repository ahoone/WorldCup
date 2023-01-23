#include "Object.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"

Object::Object(const char* textureFile, int x, int y)
{
	_texture = TextureManager::LoadTexture(textureFile);

	_xpos = x;
	_ypos = y;
}

void Object::update()
{
	_xpos++;
	_ypos++;

	_srcRect.h = 64;
	_srcRect.w = 64;
	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.h = _srcRect.h * 2;
	_destRect.w = _srcRect.w * 2;
	_destRect.x = _xpos;
	_destRect.y = _ypos;
}

void Object::render()
{
	SDL_RenderCopy(Game::renderer, _texture, &_srcRect, &_destRect);
}