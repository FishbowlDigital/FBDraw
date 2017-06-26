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
	m_thickness = 0; //Minimum thickness
	m_lineColor = lineColor;
}

Line::Line(Point p1, Point p2, BGRA_Color lineColor, int thickness) : Line(p1, p2, lineColor)
{
	m_thickness = thickness;
}

Point Line::GetPoint1()
{
	return m_p1;
}

Point Line::GetPoint2()
{
	return m_p2;
}

BGRA_Color Line::GetColor()
{
	return m_lineColor;
}

int Line::GetThickness()
{
	return m_thickness;
}

void Line::SetPoint1(Point p1)
{
	m_p1 = p1;
}

void Line::SetPoint2(Point p2)
{
	m_p2 = p2;
}

void Line::SetColor(BGRA_Color Color)
{
	m_lineColor = Color;
}

void Line::SetThickness(int thickness)
{
	m_thickness = thickness;
}

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
		float fBarHeight = fmax(abs(m), 1);
		int iBarHeight = ((int)fBarHeight);
		float fbhRem = fBarHeight - iBarHeight;	// floating pt bar height remainder

		int xStart = m_p2.X > m_p1.X ? m_p1.X : m_p2.X;
		int xEnd = m_p2.X > m_p1.X ? m_p2.X : m_p1.X;

		float fbhRemAccum = 0;
		for (int iX = xStart; iX <= xEnd; iX++)
		{
			//calculate the slope
			int iY = (int) ((m * iX) + b);
			int iY2 = (int) ((m * (iX + 1)) + b);
			int barHeight = (abs(iY2 - iY)) + m_thickness;
			if (barHeight < 1) { barHeight = 1; }

			fbhRemAccum += fbhRem;	// Increment remainder
			//int barHeight = iBarHeight + ((int)fbhRemAccum);
			if (m > 0)
			{
				for (int iYBar = barHeight-1; iYBar >= 0; iYBar--)
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
					int iYCur = iY - iYBar;
					if (iYCur >= 0 && iYCur < height)
					{
						backBuffer[(iYCur * width) + iX] = BGRAColorToU32(m_lineColor);
					}
				}
			}
			
			// Increment accumulator with remainder portion of bar height
			fbhRemAccum -= ((int)fbhRemAccum);
		}
	}
}

//void Line::Render(color32_t* backBuffer, int width, int height)
//{
//	/* Vertical line? */
//	if (m_p1.X == m_p2.X)
//	{
//		int yStart = m_p2.Y > m_p1.Y ? m_p1.Y : m_p2.Y;
//		int yEnd = m_p2.Y > m_p1.Y ? m_p2.Y : m_p1.Y;
//
//		for (int iY = yStart; iY <= yEnd; iY++)
//		{
//			backBuffer[(iY * width) + m_p1.X] = BGRAColorToU32(m_lineColor);
//		}
//	}
//	else
//	{
//		/* floating point for now */
//		float m = ((float)(m_p2.Y - m_p1.Y)) / ((float)(m_p2.X - m_p1.X));
//		float b = m_p1.Y - (m * m_p1.X);
//		float fBarHeight = fmax(abs(m), 1);
//		int iBarHeight = ((int)fBarHeight);
//		float fbhRem = fBarHeight - iBarHeight;	// floating pt bar height remainder
//
//		int xStart = m_p2.X > m_p1.X ? m_p1.X : m_p2.X;
//		int xEnd = m_p2.X > m_p1.X ? m_p2.X : m_p1.X;
//
//		float fbhRemAccum = 0;
//		for (int iX = xStart; iX <= xEnd; iX++)
//		{
//			//calculate the slope
//			int iY = (int)((m * iX) + b);
//			int iY2 = (int)((m * (iX + 1)) + b);
//			int barHeight = abs(iY2 - iY);
//			if (barHeight < 1) { barHeight = 1; }
//
//			fbhRemAccum += fbhRem;	// Increment remainder
//			//int barHeight = iBarHeight + ((int)fbhRemAccum);
//			if (m > 0)
//			{
//				for (int iYBar = barHeight - 1; iYBar >= 0; iYBar--)
//				{
//					int iYCur = iY + iYBar;
//					if (iYCur >= 0 && iYCur < height)
//					{
//						backBuffer[(iYCur * width) + iX] = BGRAColorToU32(m_lineColor);
//					}
//				}
//			}
//			else
//			{
//				for (int iYBar = 0; iYBar < barHeight; iYBar++)
//				{
//					int iYCur = iY - iYBar;
//					if (iYCur >= 0 && iYCur < height)
//					{
//						backBuffer[(iYCur * width) + iX] = BGRAColorToU32(m_lineColor);
//					}
//				}
//			}
//
//			// Increment accumulator with remainder portion of bar height
//			fbhRemAccum -= ((int)fbhRemAccum);
//		}
//	}
//}