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
	Rectangle::Rectangle(int h, int w, Point startPoint, bool fill, BGRA_Color color)
	{
		m_height = h;
		m_width = w;
		m_startPoint = startPoint;
		m_fill = fill;
		m_thickness = 0;
		m_color = color;

		m_borderLine = new Line(m_startPoint, m_startPoint, color, m_thickness);

		// Default is Visible
		Visible = true;
	}

	Rectangle::Rectangle(int h, int w, Point startPoint, bool fill, int thickness, BGRA_Color color)
	{
		m_height = h;
		m_width = w;
		m_startPoint = startPoint;
		m_fill = fill;
		m_thickness = thickness;
		m_color = color;

		m_borderLine = new Line(m_startPoint, m_startPoint, color, m_thickness);

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
		int xEnd = m_startPoint.X + m_width;
		int yEnd = m_startPoint.Y + m_height;

		if (m_fill)
		{
			for (int iY = m_startPoint.Y; iY < yEnd; iY++)
			{
				for (int iX = m_startPoint.X; iX < xEnd; iX++)
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
			m_borderLine->SetPoint1(m_startPoint);
			m_borderLine->SetPoint2(m_startPoint.X, yEnd);
			m_borderLine->Render(backBuffer, width, height);

			//Bottom
			m_borderLine->SetPoint1(m_startPoint.X, yEnd);
			m_borderLine->SetPoint2(xEnd, yEnd);
			m_borderLine->Render(backBuffer, width, height);

			//Right
			m_borderLine->SetPoint1(xEnd, yEnd);
			m_borderLine->SetPoint2(xEnd, m_startPoint.Y);
			m_borderLine->Render(backBuffer, width, height);

			//Top
			m_borderLine->SetPoint1(xEnd, m_startPoint.Y);
			m_borderLine->SetPoint2(m_startPoint);
			m_borderLine->Render(backBuffer, width, height);
		}
	}
}
