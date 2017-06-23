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

class Line : public IDrawable
{
	public:

	// Constructor/Destructor
	Line(Point p1, Point p2, BGRA_Color lineColor);
	//Line(Line& line);

	// Operators
	//Line operator=(const Line& Line);

	virtual void Render(color32_t* backBuffer, int width, int height);

	private:
	// Properties
		Point		m_p1;
		Point		m_p2;
		BGRA_Color	m_lineColor;
};



#endif			// #define _POINT_H

