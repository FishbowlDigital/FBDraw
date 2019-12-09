// Plot1D.h
// Header file for the Plot1D class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _PLOT1D_H 
#define _PLOT1D_H

#include "Types.h"
#include "Point.h"
#include "IDrawable.h"

namespace FBDraw
{
	class Plot1D : public IDrawable
	{
	public:
		Plot1D(int* data, int dataLength, Point start, ARGB_Color color);
		Plot1D(int* data, int dataLength, Point start, ARGB_Color color, int thickness);

		virtual ~Plot1D();

		virtual void Render(color32_t* backBuffer, int width, int height);

		ARGB_Color GetColor();
		int GetThickness();

		void SetColor(ARGB_Color color);
		void SetThickness(int thickness);

	private:
		// Properties
		int* m_yData;
		int m_yDataLength;
		Point m_start;
		ARGB_Color	m_color;
		int m_thickness;
	};
}
#endif			// #define _PLOT1D_H

