#include "Point.h"

Point::Point(int x, int y) :
	x(x), y(y)
{}
Point::Point() :
	x(0), y(0)
{}

Point& Point::operator+=(Point&& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Point& Point::operator-=(Point&& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Point& Point::operator+=(const Point& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Point& Point::operator-=(const Point& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Point Point::operator+(const Point& other)
{
	return Point(this->x + other.x, this->y + other.y);
}

Point Point::operator-(const Point& other)
{
	return Point(this->x - other.x, this->y - other.y);
}

Point Point::operator*(int multiplier)
{
	return Point(this->x * multiplier, this->y * multiplier);
}

bool Point::operator==(const Point& other)
{
	return this->x == other.x && this->y == other.y;
}