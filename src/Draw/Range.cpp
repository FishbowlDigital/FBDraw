//// Range.cpp
//// Implementation file for the Range class
////
//// Copyright Fishbowl Digital 2017
////
//
//#include "Range.h"
//#include "Macros.h"
//#include "Line.h"
//
//// Constructor
//Range::Range(int* data, int dataLength, Point start, BGRA_Color color)
//{
//	m_yData = data;
//	m_yDataLength = dataLength;
//	m_start = start;
//	m_color = color;
//	m_thickness = 0;
//}
//
//Range::Range(int* data, int dataLength, Point start, BGRA_Color color, int thickness) : Range(data, dataLength, start, color)
//{
//	m_thickness = thickness;
//}
//
//BGRA_Color Line::GetColor()
//{
//	return m_lineColor;
//}
//
//int Line::GetThickness()
//{
//	return m_thickness;
//}
//
//void Line::SetColor(BGRA_Color Color)
//{
//	m_lineColor = Color;
//}
//
//void Line::SetThickness(int thickness)
//{
//	m_thickness = thickness;
//}
//
//void Range::Render(color32_t* backBuffer, int width, int height)
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
