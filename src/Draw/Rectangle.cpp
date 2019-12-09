// Rectangle.cpp
// Implementation file for the Rectangle class
//
// Copyright Fishbowl Digital 2017
//

#include "Rectangle.h"
#include "Macros.h"

namespace FBDraw
{
	// Constructor
	Rectangle::Rectangle(Point topLeft, int width, int height, bool fill, ARGB_Color color)
	{
		m_width = width;
		m_height = height;
		m_topLeft = topLeft;
		m_fill = fill;
		m_thickness = 0;
		m_color = color;

		m_borderLine = new Line(m_topLeft, m_topLeft, color, m_thickness);

		// Default is Visible
		Visible = true;
	}

	Rectangle::Rectangle(Point topLeft, int width, int height, bool fill, int thickness, ARGB_Color color)
	{
		m_width = width;
		m_height = height;
		m_topLeft = topLeft;
		m_fill = fill;
		m_thickness = thickness;
		m_color = color;

		m_borderLine = new Line(m_topLeft, m_topLeft, color, m_thickness);

		// Default is Visible
		Visible = true;
	}
	
	Rectangle::~Rectangle()
	{
		delete m_borderLine;
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
		else
		{
			//Left
			m_borderLine->SetPoint1(m_topLeft);
			m_borderLine->SetPoint2(m_topLeft.X, yEnd);
			m_borderLine->Render(backBuffer, width, height);

			//Bottom
			m_borderLine->SetPoint1(m_topLeft.X, yEnd);
			m_borderLine->SetPoint2(xEnd, yEnd);
			m_borderLine->Render(backBuffer, width, height);

			//Right
			m_borderLine->SetPoint1(xEnd, yEnd);
			m_borderLine->SetPoint2(xEnd, m_topLeft.Y);
			m_borderLine->Render(backBuffer, width, height);

			//Top
			m_borderLine->SetPoint1(xEnd, m_topLeft.Y);
			m_borderLine->SetPoint2(m_topLeft);
			m_borderLine->Render(backBuffer, width, height);
		}
	}
}
