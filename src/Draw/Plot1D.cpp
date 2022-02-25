// Plot1D.cpp
// Implementation file for the Plot1D class
//
// Copyright(c) 2017 - 2022 Fishbowl Digital LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "Plot1D.h"
#include "Macros.h"
#include "Line.h"

namespace FBDraw
{

	// Constructor
	Plot1D::Plot1D(int* data, int dataLength, Point start, ARGB_Color color)
	{
		m_yData = data;
		m_yDataLength = dataLength;
		m_start = start;
		m_color = color;
		m_thickness = 0;

		// Default is Visible
		Visible = true;
	}

	Plot1D::Plot1D(int* data, int dataLength, Point start, ARGB_Color color, int thickness) : Plot1D(data, dataLength, start, color)
	{
		m_thickness = thickness;

		// Default is Visible
		Visible = true;
	}

	Plot1D::~Plot1D()
	{

	}

	ARGB_Color Plot1D::GetColor()
	{
		return m_color;
	}

	int Plot1D::GetThickness()
	{
		return m_thickness;
	}

	void Plot1D::SetColor(ARGB_Color Color)
	{
		m_color = Color;
	}

	void Plot1D::SetThickness(int thickness)
	{
		m_thickness = thickness;
	}

	void Plot1D::Render(color32_t* backBuffer, int width, int height)
	{
		for (int iX = 0; iX < (m_yDataLength - 1); iX++)
		{
			//Establishing two points to compute to line.
			Point p1((iX + m_start.X), (m_yData[iX] + m_start.Y));
			Point p2(((iX + 1) + m_start.X), (m_yData[(iX + 1)] + m_start.Y));

			//render line between each point. 
			Line ln(p1, p2, m_color, m_thickness);
			ln.Render(backBuffer, width, height);
		}
	}
}
