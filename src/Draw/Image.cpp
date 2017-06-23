// Image.cpp
// Implementation file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#include "Image.h"
#include "Macros.h"


// Constructor
Image::Image(Point loc, int w, int h, color32_t* image)
{
	m_location = loc;
	m_height = h;
	m_width = w;
	m_imageBuffer = image;
}


void Image::Render(color32_t* backBuffer, int width, int height)
{
	BGRA_Color mixBGRA = BGRA_Color{ 0x00, 0x00, 0x00, 0x00 };

	if (m_imageBuffer == NULL)
		return;

	int iCanvasStart = ((m_location.Y) * width) + m_location.X;

	// Copy the image to the backbuffer
	for (int iY = 0; iY < m_height; iY++)
	{
		int iCanvasRowStart = iCanvasStart + (iY * width);
		int iImageRowStart = (iY * m_width);
		for (int iX = 0; iX < m_width; iX++)
		{
			BGRA_Color imgBGRA, backBGRA;
			imgBGRA = U32toBGRAColor(m_imageBuffer[iImageRowStart + iX]);
			backBGRA = U32toBGRAColor(backBuffer[iCanvasRowStart + iX]);

			mixBGRA.Red = AlphaMix8(backBGRA.Red, imgBGRA.Red, imgBGRA.Alpha);
			mixBGRA.Green = AlphaMix8(backBGRA.Green, imgBGRA.Green, imgBGRA.Alpha);
			mixBGRA.Blue = AlphaMix8(backBGRA.Blue, imgBGRA.Blue, imgBGRA.Alpha);

			backBuffer[iCanvasRowStart + iX] = BGRAColorToU32(mixBGRA);
			//backBuffer[iCanvasRowStart + iX] = m_imageBuffer[iImageRowStart + iX];
		}
	}
}