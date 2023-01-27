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

Vector& Vector::operator=(const Vector& vector)
{
	_x = vector._x;
	_y = vector._y;

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

Vector& Vector::operator*(const float& i)
{
	_x = static_cast<int>(_x * i);
	_y = static_cast<int>(_y * i);

	return *this;
}

Vector& Vector::operator*(const int& i)
{
	_x *= i;
	_y *= i;

	return *this;
}

Vector& Vector::Zero()
{
	_x = 0;
	_y = 0;

	return *this;
}

Vector& Vector::OpposeX()
{
	_x = -_x;

	return *this;
}

Vector& Vector::OpposeY()
{
	_y = -_y;

	return *this;
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