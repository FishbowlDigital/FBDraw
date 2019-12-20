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

