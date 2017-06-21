// Point.cpp
// Implementation file for the Point class
//
// Copyright Fishbowl Digital 2017
//

#include "Point.h"

// Constructor
Point::Point()
{
	X = 0;
	Y = 0;
}

Point::Point(int x, int y)
{
	X = x;
	Y = y;
}

// Copy constructor
Point::Point(Point& point)
{
	X = point.X;
	Y = point.Y;
}

// Operator overloads
Point Point::operator=(const Point& point)
{
	X = point.X;
	Y = point.Y;

	return *this;
}

