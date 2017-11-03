// IDrawable.h
// Header file for the IDrawable pure virtual interface class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _IDRAWABLE_H
#define _IDRAWABLE_H

#include "Types.h"

namespace FBDraw
{

	class IDrawable
	{
	public:
		~IDrawable();

		virtual void Render(color32_t* backBuffer, int width, int height) = 0;
	};

}

#endif			// #define _IDRAWABLE_H

