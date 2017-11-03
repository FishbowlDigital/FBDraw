// Point.h
// Header file for the Point class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _POINT_H
#define _POINT_H

namespace FBDraw
{

	class Point
	{
	public:
		// Constructor/Destructor
		Point();
		Point(int x, int y);
		Point(Point& point);

		// Operators
		Point operator=(const Point& point);

		// Properties
		int		X;
		int		Y;
	};

}

#endif			// #define _POINT_H

