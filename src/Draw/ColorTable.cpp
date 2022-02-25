// ColorTable.cpp
// Implementation file for the ColorTable class
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


#include "ColorTable.h"
#include "Macros.h"

namespace FBDraw
{
	ColorTable::ColorTable(ARGB_Bytes* colors, int size, Point loc, int w, int h)
	{
		m_location = loc;
		m_width = w;
		m_height = h;
		m_lutSize = size;

		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		m_LUT = new ColorLUT(colors, m_lutSize, 0, m_lutSize); // Min and max defaulted to size of array for now. (Should min and max get passed in?)
		m_border = new Rectangle(m_location, m_width, m_height, false, 2, ARGB_Color{ 0xFF, 0xFF, 0xFF, 0xCF });

		// Default is Visible
		Visible = true;
	}
	ColorTable::ColorTable(Point loc, int w, int h)
	{
		m_location = loc;
		m_width = w;
		m_height = h;
		m_LUT = new ColorLUT(0, 256);

		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		m_border = new Rectangle(m_location, m_width, m_height, false, 2, ARGB_Color{ 0xFF, 0xFF, 0xFF, 0xCF });

		// Default is Visible
		Visible = true;
	}
	ColorTable::~ColorTable()
	{
		if (m_LUT != NULL)
			delete m_LUT;

		if (m_border != NULL)
			delete m_border;
	}

	void ColorTable::SetColorTable(ARGB_Bytes colors)
	{
		//Not Yet implemented
	}
	ARGB_Bytes ColorTable::GetColor(int value)
	{
		return m_LUT->GetColor(value);
	}

	void ColorTable::SetBorderColor(ARGB_Color color)
	{
		m_border->SetColor(color);

		Invalidate();
	}
	ARGB_Color ColorTable::GetBorderColor()
	{
		return m_border->GetColor();
	}

	void ColorTable::SetBorderThickness(int thickness)
	{
		m_border->SetThickness(thickness);

		Invalidate();
	}
	int ColorTable::GetBorderThickness()
	{
		return m_border->GetThickness();
	}

	void ColorTable::Render(color32_t* backBuffer, int width, int height)
	{
		ARGB_Bytes color, backColor, mixColor;
		int xStart = m_location.X + 1; // Taking into account the width of the border
		int xEnd = m_location.X + m_width;
		int yStart = m_location.Y + 1;
		int yEnd = m_location.Y + m_height - 2;
		int colorValue;
		float scale;

		m_border->Render(backBuffer, width, height);

		for (int iY = yStart; iY <= yEnd; iY++)
		{
			for (int iX = xStart; iX < xEnd; iX++)
			{
				scale = ((iY - yStart) * m_invHeight);
				colorValue = (int) (scale * (m_lutSize-1));
				color = m_LUT->GetColor(colorValue);

				//backBuffer[((yEnd-iY) * width) + iX] = color.U32;

				//Uncomment for alpha mixing
				int iBack = ((yEnd - iY + yStart) * width) + iX;
				backColor.U32 = backBuffer[iBack];
				mixColor.Color.Red = AlphaMix8(backColor.Color.Red, color.Color.Red, color.Color.Alpha);
				mixColor.Color.Green = AlphaMix8(backColor.Color.Green, color.Color.Green, color.Color.Alpha);
				mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, color.Color.Blue, color.Color.Alpha);

				backBuffer[iBack] = mixColor.U32;
			}
		}
	}
}
