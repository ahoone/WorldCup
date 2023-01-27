#pragma once

#include "Entity.hpp"
#include "../Vector.hpp"

//Composante de base de toute entité
//Donne une position et une vitesse à
//l'entité.
class TransformComponent : public Component
{

public:

	Vector position;
	Vector velocity;

	int width = 32;
	int height = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() {position.Zero(); }
	TransformComponent(float x, float y) {setPos(x,y); }
	TransformComponent(int x, int y) {setPos(x,y); }
	TransformComponent(int s)
	{
		position.Zero();
		scale = s;
	}
	TransformComponent(float x, float y, int w, int h, int s)
	{
		setPos(x,y);
		width = w;
		height = h;
		scale = s;
	}

	void update() override
	{
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
		velocity.Zero();
	}




private:

};