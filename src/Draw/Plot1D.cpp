// Plot1D.cpp
// Implementation file for the Plot1D class
//
// Copyright Fishbowl Digital 2017
//

#include "Plot1D.h"
#include "Macros.h"
#include "Line.h"

// Constructor
Plot1D::Plot1D(int* data, int dataLength, Point start, BGRA_Color color)
{
	m_yData = data;
	m_yDataLength = dataLength;
	m_start = start;
	m_color = color;
}

void Plot1D::Render(color32_t* backBuffer, int width, int height)
{
	/*float m = ((float)(m_p2.Y - m_p1.Y)) / ((float)(m_p2.X - m_p1.X));
	float b = m_p1.Y - (m * m_p1.X);*/

	for (int iX = 0; iX < (m_yDataLength-1); iX++)
	{
		//Establishing two points to compute to line.
		Point p1( (iX + m_start.X), (m_yData[iX] + m_start.Y) );
		Point p2( ((iX + 1) + m_start.X), (m_yData[(iX + 1)] + m_start.Y) );

		Line ln(p1, p2, m_color);
		ln.Render(backBuffer, width, height);
	}
}
