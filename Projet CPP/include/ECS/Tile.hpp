#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Entity.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"

//Composante de base de la map
//On les mets dans un groupe particulier
class TileComponent : public Component
{

public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Rect tile;
	int tileID;
	std::string path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tile.x = x;
		tile.y = y;
		tile.w = w;
		tile.h = h;
		tileID = id;

		switch(tileID)
		{
		case 0:
			path = "../assets/concrete.bmp";
			break;
		case 1:
			path = "../assets/dirt.bmp";
			break;
		case 2:
			path = "../assets/grass.bmp";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tile.x, (float)tile.y, (float)tile.w, (float)tile.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		const char* buff = path.c_str();
		
		entity->addComponent<SpriteComponent>(buff);
		sprite = &entity->getComponent<SpriteComponent>();
	}


private:



};