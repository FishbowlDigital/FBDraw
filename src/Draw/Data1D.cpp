// Data1D.cpp
// Implementation file for the Data1D class
//
// Copyright Fishbowl Digital 2017
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
