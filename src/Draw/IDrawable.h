// IDrawable.h
// Header file for the IDrawable pure virtual interface class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _IDRAWABLE_H
#define _IDRAWABLE_H

#include "Types.h"
#include "Point.h"

namespace FBDraw
{

	class IDrawable
	{
	public:
		virtual ~IDrawable();

		virtual void Render(color32_t* backBuffer, int width, int height) = 0;

		virtual bool HitTest(Point pt) = 0;
		//virtual void TouchDown(Point pt) = 0;
		//virtual void TouchUp(Point pt) = 0;

		// Properties
		bool Visible;

			};

}

#endif			// #define _IDRAWABLE_H

