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
		Rectangle(Point topLeft, int width, int height, bool fill, ARGB_Color color);
		Rectangle(Point topLeft, int width, int height, bool fill, int thickness, ARGB_Color color);
		virtual ~Rectangle();

		virtual void 	Render(color32_t* backBuffer, int width, int height) override;

		void 			SetColor(ARGB_Color color) { m_color = color; m_borderLine->SetColor(color); }
		ARGB_Color 		GetColor() { return m_color; }

		void			SetThickness(int thickness) { m_thickness = thickness; }
		int				GetThickness() { return m_thickness; }

		void			SetTopLeft(Point topLeft) { m_topLeft = topLeft; }

	private:
		// Properties
		int			m_height;
		int			m_width;
		bool		m_fill;
		int			m_thickness;
		Point		m_topLeft;
		Line*		m_borderLine;
		ARGB_Color	m_color;
	};

}
#endif			// #define _RECTANGLE_H

