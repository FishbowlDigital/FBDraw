// IDrawable.cpp
// Implementation file for the IDrawable pure virtual interface class
//
// Copyright Fishbowl Digital 2017
//

#include "IDrawable.h"
#include "Canvas.h"

namespace FBDraw
{
	IDrawable::IDrawable()
	{
		m_canvasInvalidateSubscriber = NULL;
		m_eventInvalidated = NULL;
	}
	IDrawable::~IDrawable()
	{
		// Does nothing
	}


	void IDrawable::SetEventInvalidated(Canvas* canvas, EventHandlerIDrawable event)
	{
		m_canvasInvalidateSubscriber = canvas;
		m_eventInvalidated = event;
	}

	void IDrawable::ClearEventInvalidated(Canvas* canvas, EventHandlerIDrawable event)
	{
		m_canvasInvalidateSubscriber = NULL;	// Leaving canvas param for future use (list of subscribers possible)
		m_eventInvalidated = NULL;
	}

	void IDrawable::Invalidate()
	{
		if (m_eventInvalidated && m_canvasInvalidateSubscriber)
			(m_canvasInvalidateSubscriber->*(m_eventInvalidated))(*this);
	}


}
