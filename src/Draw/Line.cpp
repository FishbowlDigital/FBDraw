// Line.cpp
// Implementation file for the Line class
//
// Copyright Fishbowl Digital 2017
//

#include "Line.h"
#include "Macros.h"
#include <math.h>

namespace FBDraw
{

	// Constructor
	Line::Line(Point p1, Point p2, ARGB_Color lineColor)
	{
		m_p1 = p1;
		m_p2 = p2;
		m_thickness = 0; //Minimum thickness
		m_lineColor = lineColor;

		// Default is Visible
		Visible = true;
	}

	Line::Line(Point p1, Point p2, ARGB_Color lineColor, int thickness) 
	{
		m_p1 = p1;
		m_p2 = p2;
		m_thickness = thickness; //Minimum thickness
		m_lineColor = lineColor;

		// Default is Visible
		Visible = true;
	}

	Line::Line(int x1, int y1, int x2, int y2, ARGB_Color lineColor)
	{
		m_p1 = Point(x1, y1);
		m_p2 = Point(x2, y2);
		m_thickness = 0; //Minimum thickness
		m_lineColor = lineColor;

		// Default is Visible
		Visible = true;
	}

	Line::Line(int x1, int y1, int x2, int y2, ARGB_Color lineColor, int thickness)
	{
		m_p1 = Point(x1, y1);
		m_p2 = Point(x2, y2);
		m_thickness = thickness; //Minimum thickness
		m_lineColor = lineColor;

		// Default is Visible
		Visible = true;
	}

	Point Line::GetPoint1()
	{
		return m_p1;
	}

	Point Line::GetPoint2()
	{
		return m_p2;
	}

	ARGB_Color Line::GetColor()
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

	void Line::SetPoint1(int x, int y)
	{
		m_p1.X = x;
		m_p1.Y = y;
	}

	void Line::SetPoint2(Point p2)
	{
		m_p2 = p2;
	}

	void Line::SetPoint2(int x, int y)
	{
		m_p2.X = x;
		m_p2.Y = y;
	}

	void Line::SetLocation(Point pt1, Point pt2)
	{
		m_p1 = pt1;
		m_p2 = pt2;
	}

	void Line::SetColor(ARGB_Color Color)
	{
		m_lineColor = Color;
	}

	void Line::SetThickness(int thickness)
	{
		m_thickness = thickness;
	}

	void Line::Render(color32_t* backBuffer, int width, int height)
	{
		ARGB_Bytes backColor, mixColor;

		if (m_p1.X == m_p2.X) /* Vertical line */
		{
			/* No thickness for vertical line! */

			int yStart = m_p2.Y > m_p1.Y ? m_p1.Y : m_p2.Y;
			int yEnd = m_p2.Y > m_p1.Y ? m_p2.Y : m_p1.Y;

			for (int iY = yStart; iY <= yEnd; iY++)
			{
				//backBuffer[(iY * width) + m_p1.X] = BGRAColorToU32(m_lineColor);
				int iBack = (iY * width) + m_p1.X;
				backColor.U32 = backBuffer[iBack];
				mixColor.Color.Red = AlphaMix8(backColor.Color.Red, m_lineColor.Red, m_lineColor.Alpha);
				mixColor.Color.Green = AlphaMix8(backColor.Color.Green, m_lineColor.Green, m_lineColor.Alpha);
				mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, m_lineColor.Blue, m_lineColor.Alpha);

				backBuffer[iBack] = mixColor.U32; //BGRAColorToU32(mixColor.Color);
			}
		}
		else /* Sloped Line and Horizontal line */
		{
			/* floating point for now */
			float m = ((float)(m_p2.Y - m_p1.Y)) / ((float)(m_p2.X - m_p1.X));
			float b = m_p1.Y - (m * m_p1.X);
			float fBarHeight = (float)fmax(fabs(m), 1.0f);
			int iBarHeight = ((int)fBarHeight);
			float fbhRem = fBarHeight - iBarHeight;	// floating pt bar height remainder

			int xStart = m_p2.X > m_p1.X ? m_p1.X : m_p2.X;
			int xEnd = m_p2.X > m_p1.X ? m_p2.X : m_p1.X;

			float fbhRemAccum = 0;
			for (int iX = xStart; iX <= xEnd; iX++)
			{
				// Calculate the slope
				int iY = (int)((m * iX) + b);

				int iY2 = (int)((m * (iX + 1)) + b);
				int barHeight = (fabs(iY2 - iY)) + m_thickness;
				if (barHeight < 1) { barHeight = 1; }

				fbhRemAccum += fbhRem;	// Increment remainder

				if (fabs(m) > 0) /* Sloped Line */
				{
					for (int iYBar = barHeight - 1; iYBar >= 0; iYBar--)
					{
						int iYCur = iY + iYBar;
						if (iYCur >= 0 && iYCur < height)
						{
							//backBuffer[(iYCur * width) + iX] = BGRAColorToU32(m_lineColor);

							int iBack = (iYCur * width) + iX;
							backColor.U32 = backBuffer[iBack];
							mixColor.Color.Red = AlphaMix8(backColor.Color.Red, m_lineColor.Red, m_lineColor.Alpha);
							mixColor.Color.Green = AlphaMix8(backColor.Color.Green, m_lineColor.Green, m_lineColor.Alpha);
							mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, m_lineColor.Blue, m_lineColor.Alpha);

							backBuffer[iBack] = mixColor.U32;
						}
					}
				}
				else /* Horizontal Line */
				{
					for (int iYBar = 0; iYBar < barHeight; iYBar++)
					{
						int iYCur = iY - iYBar;
						if (iYCur >= 0 && iYCur < height)
						{
							//backBuffer[(iYCur * width) + iX] = BGRAColorToU32(m_lineColor);

							int iBack = (iYCur * width) + iX;
							backColor.U32 = backBuffer[iBack];
							mixColor.Color.Red = AlphaMix8(backColor.Color.Red, m_lineColor.Red, m_lineColor.Alpha);
							mixColor.Color.Green = AlphaMix8(backColor.Color.Green, m_lineColor.Green, m_lineColor.Alpha);
							mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, m_lineColor.Blue, m_lineColor.Alpha);

							backBuffer[iBack] = mixColor.U32;
						}
					}
				}

				// Increment accumulator with remainder portion of bar height
				fbhRemAccum -= ((int)fbhRemAccum);
			}
		}
	}
}
