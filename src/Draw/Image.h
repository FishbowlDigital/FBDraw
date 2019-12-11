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
		~Image();

		color32_t* 		GetBuffer() { return m_imageBuffer; }
		void			ReplaceBuffer(color32_t* image);
		void			ReplaceBuffer(color32_t* image, int w, int h);
		void			ReplaceBuffer(color32_t* image, Point loc, int w, int h);

		virtual void 	Render(color32_t* backBuffer, int width, int height);

		virtual bool	HitTest(Point pt)
		{
			return false; /* NOT YET IMPLEMENTED */
		};

		// properties
		Point			Location() 				{ return m_location; }
		int				Width()					{ return m_width; }
		int				Height()				{ return m_height; }
		color32_t*		ImageData()				{ return m_imageBuffer; }

		void 			HasAlpha(bool hasit) 	{ m_bHasAlpha = hasit; }
		bool 			HasAlpha()				{ return m_bHasAlpha; }

	private:
		// Properties
		Point		m_location;
		int			m_height;
		int			m_width;
		color32_t*	m_imageBuffer;

		bool		m_bHasAlpha;
		bool		m_bOwnsBuffer;
	};

}

#endif			// #define _POINT_H

