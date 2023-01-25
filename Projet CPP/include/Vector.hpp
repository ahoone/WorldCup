#pragma once

#include <iostream>

class Vector
{

public:
	Vector();
	Vector(float x, float y);

	float x() {return _x; }
	float y() {return _y; }

	void x(float x) {_x = x; }
	void y(float y) {_y = y; }

	void x(int x) {_x = x; }
	void y(int y) {_y = y; }

	Vector& Factor(const int i);
	Vector& Factor(const float f);

	Vector& Add(const Vector& vector);
	Vector& Sub(const Vector& vector);
	Vector& Mul(const Vector& vector);
	Vector& Div(const Vector& vector);

	friend Vector& operator+(Vector& vector1, const Vector& vector2);
	friend Vector& operator-(Vector& vector1, const Vector& vector2);
	friend Vector& operator*(Vector& vector1, const Vector& vector2);
	friend Vector& operator/(Vector& vector1, const Vector& vector2);

	Vector& operator+=(const Vector& vector);
	Vector& operator-=(const Vector& vector);
	Vector& operator*=(const Vector& vector);
	Vector& operator/=(const Vector& vector);

	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);

private:
	float _x, _y;

};