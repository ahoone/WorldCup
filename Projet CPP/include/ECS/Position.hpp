#pragma once

#include "Entity.hpp"

class PositionComponent : public Component
{

public:

	PositionComponent() {setPos(0, 0); }
	PositionComponent(int x, int y) {setPos(x, y); }

	int x() {return _xpos; }
	int y() {return _ypos; }

	void x(int x) {_xpos = x; }
	void y(int y) {_ypos = y; }

	void setPos(int x, int y)
	{
		_xpos = x;
		_ypos = y;
	}

	void update() override
	{
		_xpos++;
		_ypos++;
	}

private:
	int _xpos = 0;
	int _ypos = 0;


};