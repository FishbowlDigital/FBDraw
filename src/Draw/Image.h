// Image.h
// Header file for the Image class
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

		virtual bool	HitTest(int x, int y);

		// properties
		Point			Location() 				{ return m_location; }
		void 			SetLocation(Point p)	{ m_location = p; }

		int				Width()					{ return m_width; }
		void 			SetWidth(int w)			{ m_width = w; }

		int				Height()				{ return m_height; }
		void 			SetHeight(int h)		{ m_height = h; }

		color32_t*		ImageData()				{ return m_imageBuffer; }

		void 			HasAlpha(bool hasit) 	{ m_bHasAlpha = hasit; }
		bool 			HasAlpha()				{ return m_bHasAlpha; }

	protected:
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

