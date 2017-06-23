// Rectangle.cpp
// Implementation file for the Rectangle class
//
// Copyright Fishbowl Digital 2017
//

#include "Rectangle.h"
#include "Macros.h"


// Constructor
Rectangle::Rectangle(int h, int w, Point p, BGRA_Color color)
{
	r_height = h;
	r_width = w;
	r_startPoint = p;
	r_Color = color;
}

void Rectangle::Render(color32_t* backBuffer, int width, int height)
{
	int xEnd = r_startPoint.X + r_width;
	int yEnd = r_startPoint.Y + r_height;

	for (int iY = r_startPoint.Y; iY<yEnd; iY++)
	{
		for (int iX = r_startPoint.X; iX<xEnd; iX++)
		{
			backBuffer[(iY * width) + iX] = BGRAColorToU32(r_Color);
			//backBuffer[iY] = BGRAColorToU32(r_Color);
		}
	}
}