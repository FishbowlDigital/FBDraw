// IDrawable.h
// Header file for the IDrawable pure virtual interface class
//
// Copyright Fishbowl Digital 2017
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
		// Events
		EventHandlerIDrawable		m_eventInvalidated;
		Canvas*						m_canvasInvalidateSubscriber;

		// Event executors
		void		Invalidate();
	};

}

#endif			// #define _IDRAWABLE_H

