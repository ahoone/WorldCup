#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Components.hpp"
#include "Transform.hpp"

class ColliderComponent : public Component
{

public:

	SDL_Rect collider;
	std::string tag;
	TransformComponent* transform;

	ColliderComponent(std::string name) {tag = name; }

	void init() override
	{

		if(!entity->hasComponent<TransformComponent>())
			entity->addComponent<TransformComponent>();

		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x());
		collider.y = static_cast<int>(transform->position.y());
		collider.w = transform->width;
		collider.h = transform->height;
	}


private:

};