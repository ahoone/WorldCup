#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ECS/Collider.hpp"

class ColliderComponent;

//Donne accès à une méthode pour
//vérifier que deux objets se touchent
//ou non.
class Collision
{

public:

	static bool AABB(const SDL_Rect& rect1, const SDL_Rect& rect2);
	static bool AABB(const ColliderComponent& col1, const ColliderComponent& col2);

private:


};