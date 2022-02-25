// IDrawable.h
// Header file for the IDrawable pure virtual interface class
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

#ifndef _IDRAWABLE_H
#define _IDRAWABLE_H

#include "Types.h"
#include "Point.h"
//#include "Canvas.h"


namespace FBDraw
{
	// Class prototypes
	class Canvas;
	class IDrawable;

	// Event Definitions
	typedef void (Canvas::*EventHandlerIDrawable)(IDrawable&);

	class IDrawable
	{
	public:		
		virtual ~IDrawable();

		virtual void Render(color32_t* backBuffer, int width, int height) = 0;

		virtual bool HitTest(int x, int y) = 0;
		virtual void TouchDown(int x, int y) { /* default is no implementation */ };
		virtual void TouchUp(int x, int y) { /* default is no implementation */ };

		void		SetEventInvalidated(Canvas* canvas, EventHandlerIDrawable event);
		void		ClearEventInvalidated(Canvas* canvas, EventHandlerIDrawable event);

		// Properties
		bool Visible;

	protected:
		IDrawable();

	protected:
		// Events
		EventHandlerIDrawable		m_eventInvalidated;
		Canvas*						m_canvasInvalidateSubscriber;

		// Event executors
		void		Invalidate();
	};

}

#endif			// #define _IDRAWABLE_H

