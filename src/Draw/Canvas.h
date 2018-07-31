// Canvas.h
// Header file for the Canvas class
//
// Copyright Fishbowl Digital 2017
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
		Canvas(int width, int height, BGRA_Color backgroundColor);
		~Canvas();

		//Add drawable
		void 			AddDrawable(IDrawable* drawable);

		// Draw
		virtual void 	Render();

		// Configuration & Property Access
		void			SetBackgroundColor(BGRA_Color color);
		BGRA_Color		GetBackgroundColor();

		void			SetEraseBackground(bool erase) { m_eraseBackground = erase; }
		bool			GetEraseBackground() { return m_eraseBackground; }

		int				GetWidth();
		int				GetHeight();

		color32_t*		GetBackBuffer();
		color32_t*		GetFrontBuffer();

	protected:
		// Dimensions
		int m_width;
		int m_height;

		// Default colors
		BGRA_Color		m_backgroundColor;

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

