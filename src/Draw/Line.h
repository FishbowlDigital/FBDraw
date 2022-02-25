// Line.h
// Header file for the Line class
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

#ifndef _LINE_H
#define _LINE_H
#include "Types.h"
#include "Point.h"
#include "IDrawable.h"

namespace FBDraw
{

	class Line : public IDrawable
	{
	public:

		// Constructor/Destructor
		Line(Point p1, Point p2, ARGB_Color lineColor);
		Line(Point p1, Point p2, ARGB_Color lineColor, int thickness);

		Line(int x1, int y1, int x2, int y2, ARGB_Color lineColor);
		Line(int x1, int y1, int x2, int y2, ARGB_Color lineColor, int thickness);

		// Get/Set Parameters
		Point GetPoint1();
		Point GetPoint2();
		ARGB_Color GetColor();
		int GetThickness();

		void SetPoint1(Point p1);
		void SetPoint1(int x, int y);
		void SetPoint2(Point p2);
		void SetPoint2(int x, int y);
		void SetLocation(Point pt1, Point pt2);
		void SetColor(ARGB_Color color);
		void SetThickness(int thickness);

		virtual void Render(color32_t* backBuffer, int width, int height);

		virtual bool	HitTest(int x, int y)
		{
			return false; /* NOT YET IMPLEMENTED */
		};


	private:
		// Properties
		Point		m_p1;
		Point		m_p2;
		int			m_thickness;
		ARGB_Color	m_lineColor;
	};

}

#endif			// #define _LINE_H

