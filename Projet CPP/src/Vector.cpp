#include "Vector.hpp"

Vector::Vector()
{
	_x = 0.0;
	_y = 0.0; 
}

Vector::Vector(float x, float y)
{
	_x = x;
	_y = y;
}

Vector& Vector::Factor(const int i)
{
	_x *= (float)i;
	_y *= (float)i;

	return *this;
}

Vector& Vector::Factor(const float f)
{
	_x *= f;
	_y *= f;

	return *this;
}

Vector& Vector::Add(const Vector& vector)
{
	_x += vector._x;
	_y += vector._y;

	return *this;
}

Vector& Vector::Sub(const Vector& vector)
{
	_x -= vector._x;
	_y -= vector._y;

	return *this;
}

Vector& Vector::Mul(const Vector& vector)
{
	_x *= vector._x;
	_y *= vector._y;

	return *this;
}

Vector& Vector::Div(const Vector& vector)
{
	_x /= vector._x;
	_y /= vector._y;

	return *this;
}

Vector& operator+(Vector& vector1, const Vector& vector2)
{
	return vector1.Add(vector2);
}

Vector& operator-(Vector& vector1, const Vector& vector2)
{
	return vector1.Sub(vector2);
}

Vector& operator*(Vector& vector1, const Vector& vector2)
{
	return vector1.Mul(vector2);
}

Vector& operator/(Vector& vector1, const Vector& vector2)
{
	return vector1.Div(vector2);
}

Vector& Vector::operator+=(const Vector& vector)
{
	return this->Add(vector);
}

Vector& Vector::operator-=(const Vector& vector)
{
	return this->Sub(vector);
}

Vector& Vector::operator*=(const Vector& vector)
{
	return this->Mul(vector);
}

Vector& Vector::operator/=(const Vector& vector)
{
	return this->Div(vector);
}

std::ostream& operator<<(std::ostream& stream, const Vector& vector)
{
	stream << "(" ;
	stream << vector._x;
	stream << ", ";
	stream << vector._y;
	stream << ")";
	return stream;
}