#pragma once

#include "Entity.hpp"
#include "../Vector.hpp"

class TransformComponent : public Component
{

public:

	Vector position;

	TransformComponent() {setPos(0, 0); }
	TransformComponent(float x, float y) {setPos(x, y); }
	TransformComponent(int x, int y) {setPos(x, y); }

	float x() {return position.x(); }
	float y() {return position.y(); }

	void x(float x) {position.x(x); }
	void y(float y) {position.y(y); }

	void x(int x) {position.x(x); }
	void y(int y) {position.y(y); }

	void setPos(float x, float y)
	{
		position.x(x);
		position.y(y);
	}

	void setPos(int x, int y)
	{
		position.x(x);
		position.y(y);
	}

	void update() override
	{
		position.Add(Vector(1,1));
	}

private:

};