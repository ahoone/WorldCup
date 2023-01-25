#pragma once

#include "Entity.hpp"
#include "../Vector.hpp"

class TransformComponent : public Component
{

public:

	Vector position;
	Vector velocity;

	int speed = 3;

	TransformComponent() {setPos(0, 0); }
	TransformComponent(float x, float y) {setPos(x, y); }
	TransformComponent(int x, int y) {setPos(x, y); }

	void update() override
	{
		//Not effective because apply mutliple times the speed to velocity
		//position = velocity.Factor(speed);

		position.x(position.x()+velocity.x()*speed);
		position.y(position.y()+velocity.y()*speed);
	}

//****************
//*** POSITION ***
//****************

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

//****************
//*** VELOCITY ***
//****************

	void init() override
	{
		velocity.x(0);
		velocity.y(0);
	}




private:

};