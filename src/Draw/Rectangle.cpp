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
	Rectangle::Rectangle(Point topLeft, int width, int height, bool fill, BGRA_Color color)
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

	Rectangle::Rectangle(Point topLeft, int width, int height, bool fill, int thickness, BGRA_Color color)
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
		BGRA_Bytes backColor, mixColor;
		int xEnd = m_topLeft.X + m_width;
		int yEnd = m_topLeft.Y + m_height;

		if (m_fill)
		{
			for (int iY = m_topLeft.Y; iY < yEnd; iY++)
			{
				for (int iX = m_topLeft.X; iX < xEnd; iX++)
				{
					/*backBuffer[(iY * width) + iX] = BGRAColorToU32(m_color);*/

					int iBack = (iY * width) + iX;
					backColor.U32 = backBuffer[iBack];
					mixColor.Color.Red = AlphaMix8(backColor.Color.Red, m_color.Red, m_color.Alpha);
					mixColor.Color.Green = AlphaMix8(backColor.Color.Green, m_color.Green, m_color.Alpha);
					mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, m_color.Blue, m_color.Alpha);

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
