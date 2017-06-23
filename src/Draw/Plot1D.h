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

class Plot1D : public IDrawable
{
public:
	Plot1D(int* data, int start, BGRA_Color color);

	virtual void Render(color32_t* backBuffer, int width, int height);
	
private:
	// Properties
	int* m_yData;
	int m_xStart;
	BGRA_Color	m_color;
};
#endif			// #define _POINT_H

