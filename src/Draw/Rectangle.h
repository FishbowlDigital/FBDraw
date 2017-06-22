// Line.h
// Header file for the Point class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _LINE_H
#define _LINE_H
#include "Types.h"
#include "Point.h"
#include "IDrawable.h"

class Rectangle : public IDrawable
{
	public:
		Rectangle(int h, int w, BGRA_Color color);

		virtual void Render(color32_t* backBuffer, int width, int height);

		private:
		// Properties
			int			r_height;
			int			r_width;
			BGRA_Color	r_Color;


};



#endif			// #define _POINT_H

