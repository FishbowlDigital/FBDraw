// Line.cpp
// Implementation file for the Point class
//
// Copyright Fishbowl Digital 2017
//

#include "Rectangle.h"
#include "Macros.h"

// Constructor
Rectangle::Rectangle(int h, int w, BGRA_Color color)
{
	r_height = h;
	r_width = w;
	r_Color = color;
}

/*
void Rectangle::Render(color32_t* backBuffer, int width, int height)
{
	if (m_p1.X == m_p2.X)
	{
		int yStart = m_p2.Y > m_p1.Y ? m_p1.Y : m_p2.Y;
		int yEnd = m_p2.Y > m_p1.Y ? m_p2.Y : m_p1.Y;

		for (int iY = yStart; iY <= yEnd; iY++)
		{
			backBuffer[(iY * width) + m_p1.X] = BGRAColorToU32(r_Color);
		}
	}
	else
	{

		float m = ((float)(m_p2.Y - m_p1.Y)) / ((float)(m_p2.X - m_p1.X));
		float b = m_p1.Y - (m * m_p1.X);

		int xStart = m_p2.X > m_p1.X ? m_p1.X : m_p2.X;
		int xEnd = m_p2.X > m_p1.X ? m_p2.X : m_p1.X;

		for (int iX = xStart; iX <= xEnd; iX++)
		{
			int iY = ((m*iX) + b);
			backBuffer[(iY * width) + iX] = BGRAColorToU32(r_Color);
		}
	}
}
*/