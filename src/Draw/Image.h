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
		Image(int x, int y, int w, int h, color32_t* image, bool hasAlpha = true);
		Image(int x, int y, int w, int h, bool hasAlpha = true);

		color32_t* 		GetBuffer() { return m_imageBuffer; }

		virtual void 	Render(color32_t* backBuffer, int width, int height);

		// properties
		void 			HasAlpha(bool hasit) 	{ m_bHasAlpha = hasit; }
		bool 			HasAlpha()				{ return m_bHasAlpha; }

	private:
		// Properties
		Point		m_location;
		int			m_height;
		int			m_width;
		color32_t*	m_imageBuffer;

		bool		m_bHasAlpha;
	};

}

#endif			// #define _POINT_H

