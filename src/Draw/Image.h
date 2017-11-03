// Image.h
// Header file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _IMAGE_H
#define _IMAGE_H
#include "Types.h"
#include "IDrawable.h"
#include "Point.h"

namespace FBDraw
{

	class Image : public IDrawable
	{
	public:
		Image(Point loc, int w, int h, color32_t* image);
		Image(Point loc, int w, int h);

		color32_t* GetBuffer() { return m_imageBuffer; }

		virtual void Render(color32_t* backBuffer, int width, int height);

	private:
		// Properties
		Point		m_location;
		int			m_height;
		int			m_width;
		color32_t*	m_imageBuffer;
	};

}

#endif			// #define _POINT_H

