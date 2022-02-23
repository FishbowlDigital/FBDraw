// Rectangle.cpp
// Implementation file for the Rectangle class
//
// Copyright Fishbowl Digital 2017
//

#include "Rectangle.h"
#include "Macros.h"

#include <math.h>

namespace FBDraw
{
	// Constructor
	Rectangle::Rectangle(Point topLeft, int width, int height, bool fill, ARGB_Color color) :
		Rectangle(topLeft.X, topLeft.Y, width, height, fill, 0, 0, color)
	{
	}

	Rectangle::Rectangle(Point topLeft, int width, int height, bool fill, int thickness, ARGB_Color color) :
		Rectangle(topLeft.X, topLeft.Y, width, height, fill, thickness, 0, color)
	{
	}

	Rectangle::Rectangle(Point topLeft, int width, int height, bool fill, int thickness, int radius, ARGB_Color color) :
		Rectangle(topLeft.X, topLeft.Y, width, height, fill, thickness, radius, color)
	{
	}

	Rectangle::Rectangle(int x, int y, int width, int height, bool fill, ARGB_Color color) :
		Rectangle(x, y, width, height, fill, 0, 0, color)
	{

	}

	Rectangle::Rectangle(int x, int y, int width, int height, bool fill, int thickness, ARGB_Color color) :
		Rectangle(x, y, width, height, fill, thickness, 0, color)
	{

	}

	Rectangle::Rectangle(int x, int y, int width, int height, bool fill, int thickness, int radius, ARGB_Color color)
	{
		m_width = width;
		m_height = height;
		m_topLeft = Point(x, y);
		m_fill = fill;
		m_thickness = thickness;
		m_radius = radius;
		m_color = color;

		m_borderLine = new Line(m_topLeft, m_topLeft, color, m_thickness);

		// Default is Visible
		Visible = true;
	}


	
	Rectangle::~Rectangle()
	{
		delete m_borderLine;
	}

	void Rectangle::SetRect(Point topLeft, int width, int height)
	{
		m_topLeft = topLeft;
		m_width = width;
		m_height = height;
	}

	void Rectangle::SetRect(int x, int y, int width, int height)
	{
		SetRect(Point(x, y), width, height);
	}


	void Rectangle::Render(color32_t* backBuffer, int width, int height)
	{
		ARGB_Bytes backColor, mixColor;
		int xStart = m_topLeft.X;
		int yStart = m_topLeft.Y;
		int xEnd = m_topLeft.X + m_width;
		int yEnd = m_topLeft.Y + m_height;

		// Bounds checks
		if (xStart < 0)
			xStart = 0;
		else if (xStart >= width)
			return;

		if (yStart < 0)
			yStart = 0;
		else if (yStart >= height)
			return;

		if (xEnd >= width)
			xEnd = width-1;
		else if (xEnd < 0)
			return;

		if (yEnd >= height)
			yEnd = height-1;
		else if (yEnd < 0)
			return;

		if (m_fill)
		{
			mixColor.U32 = 0;
			for (int iY = yStart; iY < yEnd; iY++)
			{
				for (int iX = xStart; iX < xEnd; iX++)
				{
					/*backBuffer[(iY * width) + iX] = BGRAColorToU32(m_color);*/

					if (CheckBounds(iX, iY))
					{
						int iBack = (iY * width) + iX;
						backColor.U32 = backBuffer[iBack];
						mixColor.Color.Red = AlphaMix8(backColor.Color.Red, m_color.Red, m_color.Alpha);
						mixColor.Color.Green = AlphaMix8(backColor.Color.Green, m_color.Green, m_color.Alpha);
						mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, m_color.Blue, m_color.Alpha);
						mixColor.Color.Alpha = m_color.Alpha;

						backBuffer[iBack] = mixColor.U32;
					}
				}
			}
		}
		else
		{
			// FIX! - no bounds checking, need to do this in draw line

			//Left
			m_borderLine->SetPoint1(m_topLeft.X, m_topLeft.Y+m_radius);
			m_borderLine->SetPoint2(m_topLeft.X, m_topLeft.Y + m_height - m_radius);
			m_borderLine->Render(backBuffer, width, height);

			//Bottom
			m_borderLine->SetPoint1(m_topLeft.X + m_radius, m_topLeft.Y+m_height);
			m_borderLine->SetPoint2(m_topLeft.X + m_width - m_radius, m_topLeft.Y + m_height);
			m_borderLine->Render(backBuffer, width, height);

			//Right
			m_borderLine->SetPoint1(m_topLeft.X + m_width, m_topLeft.Y + m_radius);
			m_borderLine->SetPoint2(m_topLeft.X + m_width, m_topLeft.Y + m_height - m_radius);
			m_borderLine->Render(backBuffer, width, height);

			//Top
			m_borderLine->SetPoint1(m_topLeft.X + m_radius, m_topLeft.Y);
			m_borderLine->SetPoint2(m_topLeft.X + m_width - m_radius, m_topLeft.Y);
			m_borderLine->Render(backBuffer, width, height);

			// TO DO!
			// Draw arc on four corners
			if (m_radius > 0)
			{

			}
		}
	}

	bool Rectangle::CheckBounds(int x, int y)
	{
		int xLeft = m_topLeft.X;
		int xRight = m_topLeft.X + +m_width;
		int yTop = m_topLeft.Y;
		int yBottom = m_topLeft.Y + m_height;

		Point pt(x, y);

		if ((x > (xLeft + m_radius) && x < (xRight - m_radius)) ||		// Covers everything except the four corners
			(y > (yTop + m_radius) && y < (yBottom - m_radius)))
		{
			return true;
		}
		else if ((x >= xLeft && x <= (xLeft + m_radius)) &&						// Top Left
				 (y >= yTop && y <= (yTop + m_radius)))
		{
			Point ptCenter = { xLeft + m_radius, yTop + m_radius };
			if (Distance(pt, ptCenter) <= m_radius)
				return true;
		}
		else if ((x >= (xRight-m_radius) && x <= xRight) &&						// Top Right
				 (y >= yTop && y <= (yTop + m_radius)))
		{
			Point ptCenter = { xRight - m_radius, yTop + m_radius };
			if (Distance(pt, ptCenter) <= m_radius)
				return true;
		}
		else if ((x >= xLeft && x <= (xLeft + m_radius)) &&						// Bottom Left
			(y >= (yBottom - m_radius) && y <= yBottom))
		{
			Point ptCenter = { xLeft + m_radius, yBottom - m_radius };
			if (Distance(pt, ptCenter) <= m_radius)
				return true;
		}
		else if ((x >= (xRight - m_radius) && x <= xRight) &&					// Bottom Right
			(y >= (yBottom - m_radius) && y <= yBottom))
		{
			Point ptCenter = { xRight - m_radius, yBottom - m_radius };
			if (Distance(pt, ptCenter) <= m_radius)
				return true;
		}


		//for (int iPt = 0; iPt < numPts; iPt++)
		//{
		//	Point pt = pts[iPt];

		//	int xVect = x - pt.X;
		//	int yVect = y - pt.Y;

		//	if (sqrt(xVect * xVect + yVect * yVect) > m_radius)
		//		return false;
		//}

		// Assume no
		return false;
	}

	float Rectangle::Distance(Point pt1, Point pt2)
	{
		int xVect = pt1.X - pt2.X;
		int yVect = pt1.Y - pt2.Y;

		return (float) sqrt(xVect * xVect + yVect * yVect);
	}

}
