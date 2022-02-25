// ColorTable.h
// Header file for the ColorTable class
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

#ifndef _COLORTABLE_H
#define _COLORTABLE_H
#include "Types.h"
#include "IDrawable.h"
#include "Rectangle.h"
#include "ColorLUT.h"

namespace FBDraw
{
	class ColorTable : public IDrawable
	{
	public:
		ColorTable(ARGB_Bytes* colors, int size, Point loc, int w, int h);
		ColorTable(Point loc, int w, int h);
		~ColorTable();

		void SetColorTable(ARGB_Bytes colors);
		ARGB_Bytes GetColor(int value);

		void SetBorderColor(ARGB_Color color);
		ARGB_Color GetBorderColor();

		void SetBorderThickness(int thickness);
		int GetBorderThickness();

		virtual void Render(color32_t* backBuffer, int width, int height);

		virtual bool HitTest(int x, int y)
		{
			return false; /* NOT YET IMPLEMENTED */
		};

		virtual void TouchDown(Point pt)
		{
			return; /* NOT YET IMPLEMENTED */
		};

	private:
		// Properties
		Point		m_location;
		int			m_height;
		int			m_width;

		float		m_invWidth;
		float		m_invHeight;

		int			m_lutSize;
		ColorLUT*	m_LUT;
		Rectangle*	m_border;
	};

}

#endif			// #define _COLORTABLE_H

