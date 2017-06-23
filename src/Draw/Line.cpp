// Line.cpp
// Implementation file for the Line class
//
// Copyright Fishbowl Digital 2017
//

#include "Line.h"
#include "Macros.h"
#include <math.h>

// Constructor
Line::Line(Point p1, Point p2, BGRA_Color lineColor)
{
	m_p1 = p1;
	m_p2 = p2;
	m_lineColor = lineColor;
}

/* Copy constructor
Line::Line(Line& line)
{
	m_p1 = Line.p1;
	m_p2 = Line.p2;
}

// Operator overloads
/*
Point Point::operator=(const Point& point)
{
	X = point.X;
	Y = point.Y;

	return *this;
}
*/

void Line::Render(color32_t* backBuffer, int width, int height)
{
	/* Vertical line? */
	if (m_p1.X == m_p2.X)
	{
		int yStart = m_p2.Y > m_p1.Y ? m_p1.Y : m_p2.Y;
		int yEnd = m_p2.Y > m_p1.Y ? m_p2.Y : m_p1.Y;

		for (int iY = yStart; iY <= yEnd; iY++)
		{
			backBuffer[(iY * width) + m_p1.X] = BGRAColorToU32(m_lineColor);
		}
	}
	else
	{
		/* floating point for now */
		float m = ((float)(m_p2.Y - m_p1.Y)) / ((float)(m_p2.X - m_p1.X));
		float b = m_p1.Y - (m * m_p1.X);
		int barHeight = (int)fmax(abs(m), 1);

		int xStart = m_p2.X > m_p1.X ? m_p1.X : m_p2.X;
		int xEnd = m_p2.X > m_p1.X ? m_p2.X : m_p1.X;

		for (int iX = xStart; iX <= xEnd; iX++)
		{
			//calculate the slope
			int iY = ((m * iX) + b);

			//}
			if (m > 0)
			{
				for (int iYBar = (barHeight-1); iYBar >= 0; iYBar--)
				{
					int iYCur = iY + iYBar;
					if (iYCur >= 0 && iYCur < height)
					{
						backBuffer[(iYCur * width) + iX] = BGRAColorToU32(m_lineColor);
					}
				}
			}
			else
			{
				for (int iYBar = 0; iYBar < barHeight; iYBar++)
				{
					int iYCur = iY + iYBar;
					if (iYCur >= 0 && iYCur < height)
					{
						backBuffer[(iYCur * width) + iX] = BGRAColorToU32(m_lineColor);
					}
				}
			}
			//backBuffer[(iY * width) + iX] = BGRAColorToU32(m_lineColor);
		}
	}
}
