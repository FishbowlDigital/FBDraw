// Image.h
// Header file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _COLORTABLE_H
#define _COLORTABLE_H
#include "Types.h"
#include "IDrawable.h"
#include "Rectangle.h"
#include "ColorLUT.h"

namespace FBDraw
{
	class ColorTable : public IDrawable
	{
	public:
		ColorTable(ARGB_Bytes* colors, int size, Point loc, int w, int h);
		ColorTable(Point loc, int w, int h);
		~ColorTable();

		void SetColorTable(ARGB_Bytes colors);
		ARGB_Bytes GetColor(int value);

		virtual void Render(color32_t* backBuffer, int width, int height);

	private:
		// Properties
		Point		m_location;
		int			m_height;
		int			m_width;

		float		m_invWidth;
		float		m_invHeight;

		int			m_lutSize;
		ColorLUT*	m_LUT;
		Rectangle*	m_border;
	};

}

#endif			// #define _COLORTABLE_H

