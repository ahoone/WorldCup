#include "Collision.hpp"
#include "ECS/Entity.hpp"

bool Collision::AABB(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	if(
		rect1.x + rect1.w >= rect2.x &&
		rect2.x + rect2.w >= rect1.x &&
		rect1.y + rect1.h >= rect2.y &&
		rect2.y + rect2.h >= rect1.y
		)
	{
		return true;
	}

	return false;

}

bool Collision::AABB(const ColliderComponent& col1, const ColliderComponent& col2)
{
	if(AABB(col1.collider, col2.collider))
	{
		std::cout << col1.tag;
		std::cout << "hit: ";
		std::cout << col2.tag << std::endl;
		return true;
	}

	return false;
}