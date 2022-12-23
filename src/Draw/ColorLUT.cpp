// ColorLUT.cpp
// Implementation file for the ColorLUT class
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
		m_colorTable = new ARGB_Bytes[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_colorTable[i].Color = ARGB_Color{ (uint8_t)i, (uint8_t)i, (uint8_t)i, 0xFF};
		}

		// This version maintains it's own table. Note for cleanup later
		m_ownsColorTable = true;
	}

	ColorLUT::ColorLUT(ARGB_Bytes* table, int size, int min, int max)
	{
		m_colorTable = table;
		m_size = size;
		m_min = min;
		m_max = max;

		m_invRange = 1.0f / (m_max - m_min);

		m_ownsColorTable = false;
	}

	ColorLUT::~ColorLUT()
	{
		if (m_ownsColorTable && m_colorTable != NULL)
			delete m_colorTable;
	}

	ARGB_Bytes ColorLUT::GetColor(int value)
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
		m_invRange = 1.0f / (m_max - m_min); // Precalculate the range. Inverse to provide faster division
	}

	int ColorLUT::GetMax()
	{
		return m_max;
	}
	void ColorLUT::SetMax(int value)
	{
		m_max = value;
		m_invRange = 1.0f / (m_max - m_min); // Precalculate the range. Inverse to provide faster division
	}

}
