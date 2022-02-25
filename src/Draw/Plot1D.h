// Plot1D.h
// Header file for the Plot1D class
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

#ifndef _PLOT1D_H 
#define _PLOT1D_H

#include "Types.h"
#include "Point.h"
#include "IDrawable.h"

namespace FBDraw
{
	class Plot1D : public IDrawable
	{
	public:
		Plot1D(int* data, int dataLength, Point start, ARGB_Color color);
		Plot1D(int* data, int dataLength, Point start, ARGB_Color color, int thickness);

		virtual ~Plot1D();

		virtual void Render(color32_t* backBuffer, int width, int height);

		virtual bool	HitTest(Point pt)
		{
			return false; /* NOT YET IMPLEMENTED */
		};

		ARGB_Color GetColor();
		int GetThickness();

		void SetColor(ARGB_Color color);
		void SetThickness(int thickness);

	private:
		// Properties
		int* m_yData;
		int m_yDataLength;
		Point m_start;
		ARGB_Color	m_color;
		int m_thickness;
	};
}
#endif			// #define _PLOT1D_H

