// Canvas.cpp
// Implementation file for the Canvas class
//
// Copyright Fishbowl Digital 2017
//

#include "Canvas.h"
#include "Macros.h"

#define DEFAULT_NUM_DRAWABLES			10


// Constructor/Destructor
Canvas::Canvas(int width, int height)
{
	// Create the backbuffer
	m_backBuffer = new color32_t[width * height];

	// Store configuration
	m_width = width;
	m_height = height;

	// Default background is black
	m_backgroundColor = BGRA_Color { 0, 0, 0, 0 };

	// Initialize the array of drawables
	m_numDrawables = 0;
	m_drawables = new IDrawable* [DEFAULT_NUM_DRAWABLES];
}

Canvas::Canvas(int width, int height, BGRA_Color backgroundColor)
	: Canvas(width, height)
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
	m_drawables[m_numDrawables++] = drawable;
}

// Draw
void Canvas::Render()
{

	// Check
	if (m_backBuffer == NULL)
		return;

	// Draw background
	color32_t bColor = BGRAColorToU32(m_backgroundColor);

	int numPx = m_width * m_height;
	for (int i = 0; i < numPx; i++)
	{
		m_backBuffer[i] = bColor;
	}

	// Draw objects in the scene
	for (int i = 0; i < m_numDrawables; i++)
	{
		m_drawables[i]->Render(m_backBuffer, m_width, m_height);
	}
	
}

// Configuration & Property Access
void Canvas::SetBackgroundColor(BGRA_Color color)
{
	m_backgroundColor = color;
}

BGRA_Color Canvas::GetBackgroundColor()
{
	return m_backgroundColor;
}

color32_t* Canvas::GetBackBuffer()
{
	return m_backBuffer;
}


