// Rectangle.h
// Header file for the Rectangle class
//
// Copyright(c) 2017 - 2022 Fishbowl Digital LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
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
		Rectangle(Point topLeft, int width, int height, bool fill, int thickness, int radius, ARGB_Color color);
		Rectangle(int x, int y, int width, int height, bool fill, ARGB_Color color);
		Rectangle(int x, int y, int width, int height, bool fill, int thickness, ARGB_Color color);
		Rectangle(int x, int y, int width, int height, bool fill, int thickness, int radius, ARGB_Color color);
		virtual ~Rectangle();

		virtual void 	Render(color32_t* backBuffer, int width, int height) override;

		virtual bool	HitTest(int x, int y)
		{
			return CheckBounds(x, y);
		};

		void 			SetColor(ARGB_Color color) { m_color = color; m_borderLine->SetColor(color); }
		ARGB_Color 		GetColor() { return m_color; }
		
		void			SetThickness(int thickness) { m_thickness = thickness; }
		int				GetThickness() { return m_thickness; }
		Point			GetTopLeft() { return m_topLeft; }
		int				GetWidth() { return m_width; }
		int				GetHeight() { return m_height; }

		void			SetTopLeft(Point topLeft) { m_topLeft = topLeft; }
		void			SetRect(Point topLeft, int width, int height);
		void			SetRect(int x, int y, int width, int height);

	protected:
		bool			CheckBounds(int x, int y);

		float			Distance(Point pt1, Point pt2);

	protected:

		// Properties
		int			m_height;
		int			m_width;
		bool		m_fill;
		int			m_thickness;
		int			m_radius;
		Point		m_topLeft;
		Line*		m_borderLine;
		ARGB_Color	m_color;

	};

}
#endif			// #define _RECTANGLE_H

