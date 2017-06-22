// Rectangle.h
// Header file for the Rectangle class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _RECTANGLE_H
#define _RECTANGLE_H
#include "Types.h"
#include "Point.h"
#include "IDrawable.h"

class Rectangle : public IDrawable
{
	public:
	Rectangle(int h, int w, Point p, BGRA_Color color);

	virtual void Render(color32_t* backBuffer, int width, int height);

	private:
		// Properties
		int			r_height;
		int			r_width;
		Point		r_startPoint;
		BGRA_Color	r_Color;
};

#endif			// #define _POINT_H

