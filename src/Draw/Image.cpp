// Image.cpp
// Implementation file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#include "Image.h"
#include "Macros.h"


// Constructor
Image::Image(int w, int h, color32_t* image)
{
	i_height = h;
	i_width = w;
	i_imageBuffer = image;
	i_color = BGRA_Color{ 0xFF, 0xFF, 0xFF, 0x00 };

}

Image::Image(int w, int h, color32_t* image, BGRA_Color color) : Image(h, w, image)
{
	i_color = color;
}

void Image::Render(color32_t* backBuffer, int width, int height)
{
	if (i_imageBuffer == NULL)
		return;

	/*
	// create image buffer
	color32_t i_color32 = BGRAColorToU32(i_color);
	int numPx = i_width * i_height;
	for (int i = 0; i < numPx; i++)
	{
		i_imageBuffer[i] = i_color32;
	}
	*/

	//Drawing image
	color32_t i_RowStart;

	for (color32_t iY = 0; iY < i_height; iY++)
	{
		i_RowStart = (iY * i_width);

		//#pragma vector_for (4)
#pragma no_alias						// tells compiler that no loads or stores conflict
		for (color32_t iX = 0; iX < i_width; iX++)
		{
			//backBuffer[(iY * width) + iX] = BGRAColorToU32(r_Color);
			int color = i_imageBuffer[i_RowStart + iX];
			backBuffer[((iY) * width) + (i_imageBuffer[i_RowStart + iX])] = BGRAColorToU32(i_color);
		}
	}
}