// ColorLUT.cpp
// Implementation file for the ColorLUT class
//
// Copyright Fishbowl Digital 2017
//
#include <math.h>

#include "ColorLUT.h"
#include "Macros.h"

namespace FBDraw
{
	// Constructors
	ColorLUT::ColorLUT(int min, int max)
	{
		m_min = min;
		m_max = max;
		m_size = 256;

		m_invRange = 1.0f / (m_max - m_min); // Precalculate the range. Inverse to provide faster division

		// No Look-up table passed in. Generate a default greyscale look-up table. 
		m_colorTable = new BGRA_Bytes[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_colorTable[i].Color = BGRA_Color{ (uint8_t)i, (uint8_t)i, (uint8_t)i, 0xFF};
		}
	}

	ColorLUT::ColorLUT(BGRA_Bytes* table, int size, int min, int max)
	{
		m_colorTable = table;
		m_size = size;
		m_min = min;
		m_max = max;

		m_invRange = 1.0f / (m_max - m_min);
	}

	ColorLUT::~ColorLUT()
	{
		if (m_colorTable != NULL)
			delete m_colorTable;
	}

	BGRA_Bytes ColorLUT::GetColor(int value)
	{
		float scale;
		int returnIndex;

		if (value > m_max)
		{
			return m_colorTable[m_max];
		}
		else if (value < m_min)
		{
			return m_colorTable[m_min];
		}
		else
		{
			scale = value * m_invRange; // value / (max - min)
			
			returnIndex = (int)(m_size * scale);
			return m_colorTable[returnIndex];
		}
	}

	int ColorLUT::GetMin()
	{
		return m_min;
	}
	void ColorLUT::SetMin(int value)
	{
		m_min = value;
	}

	int ColorLUT::GetMax()
	{
		return m_max;
	}
	void ColorLUT::SetMax(int value)
	{
		m_max = value;
	}

}
