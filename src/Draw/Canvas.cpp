// Canvas.cpp
// Implementation file for the Canvas class
//
// Copyright Fishbowl Digital 2017
//

#include "Canvas.h"
#include "Macros.h"

#include <stdlib.h>

#define DEFAULT_MAX_DRAWABLES			10

namespace FBDraw
{

	// Constructor/Destructor
	Canvas::Canvas(int width, int height) :
		Canvas(width, height, new color32_t[width*height])
	{
		// Default constructor ok
	}

	Canvas::Canvas(int width, int height, color32_t* backbuffer)
	{
		// Create the backbuffer
		m_backBuffer = backbuffer;
		m_frontBuffer = new color32_t[width * height];

		// Store configuration
		m_width = width;
		m_height = height;

		// Default background is black
		m_backgroundColor = ARGB_Color{ 0, 0, 0, 0 };

		// Initialize the array of drawables
		m_numDrawables = 0;
		m_maxDrawables = DEFAULT_MAX_DRAWABLES;
		m_drawables = new IDrawable * [DEFAULT_MAX_DRAWABLES];

		// Default property values
		m_eraseBackground = false;
	}

	Canvas::Canvas(int width, int height, ARGB_Color backgroundColor) : Canvas(width, height)
	{
		// Store configuration
		m_backgroundColor = backgroundColor;
	}

	Canvas::~Canvas()
	{
		if (m_backBuffer != NULL)
		{
			delete m_backBuffer;
		}
	}

	void Canvas::AddDrawable(IDrawable* drawable)
	{
		// Need to increase the list size?
		if (m_numDrawables >= m_maxDrawables)
		{
			// add 10 more in a new buffer
			m_maxDrawables += 10;
			IDrawable** newDrawableList = new IDrawable*[m_maxDrawables];

			// Copy pointers to new list
			for (int i=0; i<m_numDrawables; i++)
			{
				newDrawableList[i] = m_drawables[i];
			}

			// Delete old and update array pointer
			delete m_drawables;
			m_drawables = newDrawableList;
		}

		// Add it to the list
		m_drawables[m_numDrawables++] = drawable;
		drawable->SetEventInvalidated(this, &Canvas::DrawableInvalidated);
	}

	void Canvas::RemoveDrawable(IDrawable* drawable)
	{
		
	}

	// Draw
	void Canvas::Render()
	{
		// Check
		if (m_backBuffer == NULL)
			return;

		// Draw background
		color32_t bColor = ARGBColorToU32(m_backgroundColor);

		if (m_eraseBackground)
		{
			int numPx = m_width * m_height;
			for (int i = 0; i < numPx; i++)
			{
				m_backBuffer[i] = bColor;
			}
		}

		// Draw objects in the scene
		for (int i = 0; i < m_numDrawables; i++)
		{
			if (m_drawables[i]->Visible)
				m_drawables[i]->Render(m_backBuffer, m_width, m_height);
		}
	}


	void Canvas::TouchDown(int x, int y)
	{
		// Check for touch on IDrawables in scene, backwards for Z-order
		for (int i = m_numDrawables-1; i >= 0; i--)
		{
			if (m_drawables[i]->Visible && 
				m_drawables[i]->HitTest(x, y))
			{
				m_drawables[i]->TouchDown(x, y);
			}
		}
	}

	void Canvas::TouchUp(int x, int y)
	{
		// Check for touch on IDrawables in scene, backwards for Z-order
		for (int i = m_numDrawables - 1; i >= 0; i--)
		{
			if (m_drawables[i]->Visible &&
				m_drawables[i]->HitTest(x, y))
			{
				m_drawables[i]->TouchUp(x, y);
			}
		}
	}


	// Configuration & Property Access
	void Canvas::SetBackgroundColor(ARGB_Color color)
	{
		m_backgroundColor = color;
	}

	ARGB_Color Canvas::GetBackgroundColor()
	{
		return m_backgroundColor;
	}

	int Canvas::GetWidth()
	{
		return m_width;
	}

	int Canvas::GetHeight()
	{
		return m_height;
	}


	color32_t* Canvas::GetBackBuffer()
	{
		return m_backBuffer;
	}

	color32_t* Canvas::GetFrontBuffer()
	{
		// Mem copy back to front
		int numPx = m_width * m_height;
		for (int i = 0; i < numPx; i++) { m_frontBuffer[i] = m_backBuffer[i]; }

		// Return it
		return m_frontBuffer;
	}

	/////////////////////////////
	// EVENTS

	void Canvas::DrawableInvalidated(IDrawable& drawable)
	{
		// Simple re-draw for now
		Render();
	}

}
