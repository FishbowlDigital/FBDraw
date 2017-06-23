// Canvas.h
// Header file for the Canvas class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _CANVAS_H
#define _CANVAS_H

#include "Types.h"
#include "IDrawable.h"

class Canvas
{
public:
	// Constructor/Destructor
	Canvas(int width, int height);
	Canvas(int width, int height, BGRA_Color backgroundColor);
	~Canvas();

	//Add drawable
	void AddDrawable(IDrawable* drawable);

	// Draw
	void Render();

	// Configuration & Property Access
	void		SetBackgroundColor(BGRA_Color color);
	BGRA_Color	GetBackgroundColor();

	color32_t*	GetBackBuffer();

private:
	// Dimensions
	int m_width;
	int m_height;

	// Default colors
	BGRA_Color		m_backgroundColor;

	// The rendering backbuffer (always 32-bit color)
	color32_t*		m_backBuffer;

	// List of drawables
	IDrawable**		m_drawables;
	int				m_numDrawables;

};


#endif			// #define _CANVAS_H

