// IDrawable.cpp
// Implementation file for the IDrawable pure virtual interface class
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
