// Data1D.cpp
// Implementation file for the Data1D class
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

#include <math.h>
#include "Data1D.h"
#include "Macros.h"
#include "Line.h"

namespace FBDraw
{

	// Constructor
	Data1D::Data1D(float* data, int dataLength) : IData()
	{
		m_Data = data;
		m_DataLength = dataLength;
		m_Resolution = 3;
		m_LowerBoundX = 0;

	}

	Data1D::Data1D(float* data, int dataLength, char* label, float resolution, float lowerBoundX) : Data1D(data, dataLength)
	{
		m_Label = label;
		m_Resolution = resolution;
		m_LowerBoundX = lowerBoundX;
	}


	char* Data1D::getLabel()
	{
		return m_Label;
	}

	void Data1D::setLabel(char* label)
	{
		m_Label = label;
	}

	float* Data1D::getData()
	{
		return m_Data;
	}

	void Data1D::setData(float* data, int size)
	{
		m_Data = data;
		m_DataLength = size;
	}

	int Data1D::getSize()
	{
		return m_DataLength;
	}

	float Data1D::getResolution()
	{
		return m_Resolution;
	}
	void Data1D::setResolution(float resolution)
	{
		m_Resolution = resolution;
	}

	float Data1D::getLowerBoundX()
	{
		return abs(m_LowerBoundX);
	}

	void Data1D::setLowerBoundX(float lowerBoundX)
	{
		m_LowerBoundX = lowerBoundX;
	}

}

//void Data1D::Render(color32_t* backBuffer, int width, int height)
//{
//
//	for (int iX = 0; iX < (m_yDataLength-1); iX++)
//	{
//		//Establishing two points to compute to line.
//		Point p1( (iX + m_start.X), (m_yData[iX] + m_start.Y) );
//		Point p2( ((iX + 1) + m_start.X), (m_yData[(iX + 1)] + m_start.Y) );
//		
//		//render line between each point. 
//		Line ln(p1, p2, m_color, m_thickness);
//		ln.Render(backBuffer, width, height);
//	}
//}
