// Rectangle.h
// Header file for the Rectangle class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "IDrawable.h"
#include "Line.h"
#include "Types.h"
#include "Point.h"

namespace FBDraw
{
	class Rectangle : public IDrawable
	{
	public:
		Rectangle(int h, int w, Point startPoint, bool fill, BGRA_Color color);
		Rectangle(int h, int w, Point startPoint, bool fill, int thickness, BGRA_Color color);
		~Rectangle();

		virtual void Render(color32_t* backBuffer, int width, int height);

	private:
		// Properties
		int			m_height;
		int			m_width;
		bool		m_fill;
		int			m_thickness;
		Point		m_startPoint;
		Line*		m_borderLine;
		BGRA_Color	m_color;
	};

}
#endif			// #define _RECTANGLE_H

