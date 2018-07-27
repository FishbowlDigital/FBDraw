// Histogram.cpp
//
// Copyright AIBioMed 2017
//

#include "ColorTable.h"
#include "Macros.h"

namespace FBDraw
{
	ColorTable::ColorTable(BGRA_Bytes* colors, int size, Point loc, int w, int h)
	{
		m_location = loc;
		m_width = w;
		m_height = h;
		m_lutSize = size;

		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		m_LUT = new ColorLUT(colors, m_lutSize, 0, m_lutSize); // Min and max defaulted to size of array for now. (Should min and max get passed in?)
		m_border = new Rectangle(m_location, m_width, m_height, false, 2, BGRA_Color{ 0xFF, 0xFF, 0xFF, 0xCF });

		// Default is Visible
		Visible = true;
	}

	ColorTable::ColorTable(Point loc, int w, int h)
	{
		m_location = loc;
		m_width = w;
		m_height = h;
		m_LUT = new ColorLUT(0, 256);

		m_border = new Rectangle(m_location, m_width, m_height, false, 2, BGRA_Color{ 0xFF, 0xFF, 0xFF, 0xCF });

		// Default is Visible
		Visible = true;
	}

	ColorTable::~ColorTable()
	{
		if (m_border != NULL)
			delete m_border;
	}

	void ColorTable::SetColorTable(BGRA_Bytes colors)
	{
		//Not Yet implemented
	}

	BGRA_Bytes ColorTable::GetColor(int value)
	{
		return m_LUT->GetColor(value);
	}


	void ColorTable::Render(color32_t* backBuffer, int width, int height)
	{
		BGRA_Bytes color, backColor, mixColor;
		int xStart = m_location.X + 1; // Taking into account the width of the border
		int xEnd = m_location.X + m_width;
		int yStart = m_location.Y + 1;
		int yEnd = m_location.Y + m_height - 2;
		int colorValue;
		float scale;

		m_border->Render(backBuffer, width, height);

		for (int iY = yStart; iY < yEnd; iY++)
		{
			for (int iX = xStart; iX < xEnd; iX++)
			{
				scale = ((iY - yStart) * m_invHeight);
				colorValue = (scale * (m_lutSize-1));
				color = m_LUT->GetColor(colorValue);

				//backBuffer[((yEnd-iY) * width) + iX] = color.U32;

				//Uncomment for alpha mixing
				int iBack = ((yEnd-iY) * width) + iX;
				backColor.U32 = backBuffer[iBack];
				mixColor.Color.Red = AlphaMix8(backColor.Color.Red, color.Color.Red, color.Color.Alpha);
				mixColor.Color.Green = AlphaMix8(backColor.Color.Green, color.Color.Green, color.Color.Alpha);
				mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, color.Color.Blue, color.Color.Alpha);

				backBuffer[iBack] = mixColor.U32;
			}
		}
	}
}
