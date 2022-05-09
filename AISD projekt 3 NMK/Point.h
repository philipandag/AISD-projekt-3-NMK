#pragma once

class Point
{
public:
	int x, y;
	Point();
	Point(int x, int y);
	Point& operator+=(Point&& other);
	Point& operator+=(const Point& other);
	Point& operator-=(Point&& other);
	Point& operator-=(const Point& other);
	Point operator+(const Point& other);
	Point operator-(const Point& other);
	Point operator*(int multiplier);
	bool operator==(const Point& other);
};

