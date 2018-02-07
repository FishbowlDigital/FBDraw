// Image.cpp
// Implementation file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#include "Image.h"
#include "Macros.h"

namespace FBDraw
{

	// Constructor
	Image::Image(int x, int y, int w, int h, color32_t* image, bool hasAlpha /* = true */)
	{
		m_location = Point(x, y);
		m_height = h;
		m_width = w;
		m_imageBuffer = image;
		m_bHasAlpha = hasAlpha;

		// Default is Visible
		Visible = true;
	}

	Image::Image(int x, int y, int w, int h, bool hasAlpha /* = true */)
	{
		m_location = Point(x, y);
		m_height = h;
		m_width = w;
		m_imageBuffer = new color32_t[w * h];
		m_bHasAlpha = hasAlpha;

		// Default is Visible
		Visible = true;
	}

	__attribute__((optimize("unroll-loops")))
	void Image::Render(color32_t* backBuffer, int width, int height)
	{
		if (m_imageBuffer == NULL)
			return;

		int iCanvasStart = ((m_location.Y) * width) + m_location.X;

		// Copy the image to the backbuffer
		if (m_bHasAlpha)
		{
			BGRA_Color mixBGRA = BGRA_Color{ 0x00, 0x00, 0x00, 0x00 };
			for (int iY = 0; iY < m_height; iY++)
			{
				int iCanvasRowStart = iCanvasStart + (iY * width);
				int iImageRowStart = (iY * m_width);
				for (int iX = 0; iX < m_width; iX++)
				{
					// Alpha mix the image pixel and the back buffer
					BGRA_Bytes imgColor, backColor, mixColor;
					imgColor.U32 = m_imageBuffer[iImageRowStart + iX];
					backColor.U32 = backBuffer[iImageRowStart + iX];
					mixColor.Color.Red = AlphaMix8(backColor.Color.Red, imgColor.Color.Red, imgColor.Color.Alpha);
					mixColor.Color.Green = AlphaMix8(backColor.Color.Green, imgColor.Color.Green, imgColor.Color.Alpha);
					mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, imgColor.Color.Blue, imgColor.Color.Alpha);

					backBuffer[iCanvasRowStart + iX] = mixColor.U32;
				}
			}
		}
		else
		{
			for (int iY = 0; iY < m_height; iY++)
			{
				uint32_t* pBackBuffer = &backBuffer[iCanvasStart + (iY * width)];
				uint32_t* pImgBuffer = &m_imageBuffer[(iY * m_width)];
				for (int iX = 0; iX < m_width; iX++, pBackBuffer++, pImgBuffer++)
				{
					*pBackBuffer = *pImgBuffer;
				}
			}
		}
	}

}
