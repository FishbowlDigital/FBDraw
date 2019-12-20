// Line.h
// Header file for the Line class
//
// Copyright Fishbowl Digital 2017
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

		// Get/Set Parameters
		Point GetPoint1();
		Point GetPoint2();
		ARGB_Color GetColor();
		int GetThickness();

		void SetPoint1(Point p1);
		void SetPoint1(int x, int y);
		void SetPoint2(Point p2);
		void SetPoint2(int x, int y);
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

