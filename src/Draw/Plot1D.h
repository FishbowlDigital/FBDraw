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
	Plot1D(int* data, int dataLength, Point start, BGRA_Color color);
	Plot1D(int* data, int dataLength, Point start, BGRA_Color color, int thickness);

	virtual void Render(color32_t* backBuffer, int width, int height);
	
	BGRA_Color GetColor();
	int GetThickness();

	void SetColor(BGRA_Color color);
	void SetThickness(int thickness);

private:
	// Properties
	int* m_yData;
	int m_yDataLength;
	Point m_start;
	BGRA_Color	m_color;
	int m_thickness;
};
#endif			// #define _POINT_H

