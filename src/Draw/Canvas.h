// Canvas.h
// Header file for the Canvas class
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

#ifndef _CANVAS_H
#define _CANVAS_H

#include "Types.h"
#include "IDrawable.h"

namespace FBDraw
{

	class Canvas
	{
	public:
		// Constructor/Destructor
		Canvas(int width, int height);
		Canvas(int width, int height, color32_t* backbuffer);
		Canvas(int width, int height, ARGB_Color backgroundColor);
		~Canvas();

		//Add drawable
		void 			AddDrawable(IDrawable* drawable);
		void 			RemoveDrawable(IDrawable* drawable);

		// Draw
		virtual void 	Render();

		// Interaction Events
		virtual void	TouchDown(int x, int y);
		virtual void	TouchUp(int x, int y);


		// Configuration & Property Access
		void			SetBackgroundColor(ARGB_Color color);
		ARGB_Color		GetBackgroundColor();

		void			SetEraseBackground(bool erase) { m_eraseBackground = erase; }
		bool			GetEraseBackground() { return m_eraseBackground; }

		int				GetWidth();
		int				GetHeight();

		color32_t*		GetBackBuffer();
		color32_t*		GetFrontBuffer();

	protected:
		void			DrawableInvalidated(IDrawable& drawable);

	protected:
		// Dimensions
		int m_width;
		int m_height;

		// Default colors
		ARGB_Color		m_backgroundColor;

		// Config properties
		bool 			m_eraseBackground;

		// The rendering backbuffer (always 32-bit color)
		color32_t*		m_backBuffer;
		color32_t*		m_frontBuffer;

		// List of drawables
		IDrawable**		m_drawables;
		int				m_numDrawables;
		int				m_maxDrawables;

	};

}

#endif			// #define _CANVAS_H

